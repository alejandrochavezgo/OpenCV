//Libraries.
#include <opencv2\core\core.hpp>
#include <opencv2\imgcodecs\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

//Main function.
int main(int argc, char** argv) 
{
	//Loading an image.
	cv::Mat image = cv::imread("nebula.JPG");

	//If the images is empty, terminate program.
	if (image.empty()) 
	{
		std::cout << "[+] Error: Unable to load image." << std::endl;
		system("PAUSE");
		return -1;
	}

	//Display the image.
	cv::imshow("Output", image);
	cv::waitKey(0);

	//Freed memory space.
	image.release();
	cv::destroyWindow("Output");

	return 0;
}