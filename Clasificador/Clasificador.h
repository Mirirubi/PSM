#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Clasificador.h"

#include "opencv2/world.hpp"

#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <QtImageManager.h>
#include <iostream>
#include <QTimer>
//#include <BlobResult.h>

#include <sstream>
#include <stdio.h>
#include <opencv2\video\background_segm.hpp>

using namespace std;
using namespace cv;

class CClasificador : public QMainWindow
{
	Q_OBJECT

public:
	CClasificador(QWidget *parent = Q_NULLPTR);
	~CClasificador();


private slots :

	void entrena(void);

	void verImag(void);
	void StartStop(void);
	void verVideo(void);
	void guardaImag(void);
	void procesado(Mat img);
	
	Mat clasificacionFS(Mat img_in); // Modificaciones imagen
	int computeOutput(int x, int r1, int s1, int r2, int s2);
	void leyenda(void);

private:
	Ui::CClasificadorClass m_ui;
	cv::Mat img;



	bool ss;
	cv::Mat imgV;	//captura video
	cv::Mat img_proces;
	cv::VideoCapture capture;
	int n;
	string nn;

	cv::Mat bgr[3];

	cv::Mat frame, edges;
	int cannyUmbral;

	//
	int cutreza = 0;

	Mat img_clasif;
	Mat imgV2;

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<Mat> img_mask;

	Scalar colorAvellana = Scalar(0, 255, 0);//color verde
	Scalar colorAlmendra = Scalar(255, 0, 255);//color fucsia
	Scalar colorCastana = Scalar(0, 255, 255);//color amarillo
	Scalar colorNuez = Scalar(255, 255, 0);//color  azul claro
	Scalar colorPistacho = Scalar(255, 0, 0);//color azul
	Mat img_leyenda;
	const Mat responses;
	const Mat sampleIdx = Mat();
	bool isRegression = false;
	int maxK = 32;
	bool updateBase = false;

	Mat mediac = Mat::zeros(1, 100, CV_32F);
	Ptr<ml::SVM> clasificador;// = ml::SVM::create();

	Mat min = Mat::zeros(1, 100, CV_32F);
	Mat max = Mat::zeros(1, 100, CV_32F);
};
