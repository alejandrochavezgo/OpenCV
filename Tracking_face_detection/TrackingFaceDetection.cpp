//Libraries.
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

//Main function.
int main(int argc, char** argv) 
{	
	//If the cascade classifier does not load, terminate program.
	cv::CascadeClassifier haarcascade_frontalface;																				
	if (!haarcascade_frontalface.load("C:\\OpenCV-3.1.0\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml"))	
	{
		std::cout << "[+] Error: Unable to load cascade classifier file." << std::endl;
		system("PAUSE");
		return -1;
	}

	//Open any webcam.
	cv::VideoCapture webcam(CV_CAP_ANY);																							

	//If the webcam does not open, terminate program.
	if (!webcam.isOpened())																											
	{
		std::cout << "[+] Error: Unable to open the webcam." << std::endl;
		system("PAUSE");
		return -1;
	}
	
	cv::namedWindow("WebCam", CV_WINDOW_AUTOSIZE);
	
	//Vector for faces found.
	std::vector<cv::Rect> faces;																									

	while (1)
	{
		//Get a frame of the webcam.
		cv::Mat frmOriginal;
		webcam >> frmOriginal;

		//Convert frame to grayscale.
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

		if (cv::waitKey(1) == 27)
			break;
	}

	//Freed memory space.
	faces.clear();
	webcam.release();
	cv::destroyAllWindows();

	return 0;
}