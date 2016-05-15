//Libraries.
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgcodecs\imgcodecs.hpp>
#include <iostream>

//Main function.
int main(int argc, char** argv)
{
	//Loading an image.
	cv::Mat image = cv::imread("nebula.JPG");

	//If the images is empty, terminate program.
	if (image.empty())
	{
		std::cerr << "[-] Error: Unable to load image.\n" << std::endl;
		std::cerr << "Press ENTER to exit..." << std::endl;
		std::cin.ignore();
		return EXIT_FAILURE;
	}

	//Display the image.
	cv::imshow("Output", image);
	std::cout << "Press any key to exit..." << std::endl;
	cv::waitKey(0);

	//Freed memory space.
	image.release();
	cv::destroyWindow("Output");

	return EXIT_SUCCESS;
}