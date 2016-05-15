//Libraries.
#include <opencv2\opencv.hpp>
#include <iostream>

//Main function.
int main(int argc, char** argv)
{
	//Load the video.
	cv::VideoCapture vc("RPG_Afghanistan.avi");

	//If the video isn't open, terminate program. 
	if (!vc.isOpened())
	{
		std::cerr << "[-] Error: Unable to load video.\n" << std::endl;
		std::cerr << "Press ENTER to exit..." << std::endl;
		std::cin.ignore();
		return EXIT_FAILURE;
	}

	//Create new window.
	cv::namedWindow("Output", CV_WINDOW_AUTOSIZE);

	//Get frames per seconds.
	double fps = vc.get(CV_CAP_PROP_FPS);

	//Calculate the time between each frame to display.
	int delay = 1000 / (int)fps;

	std::cout << "Press ESC to exit..." << std::endl;

	for (;;)
	{
		//Input image.
		cv::Mat frame;

		//A frame is obtained and stored in "frame".
		vc >> frame;

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
	vc.release();
	cv::destroyWindow("Output");

	return EXIT_SUCCESS;
}