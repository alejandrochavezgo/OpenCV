#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

int  main(int argc, char** argv) 
{
	cv::VideoCapture vc(CV_CAP_ANY);
	
	if (!vc.isOpened())
		return -1;

	cv::namedWindow("Input", CV_WINDOW_NORMAL);
	cv::namedWindow("Output", CV_WINDOW_NORMAL);
	cv::namedWindow("Binary", CV_WINDOW_NORMAL);
	cv::namedWindow("Adjust", CV_WINDOW_NORMAL);

	cv::resizeWindow("Input", 200, 150);
	cv::resizeWindow("Binary", 200, 150);
	cv::resizeWindow("Output", 550, 400);
	cv::resizeWindow("Adjust", 500, 200);

	int iLowH = 0;
	int iHighH = 79;

	int iLowS = 0;
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	cvCreateTrackbar("Low - Hue", "Adjust", &iLowH, 255);				//Hue (0 - 79)
	cvCreateTrackbar("High - Hue", "Adjust", &iHighH, 255);

	cvCreateTrackbar("Low - Saturation", "Adjust", &iLowS, 255);		//Saturation (0 - 255)
	cvCreateTrackbar("High - Saturation", "Adjust", &iHighS, 255);

	cvCreateTrackbar("Low - Value", "Adjust", &iLowV, 255);				//Value (0 - 255)
	cvCreateTrackbar("High - Value", "Adjust", &iHighV, 255);

	while (1) 
	{	
		cv::Mat frmOriginal;
		vc >> frmOriginal;

		cv::imshow("Input", frmOriginal);

		cv::Mat hsv, binary;
		//Convertir imagen RGB a HSV 
		cv::cvtColor(frmOriginal, hsv, CV_BGR2HSV);

		//Aplicar filtro para color deseado
		cv::inRange(hsv, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), binary);

		//Aplicar tranformaciones morfologicas (se extrae la región de interes)
		cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
		cv::erode(binary, binary, element);
		cv::dilate(binary, binary, element);

		cv::imshow("Binary", binary);

		//Buscar contornos en la imagen binaria
		std::vector< std::vector<cv::Point> > contours;
		findContours(binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		//Dibujar todos los contornos encontrados
		drawContours(binary, contours, -1, cv::Scalar(255), CV_FILLED);

		//Dibujar rectangulo y texto con coordenadas (x, y)
		for (std::vector<cv::Point> contour : contours) 
		{
			cv::Rect r = boundingRect(contour);
			cv::rectangle(frmOriginal, r.tl(), r.br(), CV_RGB(255, 0, 0), 2, CV_AA, 0);

			cv::Point center(r.x + (r.width / 2), r.y + (r.height / 2));

			std::ostringstream points;
			points << center.x << "," << center.y;

			std::cout << "Point: " << points.str() << std::endl;
			putText(frmOriginal, points.str(), center, cv::FONT_HERSHEY_COMPLEX_SMALL, 0.60, CV_RGB(0, 255, 0), 1, CV_AA);
		}

		cv::imshow("Output", frmOriginal);

		if (cv::waitKey(10) == 27)
			break;
	}

	vc.release();
	cv::destroyAllWindows();

	return 0;
}