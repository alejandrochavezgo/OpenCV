//Libraries.
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\objdetect\objdetect.hpp>
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
		return false;
	}

	//Load the image to be processed, if not load, terminate program.
	cv::Mat imgOriginal = cv::imread("astronauts_class_of_1998.JPG");
	if (imgOriginal.empty())
	{
		std::cout << "[+] Error: Unable to load the image." << std::endl;
		system("PAUSE");
		return -1;
	}

	cv::namedWindow("Input", CV_WINDOW_AUTOSIZE);
	cv::namedWindow("Output", CV_WINDOW_AUTOSIZE);
	cv::imshow("Input", imgOriginal);

	//Convert to grayscale the original image. 
	cv::Mat imgGrayscale;
	cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);

	//Apply histogram equalization image gray to standardize the contrast and brightness of the image,
	//this so different lighting conditions do not affect the detection of the face in the image.
	cv::equalizeHist(imgGrayscale, imgGrayscale);

	//Vector for faces found.
	std::vector<cv::Rect> faces;

	//Detect the faces founds.
	haarcascade_frontalface.detectMultiScale(imgGrayscale, faces, 1.2, 3);

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
		cv::circle(imgOriginal, cv::Point(x , y), radius, cv::Scalar(0, 255, 0), 1, CV_AA, 0);
		*/

		//Draw a rectangle around of the face found in the original frame.
		cv::rectangle(imgOriginal, cv::Point(r.x, r.y), cv::Point(r.x + r.width, r.y + r.height), cv::Scalar(0, 255, 0), 1, CV_AA, 0);

		std::cout << "Point: " << r.x << ", " << r.y << std::endl;
	}

	//Display the original frame.
	cv::imshow("Output", imgOriginal);
	cv::waitKey(0);

	//Freed memory space.
	faces.clear();
	imgOriginal.release();
	imgGrayscale.release();
	cv::destroyAllWindows();

	return 0;
}