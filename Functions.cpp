//Vial and Crack Detection Algoryhtm - Group 464 ROB4
//V6.0 - 20/05/2020

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include "Vials.h"
#include <fstream>
#include <sstream>
#include<string>

using namespace std;

void inspectVial::loadDataTop() {
	std::ifstream in("datatop.txt");
	int numRows = 179;
	int numCols = 4;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			in >> topinit[i][j];
		}
	}

	for (int i = 0; i < numRows; i++) {
		float value = topinit[i][0] / topinit[i][1];
		double ratio = (value - 0.105263158) / (14.06367041 - 0.105263158);
		top[i][0] = ratio;
	}

	for (int i = 0; i < numRows; i++) {
		float value = topinit[i][2];
		double circ = (value - 0.0599653) / (0.785 - 0.0599653);
		top[i][1] = circ;
	}

	for (int i = 0; i < numRows; i++) {
		float value = topinit[i][3];
		double elong = (value - 1) / (13.4 - 1);
		top[i][2] = elong;
	}
	/*
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < 3; j++) {
			cout << top[i][j] << " ";
		}
		cout << "" << endl;
	}
	*/
}

void inspectVial::loadDataBottom() {
	std::ifstream in("databottom.txt");
	int numRows = 290;
	int numCols = 4;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			in >> bottominit[i][j];
		}
	}

	for (int i = 0; i < numRows; i++) {
		float value = bottominit[i][0] / bottominit[i][1];
		double ratio = (value - 0.105263158) / (14.06367041 - 0.105263158);
		bottom[i][0] = ratio;
	}

	for (int i = 0; i < numRows; i++) {
		float value = bottominit[i][2];
		double circ = (value - 0.0599653) / (0.785 - 0.0599653);
		bottom[i][1] = circ;
	}

	for (int i = 0; i < numRows; i++) {
		float value = bottominit[i][3];
		double elong = (value - 1) / (13.4 - 1);
		bottom[i][2] = elong;
	}
	/*
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < 3; j++) {
			cout << bottom[i][j] << " ";
		}
		cout << "" << endl;
	}
	*/
}

void inspectVial::loadDataCrack() {
	std::ifstream in("datacrack.txt");
	int numRows = 216;
	int numCols = 4;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			in >> crackinit[i][j];
		}
	}

	for (int i = 0; i < numRows; i++) {
		float value = crackinit[i][0] / crackinit[i][1];
		double ratio = (value - 0.105263158) / (14.06367041 - 0.105263158);
		crack[i][0] = ratio;
	}

	for (int i = 0; i < numRows; i++) {
		float value = crackinit[i][2];
		double circ = (value - 0.0599653) / (0.785 - 0.0599653);
		crack[i][1] = circ;
	}

	for (int i = 0; i < numRows; i++) {
		float value = crackinit[i][3];
		double elong = (value - 1) / (13.4 - 1);
		crack[i][2] = elong;
	}
	/*
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < 3; j++) {
			cout << crack[i][j] << " ";
		}
		cout << "" << endl;
	}
	*/
}

void inspectVial::loadDataScratch() {
	std::ifstream in("datascratch.txt");
	int numRows = 143;
	int numCols = 4;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			in >> scratchinit[i][j];
		}
	}

	for (int i = 0; i < numRows; i++) {
		float value = scratchinit[i][0] / scratchinit[i][1];
		double ratio = (value - 0.105263158) / (14.06367041 - 0.105263158);
		scratch[i][0] = ratio;
	}

	for (int i = 0; i < numRows; i++) {
		float value = scratchinit[i][2];
		double circ = (value - 0.0599653) / (0.785 - 0.0599653);
		scratch[i][1] = circ;
	}

	for (int i = 0; i < numRows; i++) {
		float value = scratchinit[i][3];
		double elong = (value - 1) / (13.4 - 1);
		scratch[i][2] = elong;
	}
	/*
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < 3; j++) {
			cout << scratch[i][j] << " ";
		}
		cout << "" << endl;
	}
	*/
}

cv::Mat inspectVial::rotate(cv::Mat src, double angle) {
	cv::Mat dst;
	cv::Point2f pt(src.cols / 2., src.rows / 2.);
	cv::Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(src, dst, r, cv::Size(src.cols, src.rows));
	return dst;
}

////////////////////////////////////////////////

void inspectVial::rotatefunc(cv::Mat vial) {

	//cout << "Rotate Function" << endl;

	//Morphology for the top-bounding box.
	cv::Mat rotated_Grey = cv::Mat(vial.size(), CV_8U);
	cv::Mat rotated_Thresh2 = cv::Mat(vial.size(), CV_8U);
	cv::Mat rotated_background = cv::Mat(vial.size(), CV_8UC3);

	cvtColor(vial, rotated_Grey, cv::COLOR_BGR2GRAY);
	//imshow("rotated_Grey", rotated_Grey);
	//cv::imshow("rotated_Grey", rotated_Grey);
	//cv::waitKey(0);
	//cv::destroyAllWindows;
	threshold(rotated_Grey, cadst, 20, 200, 1);

	medianBlur(rotated_Grey, rotated_background, 7);
	//imshow("rotated_background", rotated_background);
	//cv::imshow("rotated_background", rotated_background);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	threshold(rotated_background, rotated_Thresh2, 46, 255, cv::THRESH_BINARY); //46
	//imshow("rotated_Thresh2", rotated_Thresh2);
	//cv::imshow("rotated_Thresh2", rotated_Thresh2);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::Mat rotated_morph1 = cv::Mat(vial.size(), CV_8U);
	cv::Mat ElemClosingRotated = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(13, 13));
	cv::morphologyEx(rotated_Thresh2, rotated_morph1, cv::MORPH_CLOSE, ElemClosingRotated);

	cv::Rect ROI_Morph = cv::Rect(91, 65, 527, 210); //113, 31, 422, 174

	cv::Mat contour_ROI = rotated_morph1(ROI_Morph);
	//cv::imshow("contour_ROI", contour_ROI);
	////cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::Mat Contour = cv::Mat(contour_ROI.size(), CV_8U);
	cv::Mat ContourBig = cv::Mat(vial.size(), CV_8U);
	vector<vector<cv::Point>> GcontoursTop;
	vector<cv::Vec4i> hierarchyTop;
	vector<vector<cv::Point>> GcontoursTop2;
	vector<cv::Vec4i> hierarchyTop2;

	cv::findContours(contour_ROI, GcontoursTop2, hierarchyTop2, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	cv::drawContours(Contour, GcontoursTop2, -1, cv::Scalar(0, 0, 0), 1);
//	imshow("Contour", Contour);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::findContours(rotated_morph1, GcontoursTop, hierarchyTop, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	cv::drawContours(ContourBig, GcontoursTop, -1, cv::Scalar(0, 0, 0), 1);

	vector<Vialfeatures> featVecTop;
	vector<float> circVecTop;
	vector<float> areaVecTop;

	for (int i = 0; i < GcontoursTop2.size(); i++)
	{
		if (hierarchyTop2[i][3] == -1)
		{
			Vialfeatures G;
			G.contourIndex = i;
			G.area = contourArea(GcontoursTop2[i]);
			G.perimeter = arcLength(GcontoursTop2[i], true);
			G.circularity = (4 * 3.14 * G.area) / pow(G.perimeter, 2);
			G.hasCrack = (hierarchyTop2[i][2] == -1) ? false : true;

			cv::RotatedRect box = minAreaRect(GcontoursTop2[i]);
			G.elongation = max(box.size.width / box.size.height, box.size.height / box.size.width);

			//cout <<"Top1 "<< "G.Area:" << G.area << "; G.Perimeter:" << G.perimeter << "; G.Circularity:" << G.circularity << "; G.Cracks:" << G.hasCrack << "; G.Elongation:" << G.elongation << endl;

			circVecTop.push_back(G.circularity);
		}
	}

	for (int i = 0; i < GcontoursTop.size(); i++)
	{
		if (hierarchyTop[i][3] == -1)
		{
			Vialfeatures G;
			G.contourIndex = i;
			G.area = contourArea(GcontoursTop[i]);
			G.perimeter = arcLength(GcontoursTop[i], true);
			G.circularity = (4 * 3.14 * G.area) / pow(G.perimeter, 2);
			G.hasCrack = (hierarchyTop[i][2] == -1) ? false : true;

			cv::RotatedRect box = minAreaRect(GcontoursTop[i]);
			G.elongation = max(box.size.width / box.size.height, box.size.height / box.size.width);

			//cout << "Top2 " << "G.Area:" << G.area << "; G.Perimeter:" << G.perimeter << "; G.Circularity:" << G.circularity << "; G.Cracks:" << G.hasCrack << "; G.Elongation:" << G.elongation << endl;
			featVecTop.push_back(G);
		}
	}

	cv::Mat ContourIMG = cv::Mat(vial.size(), CV_8U, cv::Scalar(255, 255, 255));
	int idx = INT_MAX;

	float circtop;

	for (int i = 0; i < circVecTop.size(); i++) {
		//cout << circVecTop[i] << endl;
	}


	for (int i = 0; i < circVecTop.size(); i++) {
		circtop = circVecTop[i];
	}

	for (int i = 0; i < featVecTop.size(); i++)
	{
		if (featVecTop[i].circularity == circtop)
		{
			cv::drawContours(ContourIMG, GcontoursTop, featVecTop[i].contourIndex, cv::Scalar(0, 255, 0), 1);
			idx = featVecTop[i].contourIndex;
		}
	}

	vector<cv::Rect> boundRect(featVecTop.size());

	for (int i = 0; i < featVecTop.size(); i++)
	{
		boundRect[i] = cv::boundingRect(cv::Mat(GcontoursTop[idx]));
	}

	vector<boundingBox> Coordinates;
	boundingBox G;
	G.x, G.y, G.w, G.h = INT_MAX;
	cv::Mat drawing = cv::Mat::zeros(vial.size(), CV_8UC3);

	int y1 = INT_MAX;
	int x1 = INT_MAX;
	int width1;
	int width2;

	for (int i = 0; i < featVecTop.size(); i++)
	{
		cv::Scalar color = cv::Scalar(75, 150, 95);
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 1, 8, 0);
		G.x = boundRect[i].x;
		G.y = boundRect[i].y;
		G.w = boundRect[i].width;
		G.h = boundRect[i].height;

		//width1 = boundRect[i].width;
		y1 = boundRect[i].y;
		x1 = boundRect[i].x;
	}

	//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//Morphology for the bottom-bounding box.
	cv::Mat cadstmorph1 = cv::Mat(vial.size(), CV_8U);
	cv::Mat cElemOpen = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
	cv::morphologyEx(cadst, cadstmorph1, cv::MORPH_OPEN, cElemOpen);

	cv::Mat cadstmorph2 = cv::Mat(vial.size(), CV_8U);
	cv::Mat cElemClose = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(22, 22));
	cv::morphologyEx(cadstmorph1, cadstmorph2, cv::MORPH_CLOSE, cElemClose);

	cv::Mat cadstmorph3 = cv::Mat(vial.size(), CV_8U);
	cv::Mat cElemErode = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(19, 19));
	cv::morphologyEx(cadstmorph2, cadstmorph3, cv::MORPH_ERODE, cElemErode);

	cv::Rect ROI_Morph2 = cv::Rect(188, 305, 259, 85); //155, 317, 315, 132
	cv::Mat contour_ROI2 = cadstmorph3(ROI_Morph2);
	//cv::imshow("contour_ROI2", contour_ROI2);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::Mat Contour2 = cv::Mat(contour_ROI2.size(), CV_8U);
	cv::Mat ContourBig2 = cv::Mat(vial.size(), CV_8U);
	vector<vector<cv::Point>> GcontoursBot;
	vector<cv::Vec4i> hierarchyBot;

	vector<vector<cv::Point>> GcontoursBot2;
	vector<cv::Vec4i> hierarchyBot2;

	cv::findContours(contour_ROI2, GcontoursBot2, hierarchyBot2, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	cv::drawContours(Contour2, GcontoursBot2, -1, cv::Scalar(0, 0, 0), 1);
	//imshow("Contour2", Contour2);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::findContours(cadstmorph3, GcontoursBot, hierarchyBot, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	cv::drawContours(ContourBig2, GcontoursBot, -1, cv::Scalar(0, 0, 0), 1);

	vector<Vialfeatures> featVecBot;
	vector<int> areaVecBot;
	vector<float> circVecBot;
	float VecBot[6][2];

	for (int i = 0; i < GcontoursBot2.size(); i++)
	{
		if (hierarchyBot2[i][3] == -1)
		{
			Vialfeatures F;
			F.contourIndex = i;
			F.area = contourArea(GcontoursBot2[i]);
			F.perimeter = arcLength(GcontoursBot2[i], true);
			F.circularity = (4 * 3.14 * F.area) / pow(F.perimeter, 2);
			F.hasCrack = (hierarchyBot2[i][2] == -1) ? false : true;

			cv::RotatedRect box = minAreaRect(GcontoursBot2[i]);
			F.elongation = max(box.size.width / box.size.height, box.size.height / box.size.width);

			//cout << "Bot1 " << "G.Area:" << F.area << "; G.Perimeter:" << F.perimeter << "; G.Circularity:" << F.circularity << "; G.Cracks:" << F.hasCrack << "; G.Elongation:" << F.elongation << endl;

			VecBot[i][0] = F.circularity;
			VecBot[i][1] = F.area;
		}
	}

	for (int i = 0; i < 6; i++) {
		if (VecBot[i][1] > 19 && VecBot[i][1] < 390) {
			circVecBot.push_back(VecBot[i][0]);
		}
	}

	for (int i = 0; i < GcontoursBot.size(); i++)
	{
		if (hierarchyBot[i][3] == -1)
		{
			Vialfeatures F;
			F.contourIndex = i;
			F.area = contourArea(GcontoursBot[i]);
			F.perimeter = arcLength(GcontoursBot[i], true);
			F.circularity = (4 * 3.14 * F.area) / pow(F.perimeter, 2);
			F.hasCrack = (hierarchyBot[i][2] == -1) ? false : true;

			cv::RotatedRect box = minAreaRect(GcontoursBot[i]);
			F.elongation = max(box.size.width / box.size.height, box.size.height / box.size.width);

			//cout << "Bot2 " << "G.Area:" << F.area << "; G.Perimeter:" << F.perimeter << "; G.Circularity:" << F.circularity << "; G.Cracks:" << F.hasCrack << "; G.Elongation:" << F.elongation << endl;

			featVecBot.push_back(F);
		}
	}

	cv::Mat ContourIMGBot = cv::Mat(vial.size(), CV_8U, cv::Scalar(255, 255, 255));
	int idxBot = INT_MAX;
	int idxBotMax = INT_MAX;

	float circ = INT_MAX;
	float area;

	for (int i = 0; i < circVecBot.size(); i++) {
		circ = *max_element(circVecBot.begin(), circVecBot.end());
	}

	for (int i = 0; i < featVecBot.size(); i++)
	{
		if (featVecBot[i].circularity == circ)
		{
			idxBot = featVecBot[i].contourIndex;
			cv::drawContours(ContourIMGBot, GcontoursBot, featVecBot[i].contourIndex, cv::Scalar(0, 255, 0), 1);
		}
	}

	vector<cv::Rect> boundRectBot(featVecBot.size());

	for (int i = 0; i < featVecBot.size(); i++)
	{
		boundRectBot[i] = cv::boundingRect(cv::Mat(GcontoursBot[idxBot]));
	}

	cv::Mat drawing1 = cv::Mat::zeros(vial.size(), CV_8UC3);

	int x2 = INT_MAX;
	int y2 = INT_MAX;
	int h = INT_MAX;

	for (int i = 0; i < featVecBot.size(); i++)
	{
		cv::Scalar color1 = cv::Scalar(75, 150, 95);
		rectangle(drawing1, boundRectBot[i].tl(), boundRectBot[i].br(), color1, 1, 8, 0);
		x2 = boundRectBot[i].x;
		y2 = boundRectBot[i].y;
		h = boundRectBot[i].height;
		G.h = y2 - y1 + h - 15;
	};

	//cout << "x1: " << x1 << " y1: " << y1 << endl;
	//cout << "x2: " << x2 << " y2: " << y2 << endl;

	int delta_x = x2 - x1;
	int delta_y = y1 - y2;
	double theta = atan2(delta_y, delta_x);
	//cout << "Rotation theta: " << theta << endl; 
	float degrees = (90 + theta * (180.0 / 3.141592653589793238463));
	//cout << "Rotation angle: " << degrees << endl;

	if (degrees > 1 && degrees < 2) {
		degrees = 0;
	}

	if (degrees > 2 && degrees < 2.1) {
		degrees = -degrees/2;
	}

	if (degrees > 2.1) {
		degrees = 0;
	}

	if (degrees > 0.5) {
		degrees = degrees / 2;
	}

	if (degrees < 0.5) {
		degrees = 2*degrees;
	}

	if (degrees < 0 && degrees > -0.3) {
		degrees = 2*abs(degrees);
	}

	if (degrees < -0.3) {
		degrees = abs(degrees);
	}

	rotated = rotate(vial, degrees);
	//imshow("rotated", rotated);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	//Defining Region Of Interest (ROI):
	cv::Rect ROI = cv::Rect(G.x, G.y, G.w, G.h);
	vial_ROI1 = vial(ROI);
	//imshow("vial_ROI", vial_ROI);
	//cv::waitKey(0);
	//cv::destroyAllWindows;
	//system("CLS");
}

void inspectVial::roifunc(cv::Mat vial) {

	//cout << "Cropping Function" << endl;

	//Morphology for the top-bounding box.
	cv::Mat rotated_Grey = cv::Mat(vial.size(), CV_8U);
	cv::Mat rotated_Thresh2 = cv::Mat(vial.size(), CV_8U);
	cv::Mat rotated_background = cv::Mat(vial.size(), CV_8UC3);

	cvtColor(vial, rotated_Grey, cv::COLOR_BGR2GRAY);
	//imshow("rotated_Grey", rotated_Grey);
	//cv::imshow("rotated_Grey", rotated_Grey);
	//cv::waitKey(0);
	//cv::destroyAllWindows;
	threshold(rotated_Grey, cadst, 20, 200, 1);

	medianBlur(rotated_Grey, rotated_background, 7);
	//imshow("rotated_background", rotated_background);
	//cv::imshow("rotated_background", rotated_background);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	threshold(rotated_background, rotated_Thresh2, 46, 255, cv::THRESH_BINARY); //46
	//imshow("rotated_Thresh2", rotated_Thresh2);
	//cv::imshow("rotated_Thresh2", rotated_Thresh2);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::Mat rotated_morph1 = cv::Mat(vial.size(), CV_8U);
	cv::Mat ElemClosingRotated = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(13, 13));
	cv::morphologyEx(rotated_Thresh2, rotated_morph1, cv::MORPH_CLOSE, ElemClosingRotated);

	cv::Rect ROI_Morph = cv::Rect(91, 65, 527, 210); //113, 31, 422, 174

	cv::Mat contour_ROI = rotated_morph1(ROI_Morph);
	//cv::imshow("contour_ROI", contour_ROI);
	////cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::Mat Contour = cv::Mat(contour_ROI.size(), CV_8U);
	cv::Mat ContourBig = cv::Mat(vial.size(), CV_8U);
	vector<vector<cv::Point>> GcontoursTop;
	vector<cv::Vec4i> hierarchyTop;
	vector<vector<cv::Point>> GcontoursTop2;
	vector<cv::Vec4i> hierarchyTop2;

	cv::findContours(contour_ROI, GcontoursTop2, hierarchyTop2, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	cv::drawContours(Contour, GcontoursTop2, -1, cv::Scalar(0, 0, 0), 1);
	//imshow("Contour", Contour);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::findContours(rotated_morph1, GcontoursTop, hierarchyTop, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	cv::drawContours(ContourBig, GcontoursTop, -1, cv::Scalar(0, 0, 0), 1);

	vector<Vialfeatures> featVecTop;
	vector<float> circVecTop;

	for (int i = 0; i < GcontoursTop2.size(); i++)
	{
		if (hierarchyTop2[i][3] == -1)
		{
			Vialfeatures G;
			G.contourIndex = i;
			G.area = contourArea(GcontoursTop2[i]);
			G.perimeter = arcLength(GcontoursTop2[i], true);
			G.circularity = (4 * 3.14 * G.area) / pow(G.perimeter, 2);
			G.hasCrack = (hierarchyTop2[i][2] == -1) ? false : true;

			cv::RotatedRect box = minAreaRect(GcontoursTop2[i]);
			G.elongation = max(box.size.width / box.size.height, box.size.height / box.size.width);

			//cout <<"Top1 "<< "G.Area:" << G.area << "; G.Perimeter:" << G.perimeter << "; G.Circularity:" << G.circularity << "; G.Cracks:" << G.hasCrack << "; G.Elongation:" << G.elongation << endl;
				circVecTop.push_back(G.circularity);
		}
	}

	for (int i = 0; i < GcontoursTop.size(); i++)
	{
		if (hierarchyTop[i][3] == -1)
		{
			Vialfeatures G;
			G.contourIndex = i;
			G.area = contourArea(GcontoursTop[i]);
			G.perimeter = arcLength(GcontoursTop[i], true);
			G.circularity = (4 * 3.14 * G.area) / pow(G.perimeter, 2);
			G.hasCrack = (hierarchyTop[i][2] == -1) ? false : true;

			cv::RotatedRect box = minAreaRect(GcontoursTop[i]);
			G.elongation = max(box.size.width / box.size.height, box.size.height / box.size.width);

			//cout << "Top2 " << "G.Area:" << G.area << "; G.Perimeter:" << G.perimeter << "; G.Circularity:" << G.circularity << "; G.Cracks:" << G.hasCrack << "; G.Elongation:" << G.elongation << endl;

			featVecTop.push_back(G);
		}
	}

	cv::Mat ContourIMG = cv::Mat(vial.size(), CV_8U, cv::Scalar(255, 255, 255));
	int idx = INT_MAX;

	float circtop;

	for (int i = 0; i < circVecTop.size(); i++) {
		circtop = circVecTop[i];
	}

	for (int i = 0; i < featVecTop.size(); i++)
	{
		if (featVecTop[i].circularity == circtop)
		{
			cv::drawContours(ContourIMG, GcontoursTop, featVecTop[i].contourIndex, cv::Scalar(0, 255, 0), 1);
			idx = featVecTop[i].contourIndex;
		}
	}

	vector<cv::Rect> boundRect(featVecTop.size());

	for (int i = 0; i < featVecTop.size(); i++)
	{
		boundRect[i] = cv::boundingRect(cv::Mat(GcontoursTop[idx]));
	}

	vector<boundingBox> Coordinates;
	boundingBox G;
	G.x, G.y, G.w, G.h = INT_MAX;
	cv::Mat drawing = cv::Mat::zeros(vial.size(), CV_8UC3);

	int y1 = INT_MAX;
	int x1 = INT_MAX;
	int width1;
	int width2;

	for (int i = 0; i < featVecTop.size(); i++)
	{
		cv::Scalar color = cv::Scalar(75, 150, 95);
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 1, 8, 0);
		G.x = boundRect[i].x;
		G.y = boundRect[i].y;
		G.w = boundRect[i].width;
		G.h = boundRect[i].height;

		//width1 = boundRect[i].width;
		y1 = boundRect[i].y;
		x1 = boundRect[i].x;
	}

	//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//Morphology for the bottom-bounding box.
	cv::Mat cadstmorph1 = cv::Mat(vial.size(), CV_8U);
	cv::Mat cElemOpen = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
	cv::morphologyEx(cadst, cadstmorph1, cv::MORPH_OPEN, cElemOpen);

	cv::Mat cadstmorph2 = cv::Mat(vial.size(), CV_8U);
	cv::Mat cElemClose = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(22, 22));
	cv::morphologyEx(cadstmorph1, cadstmorph2, cv::MORPH_CLOSE, cElemClose);

	cv::Mat cadstmorph3 = cv::Mat(vial.size(), CV_8U);
	cv::Mat cElemErode = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(19, 19));
	cv::morphologyEx(cadstmorph2, cadstmorph3, cv::MORPH_ERODE, cElemErode);

	cv::Rect ROI_Morph2 = cv::Rect(188, 305, 259, 85); //155, 317, 315, 132
	cv::Mat contour_ROI2 = cadstmorph3(ROI_Morph2);
	//cv::imshow("contour_ROI2", contour_ROI2);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::Mat Contour2 = cv::Mat(contour_ROI2.size(), CV_8U);
	cv::Mat ContourBig2 = cv::Mat(vial.size(), CV_8U);
	vector<vector<cv::Point>> GcontoursBot;
	vector<cv::Vec4i> hierarchyBot;

	vector<vector<cv::Point>> GcontoursBot2;
	vector<cv::Vec4i> hierarchyBot2;

	cv::findContours(contour_ROI2, GcontoursBot2, hierarchyBot2, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	cv::drawContours(Contour2, GcontoursBot2, -1, cv::Scalar(0, 0, 0), 1);
	//imshow("Contour2", Contour2);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::findContours(cadstmorph3, GcontoursBot, hierarchyBot, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	cv::drawContours(ContourBig2, GcontoursBot, -1, cv::Scalar(0, 0, 0), 1);

	vector<Vialfeatures> featVecBot;
	vector<int> areaVecBot;
	vector<float> circVecBot;
	float VecBot[6][2];

	for (int i = 0; i < GcontoursBot2.size(); i++)
	{
		if (hierarchyBot2[i][3] == -1)
		{
			Vialfeatures F;
			F.contourIndex = i;
			F.area = contourArea(GcontoursBot2[i]);
			F.perimeter = arcLength(GcontoursBot2[i], true);
			F.circularity = (4 * 3.14 * F.area) / pow(F.perimeter, 2);
			F.hasCrack = (hierarchyBot2[i][2] == -1) ? false : true;

			cv::RotatedRect box = minAreaRect(GcontoursBot2[i]);
			F.elongation = max(box.size.width / box.size.height, box.size.height / box.size.width);

			//cout << "Bot1 " << "G.Area:" << F.area << "; G.Perimeter:" << F.perimeter << "; G.Circularity:" << F.circularity << "; G.Cracks:" << F.hasCrack << "; G.Elongation:" << F.elongation << endl;

			VecBot[i][0] = F.circularity;
			VecBot[i][1] = F.area;
		}
	}

	for (int i = 0; i < 6; i++) {
		if (VecBot[i][1] > 19 && VecBot[i][1] < 390) {
			circVecBot.push_back(VecBot[i][0]);
		}
	}

	for (int i = 0; i < GcontoursBot.size(); i++)
	{
		if (hierarchyBot[i][3] == -1)
		{
			Vialfeatures F;
			F.contourIndex = i;
			F.area = contourArea(GcontoursBot[i]);
			F.perimeter = arcLength(GcontoursBot[i], true);
			F.circularity = (4 * 3.14 * F.area) / pow(F.perimeter, 2);
			F.hasCrack = (hierarchyBot[i][2] == -1) ? false : true;

			cv::RotatedRect box = minAreaRect(GcontoursBot[i]);
			F.elongation = max(box.size.width / box.size.height, box.size.height / box.size.width);

			//cout << "Bot2 " << "G.Area:" << F.area << "; G.Perimeter:" << F.perimeter << "; G.Circularity:" << F.circularity << "; G.Cracks:" << F.hasCrack << "; G.Elongation:" << F.elongation << endl;

			featVecBot.push_back(F);
		}
	}

	cv::Mat ContourIMGBot = cv::Mat(vial.size(), CV_8U, cv::Scalar(255, 255, 255));
	int idxBot = INT_MAX;
	int idxBotMax = INT_MAX;

	float circ = INT_MAX;
	float area;

	for (int i = 0; i < circVecBot.size(); i++) {
		circ = *max_element(circVecBot.begin(), circVecBot.end());
	}

	for (int i = 0; i < featVecBot.size(); i++)
	{
		if (featVecBot[i].circularity == circ)
		{
			idxBot = featVecBot[i].contourIndex;
			cv::drawContours(ContourIMGBot, GcontoursBot, featVecBot[i].contourIndex, cv::Scalar(0, 255, 0), 1);
		}
	}

	vector<cv::Rect> boundRectBot(featVecBot.size());

	for (int i = 0; i < featVecBot.size(); i++)
	{
		boundRectBot[i] = cv::boundingRect(cv::Mat(GcontoursBot[idxBot]));
	}

	cv::Mat drawing1 = cv::Mat::zeros(vial.size(), CV_8UC3);

	int x2 = INT_MAX;
	int y2 = INT_MAX;
	int h = INT_MAX;

	for (int i = 0; i < featVecBot.size(); i++)
	{
		cv::Scalar color1 = cv::Scalar(75, 150, 95);
		rectangle(drawing1, boundRectBot[i].tl(), boundRectBot[i].br(), color1, 1, 8, 0);
		x2 = boundRectBot[i].x;
		y2 = boundRectBot[i].y;
		h = boundRectBot[i].height;
		G.h = y2 - y1 + h - 15;
	};

	//Defining Region Of Interest (ROI):
	cv::Rect ROI = cv::Rect(G.x, G.y, G.w, G.h);
	xclass = G.x;
	yclass = G.y;
	hclass = G.h;
	wclass = G.w;

	vial_ROI = vial(ROI);
	//imshow("vial_ROI1", vial_ROI1);
	//cv::waitKey(0);
	//cv::destroyAllWindows;
	//system("CLS");
}

void inspectVial::inspection(cv::Mat vial) {

	cout << "Inspection Function" << endl;
	cv::Mat Grayscale = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat vial_Contrast = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat vial_Subt = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat vial_Thresh = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat Contour1 = cv::Mat(vial_ROI.size(), CV_8U, cv::Scalar(255, 255, 255));

	cv::Mat medianBlur = cv::Mat(vial_ROI.size(), CV_8U);
	cv::medianBlur(vial_ROI, medianBlur, 3);
	//imshow("medianBlur", medianBlur);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	for (int x = 0; x < vial_ROI.cols; x++) {
		for (int y = 0; y < vial_ROI.rows; y++) {
			for (int c = 0; c < 3; c++) {
				float alpha = 1.85;
				float beta = 100;
				int E = medianBlur.at<cv::Vec3b>(cv::Point(x, y))[c];
				vial_Contrast.at<uchar>(cv::Point(x, y)) = alpha * E + beta;
			}
		}
	}

	//imshow("vial_Contrast", vial_Contrast);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::threshold(vial_Contrast, vial_Thresh, 80, 255, cv::THRESH_BINARY_INV);
	//imshow("vial_Thresh", vial_Thresh);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::Mat vial_morph1 = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat ElemClose = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(23, 23));
	cv::morphologyEx(vial_Thresh, vial_morph1, cv::MORPH_CLOSE, ElemClose);
	//imshow("vial_morph1", vial_morph1);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::Mat vial_morph2 = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat ElemErode1 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2));
	cv::morphologyEx(vial_morph1, vial_morph2, cv::MORPH_ERODE, ElemErode1);
	vector<cv::Vec4i> hierarchy1;
	//imshow("vial_morph2", vial_morph2);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::Mat GContour1 = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat ContourIMG1 = cv::Mat(vial_ROI.size(), CV_8U);
	cv::findContours(vial_morph2, G1contours, hierarchy1, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	cv::drawContours(GContour1, G1contours, -1, cv::Scalar(0, 0, 0), 1);
	//imshow("GContour1", GContour1);
	//cv::waitKey(0);
	//cv::destroyAllWindows;


	for (int i = 0; i < G1contours.size(); i++)
	{
		if (hierarchy1[i][3] == -1)
		{
			Vialfeatures G1;
			G1.contourIndex = i;
			G1.area = contourArea(G1contours[i]);
			G1.perimeter = arcLength(G1contours[i], true);
			G1.circularity = (4 * 3.14 * G1.area) / pow(G1.perimeter, 2);
			G1.hasCrack = (hierarchy1[i][2] == -1) ? false : true;

			cv::RotatedRect box = minAreaRect(G1contours[i]);
			G1.elongation = max(box.size.width / box.size.height, box.size.height / box.size.width);

			//cout << "G1.Area:" << G1.area << "; G1.Perimeter:" << G1.perimeter << "; G1.Circularity:" << G1.circularity << "; G1.Cracks:" << G1.hasCrack << "; G1.Elongation:" << G1.elongation << endl;
			featVec1.push_back(G1);

			if (G1.area > 0 && G1.perimeter > 0) {
				areaVec.push_back(G1.area);
				perimeterVec.push_back(G1.perimeter);
				circularityVec.push_back(G1.circularity);
				elongationVec.push_back(G1.elongation);
			}
		}
	}
	
	/*
	imshow("Original Image", vial);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Rotated", rotated);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Median Blur", medianBlur);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Adjust Contrast and Brightness", vial_Contrast);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Threshold", vial_Thresh);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Opening", vial_morph1);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Erode", vial_morph2);
	cv::waitKey(0);
	cv::destroyAllWindows;
	*/
	//imshow("Contours1", GContour1);
	//cv::waitKey(0);
	//cv::destroyAllWindows;
}

void inspectVial::classify(cv::Mat vial) {

	cv::Mat everything = cv::Mat(rotated.size(), CV_8UC3);
	cv::Mat drawingfinal = cv::Mat::zeros(rotated.size(), CV_8UC3);

	int k = 8;
	cout << "The algorithm will look at the " << k << " nearest neighbours." << endl;

	/*
	cout << "To how many neighbours would you like to look at? (Choose a number between 1 and 11): ";
	cin >> k;
	cout << " " << endl;
	if (k > 11 || k < 1) {
		cout << "Please try again with a number between 1 and 11: ";
		cin >> k;
		cout << " " << endl;
	}
	else {
		cout << "The algorithm will look at the " << k << " nearest neighbours." << endl;
		cout << "  " << endl;
	}
	*/

	//After that we enter in a for loop for each BLOB previously detected.
	for (int o = 0; o < areaVec.size(); o++) {

		//All the values are normalized.
		double x1 = areaVec[o] / perimeterVec[o];
		double x = (x1 - 0.105263158) / (14.06367041 - 0.105263158);

		double y1 = circularityVec[o];
		double y = (y1 - 0.0599653) / (0.785 - 0.0599653);

		double z1 = elongationVec[o];
		double z = (z1 - 1) / (13.4 - 1);

		vector<double> distancesTop;
		vector<double> distancesBottom;
		vector<double> distancesCrack;
		vector<double> distancesScratch;

		vector<double> all;
		vector<int> allks;

		for (int i = 0; i < 179; i++) {
			double dist;
			dist = sqrt(((x - top[i][0]) * (x - top[i][0])) + ((y - top[i][1]) * (y - top[i][1])) + ((z - top[i][2]) * (z - top[i][2])));
			all.push_back(dist);
			distancesTop.push_back(dist);
		};

		for (int i = 0; i < 290; i++) {
			double dist;
			dist = sqrt(((x - bottom[i][0]) * (x - bottom[i][0])) + ((y - bottom[i][1]) * (y - bottom[i][1])) + ((z - bottom[i][2]) * (z - bottom[i][2])));
			all.push_back(dist);
			distancesBottom.push_back(dist);
		};

		for (int i = 0; i < 216; i++) {
			double dist;
			dist = sqrt(((x - crack[i][0]) * (x - crack[i][0])) + ((y - crack[i][1]) * (y - crack[i][1])) + ((z - crack[i][2]) * (z - crack[i][2])));
			all.push_back(dist);
			distancesCrack.push_back(dist);
		};

		for (int i = 0; i < 143; i++) {
			double dist;
			dist = sqrt(((x - scratch[i][0]) * (x - scratch[i][0])) + ((y - scratch[i][1]) * (y - scratch[i][1])) + ((z - scratch[i][2]) * (z - scratch[i][2])));
			all.push_back(dist);
			distancesScratch.push_back(dist);
		};

		int i;
		double first, second, third, fourth, fifth, sixth, seventh, eight, ninth, tenth, eleventh;
		first, second, third, fourth, fifth, sixth, seventh, eight, ninth, tenth, eleventh = INT_MAX;

		if (k >= 1) {
			first = INT_MAX;
			for (i = 0; i < all.size(); i++)
			{
				if (all[i] < first)
				{
					first = all[i];
				}
			};
			vector<double>::iterator it = remove(all.begin(), all.end(), first);
			all.erase(it, all.end());

			bool existsTop = std::find(std::begin(distancesTop), std::end(distancesTop), first) != std::end(distancesTop);
			bool existsBot = std::find(std::begin(distancesBottom), std::end(distancesBottom), first) != std::end(distancesBottom);
			bool existsCrack = std::find(std::begin(distancesCrack), std::end(distancesCrack), first) != std::end(distancesCrack);
			bool existsScratch = std::find(std::begin(distancesScratch), std::end(distancesScratch), first) != std::end(distancesScratch);

			if (existsTop == 1) {
				allks.push_back(0);
			}

			if (existsBot == 1) {
				allks.push_back(1);
			}

			if (existsCrack == 1) {
				allks.push_back(2);
			}

			if (existsScratch == 1) {
				allks.push_back(3);
			}
		};

		if (k >= 2) {
			second = INT_MAX;
			for (i = 0; i < all.size(); i++)
			{
				if (all[i] < second)
				{
					second = all[i];
				}
			};
			vector<double>::iterator it = remove(all.begin(), all.end(), second);
			all.erase(it, all.end());

			bool existsTop = std::find(std::begin(distancesTop), std::end(distancesTop), second) != std::end(distancesTop);
			bool existsBot = std::find(std::begin(distancesBottom), std::end(distancesBottom), second) != std::end(distancesBottom);
			bool existsCrack = std::find(std::begin(distancesCrack), std::end(distancesCrack), second) != std::end(distancesCrack);
			bool existsScratch = std::find(std::begin(distancesScratch), std::end(distancesScratch), second) != std::end(distancesScratch);

			if (existsTop == 1) {
				allks.push_back(0);
			}

			if (existsBot == 1) {
				allks.push_back(1);
			}

			if (existsCrack == 1) {
				allks.push_back(2);
			}

			if (existsScratch == 1) {
				allks.push_back(3);
			}
		};

		if (k >= 3) {
			third = INT_MAX;
			for (i = 0; i < all.size(); i++)
			{
				if (all[i] < third)
				{
					third = all[i];
				}
			};
			vector<double>::iterator it = remove(all.begin(), all.end(), third);
			all.erase(it, all.end());

			bool existsTop = std::find(std::begin(distancesTop), std::end(distancesTop), third) != std::end(distancesTop);
			bool existsBot = std::find(std::begin(distancesBottom), std::end(distancesBottom), third) != std::end(distancesBottom);
			bool existsCrack = std::find(std::begin(distancesCrack), std::end(distancesCrack), third) != std::end(distancesCrack);
			bool existsScratch = std::find(std::begin(distancesScratch), std::end(distancesScratch), third) != std::end(distancesScratch);

			if (existsTop == 1) {
				allks.push_back(0);
			}

			if (existsBot == 1) {
				allks.push_back(1);
			}

			if (existsCrack == 1) {
				allks.push_back(2);
			}

			if (existsScratch == 1) {
				allks.push_back(3);
			}
		};

		if (k >= 4) {
			fourth = INT_MAX;
			for (i = 0; i < all.size(); i++)
			{
				if (all[i] < fourth)
				{
					fourth = all[i];
				}
			};
			vector<double>::iterator it = remove(all.begin(), all.end(), fourth);
			all.erase(it, all.end());

			bool existsTop = std::find(std::begin(distancesTop), std::end(distancesTop), fourth) != std::end(distancesTop);
			bool existsBot = std::find(std::begin(distancesBottom), std::end(distancesBottom), fourth) != std::end(distancesBottom);
			bool existsCrack = std::find(std::begin(distancesCrack), std::end(distancesCrack), fourth) != std::end(distancesCrack);
			bool existsScratch = std::find(std::begin(distancesScratch), std::end(distancesScratch), fourth) != std::end(distancesScratch);

			if (existsTop == 1) {
				allks.push_back(0);
			}

			if (existsBot == 1) {
				allks.push_back(1);
			}

			if (existsCrack == 1) {
				allks.push_back(2);
			}

			if (existsScratch == 1) {
				allks.push_back(3);
			}
		};

		if (k >= 5) {
			fifth = INT_MAX;
			for (i = 0; i < all.size(); i++)
			{
				if (all[i] < fifth)
				{
					fifth = all[i];
				}
			};
			vector<double>::iterator it = remove(all.begin(), all.end(), fifth);
			all.erase(it, all.end());

			bool existsTop = std::find(std::begin(distancesTop), std::end(distancesTop), fifth) != std::end(distancesTop);
			bool existsBot = std::find(std::begin(distancesBottom), std::end(distancesBottom), fifth) != std::end(distancesBottom);
			bool existsCrack = std::find(std::begin(distancesCrack), std::end(distancesCrack), fifth) != std::end(distancesCrack);
			bool existsScratch = std::find(std::begin(distancesScratch), std::end(distancesScratch), fifth) != std::end(distancesScratch);

			if (existsTop == 1) {
				allks.push_back(0);
			}

			if (existsBot == 1) {
				allks.push_back(1);
			}

			if (existsCrack == 1) {
				allks.push_back(2);
			}

			if (existsScratch == 1) {
				allks.push_back(3);
			}
		};

		if (k >= 6) {
			sixth = INT_MAX;
			for (i = 0; i < all.size(); i++)
			{
				if (all[i] < sixth)
				{
					sixth = all[i];
				}
			};
			vector<double>::iterator it = remove(all.begin(), all.end(), sixth);
			all.erase(it, all.end());

			bool existsTop = std::find(std::begin(distancesTop), std::end(distancesTop), sixth) != std::end(distancesTop);
			bool existsBot = std::find(std::begin(distancesBottom), std::end(distancesBottom), sixth) != std::end(distancesBottom);
			bool existsCrack = std::find(std::begin(distancesCrack), std::end(distancesCrack), sixth) != std::end(distancesCrack);
			bool existsScratch = std::find(std::begin(distancesScratch), std::end(distancesScratch), sixth) != std::end(distancesScratch);

			if (existsTop == 1) {
				allks.push_back(0);
			}

			if (existsBot == 1) {
				allks.push_back(1);
			}

			if (existsCrack == 1) {
				allks.push_back(2);
			}

			if (existsScratch == 1) {
				allks.push_back(3);
			}
		};

		if (k >= 7) {
			seventh = INT_MAX;
			for (i = 0; i < all.size(); i++)
			{
				if (all[i] < seventh)
				{
					seventh = all[i];
				}
			};
			vector<double>::iterator it = remove(all.begin(), all.end(), seventh);
			all.erase(it, all.end());

			bool existsTop = std::find(std::begin(distancesTop), std::end(distancesTop), seventh) != std::end(distancesTop);
			bool existsBot = std::find(std::begin(distancesBottom), std::end(distancesBottom), seventh) != std::end(distancesBottom);
			bool existsCrack = std::find(std::begin(distancesCrack), std::end(distancesCrack), seventh) != std::end(distancesCrack);
			bool existsScratch = std::find(std::begin(distancesScratch), std::end(distancesScratch), seventh) != std::end(distancesScratch);

			if (existsTop == 1) {
				allks.push_back(0);
			}

			if (existsBot == 1) {
				allks.push_back(1);
			}

			if (existsCrack == 1) {
				allks.push_back(2);
			}

			if (existsScratch == 1) {
				allks.push_back(3);
			}
		};

		if (k >= 8) {
			eight = INT_MAX;
			for (i = 0; i < all.size(); i++)
			{
				if (all[i] < eight)
				{
					eight = all[i];
				}
			};
			vector<double>::iterator it = remove(all.begin(), all.end(), eight);
			all.erase(it, all.end());

			bool existsTop = std::find(std::begin(distancesTop), std::end(distancesTop), eight) != std::end(distancesTop);
			bool existsBot = std::find(std::begin(distancesBottom), std::end(distancesBottom), eight) != std::end(distancesBottom);
			bool existsCrack = std::find(std::begin(distancesCrack), std::end(distancesCrack), eight) != std::end(distancesCrack);
			bool existsScratch = std::find(std::begin(distancesScratch), std::end(distancesScratch), eight) != std::end(distancesScratch);

			if (existsTop == 1) {
				allks.push_back(0);
			}

			if (existsBot == 1) {
				allks.push_back(1);
			}

			if (existsCrack == 1) {
				allks.push_back(2);
			}

			if (existsScratch == 1) {
				allks.push_back(3);
			}
		};

		if (k >= 9) {
			ninth = INT_MAX;
			for (i = 0; i < all.size(); i++)
			{
				if (all[i] < ninth)
				{
					ninth = all[i];
				}
			};
			vector<double>::iterator it = remove(all.begin(), all.end(), ninth);
			all.erase(it, all.end());

			bool existsTop = std::find(std::begin(distancesTop), std::end(distancesTop), ninth) != std::end(distancesTop);
			bool existsBot = std::find(std::begin(distancesBottom), std::end(distancesBottom), ninth) != std::end(distancesBottom);
			bool existsCrack = std::find(std::begin(distancesCrack), std::end(distancesCrack), ninth) != std::end(distancesCrack);
			bool existsScratch = std::find(std::begin(distancesScratch), std::end(distancesScratch), ninth) != std::end(distancesScratch);

			if (existsTop == 1) {
				allks.push_back(0);
			}

			if (existsBot == 1) {
				allks.push_back(1);
			}

			if (existsCrack == 1) {
				allks.push_back(2);
			}

			if (existsScratch == 1) {
				allks.push_back(3);
			}
		};

		if (k >= 10) {
			tenth = INT_MAX;
			for (i = 0; i < all.size(); i++)
			{
				if (all[i] < tenth)
				{
					tenth = all[i];
				}
			};
			vector<double>::iterator it = remove(all.begin(), all.end(), tenth);
			all.erase(it, all.end());

			bool existsTop = std::find(std::begin(distancesTop), std::end(distancesTop), tenth) != std::end(distancesTop);
			bool existsBot = std::find(std::begin(distancesBottom), std::end(distancesBottom), tenth) != std::end(distancesBottom);
			bool existsCrack = std::find(std::begin(distancesCrack), std::end(distancesCrack), tenth) != std::end(distancesCrack);
			bool existsScratch = std::find(std::begin(distancesScratch), std::end(distancesScratch), tenth) != std::end(distancesScratch);

			if (existsTop == 1) {
				allks.push_back(0);
			}

			if (existsBot == 1) {
				allks.push_back(1);
			}

			if (existsCrack == 1) {
				allks.push_back(2);
			}

			if (existsScratch == 1) {
				allks.push_back(3);
			}
		};

		if (k >= 11) {
			eleventh = INT_MAX;
			for (i = 0; i < all.size(); i++)
			{
				if (all[i] < eleventh)
				{
					eleventh = all[i];
				}
			};
			vector<double>::iterator it = remove(all.begin(), all.end(), eleventh);
			all.erase(it, all.end());

			bool existsTop = std::find(std::begin(distancesTop), std::end(distancesTop), eleventh) != std::end(distancesTop);
			bool existsBot = std::find(std::begin(distancesBottom), std::end(distancesBottom), eleventh) != std::end(distancesBottom);
			bool existsCrack = std::find(std::begin(distancesCrack), std::end(distancesCrack), eleventh) != std::end(distancesCrack);
			bool existsScratch = std::find(std::begin(distancesScratch), std::end(distancesScratch), eleventh) != std::end(distancesScratch);

			if (existsTop == 1) {
				allks.push_back(0);
			}

			if (existsBot == 1) {
				allks.push_back(1);
			}

			if (existsCrack == 1) {
				allks.push_back(2);
			}

			if (existsScratch == 1) {
				allks.push_back(3);
			}
		};

		int topcount = std::count(allks.begin(), allks.end(), 0);
		int bottomcount = std::count(allks.begin(), allks.end(), 1);
		int crackcount = std::count(allks.begin(), allks.end(), 2);
		int scratchcount = std::count(allks.begin(), allks.end(), 3);

		int top;
		int bottom;
		int crack;
		int scratch;

		top = bottom = crack = scratch = INT_MAX;

		if (topcount > bottomcount && topcount > crackcount && topcount > scratchcount) {
			//cout << "For values " << x << ", " << y << " and " << z << " the green box represents the top of the vial!" << endl;

			for (int i = 0; i < featVec1.size(); i++)
			{
				if (featVec1[i].circularity == circularityVec[o])
				{
					cv::drawContours(ContourIMG, G1contours, featVec1[i].contourIndex, cv::Scalar(0, 255, 0), 1);
					top = featVec1[i].contourIndex;
					vector<cv::Rect> boundtop(featVec1.size());
					for (int i = 0; i < featVec1.size(); i++)
					{
						boundtop[i] = boundingRect(cv::Mat(G1contours[top]));
					}
					for (int i = 0; i < featVec1.size(); i++)
					{
						cv::Scalar green = cv::Scalar(0, 255, 0);
						rectangle(drawingfinal, boundtop[i].tl() + cv::Point(xclass, yclass), boundtop[i].br() + cv::Point(xclass, yclass), green, 1, 8, 0);
						cv::putText(drawingfinal, "Top", cv::Point(boundtop[i].x + xclass, boundtop[i].y + yclass - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0, 255, 0), 1.7);

					}
				}
			}
			check1.push_back(0);
			check2.push_back(0);
		}

		if (bottomcount > topcount && bottomcount > crackcount && bottomcount > scratchcount) {
			//cout << "For values " << x << ", " << y << " and " << z << " the green box represents the bottom of the vial!" << endl;

			for (int i = 0; i < featVec1.size(); i++)
			{
				if (featVec1[i].circularity == circularityVec[o])
				{
					cv::drawContours(ContourIMG, G1contours, featVec1[i].contourIndex, cv::Scalar(0, 255, 0), 1);
					bottom = featVec1[i].contourIndex;
					vector<cv::Rect> boundbottom(featVec1.size());
					for (int i = 0; i < featVec1.size(); i++)
					{
						boundbottom[i] = boundingRect(cv::Mat(G1contours[bottom]));
					}
					for (int i = 0; i < featVec1.size(); i++)
					{
						cv::Scalar green = cv::Scalar(0, 255, 0);
						rectangle(drawingfinal, boundbottom[i].tl() + cv::Point(xclass, yclass), boundbottom[i].br() + cv::Point(xclass, yclass), green, 1, 8, 0);
						cv::putText(drawingfinal, "Bottom", cv::Point(boundbottom[i].x + xclass, boundbottom[i].y + yclass - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0, 255, 0), 1.7);
					}
				}
			}
			check1.push_back(0);
			check2.push_back(0);
		}

		if (crackcount > topcount && crackcount > bottomcount && crackcount > scratchcount) {
			//cout << "For values " << x << ", " << y << " and " << z << " the red box represents a crack on the vial!" << endl;

			for (int i = 0; i < featVec1.size(); i++)
			{
				if (featVec1[i].circularity == circularityVec[o])
				{
					cv::drawContours(ContourIMG, G1contours, featVec1[i].contourIndex, cv::Scalar(0, 255, 0), 1);
					crack = featVec1[i].contourIndex;
					vector<cv::Rect> boundcrack(featVec1.size());
					for (int i = 0; i < featVec1.size(); i++)
					{
						boundcrack[i] = boundingRect(cv::Mat(G1contours[crack]));
					}
					for (int i = 0; i < featVec1.size(); i++)
					{
						cv::Scalar red = cv::Scalar(0, 0, 255);
						rectangle(drawingfinal, boundcrack[i].tl() + cv::Point(xclass, yclass), boundcrack[i].br() + cv::Point(xclass, yclass), red, 1, 8, 0);
						cv::putText(drawingfinal, "Crack", cv::Point(boundcrack[i].x + xclass, boundcrack[i].y + yclass - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(255, 0, 0), 1.7);
					}
				}
			}
			check1.push_back(1);
		}

		if (scratchcount > topcount && scratchcount > bottomcount && scratchcount > crackcount) {
			//cout << "For values " << x << ", " << y << " and " << z << " the red box represents a scratch on the vial!" << endl;

			for (int i = 0; i < featVec1.size(); i++)
			{
				if (featVec1[i].circularity == circularityVec[o])
				{
					cv::drawContours(ContourIMG, G1contours, featVec1[i].contourIndex, cv::Scalar(0, 255, 0), 1);
					scratch = featVec1[i].contourIndex;
					vector<cv::Rect> boundscratch(featVec1.size());
					for (int i = 0; i < featVec1.size(); i++)
					{
						boundscratch[i] = boundingRect(cv::Mat(G1contours[scratch]));
					}
					for (int i = 0; i < featVec1.size(); i++)
					{
						cv::Scalar red = cv::Scalar(0, 0, 255);
						rectangle(drawingfinal, boundscratch[i].tl() + cv::Point(xclass, yclass), boundscratch[i].br() + cv::Point(xclass, yclass), red, 1, 8, 0);
						cv::putText(drawingfinal, "Scratch", cv::Point(boundscratch[i].x + xclass, boundscratch[i].y + yclass - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(255, 0, 0), 1.7);
					}
				}
			}
			check2.push_back(1);
		}

		everything = rotated + drawingfinal;
	}

	count.push_back(1);

	if (count.size() > 3) {
		check();
		check1.clear();
		check2.clear();
		count.clear();
	}

	imshow("Final Result", everything);
	cv::waitKey(0);
	cv::destroyAllWindows;
	featVec1.clear();
	system("CLS");
}

void inspectVial::alldata(cv::Mat vial) {
	rotatefunc(vial);
	roifunc(rotated);
	inspection(vial);
	classify(vial);
}

void inspectVial::check() {
	bool exist1 = std::find(std::begin(check1), std::end(check1), 1) != std::end(check1);
	bool exist2 = std::find(std::begin(check2), std::end(check2), 1) != std::end(check2);
		if (exist1 == 1 || exist2 == 1) {
			cout << "This is a bad vial" << endl;
		}
		if (exist1 == 0 && exist2 == 0) {
			cout << "This is a good vial" << endl;
		}
}