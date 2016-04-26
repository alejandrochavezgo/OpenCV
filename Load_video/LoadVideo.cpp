//Libraries.
#include <opencv2\opencv.hpp>
#include <iostream>

//Main function.
int main(int argc, char** argv) 
{
	//Load the video.
	cv::VideoCapture cap("RPG_Afghanistan.avi");

	//If the video isn't open, terminate program. 
	if (!cap.isOpened())
	{
		std::cout << "[+] Error: Unable to open the video." << std::endl;
		system("PAUSE");
		return -1;
	}

	//Create new window.
	cv::namedWindow("Output", CV_WINDOW_AUTOSIZE);

	//Get frames per seconds.
	double fps = cap.get(CV_CAP_PROP_FPS);

	//Calculate the time between each frame to display.
	int delay = 1000 / (int)fps;

	for (;;)
	{
		//Input image.
		cv::Mat frame;

		//A frame is obtained and stored in "frame".
		cap >> frame;

        //If there are no more frames in the video, ends the program.
		if (frame.empty())
			break;

		//The frame is displayed.
		cv::imshow("Output", frame);
        
		//If key Esc is pressed, ends the program.
		if (cv::waitKey(delay) == 27)
			break;
	}

	//Freed memory space.
	cap.release();
	cv::destroyWindow("Output");
	
	return 0;
}