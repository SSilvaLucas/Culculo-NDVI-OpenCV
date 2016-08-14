#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <string>
#include <cv.h>
#include <highgui.h>


using namespace cv;

float ndvi_calculo(float nir, float vermelho){
	float ndvi = ((nir - vermelho) / (nir + vermelho));
	return floor((ndvi + 1) * 127.999);
}


int main(int argc, char** argv) {

	Mat	imagem, imagem_hsv;

	imagem = imread(argv[1]);
	if(!imagem.data){
		std::cout << "Erro ao carregar a Imagem!\n";
		return(-1);
	}

	Mat imagem_rgb_ndvi = imagem.clone();

	namedWindow("imagem", CV_WINDOW_AUTOSIZE);
	imshow("imagem", imagem);

	//imagem.convertTo(imagem_float, CV_32FC3);
	int width = imagem.size().width;
	int height = imagem.size().height;

	for(int x=0; x < width; x++){
		for(int y=0; y < height; y++){
			Vec3f c1 = imagem.at<Vec3f>(x, y);
			float b = c1.val[0];
			float r = c1.val[2];
			float ndvi = ndvi_calculo(b,r);
			//std::cout << ndvi << " ";
			//imagem_rgb_ndvi.at<uchar>(x, y)[0] = ndvi;
			//c1.val[0] = ndvi;
			//imagem_rgb.at<Vec3f>(x, y) = c1;
		}
	}

	imwrite("teste.tiff", imagem_rgb_ndvi);

	//namedWindow("imagem rgb + ndvi", CV_WINDOW_AUTOSIZE);
	//imshow("Imagem rgb + ndvi", imagem);

	//cvtColor(imagem_rgb, imagem_hsv, CV_BGR2HSV);

	//namedWindow("imagem HSV", CV_WINDOW_AUTOSIZE);
	//imshow("imagem HSV", imagem_hsv);

	/*int width = imagem.size().width;
	int height = imagem.size().height;

	for(int x=0; x < width; x++){
		for(int y=0; y < height; y++){
			//imagem_hsv_ndvi.at<Vec3b>(x, y) = imagem_hsv.at<Vec3b>(x, y);
			//float nir  = imagem_hsv.at<Vec3b>(x,y)[0];
			//float vermelho = imagem_hsv.at<Vec3b>(x,y)[2];
			//imagem_hsv_ndvi.at<Vec3b>(x, y)[2] = 0;
			//imagem_hsv_ndvi.at<Vec3b>(x, y)[0] = ndvi2hsv(nir, vermelho);
			Vec3f c1 = imagem.at<cv::Vec3f>(x, y);
			float r = c1.val[0];
			float g = c1.val[1];
			float b = c1.val[2];
			float ndvi = ndvi2hsv(b,r);

			std::cout << ndvi << " ";
			//std::cout << v << " ";
		}
	}*/

	//namedWindow("imagem HSV + NDVI", CV_WINDOW_AUTOSIZE);
	//imshow("imagem HSV + NDVI", imagem_hsv_ndvi);

	waitKey();
	//destroyWindow("imagem");
	//destroyWindow("imagem HSV");
	//destroyWindow("imagem HSV + NDVI");
	return 0;
}
//cvtColor(imagem, gray_ndvi, CV_BGR2GRAY);
