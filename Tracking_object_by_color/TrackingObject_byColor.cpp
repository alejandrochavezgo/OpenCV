//Libraries.
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <Windows.h>

//Namespaces used.
using namespace cv;
using namespace std;

//Main function.
int  main(int argc, char** argv)
{
	//Open any webcam.
	VideoCapture webcam(CV_CAP_ANY);

	//If the webcam does not open, terminate program.
	if (!webcam.isOpened())
	{
		cerr << "[-] Error: Unable to open the webcam.\n" << endl;
		cerr << "Press ENTER to exit." << endl;
		cin.ignore();
		return EXIT_FAILURE;
	}

	//Set position of the console.
	HWND console = GetConsoleWindow();
	SetWindowPos(console, 0, 0, 470, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	//Create windows.
	namedWindow("Input", CV_WINDOW_NORMAL);
	namedWindow("Output", CV_WINDOW_NORMAL);
	namedWindow("Binary", CV_WINDOW_NORMAL);
	namedWindow("Adjust", CV_WINDOW_NORMAL);

	//Set position of the windows.
	moveWindow("Input", 800, 25);
	moveWindow("Output", 0, 25);
	moveWindow("Binary", 1100, 25);
	moveWindow("Adjust", 800, 250);

	//Resize windows.
	resizeWindow("Input", 200, 150);
	resizeWindow("Binary", 200, 150);
	resizeWindow("Adjust", 500, 500);

	int minH = 0;
	int maxH = 255;

	int minS = 0;
	int maxS = 255;

	int minV = 0;
	int maxV = 255;

	//Create trackbars to modify variables and find the desired color.
	cvCreateTrackbar("Min-H", "Adjust", &minH, 255);				
	cvCreateTrackbar("Max-H", "Adjust", &maxH, 255);

	cvCreateTrackbar("Min-S", "Adjust", &minS, 255);		
	cvCreateTrackbar("Max-S", "Adjust", &maxS, 255);

	cvCreateTrackbar("Min-V", "Adjust", &minV, 255);			
	cvCreateTrackbar("Max-V", "Adjust", &maxV, 255);

	char checkKeyPressed = 0;

	cout << "Press ESC to exit..." << endl;

	while (checkKeyPressed != 27 && webcam.isOpened())
	{
		//Get a frame of the webcam.
		Mat frm_original;
		webcam >> frm_original;

		if (frm_original.empty()) 
		{
			cerr << "[-] Error: Unable to read the next frame.\n" << endl;
			cerr << "Press ENTER to exit." << endl;
			cin.ignore();
			break;
		}

		imshow("Input", frm_original);

		//Convert frame from RGB to HSV.
		Mat frm_hsv, frm_binary;
		cvtColor(frm_original, frm_hsv, CV_BGR2HSV);

		//Apply desired color filter.
		inRange(frm_hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), frm_binary);

		//Apply Morphological transformations. (extracted region of interest)
		Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
		erode(frm_binary, frm_binary, element);
		dilate(frm_binary, frm_binary, element);

		imshow("Binary", frm_binary);

		//Search contours in the binary image.
		vector< vector<Point> > contours;
		findContours(frm_binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		//Draw all the contours found in the binary image.
		//drawContours(frm_binary, contours, -1, Scalar(255), CV_FILLED);

		//Draw rectangle and text in coordinates (x, y)
		for (vector<Point> contour : contours)
		{
			Rect r = boundingRect(contour);
			rectangle(frm_original, r.tl(), r.br(), Scalar(0, 255, 0), 1, CV_AA, 0);

			Point pt_center(r.x + (r.width / 2), r.y + (r.height / 2));

			ostringstream coordinates;
			coordinates << pt_center.x << "," << pt_center.y;

			//cout << "Point: " << pt_center.str() << endl;
			putText(frm_original, coordinates.str(), pt_center, FONT_HERSHEY_COMPLEX_SMALL, 0.50, CV_RGB(0, 255, 0), 1, CV_AA);
		}

		imshow("Output", frm_original);

		checkKeyPressed = waitKey(1);
	}

	webcam.release();
	destroyAllWindows();

	return EXIT_SUCCESS;
}