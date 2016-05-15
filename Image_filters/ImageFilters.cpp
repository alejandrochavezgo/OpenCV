//Library.
#include <opencv2\opencv.hpp>

//Main function.
int main(int argc, char ** argv)
{
	//Input image.
	cv::Mat imgInput = cv::imread("astronaut.jpg", CV_LOAD_IMAGE_UNCHANGED);  
	
	//Output images.
	cv::Mat imgOutput, img;							  

	//If unable to open image, show error message and exit program.
	if (imgInput.empty())							  
	{
		std::cerr << "[-] Error: Unable to load image.\n" << std::endl;
		std::cerr << "Press ENTER to exit..." << std::endl;
		std::cin.ignore();
		return EXIT_FAILURE;
	}
	
	//New window.
	cv::namedWindow("GaussianBlur", CV_WINDOW_NORMAL);		
	
	//Adjusting size of the new window.	  
	cv::resizeWindow("GaussianBlur", 250, 200);				  
	
	//Adjusting the location of the new window.
	cv::moveWindow("GaussianBlur", 0, 0);		
	
	//Algorithm GaussianBlur accept the image original, matrix where the new image will be stored, 
	//size of kernel (positive and odd) and standard deviation on the X axis.
	cv::GaussianBlur(imgInput, imgOutput, cv::Size(11, 7), 1.5);		  
										  
	//Show the image processed.
	cv::imshow("GaussianBlur", imgOutput);					  

	cv::namedWindow("MedianBlur", CV_WINDOW_NORMAL);
	cv::resizeWindow("MedianBlur", 250, 200);
	cv::moveWindow("MedianBlur", 270, 0);
	
	//Algorithm MedianBlur accept the image original, matrix where the new image will be stored and 
	//kernel size (positive and odd).
	cv::medianBlur(imgInput, imgOutput, 5);					 
						  
	cv::imshow("MedianBlur", imgOutput);

	cv::namedWindow("Erode", CV_WINDOW_NORMAL);
	cv::resizeWindow("Erode", 250, 200);
	cv::moveWindow("Erode", 540, 0);
	
	//The morphological operation Erode accept the image original, matrix where the new image will be 
	//stored and the structuring element used for erosion.
	cv::erode(imgInput, imgOutput, img);				
		  
	cv::imshow("Erode", imgOutput);

	cv::namedWindow("Dilate", CV_WINDOW_NORMAL);
	cv::resizeWindow("Dilate", 250, 200);
	cv::moveWindow("Dilate", 810, 0);
	
	//The morphological operation Dilate accept the image original, matrix where the new image will be
	//stored and the structuring element used for erosion.
	cv::dilate(imgInput, imgOutput, img);	
					  
	cv::imshow("Dilate", imgOutput);

	cv::namedWindow("Invert", CV_WINDOW_NORMAL);
	cv::resizeWindow("Invert", 250, 200);
	cv::moveWindow("Invert", 1080, 0);
	
	//The method bitwise_not accept the image input, the image output that has the same size and type
	//as the input array.
	cv::bitwise_not(imgInput, imgOutput);					  
	
	cv::imshow("Invert", imgOutput);

	cv::namedWindow("GrayScale", CV_WINDOW_NORMAL);
	cv::resizeWindow("GrayScale", 250, 200);
	cv::moveWindow("GrayScale", 0, 260);
	
	//This method converts an image from one color space to another. Accept the image original, matrix 
	//where the new image will be stored and the color space conversion code.
	cv::cvtColor(imgInput, imgOutput, CV_RGB2GRAY);				  
	
	cv::imshow("GrayScale", imgOutput);

	cv::namedWindow("Canny", CV_WINDOW_NORMAL);
	cv::resizeWindow("Canny", 250, 200);
	cv::moveWindow("Canny", 270, 260);
	
	//This method finds edges in an image using the Canny86 algorithm. Accept the image original, matrix 
	//where the new image will be stored, the low threshold and the high threshold.
	cv::Canny(imgInput, imgOutput, 0, 30);		
				  
	cv::imshow("Canny", imgOutput);

	cv::namedWindow("Original", CV_WINDOW_NORMAL);
	cv::resizeWindow("Original", 400, 300);
	cv::moveWindow("Original", 540, 260);
	
	//Show original image.
	cv::imshow("Original", imgInput);

	//Wait until any key is pressed.
	std::cerr << "Press any key to exit..." << std::endl;
	cv::waitKey(0);

	//Freeing up memory.
	cv::destroyAllWindows();
	img.release();								  
	imgInput.release();							  
	imgOutput.release();							  

	return EXIT_SUCCESS;
}