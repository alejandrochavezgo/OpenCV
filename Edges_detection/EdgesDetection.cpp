//Libraries.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

//Main function.
int main(int argc, char** argv)
{
	//Gray scale of the input image.
	cv::Mat imgGrayScale;

	//The grayscale image blurred.
	cv::Mat imgBlurred;

	//Image with only the edges.						
	cv::Mat imgCanny;

	//Open any webcam.
	cv::VideoCapture vc(CV_CAP_ANY);

	//If the webcam does not open, terminate program.
	if (!vc.isOpened())
	{
		std::cerr << "[-] Error: Unable to open the webcam.\n" << std::endl;
		std::cerr << "Press ENTER to exit..." << std::endl;
		std::cin.ignore();
		return EXIT_FAILURE;
	}

	//Input window.
	cv::namedWindow("Input", CV_WINDOW_AUTOSIZE);

	//Output window.				
	cv::namedWindow("Output", CV_WINDOW_AUTOSIZE);

	char checkKeyPressed = 0;

	std::cout << "Press ESC to exit..." << std::endl;

	while (checkKeyPressed != 27 && vc.isOpened())
	{
		//Input image.
		cv::Mat imgOriginal;

		//A frame is obtained and stored in imgOriginal.			
		vc >> imgOriginal;

		if (imgOriginal.empty()) 
		{
			cerr << "[-] Error: Unable to read the next frame.\n" << endl;
			cerr << "Press ENTER to exit." << endl;
			cin.ignore();
			break;
		}

		//The frame is displayed.								
		cv::imshow("Input", imgOriginal);

		//Convert the input image to gray scale.
		cv::cvtColor(imgOriginal, imgGrayScale, CV_BGR2GRAY);

		//Blur the image in gray scale.
		cv::GaussianBlur(imgGrayScale, imgBlurred, cv::Size(5, 5), 1.5);

		//Canny algorithm is used to detect the edges of the frame and stored in imgBlurred.
		cv::Canny(imgBlurred, imgCanny, 100, 100);

		//The frame is displayed.
		cv::imshow("Output", imgCanny);

		//If key Esc is pressed, ends the program.
		checkKeyPressed = cv::waitKey(1);
	}

	//Freed memory space.
	vc.release();
	cv::destroyAllWindows();

	return EXIT_SUCCESS;
}