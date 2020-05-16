//Vial and Crack Detection Algoryhtm - Group 464 ROB4
//V5.0 - 09/05/2020

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

void inspectVial::alldata(cv::Mat vial) {

	///////////////////////////////////////////////////
	/////////ROTATION//////////////////////////////////
	///////////////////////////////////////////////////

	if (vial.empty()) cout << "Failed loading image" << endl;
	else cout << "Image Loaded succesfully" << endl;

	cv::Mat grey, cadst, cadst1, cdst, cdst2, cadstth = cv::Mat(vial.size(), CV_8U);

	cvtColor(vial, grey, cv::COLOR_BGR2GRAY);

	threshold(grey, cadst1, 20, 200, 1);

	Canny(grey, cadst, 1, 255);
	//cv::imshow("cadst", cadst);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cvtColor(grey, cdst, cv::COLOR_GRAY2BGR);

	vector<cv::Vec2f> lines;
	vector<float> angles;
	vector<int> rhovec;
	vector<int> rhos;
	HoughLines(cadst, lines, 1, CV_PI / 180, 100, 0, 0);

	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		//cout << rho << "  " << theta << endl;							
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
		angles.push_back(lines[i][1]);
		rhovec.push_back(lines[i][0]);
	}

	//cv::imshow("cdst", cdst);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	float angle;
	float anglemax;
	float anglemin;
	float slope;
	int anglemaxindex;
	int angleminindex;
	int index = INT_MAX;
	angle = INT_MAX;
	anglemin = *min_element(angles.begin(), angles.end());
	//cout << "Smallest angle " << anglemin << endl;
	angleminindex = min_element(angles.begin(), angles.end()) - angles.begin();
	anglemax = *max_element(angles.begin(), angles.end());
	//cout << "Biggest angle " << anglemax << endl;
	anglemaxindex = max_element(angles.begin(), angles.end()) - angles.begin();

	if (anglemin == 0 && anglemax < 3.2) {
		angle = 0;
		index = anglemaxindex;
		slope = angle;
	}

	if (anglemax > 3.2) {
		angle = anglemax;
		anglemin = 3.2;
		index = anglemaxindex;
		slope = angle;
	}

	if (angle >= 2) {
		angle = *max_element(angles.begin(), angles.end());
		index = max_element(angles.begin(), angles.end()) - angles.begin();
		slope = angle;
		angle = angle + 3.14159265;
	};

	if (anglemin < 3.2) {
		angle = anglemin;
		index = angleminindex;
		slope = angle;
	}

	if (angle == 0) {
		vector<float>::iterator it = remove(angles.begin(), angles.end(), angle);
	    angles.erase(it, angles.end());
		angle = *min_element(angles.begin(), angles.end());
		slope = angle;
	};

	if (angle > 0.70 && angle < 2) {
		angle = 0.0;
		slope = angle;
	}

	//cout << "Rotation angle " << angle << endl;

	float degrees = angle * (180.0 / 3.141592653589793238463);
	cv::Mat rotated;
	rotated = rotate(vial, degrees);

	///////////////////////////////////////////////////
	/////////COUNTOUR/BOUNDING BOX/////////////////////
	///////////////////////////////////////////////////

	//Morphology for the top-bounding box.
	cv::Mat rotated_Grey = cv::Mat(rotated.size(), CV_8U);
	cv::Mat rotated_Thresh2 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat rotated_background = cv::Mat(rotated.size(), CV_8UC3);

	cvtColor(rotated, rotated_Grey, cv::COLOR_BGR2GRAY);
	//imshow("rotated_Grey", rotated_Grey);

	medianBlur(rotated_Grey, rotated_background, 7);
	//imshow("rotated_background", rotated_background);

	threshold(rotated_background, rotated_Thresh2, 65, 255, cv::THRESH_BINARY); //46
	//imshow("rotated_Thresh2", rotated_Thresh2);

	cv::Mat rotated_morph1 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat ElemDilateRotated = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));
	cv::morphologyEx(rotated_Thresh2, rotated_morph1, cv::MORPH_DILATE, ElemDilateRotated);

	cv::Rect ROI_Morph = cv::Rect(140, 59, 365, 222); //113, 31, 422, 174

	cv::Mat contour_ROI = rotated_morph1(ROI_Morph);
	//cv::imshow("contour_ROI", contour_ROI);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::Mat Contour = cv::Mat(contour_ROI.size(), CV_8U);
	cv::Mat ContourBig = cv::Mat(rotated.size(), CV_8U);
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

	cv::Mat ContourIMG = cv::Mat(rotated.size(), CV_8U, cv::Scalar(255, 255, 255));
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
	cv::Mat drawing = cv::Mat::zeros(rotated.size(), CV_8UC3);

	int y1 = INT_MAX;
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
	}

	//Morphology for the bottom-bounding box.
	cv::Mat cadstmorph1 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat cElemOpen = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
	cv::morphologyEx(cadst1, cadstmorph1, cv::MORPH_OPEN, cElemOpen);

	cv::Mat cadstmorph2 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat cElemClose = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(22, 22));
	cv::morphologyEx(cadstmorph1, cadstmorph2, cv::MORPH_CLOSE, cElemClose);

	cv::Mat cadstmorph3 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat cElemErode = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(19, 19));
	cv::morphologyEx(cadstmorph2, cadstmorph3, cv::MORPH_ERODE, cElemErode);

	cv::Rect ROI_Morph2 = cv::Rect(188, 305, 259, 85); //155, 317, 315, 132
	cv::Mat contour_ROI2 = cadstmorph3(ROI_Morph2);
	//cv::imshow("contour_ROI2", contour_ROI2);
	//cv::waitKey(0);
	//cv::destroyAllWindows;

	cv::Mat Contour2 = cv::Mat(contour_ROI2.size(), CV_8U);
	cv::Mat ContourBig2 = cv::Mat(rotated.size(), CV_8U);
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

	cv::Mat ContourIMGBot = cv::Mat(rotated.size(), CV_8U, cv::Scalar(255, 255, 255));
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

	cv::Mat drawing1 = cv::Mat::zeros(rotated.size(), CV_8UC3);

	int y2 = INT_MAX;
	int h = INT_MAX;

	for (int i = 0; i < featVecBot.size(); i++)
	{
		cv::Scalar color1 = cv::Scalar(75, 150, 95);
		rectangle(drawing1, boundRectBot[i].tl(), boundRectBot[i].br(), color1, 1, 8, 0);
		y2 = boundRectBot[i].y;
		h = boundRectBot[i].height;
		G.h = y2 - y1 + h - 15;
	};


	//Defining Region Of Interest (ROI):
	cv::Rect ROI = cv::Rect(G.x, G.y, G.w, G.h);
	cv::Mat vial_ROI = rotated(ROI);

	cv::Mat Grayscale = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat vial_Contrast = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat vial_Subt = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat vial_Thresh = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat Contour1 = cv::Mat(vial_ROI.size(), CV_8U, cv::Scalar(255, 255, 255));

	cv::Mat medianBlur = cv::Mat(vial_ROI.size(), CV_8U);
	cv::medianBlur(vial_ROI, medianBlur, 3);

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

	///////////////////////////////////////////////////
	/////////CRACK DETECTION PART//////////////////////
	///////////////////////////////////////////////////

	cv::threshold(vial_Contrast, vial_Thresh, 80, 255, cv::THRESH_BINARY_INV);

	cv::Mat vial_morph1 = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat ElemClose = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(23, 23));
	cv::morphologyEx(vial_Thresh, vial_morph1, cv::MORPH_CLOSE, ElemClose);

	cv::Mat vial_morph2 = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat ElemErode1 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2));
	cv::morphologyEx(vial_morph1, vial_morph2, cv::MORPH_ERODE, ElemErode1);
	vector<cv::Vec4i> hierarchy1;


	cv::Mat GContour1 = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat ContourIMG1 = cv::Mat(vial_ROI.size(), CV_8U);
	cv::findContours(vial_morph2, G1contours, hierarchy1, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	cv::drawContours(GContour1, G1contours, -1, cv::Scalar(0, 0, 0), 1);

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

			cout << "G1.Area:" << G1.area << "; G1.Perimeter:" << G1.perimeter << "; G1.Circularity:" << G1.circularity << "; G1.Cracks:" << G1.hasCrack << "; G1.Elongation:" << G1.elongation << endl;
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
	waitKey(0);
	destroyAllWindows;
	imshow("detected lines", cadst);
	waitKey(0);
	destroyAllWindows;
	imshow("DST", cdst);
	waitKey(0);
	destroyAllWindows;
	imshow("Rotated", rotated);
	waitKey(0);
	destroyAllWindows;
	waitKey(0);
	destroyAllWindows;
	imshow("Vial Rotated Background", rotated_background);
	waitKey(0);
	destroyAllWindows;
	imshow("Vial Rotated Thresh1", rotated_Thresh1);
	waitKey(0);
	destroyAllWindows;
	imshow("Vial Rotated Thresh2", rotated_Thresh2);
	waitKey(0);
	destroyAllWindows;
	imshow("Vial Rotated Subtraction", rotated_subt);
	waitKey(0);
	destroyAllWindows;
	imshow("Vial Rotated Morph", rotated_morph1);
	waitKey(0);
	destroyAllWindows;
	imshow("Region of interest", contour_ROI);
	waitKey(0);
	destroyAllWindows;
	imshow("Region of interest BIG", ContourBig);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Region of interest 2", contour_ROI2);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("c2", Contour2);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Region of interest BIG22", ContourBig2);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("cadstmorph2", cadstmorph1);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("cadstmorph2", cadstmorph2);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("contour_ROI2", contour_ROI2);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("ContourBig2", ContourBig2);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Contour 1", Contour);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Contour 2", Contour2);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Top Contour", drawing);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Bot Contour", drawing1);
	cv::waitKey(0);
	cv::destroyAllWindows;
	*/
	imshow("ROI Image", vial_ROI);
	cv::waitKey(0);
	cv::destroyAllWindows;
	/*
	imwrite("C:\\Users\\artur\\Desktop\\vial_ROI.jpg", vial_ROI);
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
	imshow("Contours", Contour);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Contours IMG", ContourIMG);
	cv::waitKey(0);
	cv::destroyAllWindows;
		*/
	imshow("Contours1", GContour1);
	cv::waitKey(0);
	cv::destroyAllWindows;
		//imshow("Contours IMG1", ContourIMG1);
		//waitKey(0);
		//destroyAllWindows;

}

void inspectVial::classify(cv::Mat vial) {

	cv::Mat grey, cadst, cdst, cadstth = cv::Mat(vial.size(), CV_8U);

	cvtColor(vial, grey, cv::COLOR_BGR2GRAY);
	threshold(grey, cadst, 20, 200, 1);
	cvtColor(grey, cdst, cv::COLOR_GRAY2BGR);
	//Canny(vial, cdst, 20, 255, 3);	

	vector<cv::Vec2f> lines;
	vector<float> angles;
	vector<int> rhovec;
	vector<int> rhos;
	HoughLines(cadst, lines, 1, CV_PI / 180, 100, 0, 0);

	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		//cout << rho << "  " << theta << endl;							
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		//line(cdst, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);
		angles.push_back(lines[i][1]);
		rhovec.push_back(lines[i][0]);
	}

	float angle;
	float anglemax;
	float anglemin;
	float slope;
	int anglemaxindex;
	int angleminindex;
	int index = INT_MAX;
	angle = INT_MAX;
	anglemin = *min_element(angles.begin(), angles.end());
	angleminindex = min_element(angles.begin(), angles.end()) - angles.begin();
	anglemax = *max_element(angles.begin(), angles.end());
	anglemaxindex = max_element(angles.begin(), angles.end()) - angles.begin();

	if (anglemax > 3) {
		angle = anglemax;
		anglemin = 3.1;
		index = anglemaxindex;
		slope = angle;
	}

	if (angle >= 2) {
		angle = *max_element(angles.begin(), angles.end());
		index = max_element(angles.begin(), angles.end()) - angles.begin();
		slope = angle;
		angle = angle + 3.14159265;
	};

	if (anglemin < 3) {
		angle = anglemin;
		index = angleminindex;
		slope = angle;
	}

	if (angle == 0) {
		vector<float>::iterator it = remove(angles.begin(), angles.end(), angle);
		angles.erase(it, angles.end());
		angle = *min_element(angles.begin(), angles.end());
		slope = angle;
	};

	if (angle > 0.70 && angle < 2) {
		angle = 0.0;
		slope = angle;
	}

	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i][1] == slope) {
			rhos.push_back(lines[i][0]);
		}
	}

	vector<int> pos;
	vector<int> neg;
	vector<int> good;
	vector<int> rhos_final;

	for (int i = 0; i < rhos.size(); i++) {
		if (rhos[i] > -320) {
			pos.push_back(rhos[i]);
		}
		if (rhos[i] < -320) {
			neg.push_back(rhos[i]);
		}
	}

	int rhoplus = *min_element(pos.begin(), pos.end());
	int rhonegative = *max_element(neg.begin(), neg.end());

	rhos_final.push_back(rhoplus);
	rhos_final.push_back(rhonegative);

	for (int i = 0; i < rhos_final.size(); i++)
	{
		cv::Point pt1, pt2;
		double a = cos(slope), b = sin(slope);
		double x0 = a * rhos_final[i], y0 = b * rhos_final[i];
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
	}

	float degrees = angle * (180.0 / 3.141592653589793238463);
	cv::Mat rotated;
	rotated = rotate(vial, degrees);

	cv::Mat everything = cv::Mat(rotated.size(), CV_8UC3);
	cv::Mat drawingfinal = cv::Mat::zeros(rotated.size(), CV_8UC3);

	//Morphology for the top-bounding box.
	cv::Mat rotated_Grey = cv::Mat(rotated.size(), CV_8U);
	cv::Mat rotated_Thresh1 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat rotated_Thresh2 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat rotated_background = cv::Mat(rotated.size(), CV_8UC3);
	cv::Mat rotated_subt = cv::Mat(rotated.size(), CV_8UC3);

	cvtColor(rotated, rotated_Grey, cv::COLOR_BGR2GRAY);
	medianBlur(rotated_Grey, rotated_background, 7);
	threshold(rotated_background, rotated_Thresh2, 50, 255, cv::THRESH_BINARY);

	cv::Mat rotated_morph1 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat ElemDilateRotated = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 9));
	cv::morphologyEx(rotated_Thresh2, rotated_morph1, cv::MORPH_DILATE, ElemDilateRotated);

	cv::Rect ROI_Morph = cv::Rect(140, 59, 365, 222); //113, 31, 422, 174
	cv::Mat contour_ROI = rotated_morph1(ROI_Morph);
	cv::Mat Contour = cv::Mat(contour_ROI.size(), CV_8U);
	cv::Mat ContourBig = cv::Mat(rotated.size(), CV_8U);
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

			//cout <<"solve this "<< "G.Area:" << G.area << "; G.Perimeter:" << G.perimeter << "; G.Circularity:" << G.circularity << "; G.Cracks:" << G.hasCrack << "; G.Elongation:" << G.elongation << endl;

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

			//cout << "G.Area:" << G.area << "; G.Perimeter:" << G.perimeter << "; G.Circularity:" << G.circularity << "; G.Cracks:" << G.hasCrack << "; G.Elongation:" << G.elongation << endl;

			featVecTop.push_back(G);
		}
	}

	cv::Mat ContourIMG = cv::Mat(rotated.size(), CV_8U, cv::Scalar(255, 255, 255));
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
	cv::Mat drawing = cv::Mat::zeros(rotated.size(), CV_8UC3);

	int y1 = INT_MAX;
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
	}

	//Morphology for the bottom-bounding box.
	cv::Mat cadstmorph1 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat cElemOpen = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
	cv::morphologyEx(cadst, cadstmorph1, cv::MORPH_OPEN, cElemOpen);

	cv::Mat cadstmorph2 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat cElemClose = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(22, 22));
	cv::morphologyEx(cadstmorph1, cadstmorph2, cv::MORPH_CLOSE, cElemClose);

	cv::Mat cadstmorph3 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat cElemErode = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(19, 19));
	cv::morphologyEx(cadstmorph2, cadstmorph3, cv::MORPH_ERODE, cElemErode);

	cv::Rect ROI_Morph2 = cv::Rect(188, 305, 259, 85); //155, 317, 315, 132
	cv::Mat contour_ROI2 = cadstmorph3(ROI_Morph2);
	cv::Mat Contour2 = cv::Mat(contour_ROI2.size(), CV_8U);
	cv::Mat ContourBig2 = cv::Mat(rotated.size(), CV_8U);
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

			//cout << "Circularity Aquisition" << "G.Area:" << F.area << "; G.Perimeter:" << F.perimeter << "; G.Circularity:" << F.circularity << "; G.Cracks:" << F.hasCrack << "; G.Elongation:" << F.elongation << endl;

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

			//cout << "Bot " << "G.Area:" << F.area << "; G.Perimeter:" << F.perimeter << "; G.Circularity:" << F.circularity << "; G.Cracks:" << F.hasCrack << "; G.Elongation:" << F.elongation << endl;

			featVecBot.push_back(F);
		}
	}

	cv::Mat ContourIMGBot = cv::Mat(rotated.size(), CV_8U, cv::Scalar(255, 255, 255));
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

	cv::Mat drawing1 = cv::Mat::zeros(rotated.size(), CV_8UC3);

	int y2 = INT_MAX;
	int h = INT_MAX;

	for (int i = 0; i < featVecBot.size(); i++)
	{
		cv::Scalar color1 = cv::Scalar(75, 150, 95);
		rectangle(drawing1, boundRectBot[i].tl(), boundRectBot[i].br(), color1, 1, 8, 0);
		y2 = boundRectBot[i].y;
		h = boundRectBot[i].height;
		G.h = y2 - y1 + h - 15;
	};

	//Defining Region Of Interest (ROI):
	cv::Rect ROI = cv::Rect(G.x, G.y, G.w, G.h);
	cv::Mat vial_ROI = rotated(ROI);

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
		double x = (x1 - 0.105263158) / (10.23316062 - 0.105263158);

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

		for (int i = 0; i < 129; i++) {
			double dist;
			dist = sqrt(((x - top[i][0]) * (x - top[i][0])) + ((y - top[i][1]) * (y - top[i][1])) + ((z - top[i][2]) * (z - top[i][2])));
			all.push_back(dist);
			distancesTop.push_back(dist);
		};

		for (int i = 0; i < 230; i++) {
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

		for (int i = 0; i < 49; i++) {
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
						//rectangle(drawingfinal, boundtop[i].tl() + cv::Point(G.x, G.y), boundtop[i].br() + cv::Point(G.x, G.y), green, 1, 8, 0);
						//cv::putText(drawingfinal, "Top", cv::Point(boundtop[i].x + G.x, boundtop[i].y + G.y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0, 255, 0), 1.7);

					}
				}
			}
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
						//rectangle(drawingfinal, boundbottom[i].tl() + cv::Point(G.x, G.y), boundbottom[i].br() + cv::Point(G.x, G.y), green, 1, 8, 0);
						//cv::putText(drawingfinal, "Bottom", cv::Point(boundbottom[i].x + G.x, boundbottom[i].y + G.y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0, 255, 0), 1.7);
					}
				}
			}
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
						rectangle(drawingfinal, boundcrack[i].tl() + cv::Point(G.x, G.y), boundcrack[i].br() + cv::Point(G.x, G.y), red, 1, 8, 0);
						cv::putText(drawingfinal, "Crack", cv::Point(boundcrack[i].x + G.x, boundcrack[i].y + G.y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(255, 0, 0), 1.7);
					}
				}
			}
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
						rectangle(drawingfinal, boundscratch[i].tl() + cv::Point(G.x, G.y), boundscratch[i].br() + cv::Point(G.x, G.y), red, 1, 8, 0);
						cv::putText(drawingfinal, "Scratch", cv::Point(boundscratch[i].x + G.x, boundscratch[i].y + G.y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(255, 0, 0), 1.7);
					}
				}
			}
		}

		everything = rotated + drawingfinal;
	}
	imshow("Final Result", everything);
	cv::waitKey(0);
	cv::destroyAllWindows;
	featVec1.clear();
	system("CLS");
}

void inspectVial::loadDataTop() {
	std::ifstream in("datatop.txt");
	int numRows = 129;
	int numCols = 4;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			in >> topinit[i][j];
		}
	}

	for (int i = 0; i < numRows; i++) {
		float value = topinit[i][0] / topinit[i][1];
		double ratio = (value - 0.105263158) / (10.23316062 - 0.105263158);
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
	int numRows = 230;
	int numCols = 4;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			in >> bottominit[i][j];
		}
	}

	for (int i = 0; i < numRows; i++) {
		float value = bottominit[i][0] / bottominit[i][1];
		double ratio = (value - 0.105263158) / (10.23316062 - 0.105263158);
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
		double ratio = (value - 0.105263158) / (10.23316062 - 0.105263158);
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
	int numRows = 49;
	int numCols = 4;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			in >> scratchinit[i][j];
		}
	}

	for (int i = 0; i < numRows; i++) {
		float value = scratchinit[i][0] / scratchinit[i][1];
		double ratio = (value - 0.105263158) / (10.23316062 - 0.105263158);
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