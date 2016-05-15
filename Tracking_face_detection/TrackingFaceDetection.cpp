//Libraries.
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <iostream>

//Main function.
int main(int argc, char** argv)
{
	//If the cascade classifier does not load, terminate program.
	cv::CascadeClassifier haarcascade_frontalface;
	if (!haarcascade_frontalface.load("C:\\OpenCV-3.1.0\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml"))
	{
		std::cerr << "[-] Error: Unable to load the cascade classifier file.\n" << std::endl;
		std::cerr << "Press ENTER to exit..." << std::endl;
		std::cin.ignore();
		return EXIT_FAILURE;
	}

	//Open any webcam.
	cv::VideoCapture webcam(CV_CAP_ANY);

	//If the webcam does not open, terminate program.
	if (!webcam.isOpened())
	{
		std::cerr << "[-] Error: Unable to open the webcam." << std::endl;
		std::cerr << "Press ENTER to exit..." << std::endl;
		std::cin.ignore();
		return EXIT_FAILURE;
	}

	cv::namedWindow("WebCam", CV_WINDOW_AUTOSIZE);

	//Vector for faces found.
	std::vector<cv::Rect> faces;

	char checkKeyPressed = 0;

	std::cout << "Press ESC to exit..." << std::endl;

	while (checkKeyPressed != 27 && webcam.isOpened())
	{
		//Get a frame of the webcam.
		cv::Mat frmOriginal;
		webcam >> frmOriginal;

		if (frm_original.empty()) 
		{
			cerr << "[-] Error: Unable to read the next frame.\n" << endl;
			cerr << "Press ENTER to exit." << endl;
			cin.ignore();
			break;
		}

		//Convert frame from RGB to grayscale.
		cv::Mat frmGrayscale;
		cv::cvtColor(frmOriginal, frmGrayscale, CV_BGR2GRAY);

		//Apply histogram equalization image gray to standardize the contrast and brightness of the image,
		//this so different lighting conditions do not affect the detection of the face in the image.
		cv::equalizeHist(frmGrayscale, frmGrayscale);

		//Detect the faces founds.
		haarcascade_frontalface.detectMultiScale(frmGrayscale, faces, 1.2, 3, 0, cv::Size(60, 60));

		//Loop for draw a figure around of the faces founds.
		for (int i = 0; i < (int)faces.size(); i++)
		{
			//Create a new object Rectangle for the face found.
			cv::Rect r = faces[i];

			/*
			int radius = r.width / 2;
			int x = r.x + (r.width / 2);
			int y = r.y + (r.height / 2);
			//Draw a circle around of the face found.
			cv::circle(frmOriginal, cv::Point(x , y), radius, cv::Scalar(0, 255, 0), 1, CV_AA, 0);
			*/

			//Draw a rectangle around of the face found in the original frame.
			cv::rectangle(frmOriginal, cv::Point(r.x, r.y), cv::Point(r.x + r.width, r.y + r.height), cv::Scalar(0, 255, 0), 1, CV_AA, 0);

			std::cout << "Point: " << r.x << ", " << r.y << std::endl;
		}

		//Display the original frame.
		cv::imshow("WebCam", frmOriginal);

		checkKeyPressed = cv::waitKey(1);
	}

	//Freed memory space.
	faces.clear();
	webcam.release();
	cv::destroyAllWindows();

	return EXIT_SUCCESS;
}