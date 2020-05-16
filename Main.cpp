//Vial and Crack Detection Algoryhtm - Group 464 ROB4
//V5.0 - 09/05/2020

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <math.h>
#include <cmath>
#include "Vials.h"

using namespace cv;
using namespace std;

/*
cv::Mat test1 = cv::imread("C:\\Users\\artur\\Desktop\\Test\\9_2.png");
cv::Mat test2 = cv::imread("C:\\Users\\artur\\Desktop\\Test\\41_Color.png");
cv::Mat test3 = cv::imread("C:\\Users\\artur\\Desktop\\Test\\113_Color.png");
cv::Mat test4 = cv::imread("C:\\Users\\artur\\Desktop\\Test\\149_Color.png");
cv::Mat test5 = cv::imread("C:\\Users\\artur\\Desktop\\Test\\163_Color.png");
cv::Mat test6 = cv::imread("C:\\Users\\artur\\Desktop\\Test\\4_Color.png");
cv::Mat test7 = cv::imread("C:\\Users\\artur\\Desktop\\Test\\24_Color.png");
cv::Mat test8 = cv::imread("C:\\Users\\artur\\Desktop\\Test\\46_Color.png");
cv::Mat test9 = cv::imread("C:\\Users\\artur\\Desktop\\Test\\134_Color.png");
*/

//Vial 1 
cv::Mat vial1_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\1_Color.png");
cv::Mat vial1_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\2_Color.png");
cv::Mat vial1_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\3_Color.png");
cv::Mat vial1_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\4_Color.png");

//Vial 2
cv::Mat vial2_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\5_Color.png");
cv::Mat vial2_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\6_Color.png");
cv::Mat vial2_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\7_Color.png");
cv::Mat vial2_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\8_Color.png");

//Vial 3
cv::Mat vial3_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\9_Color.png");
cv::Mat vial3_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\10_Color.png");
cv::Mat vial3_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\11_Color.png");
cv::Mat vial3_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\12_Color.png");

//Vial 4
cv::Mat vial4_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\13_Color.png");
cv::Mat vial4_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\14_Color.png");
cv::Mat vial4_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\15_Color.png");
cv::Mat vial4_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\16_Color.png");

//Vial 5
cv::Mat vial5_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\17_Color.png");
cv::Mat vial5_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\18_Color.png");
cv::Mat vial5_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\19_Color.png");
cv::Mat vial5_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\20_Color.png");

//Vial 6
cv::Mat vial6_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\21_Color.png");
cv::Mat vial6_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\22_Color.png");
cv::Mat vial6_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\23_Color.png");
cv::Mat vial6_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\24_Color.png");

//Vial 7
cv::Mat vial7_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\25_Color.png");
cv::Mat vial7_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\26_Color.png");
cv::Mat vial7_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\27_Color.png");
cv::Mat vial7_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\28_Color.png");

//Vial 8
cv::Mat vial8_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\29_Color.png");
cv::Mat vial8_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\30_Color.png");
cv::Mat vial8_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\31_Color.png");
cv::Mat vial8_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\32_Color.png");

//Vial 9
cv::Mat vial9_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\33_Color.png");
cv::Mat vial9_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\34_Color.png");
cv::Mat vial9_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\35_Color.png");
cv::Mat vial9_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\36_Color.png");

//Vial 10
cv::Mat vial10_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\37_Color.png");
cv::Mat vial10_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\38_Color.png");
cv::Mat vial10_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\39_Color.png");
cv::Mat vial10_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\40_Color.png");

//Vial 11
cv::Mat vial11_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\41_Color.png");
cv::Mat vial11_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\42_Color.png");
cv::Mat vial11_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\43_Color.png");
cv::Mat vial11_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\44_Color.png");

//Vial 12
cv::Mat vial12_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\45_Color.png");
cv::Mat vial12_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\46_Color.png");
cv::Mat vial12_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\47_Color.png");
cv::Mat vial12_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\48_Color.png");

//Vial 13
cv::Mat vial13_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\49_Color.png");
cv::Mat vial13_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\50_Color.png");
cv::Mat vial13_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\51_Color.png");
cv::Mat vial13_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\52_Color.png");

//Vial 14
cv::Mat vial14_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\53_Color.png");
cv::Mat vial14_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\54_Color.png");
cv::Mat vial14_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\55_Color.png");
cv::Mat vial14_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\56_Color.png");

//Vial 15
cv::Mat vial15_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\57_Color.png");
cv::Mat vial15_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\58_Color.png");
cv::Mat vial15_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\59_Color.png");
cv::Mat vial15_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\60_Color.png");

//Vial 16
cv::Mat vial16_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\61_Color.png");
cv::Mat vial16_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\62_Color.png");
cv::Mat vial16_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\63_Color.png");
cv::Mat vial16_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\64_Color.png");

//Vial 17
cv::Mat vial17_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\65_Color.png");
cv::Mat vial17_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\66_Color.png");
cv::Mat vial17_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\67_Color.png");
cv::Mat vial17_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\68_Color.png");

//Vial 18
cv::Mat vial18_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\69_Color.png");
cv::Mat vial18_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\70_Color.png");
cv::Mat vial18_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\71_Color.png");
cv::Mat vial18_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\72_Color.png");

//Vial 19
cv::Mat vial19_1 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\75_Color.png");
cv::Mat vial19_2 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\76_Color.png");
cv::Mat vial19_3 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\76_Color.png");
cv::Mat vial19_4 = cv::imread("C:\\Users\\artur\\Desktop\\TestData\\76_Color.png");

void main()
{
	inspectVial data;


	data.loadDataTop();
	data.loadDataBottom();
	data.loadDataCrack();
	data.loadDataScratch();


	cout << "Vial Number 1" << endl;
	data.alldata(vial1_1);
	data.classify(vial1_1);
	data.alldata(vial1_2);
	data.classify(vial1_2);
	data.alldata(vial1_3);
	data.classify(vial1_3);
	data.alldata(vial1_4);
	data.classify(vial1_4);

	/*
	cout << "Vial Number 2" << endl;
	data.alldata(vial2_1);
	data.classify(vial2_1);
	data.alldata(vial2_2);
	data.classify(vial2_2);
	data.alldata(vial2_3);
	data.classify(vial2_3);
	data.alldata(vial2_4);
	data.classify(vial2_4);

	cout << "Vial Number 3" << endl;
	data.alldata(vial3_1);
	data.classify(vial3_1);
	data.alldata(vial3_2);
	data.classify(vial3_2);
	data.alldata(vial3_3);
	data.classify(vial3_3);
	data.alldata(vial3_4);
	data.classify(vial3_4);

	cout << "Vial Number 4" << endl;
	data.alldata(vial4_1);
	data.classify(vial4_1);
	data.alldata(vial4_2);
	data.classify(vial4_2);
	data.alldata(vial4_3);
	data.classify(vial4_3);
	data.alldata(vial4_4);
	data.classify(vial4_4);

	cout << "Vial Number 5" << endl;
	data.alldata(vial5_1);
	data.classify(vial5_1);
	data.alldata(vial5_2);
	data.classify(vial5_2);
	data.alldata(vial5_3);
	data.classify(vial5_3);
	data.alldata(vial5_4);
	data.classify(vial5_4);

	cout << "Vial Number 6" << endl;
	data.alldata(vial6_1);
	data.classify(vial6_1);
	data.alldata(vial6_2);
	data.classify(vial6_2);
	data.alldata(vial6_3);
	data.classify(vial6_3);
	data.alldata(vial6_4);
	data.classify(vial6_4);

	cout << "Vial Number 7" << endl;
	data.alldata(vial7_1);
	data.classify(vial7_1);
	data.alldata(vial7_2);
	data.classify(vial7_2);
	data.alldata(vial7_3);
	data.classify(vial7_3);
	data.alldata(vial7_4);
	data.classify(vial7_4);

	cout << "Vial Number 8" << endl;
	data.alldata(vial8_1);
	data.classify(vial8_1);
	data.alldata(vial8_2);
	data.classify(vial8_2);
	data.alldata(vial8_3);
	data.classify(vial8_3);
	data.alldata(vial8_4);
	data.classify(vial8_4);

	cout << "Vial Number 9" << endl;
	data.alldata(vial9_1);
	data.classify(vial9_1);
	data.alldata(vial9_2);
	data.classify(vial9_2);
	data.alldata(vial9_3);
	data.classify(vial9_3);
	data.alldata(vial9_4);
	data.classify(vial9_4);

	cout << "Vial Number 10" << endl;
	data.alldata(vial10_1);
	data.classify(vial10_1);
	data.alldata(vial10_2);
	data.classify(vial10_2);
	data.alldata(vial10_3);
	data.classify(vial10_3);
	data.alldata(vial10_4);
	data.classify(vial10_4);

	cout << "Vial Number 11" << endl;
	data.alldata(vial11_1);
	data.classify(vial11_1);
	data.alldata(vial11_2);
	data.classify(vial11_2);
	data.alldata(vial11_3);
	data.classify(vial11_3);
	data.alldata(vial11_4);
	data.classify(vial11_4);

	cout << "Vial Number 12" << endl;
	data.alldata(vial12_1);
	data.classify(vial12_1);
	data.alldata(vial12_2);
	data.classify(vial12_2);
	data.alldata(vial12_3);
	data.classify(vial12_3);
	data.alldata(vial12_4);
	data.classify(vial12_4);

	cout << "Vial Number 13" << endl;
	data.alldata(vial13_1);
	data.classify(vial13_1);
	data.alldata(vial13_2);
	data.classify(vial13_2);
	data.alldata(vial13_3);
	data.classify(vial13_3);
	data.alldata(vial13_4);
	data.classify(vial13_4);

	cout << "Vial Number 14" << endl;
	data.alldata(vial14_1);
	data.classify(vial14_1);
	data.alldata(vial14_2);
	data.classify(vial14_2);
	data.alldata(vial14_3);
	data.classify(vial14_3);
	data.alldata(vial14_4);
	data.classify(vial14_4);

	cout << "Vial Number 15" << endl;
	data.alldata(vial15_1);
	data.classify(vial15_1);
	data.alldata(vial15_2);
	data.classify(vial15_2);
	data.alldata(vial15_3);
	data.classify(vial15_3);
	data.alldata(vial15_4);
	data.classify(vial15_4);

	cout << "Vial Number 16" << endl;
	data.alldata(vial16_1);
	data.classify(vial16_1);
	data.alldata(vial16_2);
	data.classify(vial16_2);
	data.alldata(vial16_3);
	data.classify(vial16_3);
	data.alldata(vial16_4);
	data.classify(vial16_4);

	cout << "Vial Number 17" << endl;
	data.alldata(vial17_1);
	data.classify(vial17_1);
	data.alldata(vial17_2);
	data.classify(vial17_2);
	data.alldata(vial17_3);
	data.classify(vial17_3);
	data.alldata(vial17_4);
	data.classify(vial17_4);

	cout << "Vial Number 18" << endl;
	data.alldata(vial18_1);
	data.classify(vial18_1);
	data.alldata(vial18_2);
	data.classify(vial18_2);
	data.alldata(vial18_3);
	data.classify(vial18_3);
	data.alldata(vial18_4);
	data.classify(vial18_4);

	cout << "Vial Number 19" << endl;
	data.alldata(vial19_1);
	data.classify(vial19_1);
	data.alldata(vial19_2);
	data.classify(vial19_2);
	data.alldata(vial19_3);
	data.classify(vial19_3);
	data.alldata(vial19_4);
	data.classify(vial19_4);
	*/

	/*
	//data.alldata(test1);
	//data.classify(test1);
	//data.alldata(test2);
	//data.classify(test2);
	//data.alldata(test3);
	//data.classify(test3);
	//data.alldata(test4);
	//data.classify(test4);
	//data.alldata(test5);
	//data.classify(test5);
	//data.alldata(test6);
	//data.classify(test6);
	//data.alldata(test7);
	//data.classify(test7);
	//data.alldata(test8);
	//data.classify(test8);
	//data.alldata(test9);
	//data.classify(test9);

	cout << "Vial 1" << endl;
	data.alldata(data.vial1);
	cout << "Vial 2" << endl;
	data.alldata(data.vial2);
	cout << "Vial 3" << endl;
	data.alldata(data.vial3);
	cout << "Vial 4" << endl;
	data.alldata(data.vial4);
	cout << "Vial 5" << endl;
	data.alldata(data.vial5);
	cout << "Vial 6" << endl;
	data.alldata(data.vial6);
	cout << "Vial 7" << endl;
	data.alldata(data.vial7);
	cout << "Vial 8" << endl;
	data.alldata(data.vial8);
	cout << "Vial 9" << endl;
	data.alldata(data.vial9);
	cout << "Vial 10" << endl;
	data.alldata(data.vial10);
	cout << "Vial 11" << endl;
	data.alldata(data.vial11);
	cout << "Vial 12" << endl;
	data.alldata(data.vial12);
	cout << "Vial 13" << endl;
	data.alldata(data.vial13);
	cout << "Vial 14" << endl;
	data.alldata(data.vial14);
	cout << "Vial 15" << endl;
	data.alldata(data.vial15);
	cout << "Vial 16" << endl;
	data.alldata(data.vial16);
	cout << "Vial 17" << endl;
	data.alldata(data.vial17);
	cout << "Vial 18" << endl;
	data.alldata(data.vial18);
	cout << "Vial 19" << endl;
	data.alldata(data.vial19);
	cout << "Vial 20" << endl;
	data.alldata(data.vial20);
	cout << "Vial 21" << endl;
	data.alldata(data.vial21);
	cout << "Vial 22" << endl;
	data.alldata(data.vial22);
	cout << "Vial 23" << endl;
	data.alldata(data.vial23);
	cout << "Vial 24" << endl;
	data.alldata(data.vial24);
	cout << "Vial 25" << endl;
	data.alldata(data.vial25);
	cout << "Vial 26" << endl;
	data.alldata(data.vial26);
	cout << "Vial 29" << endl;
	data.alldata(data.vial29);
	cout << "Vial 31" << endl;
	data.alldata(data.vial31);
	cout << "Vial 32" << endl;
	data.alldata(data.vial32);
	cout << "Vial 33" << endl;
	data.alldata(data.vial33);
	cout << "Vial 34" << endl;
	data.alldata(data.vial34);
	cout << "Vial 35" << endl;
	data.alldata(data.vial35);
	cout << "Vial 36" << endl;
	data.alldata(data.vial36);
	cout << "Vial 37" << endl;
	data.alldata(data.vial37);
	cout << "Vial 38" << endl;
	data.alldata(data.vial38);
	cout << "Vial 39" << endl;
	data.alldata(data.vial39);
	cout << "Vial 40" << endl;
	data.alldata(data.vial40);
	cout << "Vial 41" << endl;
	data.alldata(data.vial41);
	cout << "Vial 42" << endl;
	data.alldata(data.vial42);
	cout << "Vial 43" << endl;
	data.alldata(data.vial43);
	cout << "Vial 44" << endl;
	data.alldata(data.vial44);
	cout << "Vial 46" << endl;
	data.alldata(data.vial46);
	cout << "Vial 47" << endl;
	data.alldata(data.vial47);
	cout << "Vial 48" << endl;
	cout << "Vial 49" << endl;
	data.alldata(data.vial49);
	cout << "Vial 50" << endl;
	data.alldata(data.vial50);
	cout << "Vial 51" << endl;
	data.alldata(data.vial51);
	cout << "Vial 52" << endl;
	data.alldata(data.vial52);
	cout << "Vial 53" << endl;
	data.alldata(data.vial53);
	cout << "Vial 54" << endl;
	data.alldata(data.vial54);
	cout << "Vial 55" << endl;
	data.alldata(data.vial55);
	cout << "Vial 56" << endl;
	data.alldata(data.vial56);
	//cout << "Vial 57" << endl;
	//data.alldata(data.vial57);
	cout << "Vial 58" << endl;
	data.alldata(data.vial58);
	cout << "Vial 59" << endl;
	data.alldata(data.vial59);
	cout << "Vial 60" << endl;
	data.alldata(data.vial60);
	cout << "Vial 61" << endl;
	data.alldata(data.vial61);
	cout << "Vial 62" << endl;
	data.alldata(data.vial62);
	cout << "Vial 63" << endl;
	data.alldata(data.vial63);
	cout << "Vial 64" << endl;
	data.alldata(data.vial64);
	cout << "Vial 65" << endl;
	data.alldata(data.vial65);
	cout << "Vial 66" << endl;
	data.alldata(data.vial66);
	cout << "Vial 67" << endl;
	data.alldata(data.vial67);
	cout << "Vial 68" << endl;
	data.alldata(data.vial68);
	cout << "Vial 69" << endl;
	data.alldata(data.vial69);
	cout << "Vial 70" << endl;
	data.alldata(data.vial70);
	cout << "Vial 71" << endl;
	data.alldata(data.vial71);
	cout << "Vial 72" << endl;
	data.alldata(data.vial72);
	cout << "Vial 73" << endl;
	data.alldata(data.vial73);
	cout << "Vial 74" << endl;
	data.alldata(data.vial74);
	cout << "Vial 75" << endl;
	data.alldata(data.vial75);
	cout << "Vial 76" << endl;
	data.alldata(data.vial76);
	cout << "Vial 77" << endl;
	data.alldata(data.vial77);
	cout << "Vial 78" << endl;
	data.alldata(data.vial78);
	cout << "Vial 79" << endl;
	data.alldata(data.vial79);
	cout << "Vial 80" << endl;
	data.alldata(data.vial80);
	cout << "Vial 81" << endl;
	data.alldata(data.vial81);
	cout << "Vial 82" << endl;
	data.alldata(data.vial82);
	cout << "Vial 83" << endl;
	data.alldata(data.vial83);
	cout << "Vial 84" << endl;
	data.alldata(data.vial84);
	cout << "Vial 85" << endl;
	data.alldata(data.vial85);
	cout << "Vial 86" << endl;
	data.alldata(data.vial86);
	cout << "Vial 87" << endl;
	data.alldata(data.vial87);
	cout << "Vial 88" << endl;
	data.alldata(data.vial88);
	cout << "Vial 89" << endl;
	data.alldata(data.vial89);
	cout << "Vial 90" << endl;
	data.alldata(data.vial90);
	cout << "Vial 91" << endl;
	data.alldata(data.vial91);
	cout << "Vial 92" << endl;
	data.alldata(data.vial92);
	cout << "Vial 93" << endl;
	data.alldata(data.vial93);
	cout << "Vial 94" << endl;
	data.alldata(data.vial94);
	cout << "Vial 95" << endl;
	data.alldata(data.vial95);
	cout << "Vial 96" << endl;
	data.alldata(data.vial96);
	cout << "Vial 97" << endl;
	data.alldata(data.vial97);
	cout << "Vial 98" << endl;
	data.alldata(data.vial98);
	cout << "Vial 99" << endl;
	data.alldata(data.vial99);
	cout << "Vial 100" << endl;
	data.alldata(data.vial100);
	cout << "Vial 101" << endl;
	data.alldata(data.vial101);
	cout << "Vial 102" << endl;
	data.alldata(data.vial102);
	cout << "Vial 103" << endl;
	data.alldata(data.vial103);
	cout << "Vial 104" << endl;
	data.alldata(data.vial104);
	cout << "Vial 105" << endl;
	data.alldata(data.vial105);
	cout << "Vial 106" << endl;
	data.alldata(data.vial106);
	cout << "Vial 107" << endl;
	data.alldata(data.vial107);
	cout << "Vial 108" << endl;
	data.alldata(data.vial108);
	cout << "Vial 109" << endl;
	data.alldata(data.vial109);
	cout << "Vial 110" << endl;
	data.alldata(data.vial110);
	cout << "Vial 111" << endl;
	data.alldata(data.vial111);
	cout << "Vial 112" << endl;
	data.alldata(data.vial112);
	cout << "Vial 113" << endl;
	data.alldata(data.vial113);
	cout << "Vial 114" << endl;
	data.alldata(data.vial114);
	cout << "Vial 115" << endl;
	data.alldata(data.vial115);
	cout << "Vial 116" << endl;
	data.alldata(data.vial116);
	cout << "Vial 117" << endl;
	data.alldata(data.vial117);
	cout << "Vial 118" << endl;
	data.alldata(data.vial118);
	cout << "Vial 119" << endl;
	data.alldata(data.vial119);
	cout << "Vial 120" << endl;
	data.alldata(data.vial120);
	cout << "Vial 121" << endl;
	data.alldata(data.vial121);
	cout << "Vial 122" << endl;
	data.alldata(data.vial122);
	cout << "Vial 123" << endl;
	data.alldata(data.vial123);
	cout << "Vial 124" << endl;
	data.alldata(data.vial124);
	cout << "Vial 125" << endl;
	data.alldata(data.vial125);
	cout << "Vial 126" << endl;
	data.alldata(data.vial126);
	cout << "Vial 127" << endl;
	data.alldata(data.vial127);
	//cout << "Vial 128" << endl;
	//data.alldata(data.vial128);
	cout << "Vial 129" << endl;
	data.alldata(data.vial129);
	cout << "Vial 130" << endl;
	data.alldata(data.vial130);
	cout << "Vial 131" << endl;
	data.alldata(data.vial131);
	cout << "Vial 132" << endl;
	data.alldata(data.vial132);
	cout << "Vial 133" << endl;
	data.alldata(data.vial133);
	cout << "Vial 134" << endl;
	data.alldata(data.vial134);
	cout << "Vial 135" << endl;
	data.alldata(data.vial135);
	cout << "Vial 136" << endl;
	data.alldata(data.vial136);
	cout << "Vial 137" << endl;
	data.alldata(data.vial137);
	cout << "Vial 138" << endl;
	data.alldata(data.vial138);
	cout << "Vial 139" << endl;
	data.alldata(data.vial139);
	cout << "Vial 140" << endl;
	data.alldata(data.vial140);
	cout << "Vial 141" << endl;
	data.alldata(data.vial141);
	cout << "Vial 142" << endl;
	data.alldata(data.vial142);
	cout << "Vial 143" << endl;
	data.alldata(data.vial143);
	cout << "Vial 144" << endl;
	data.alldata(data.vial144);
	cout << "Vial 145" << endl;
	data.alldata(data.vial145);
	cout << "Vial 146" << endl;
	data.alldata(data.vial146);
	cout << "Vial 147" << endl;
	data.alldata(data.vial147);
	cout << "Vial 148" << endl;
	data.alldata(data.vial148);
	cout << "Vial 149" << endl;
	data.alldata(data.vial149);
	cout << "Vial 150" << endl;
	data.alldata(data.vial150);
	cout << "Vial 151" << endl;
	data.alldata(data.vial151);
	cout << "Vial 152" << endl;
	data.alldata(data.vial152);
	cout << "Vial 153" << endl;
	data.alldata(data.vial153);
	cout << "Vial 154" << endl;
	data.alldata(data.vial154);
	cout << "Vial 155" << endl;
	data.alldata(data.vial155);
	cout << "Vial 156" << endl;
	data.alldata(data.vial156);
	cout << "Vial 157" << endl;
	data.alldata(data.vial157);
	cout << "Vial 158" << endl;
	data.alldata(data.vial158);
	cout << "Vial 159" << endl;
	data.alldata(data.vial159);
	cout << "Vial 160" << endl;
	data.alldata(data.vial160);
	cout << "Vial 161" << endl;
	data.alldata(data.vial161);
	cout << "Vial 162" << endl;
	data.alldata(data.vial162);
	cout << "Vial 163" << endl;
	data.alldata(data.vial163);
	cout << "Vial 164" << endl;
	data.alldata(data.vial164);
	cout << "Vial 165" << endl;
	data.alldata(data.vial165);
	cout << "Vial 166" << endl;
	data.alldata(data.vial166);
	cout << "Vial 167" << endl;
	data.alldata(data.vial167);
	cout << "Vial 168" << endl;
	data.alldata(data.vial168);
	cout << "Vial 169" << endl;
	data.alldata(data.vial169);
	cout << "Vial 170" << endl;
	data.alldata(data.vial170);
	cout << "Vial 171" << endl;
	data.alldata(data.vial171);
	cout << "Vial 172" << endl;
	data.alldata(data.vial172);
	cout << "Vial 173" << endl;
	data.alldata(data.vial173);
	cout << "Vial 174" << endl;
	data.alldata(data.vial174);
	cout << "Vial 175" << endl;
	data.alldata(data.vial175);
	cout << "Vial 176" << endl;
	data.alldata(data.vial176);
	cout << "Vial 177" << endl;
	data.alldata(data.vial177);
	cout << "Vial 178" << endl;
	data.alldata(data.vial178);
	cout << "Vial 179" << endl;
	data.alldata(data.vial179);
	cout << "Vial 180" << endl;
	data.alldata(data.vial180);
	cout << "Vial 181" << endl;
	data.alldata(data.vial181);
	cout << "Vial 182" << endl;
	data.alldata(data.vial182);
	cout << "Vial 183" << endl;
	data.alldata(data.vial183);
	cout << "Vial 184" << endl;
	data.alldata(data.vial184);
	cout << "Vial 185" << endl;
	data.alldata(data.vial185);
	cout << "Vial 186" << endl;
	data.alldata(data.vial186);
	cout << "Vial 187" << endl;
	data.alldata(data.vial187);
	cout << "Vial 188" << endl;
	data.alldata(data.vial188);
	cout << "Vial 189" << endl;
	data.alldata(data.vial189);
	cout << "Vial 190" << endl;
	data.alldata(data.vial190);
	cout << "Vial 191" << endl;
	data.alldata(data.vial191);
	cout << "Vial 192" << endl;
	data.alldata(data.vial192);
	cout << "Vial 193" << endl;
	data.alldata(data.vial193);
	cout << "Vial 194" << endl;
	data.alldata(data.vial194);
	cout << "Vial 195" << endl;
	data.alldata(data.vial195);
	cout << "Vial 196" << endl;
	data.alldata(data.vial196);
	cout << "Vial 197" << endl;
	data.alldata(data.vial197);
	cout << "Vial 198" << endl;
	data.alldata(data.vial198);
	cout << "Vial 199" << endl;
	data.alldata(data.vial199);
	cout << "Vial 200" << endl;
	data.alldata(data.vial200);
	cout << "Vial 201" << endl;
	data.alldata(data.vial201);
	cout << "Vial 202" << endl;
	data.alldata(data.vial202);
	cout << "Vial 203" << endl;
	data.alldata(data.vial203);
	cout << "Vial 204" << endl;
	data.alldata(data.vial204);
	cout << "Vial 205" << endl;
	data.alldata(data.vial205);
	cout << "Vial 206" << endl;
	data.alldata(data.vial206);
	cout << "Vial 207" << endl;
	data.alldata(data.vial207);
	cout << "Vial 208" << endl;
	data.alldata(data.vial208);
	cout << "Vial 209" << endl;
	data.alldata(data.vial209);
	cout << "Vial 210" << endl;
	data.alldata(data.vial210);
	cout << "Vial 211" << endl;
	data.alldata(data.vial211);
	cout << "Vial 212" << endl;
	data.alldata(data.vial212);
	cout << "good1" << endl;
	data.alldata(data.good1);
	cout << "good2" << endl;
	data.alldata(data.good2);
	cout << "good3" << endl;
	data.alldata(data.good3);
	cout << "good5" << endl;
	data.alldata(data.good5);
	cout << "good6" << endl;
	data.alldata(data.good6);
	cout << "good7" << endl;
	data.alldata(data.good7);
	cout << "good8" << endl;
	data.alldata(data.good8);
	cout << "good9" << endl;
	data.alldata(data.good9);
	cout << "good10" << endl;
	data.alldata(data.good10);
	cout << "good11" << endl;
	data.alldata(data.good11);
	cout << "good12" << endl;
	data.alldata(data.good12);
	cout << "good13" << endl;
	data.alldata(data.good13);
	cout << "good14" << endl;
	data.alldata(data.good14);
	cout << "good15" << endl;
	data.alldata(data.good15);
	cout << "good16" << endl;
	data.alldata(data.good16);
	cout << "good17" << endl;
	data.alldata(data.good17);
	cout << "good18" << endl;
	data.alldata(data.good18);
	cout << "good19" << endl;
	data.alldata(data.good19);
	cout << "good20" << endl;
	data.alldata(data.good20);
	cout << "good21" << endl;
	data.alldata(data.good21);
	cout << "good22" << endl;
	data.alldata(data.good22);
	cout << "good23" << endl;
	data.alldata(data.good23); 
	cout << "good25" << endl;
	data.alldata(data.good25);
	cout << "good26" << endl;
	data.alldata(data.good26);
	cout << "good27" << endl;
	data.alldata(data.good27);
	cout << "good28" << endl;
	data.alldata(data.good28);
	cout << "good29" << endl;
	data.alldata(data.good29);
	cout << "good30" << endl;
	data.alldata(data.good30);
	*/
}
