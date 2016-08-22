#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <string>
#include <cv.h>
#include <highgui.h>

using namespace cv;

int main(int argc, char** argv) {

	Mat imagem_BGR, imagem_HSV, imagem_ColorMap;

	imagem_BGR = imread(argv[1]);
	if (!imagem_BGR.data) {
		std::cout << "Erro ao carregar a Imagem!\n";
		return (-1);
	}

	namedWindow("Imagem Original", WINDOW_NORMAL);
	imshow("Imagem Original", imagem_BGR);

	cvtColor(imagem_BGR, imagem_HSV, COLOR_BGR2HSV);

	namedWindow("Imagem HSV", WINDOW_NORMAL);
	imshow("Imagem HSV", imagem_HSV);

	Mat numerador = Mat::ones(imagem_BGR.rows, imagem_BGR.cols, CV_32FC1);
	Mat denominador = Mat::ones(imagem_BGR.rows, imagem_BGR.cols, CV_32FC1);
	Mat imagem_NDVI = Mat::ones(imagem_BGR.rows, imagem_BGR.cols, CV_32FC1);
	Mat imagem_MAPHSV = Mat::ones(imagem_BGR.rows, imagem_BGR.cols, CV_8UC1);
	std::vector<Mat> channels;

	split(imagem_BGR, channels);

	subtract(channels[2], channels[1], numerador);
	add(channels[2], channels[1], denominador);
	divide(denominador, numerador, imagem_NDVI);

	normalize(imagem_NDVI, imagem_NDVI, 0, 180, NORM_MINMAX, CV_8UC1);

	std::vector<Mat> channel;

	split(imagem_HSV, channel);

	std::vector<Mat> newChannels;
	newChannels.push_back(imagem_NDVI);
	newChannels.push_back(channel[1]);
	newChannels.push_back(channel[2]);
	merge(newChannels, imagem_MAPHSV);

	namedWindow("Imagem NDVI", WINDOW_NORMAL);
	imshow("Imagem NDVI", imagem_NDVI);

	namedWindow("Mapa de cores HSV", WINDOW_NORMAL);
	imshow("Mapa de cores HSV", imagem_MAPHSV);

	waitKey(0);
	return 0;
}
