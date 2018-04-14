#include "Clasificador.h"

CClasificador::CClasificador(QWidget *parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);

	/*cv::Mat a(100, 200, CV_8U);
	a.setTo(255);
	m_ui.widgetImg->setVisualicedImage(a);*/

	ss = false;
	connect(m_ui.ssButton_2, SIGNAL(clicked(bool)), this, SLOT(verImag())); // para mostrar la leyenda cuando aparezca el video
	connect(m_ui.ssButton, SIGNAL(clicked(bool)), this, SLOT(StartStop()));
	capture.open(1);	// 0 para la camara por defecto, 1 para la secundaria etc 

	capture >> imgV;	// Captura del video
						//procesado(imgV);
	verVideo();



	img_leyenda = imread("leyenda.jpg");
	leyenda();

}

CClasificador::~CClasificador() 
{
}

void CClasificador::entrena(void) {

	Mat etiquetas = Mat::zeros(100, 1, CV_32S); //Mat mask = Mat::zeros(img_in.size(), CV_8UC3);
	Mat  hist_entrena = Mat::zeros(100, 100, CV_32F); //Mat mask = Mat::zeros(img_in.size(), CV_8UC3);
	string ident;
	int nf = 1;
	Mat hsv_ent;
	for (int i = 0; i < 100; i++) {
		if (i < 20) {
			ident = "almendra(";
			etiquetas.at<int>(i, 0) = 1;
		}
		else if (i < 40) {
			ident = "avellana(";
			etiquetas.at<int>(i, 0) = 2;
		}
		else if (i<60) {
			ident = "castana(";
			etiquetas.at<int>(i, 0) = 3;
		}
		else if (i<80) {
			ident = "nuez(";
			etiquetas.at<int>(i, 0) = 4;
		}
		else if (i<100) {
			ident = "pistacho(";
			etiquetas.at<int>(i, 0) = 5;
		}


		string nfoto = to_string(nf);
		string name1 = "Entrena/Nuevas/" + ident;
		string name2 = name1 + nfoto;

		Mat img_ent = imread(name2 + ").jpg"); // imagen para entrenar

		cvtColor(img_ent, hsv_ent, CV_RGB2HSV);

		int s_bins = 10;
		int v_bins = 10;
		int size = hsv_ent.rows*hsv_ent.cols;
		int histSize[] = { s_bins, v_bins };

		//float h_ranges[] = { 0, 179 };
		float s_ranges[] = { 0, 255 };
		float v_ranges[] = { 0, 255 };

		const float* ranges[] = { s_ranges, v_ranges };
		//int channels[] = { 0, 1, 2 };

		int channels[] = { 1,2 };
		//calcHist(img_hsv, 1, channels, Mat(), hist, );
		MatND hist_base;
		calcHist(&hsv_ent, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);

		//normalize(hist_base, hist_base);

		for (int y = 0; y < 10; y++) {		// pasar matriz 10*10 de histograma a vector
			for (int x = 0; x < 10; x++) {
				hist_entrena.at<float>(i, x + (y * 10)) = hist_base.at<float>(y, x) / size;
			}
			hist_entrena.at<float>(i, 99) = size;
		}

		if (nf == 20) {
			nf = 0;
		}
		nf++;
	}

	//	NORMALIZACIóN:

	/*		for (int c = 0; c < 100; c++) {
	float minxx = 100000;
	float maxxx = 0;
	for (int f = 0; f < 100; f++) {
	if (minxx > hist_entrena.at<float>(f, c)) {
	minxx = hist_entrena.at<float>(f, c);
	}
	if (maxxx < hist_entrena.at<float>(f, c)) {
	maxxx = hist_entrena.at<float>(f, c);
	}
	}
	min.at<float>(0, c) = minxx;
	max.at<float>(0, c) = maxxx;
	}*/
	for (int c = 0; c < 100; c++) {
		float minxx = hist_entrena.at<float>(0, c);
		float maxxx = hist_entrena.at<float>(0, c);
		for (int f = 0; f < 100; f++) {
			if (minxx > hist_entrena.at<float>(f, c)) {
				minxx = hist_entrena.at<float>(f, c);
			}
			if (maxxx < hist_entrena.at<float>(f, c)) {
				maxxx = hist_entrena.at<float>(f, c);
			}
			min.at<float>(0, c) = minxx;
			max.at<float>(0, c) = maxxx;
		}

	}

	Mat hist_entrenaNORMA = Mat::zeros(100, 100, CV_32F);
	Mat lol = Mat::zeros(1, 100, CV_32F);
	for (int c = 0; c < 100; c++) {		// Suma todas las columnas	
		for (int f = 0; f < 100; f++) {
			hist_entrenaNORMA.at<float>(f, c) = hist_entrena.at<float>(f, c) - min.at<float>(0, c);
			lol.at<float>(0, c) = max.at<float>(0, c) - min.at<float>(0, c);
			hist_entrenaNORMA.at<float>(f, c) = hist_entrenaNORMA.at<float>(f, c) / lol.at<float>(0, c);

		}
	}



	// ESTANDARIZACION
	Mat sumac = Mat::zeros(1, 100, CV_32F);
	for (int c = 0; c < 100; c++) {		// Suma todas las columnas
		for (int f = 0; f < 100; f++) {
			sumac.at<float>(0, c) = sumac.at<float>(0, c) + hist_entrena.at<float>(f, c);
		}
	}
	//Mat mediac = Mat::zeros(1, 100, CV_32F);
	for (int c = 0; c < 100; c++) {		// Calcula la media de cada columna
		mediac.at<float>(0, c) = sumac.at<float>(0, c) / 100;
	}
	Mat desviaStndc = Mat::zeros(1, 100, CV_32F);
	Mat pasoSuma = Mat::zeros(1, 100, CV_32F);
	Mat pasods = Mat::zeros(1, 100, CV_32F);
	Mat pasoDesv = Mat::zeros(100, 100, CV_32F);
	for (int c = 0; c < 100; c++) {		// Calcula desviación estandar
		for (int f = 0; f < 100; f++) {		// Calcula el previo a la multiplicacion y la raiz
			pasoDesv.at<float>(f, c) = pow((hist_entrena.at<float>(f, c) - mediac.at<float>(0, c)), 2); // elevar al cuadrado 
			pasoSuma.at<float>(0, c) = pasoSuma.at<float>(0, c) + pasoDesv.at<float>(0, c);
		}
		pasods.at<float>(0, c) = pasoSuma.at<float>(0, c) / 99;
		desviaStndc.at<float>(0, c) = sqrt(pasods.at<float>(0, c));
	}
	Mat hist_stand = Mat::zeros(100, 100, CV_32F);
	for (int c = 0; c < 100; c++) {		// CALCULA MATRIZ ESTANDARIZADA !!!! 
		for (int f = 0; f < 100; f++) {
			if (desviaStndc.at<float>(0, c) != 0) {
				hist_stand.at<float>(f, c) = (hist_entrena.at<float>(f, c) - mediac.at<float>(0, c)) / desviaStndc.at<float>(0, c);
			}
		}
	}
	/*	float *d = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5 ,5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
	Mat etiquetas (100, 1, CV_32F, d) ;*/



	//bool entramosCvKNearest::train(const Mat& trainData, const Mat& responses, const Mat& sampleIdx = Mat(), bool isRegression = false, int maxK = 32, bool updateBase = false)
	//bool train(&hist_entrena, &responses, &sampleIdx, isRegression, 32, bool updateBase = false);

	Ptr<ml::SVM> clasificado = ml::SVM::create();
	clasificado->setType(ml::SVM::C_SVC);
	clasificado->setKernel(ml::SVM::LINEAR);
	//clasificador->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));

	//clasificador->train(hist_stand, ml::ROW_SAMPLE, etiquetas);6+
	//clasificador->train(hist_entrena, ml::ROW_SAMPLE, etiquetas); 
	Mat etT = etiquetas;// .rowRange(0, 99);
	Mat datos = hist_entrenaNORMA;// .rowRange(0, 99);
	cv::Ptr<ml::TrainData> td = ml::TrainData::create(datos, cv::ml::ROW_SAMPLE, etT);
	//clasificador->train(hist_entrenaNORMA, ml::ROW_SAMPLE, etiquetas.t());
	clasificado->train(td);
	//clasificador->predict(testdata, output);
	//clasificador->save("modelo_entrena_SVM.xml");



}

// FUNCIONES DE PROCESADO
void CClasificador::procesado(Mat img) {
	capture >> img;
	Mat img_blur;
	Mat img_clasif = img.clone();
	Mat img_in = clasificacionFS(img_clasif);

	findContours(img_in, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Mat> contour_rois;
	int indice = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		Mat mask = Mat::zeros(img_in.size(), CV_8UC3);
		Scalar color = Scalar(1, 1, 1); // color azul
		drawContours(mask, contours, i, color, CV_FILLED); // coge cada contorno uno a uno y lo mete en contours

		Mat img_seg = mask.mul(img);	// multiplicación de las dos matrices elemento a elemento

		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true); // aproximación de forma
		boundRect[i] = boundingRect(Mat(contours_poly[i]));	// corta rectangulo

		Mat roi(img_seg, boundRect[i]);	// crea una matriz de la imagen segmentada aplicandole la máscara

		Size s = roi.size();
		int rows = s.height;
		int cols = s.width;
		int result = rows * cols;
		Mat img_hsv;
		Mat hist;

		if (result > 500) {
			contour_rois.push_back(roi); // guardamos todos los valores de las rois
										 //namedWindow("prueba", CV_WINDOW_AUTOSIZE);
										 //imshow("prueba" + i, roi); // +i para que represente en dierentes ventanas

			string valor = to_string(indice);
			string filen = "Entrena/extras" + valor;
			string filename = filen + ".jpg";
			imwrite(filename, roi);	// Si no se introduce un valor de formato válido salta error

			cvtColor(roi, img_hsv, CV_RGB2HSV);

			//int h_bins = 50;
			int s_bins = 10;
			int v_bins = 10;
			int histSize[] = { s_bins, v_bins };

			//float h_ranges[] = { 0, 256 };
			float s_ranges[] = { 0, 255 };
			float v_ranges[] = { 0, 255 };

			const float* ranges[] = { s_ranges, v_ranges };
			//int channels[] = { 0, 1, 2 };

			int channels[] = { 1,2 };
			//calcHist(img_hsv, 1, channels, Mat(), hist, );
			MatND hist_base;
			calcHist(&img_hsv, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);

			waitKey();



			// poner en funcion del fruto seco que sea

			//COMPRUEEBA FRUTOOOOOO  !!!!!

			//C++: bool CvKNearest::train(const CvMat* trainData, const CvMat* responses, const CvMat* sampleIdx = 0, bool is_regression = false, int maxK = 32, bool updateBase = false)

			Mat hist_base_new = Mat::zeros(1, 100, CV_32F);
			for (int c = 0; c < 10; c++) {		// CALCULA MATRIZ ESTANDARIZADA !!!! 
				for (int f = 0; f < 10; f++) {
					hist_base_new.at<int>(0, f + (c * 10)) = hist_base.at<int>(c, f);
				}
			}

			Mat result;



			/// Estandarización frutos:

			// ESTANDARIZACION
			/*		Mat sumac = Mat::zeros(1, 100, CV_32F);
			for (int c = 0; c < 100; c++) {		// Suma todas las columnas
			for (int f = 0; f < 100; f++) {
			sumac.at<float>(0, c) = sumac.at<float>(0, c) + hist_base_new.at<float>(f, c);
			}
			}
			Mat mediac = Mat::zeros(1, 100, CV_32F);
			for (int c = 0; c < 100; c++) {		// Calcula la media de cada columna
			mediac.at<float>(0, c) = sumac.at<float>(0, c) / 100;
			}*/
			Mat desviaStndc = Mat::zeros(1, 100, CV_32F);
			Mat pasoSuma = Mat::zeros(1, 100, CV_32F);
			Mat pasods = Mat::zeros(1, 100, CV_32F);
			Mat pasoDesv = Mat::zeros(1, 100, CV_32F);
			for (int c = 0; c < 100; c++) {		// Calcula desviación estandar
												///for (int f = 0; f < 100; f++) {		// Calcula el previo a la multiplicacion y la raiz
				pasoDesv.at<float>(0, c) = pow((hist_base_new.at<float>(0, c) - mediac.at<float>(0, c)), 2); // elevar al cuadrado 
				pasoSuma.at<float>(0, c) = pasoSuma.at<float>(0, c) + pasoDesv.at<float>(0, c);
				//}
				pasods.at<float>(0, c) = pasoSuma.at<float>(0, c) / 99;
				desviaStndc.at<float>(0, c) = sqrt(pasods.at<float>(0, c));
			}
			Mat hist_stand_base = Mat::zeros(1, 100, CV_32F);
			for (int c = 0; c < 100; c++) {		// CALCULA MATRIZ ESTANDARIZADA !!!! 
												//for (int f = 0; f < 100; f++) {
				if (desviaStndc.at<float>(0, c) != 0) {
					hist_stand_base.at<float>(0, c) = (hist_base_new.at<float>(0, c) - mediac.at<float>(0, c)) / desviaStndc.at<float>(0, c);
				}
				//}
			}

			//		NORMALIZACION
			/*	float minxx = 1000000000000;
			float maxxx = 0;
			for (int c = 0; c < 100; c++) {		// Suma todas las columnas
			if (minxx > min.at<float>(0, c)) {
			minxx = min.at<float>(0, c);
			}
			if (maxxx > max.at<float>(0, c)) {
			maxxx = max.at<float>(0, c);
			}
			min.at<float>(0, c) = minxx;
			max.at<float>(0, c) = maxxx;
			}*/
			Mat hist_baseNORMA = Mat::zeros(1, 100, CV_32F);
			for (int c = 0; c < 100; c++) {		// Suma todas las columnas	
				hist_baseNORMA.at<float>(0, c) = (hist_base_new.at<float>(0, c) - min.at<float>(0, c)) / (max.at<float>(0, c) - min.at<float>(0, c));
			}



			//clasificador->predict(hist_stand_base, result);
			//clasificador->predict(hist_base_new, result);
			clasificador->predict(hist_baseNORMA, result);


			Scalar color = Scalar(0, 0, 0);// = Scalar(255, 0, 0);//color rojo;
			int idenColor = result.at<float>(0, 0);

			if (idenColor == 1) {
				color = colorAvellana;//color verde
			}
			else if (idenColor == 2) {
				color = colorAlmendra;//color fucsia
			}
			else if (idenColor == 3) {
				color = colorCastana;//color amarillo
			}
			else if (idenColor == 4) {
				color = colorNuez;//color azul claro
			}
			else if (idenColor == 5) {
				color = colorPistacho;//color azul
			}
			else {
				color = Scalar(155, 155, 155);
			}
			//	drawContours(img_new, contours, (int)i, colorPistacho, 2, 8, hierarchy, 0, Point());//dibuja los contornos
			drawContours(imgV, contours, (int)i, color, 2, 8, hierarchy, 0, Point());//dibuja los contornos		

			indice++;
		}
		m_ui.video->setVisualicedImage(imgV);
	}
}
Mat CClasificador::clasificacionFS(Mat img_in) {
	// Stretching:*********************************************************************************************

	Mat img_stret = img_in.clone();

	int r1, s1, r2, s2;
	r1 = 70; s1 = 0; r2 = 125; s2 = 255;

	for (int y = 0; y < img_in.rows; y++) {
		for (int x = 0; x < img_in.cols; x++) {
			for (int c = 0; c < 3; c++) {
				int output = computeOutput(img_in.at<Vec3b>(y, x)[c], r1, s1, r2, s2);
				img_stret.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(output);
			}
		}
	}
	//namedWindow("Stretching (1)", 1);
	//imshow("Stretching (1)", img_stret);


	// UMBRALIZACIÓN:*******************************************************************************************
	Mat img_umbral;
	Mat img_grey;
	cvtColor(img_stret, img_grey, CV_RGB2GRAY);//pasar a escala de grises

	adaptiveThreshold(img_grey, img_umbral, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 75, 1);
	//void adaptiveThreshold(new_image, im_in, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
	//imshow("Umbralización (3)", img_umbral);

	/*PARA EL FUTURO:TEXTURAS
	// Canny:***************************************************************************************************

	cvtColor(new_image, edges, COLOR_BGR2GRAY);
	GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
	Canny(edges, edges, 0, 30, 3);	//(,,,umbral*ratio,)

	imshow("edges", edges);*/

	/*Mat im_in(edges.rows, new_image.cols, CV_8UC1); // convertir a escala gris:
	for (int i = 0; i < edges.rows; i++)
	{
	Vec3b* imgrow = edges.ptr<Vec3b>(i);
	uchar* grayrow = im_in.ptr<uchar>(i);

	for (int j = 0; j < edges.cols; j++)
	{
	uchar B = imgrow[j][0];
	uchar G = imgrow[j][1];
	uchar R = imgrow[j][2];

	grayrow[j] = (B + G + R) / 3;
	}
	}*/
	//Mat im_in = edges;


	// Cierre apertura:
	/*Opening: MORPH_OPEN : 2
	Closing: MORPH_CLOSE: 3
	Gradient: MORPH_GRADIENT: 4
	Top Hat: MORPH_TOPHAT: 5
	Black Hat: MORPH_BLACKHAT: 6*/
	//https://docs.opencv.org/2.4/doc/tutorials/imgproc/opening_closing_hats/opening_closing_hats.html
	/*
	Mat dst;

	int morph_size = 6;

	Mat element = getStructuringElement(2, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	morphologyEx(im_in, dst,3, element);//3 porque es la funcion close
	imshow("close1", dst);
	//	https://docs.opencv.org/3.3.0/d3/dbe/tutorial_opening_closing_hats.html

	morph_size = 2;
	element = getStructuringElement(2, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	morphologyEx(dst, dst, 4, element);
	imshow("close2", dst);

	morph_size = 6;

	im_in = dst;*/


	// ImFill:*************************************************************************************************

	// Threshold.
	// Set values equal to or above 220 to 0.
	// Set values below 220 to 255.

	Mat im_th;
	threshold(img_umbral, im_th, 220, 255, THRESH_BINARY_INV);
	//threshold(im_in, im_th, 65, 255, THRESH_BINARY_INV);

	// Floodfill from point (0, 0)
	Mat im_floodfill = im_th.clone();
	floodFill(im_floodfill, cv::Point(0, 0), Scalar(255));

	// Invert floodfilled image
	Mat im_floodfill_inv;
	bitwise_not(im_floodfill, im_floodfill_inv);

	// Combine the two images to get the foreground.
	//Mat img_imfill = (im_th | im_floodfill_inv);

	img_clasif = (im_th | im_floodfill_inv);	/////////////////////////////////////////////////////////


												// Display images
												/*imshow("Thresholded Image1", im_th);
												imshow("Floodfilled Image2", im_floodfill);
												imshow("Inverted Floodfilled Image3", im_floodfill_inv);
												imshow("Foreground4", img_imfill);*/
												//imshow("Imfill (4)", img_clasif);
												//waitKey(0);
												//https://www.learnopencv.com/filling-holes-in-an-image-using-opencv-python-c/

												/////////
												/*Mat img_erode;
												int erosion_size = 10;
												Mat element = getStructuringElement(cv::MORPH_CROSS,
												cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
												cv::Point(erosion_size, erosion_size));
												erode(img_imfill, img_erode, element);

												namedWindow("Display window", CV_WINDOW_AUTOSIZE);
												imshow("Display window", img_erode);
												img_imfill = img_erode;
												*/
												//return img_imfill;
	return img_clasif;

}



int CClasificador::computeOutput(int x, int r1, int s1, int r2, int s2)
{		// Funcion necesaria para el Stretching 
	float result;
	if (0 <= x && x <= r1) {
		result = s1 / r1 * x;
	}
	else if (r1 < x && x <= r2) {
		result = ((s2 - s1) / (r2 - r1)) * (x - r1) + s1;
	}
	else if (r2 < x && x <= 255) {
		result = ((255 - s2) / (255 - r2)) * (x - r2) + s2;
	}
	return (int)result;
}

// FUNCIONES DE ACCIÓN 
void CClasificador::StartStop() {

	if (ss == true) {
		ss = false;
		m_ui.lineEdit->setText("Estado: STOP");
		m_ui.ssButton->setText("PLAY");
		guardaImag();
	}
	else {
		ss = true;
		m_ui.ssButton->setText("STOP-Captura");
		verVideo();
	}
}

void CClasificador::verVideo() {
	procesado(imgV);
	if (ss) {
		QTimer::singleShot(10, this, SLOT(verVideo()));
	}
}

void CClasificador::guardaImag() {
	QString archivoSalida = "muestra" + QString::number(n) + ".jpg"; // Nombre archivo
	string filename = archivoSalida.toStdString();
	cv::imwrite("Imagenes/" + filename, imgV);	// Si no se introduce un valor de formato válido salta error

	m_ui.lineEdit->setText("La imagen ha sido convertida y guardada como:" + archivoSalida);
	n++;
}

void CClasificador::leyenda(void) 
{
	Point org1(50, 50);
	putText(img_leyenda, "Avellana", org1, CV_FONT_NORMAL, 1, colorAvellana, 2);
	Point org2(50, 100);
	putText(img_leyenda, "Almendra", org2, CV_FONT_NORMAL, 1, colorAlmendra, 2);
	Point org3(50, 150);
	putText(img_leyenda, "Castana", org3, CV_FONT_NORMAL, 1, colorCastana, 2);
	Point org4(50, 200);
	putText(img_leyenda, "Nuez", org4, CV_FONT_NORMAL, 1, colorNuez, 2);
	Point org5(50, 250);
	putText(img_leyenda, "Pistacho", org5, CV_FONT_NORMAL, 1, colorPistacho, 2);
}

void CClasificador::verImag(void)
{
	m_ui.cuadro->setVisualicedImage(img_leyenda);
	m_ui.cuadro->setVisualicedImage(img_leyenda);
}

