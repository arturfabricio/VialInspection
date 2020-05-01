#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include "Vials.h"
#include <fstream>
#include <sstream>
#include<string>

//using namespace cv;
using namespace std;

void collectData::alldata(cv::Mat vial) {
	
	///////////////////////////////////////////////////
	/////////ROTATION//////////////////////////////////
	///////////////////////////////////////////////////

	if (vial.empty()) cout << "Failed loading image" << endl;		
	else cout << "Image Loaded succesfully" << endl;

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
		index = max_element(angles.begin(), angles.end())-angles.begin();
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

	///////////////////////////////////////////////////
	/////////COUNTOUR/BOUNDING BOX/////////////////////
	///////////////////////////////////////////////////

	//Morphology for the top-bounding box.
	cv::Mat rotated_Grey = cv::Mat(rotated.size(), CV_8U);
	cv::Mat rotated_Thresh1 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat rotated_Thresh2 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat rotated_background = cv::Mat(rotated.size(), CV_8UC3);
	cv::Mat rotated_subt = cv::Mat(rotated.size(), CV_8UC3);

	cvtColor(rotated, rotated_Grey, cv::COLOR_BGR2GRAY);
	medianBlur(rotated_Grey, rotated_background, 7);								
	threshold(rotated_background, rotated_Thresh1, 24, 255, cv::THRESH_BINARY_INV);
	threshold(rotated_background, rotated_Thresh2, 46, 255, cv::THRESH_BINARY);
	subtract(rotated_Thresh2, rotated_Thresh1, rotated_subt);

	cv::Mat rotated_morph1 = cv::Mat(rotated.size(), CV_8U);
	cv::Mat ElemDilateRotated = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 9));
	cv::morphologyEx(rotated_subt, rotated_morph1, cv::MORPH_DILATE, ElemDilateRotated);

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
	imshow("Contour", Contour);
	cv::waitKey(0);
	cv::destroyAllWindows;

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
	imshow("Contour2", Contour2);
	cv::waitKey(0);
	cv::destroyAllWindows;

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
		if (VecBot[i][1] > 19 && VecBot[i][1] < 300) {
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
		G.h = y2 - y1 + h - 22;
	};

	
    //Defining Region Of Interest (ROI):
	cv::Rect ROI = cv::Rect(G.x, G.y, G.w, G.h);
	cv::Mat vial_ROI = rotated(ROI);
	cv::Mat Grayscale = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat vial_Contrast = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat vial_Subt = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat vial_Thresh = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat Contour1 = cv::Mat(vial_ROI.size(), CV_8U, cv::Scalar(255, 255, 255));

	for (int x = 0; x < vial_ROI.cols; x++) {
		for (int y = 0; y < vial_ROI.rows; y++) {
			for (int c = 0; c < 3; c++) {
				float alpha = 1.15;
				float beta = 150;
				int E = vial_ROI.at<cv::Vec3b>(cv::Point(x, y))[c];
				vial_Contrast.at<uchar>(cv::Point(x, y)) = alpha * E + beta;
			}
		}
	}

	///////////////////////////////////////////////////
	/////////CRACK DETECTION PART//////////////////////
	///////////////////////////////////////////////////

	cv::threshold(vial_Contrast, vial_Thresh, 80, 255, cv::THRESH_BINARY_INV);

	cv::Mat vial_morph1 = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat ElemClose = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(21, 21));
	cv::morphologyEx(vial_Thresh, vial_morph1, cv::MORPH_CLOSE, ElemClose);

	cv::Mat vial_morph2 = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat ElemErode1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
	cv::morphologyEx(vial_morph1, vial_morph2, cv::MORPH_ERODE, ElemErode1);

	vector<vector<cv::Point>> G1contours;
	vector<cv::Vec4i> hierarchy1;

	cv::Mat GContour1 = cv::Mat(vial_ROI.size(), CV_8U);
	cv::Mat ContourIMG1 = cv::Mat(vial_ROI.size(), CV_8U);
	cv::findContours(vial_morph2, G1contours, hierarchy1, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	cv::drawContours(GContour1, G1contours, -1, cv::Scalar(0, 0, 0), 1);

	vector<Vialfeatures> featVec1;
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
	*/
	imshow("Top Contour", drawing);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Bot Contour", drawing1);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("ROI Image", vial_ROI);
	cv::waitKey(0);
	cv::destroyAllWindows;
	/*
	imshow("Adjust Contrast and Brightness", vial_Contrast);
	waitKey(0);
	destroyAllWindows;
	imshow("Threshold", vial_Thresh);
	waitKey(0);
	destroyAllWindows;
	imshow("Opening", vial_morph1);
	waitKey(0);
	destroyAllWindows;
	imshow("Erode", vial_morph2);
	cv::waitKey(0);
	cv::destroyAllWindows;
	imshow("Contours", Contour);
    waitKey(0);
	destroyAllWindows;
	imshow("Contours IMG", ContourIMG);
	waitKey(0);
	destroyAllWindows;
	*/
	imshow("Contours1", GContour1);
	cv::waitKey(0);
	cv::destroyAllWindows;

	//imshow("Contours IMG1", ContourIMG1);
	//waitKey(0);
	//destroyAllWindows;
}

cv::Mat collectData::rotate(cv::Mat src, double angle) {
	cv::Mat dst;
	cv::Point2f pt(src.cols / 2., src.rows / 2.);
	cv::Mat r = getRotationMatrix2D(pt, angle, 1.0);
		warpAffine(src, dst, r, cv::Size(src.cols, src.rows));
		return dst;
}

void inspectVial::classify(cv::Mat vial) {

};

/*
void inspectVial::loadData() {
	std::ifstream in("tbd");
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			//The area was devided by the perimeter, yielding a new feature: ratio.
			//This data is stored in the array euro;
			in >> euro[i][j];
		}
		//Here the data is normalized, since the circularity value varies between
		//0.7 and 1, and the ratio between 25-50.
		double value = euro[i][1] / 45;
		euro[i][1] = value;
		double value2 = ((euro[i][0] - 0.827443) / (0.900933 - 0.827443));
		euro[i][0] = value2;
	}
	//The same logic is applied to the other loadData functions, just for the kroner and the pence.
}
};*/
