#include "iostream" 
#include <opencv2/opencv.hpp>

using namespace std;

int main(void) {
	cv::Mat image = cv::imread("/home/caio/Imagens/a.png", 1);

	cv::namedWindow("Display image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display Image", image);

	cv::waitKey(0);

	return 0;
}

