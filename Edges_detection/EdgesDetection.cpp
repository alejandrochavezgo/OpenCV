//Libraries.
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
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
	
	//Initialize the webcam.
	cv::VideoCapture vc(CV_CAP_ANY);										
	
	//If the webcam unable to open, ends the program.
	if (!vc.isOpened())														
	{
		std::cout << "Error: Unable to open the webcam.\n\n";
		system("PAUSE");
		return -1;
	}

	//Input window.
	cv::namedWindow("Input", CV_WINDOW_AUTOSIZE);			
	
	//Output window.				
	cv::namedWindow("Output", CV_WINDOW_AUTOSIZE);							

	for (;;)															
	{
		//Input image.
		cv::Mat imgOriginal;									
		
		//A frame is obtained and stored in imgOriginal.			
		vc >> imgOriginal;					
		
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
		if (cv::waitKey(5) == 27)											
			break;
	}
	
	//Freed memory space.
	vc.release();															
	cv::destroyAllWindows();												

	return 0;
}