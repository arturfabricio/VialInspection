//Vial and Crack Detection Algoryhtm - Group 464 ROB4
//V6.0 - 20/05/2020

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace std;

#ifndef VIALS_H 
#define VIALS_H

class inspectVial {
public:
	void rotatefunc(cv::Mat vial);
	void roifunc(cv::Mat vial);
	void inspection(cv::Mat vial);
	void alldata(cv::Mat vial);
	void check();

	void classify(cv::Mat vial);
	void loadDataTop();
	void loadDataBottom();
	void loadDataCrack();
	void loadDataScratch();
	cv::Mat rotate(cv::Mat src, double angle);

	cv::Mat cadst;
	cv::Mat rotated;
	cv::Mat vial_ROI;
	cv::Mat vial_ROI1;
	cv::Mat ContourIMG;

	int xclass;
	int yclass;
	int wclass;
	int hclass;

	//TrainingData/Mixed
	cv::Mat vial1 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\1_1.png");
	cv::Mat vial2 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\1_2.png");
	cv::Mat vial3 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\1_3.png");
	cv::Mat vial4 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\2_1.png");
	cv::Mat	vial5 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\2_2.png");
	cv::Mat vial6 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\2_3.png");
	cv::Mat vial7 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\3_1.png");
	cv::Mat	vial8 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\3_2.png");
	cv::Mat vial9 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\3_3.png");
	cv::Mat vial10 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\4_1.png");
	cv::Mat	vial11 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\4_2.png");
	cv::Mat vial12 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\4_3.png");
	cv::Mat vial13 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\5_1.png");
	cv::Mat	vial14 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\5_2.png");
	cv::Mat vial15 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\5_3.png");
	cv::Mat vial16 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\6_1.png");
	cv::Mat vial17 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\6_2.png");
	cv::Mat vial18 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\6_3.png");
	cv::Mat vial19 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\7_1.png");
	cv::Mat vial20 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\7_2.png");
	cv::Mat vial21 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\7_3.png");
	cv::Mat vial22 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\8_1.png");
	cv::Mat vial23 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\8_2.png");
	cv::Mat vial24 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\8_3.png");
	cv::Mat vial25 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\9_1.png");
	cv::Mat vial26 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\9_3.png");
	cv::Mat vial29 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\10_3.png");
	cv::Mat vial31 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\11_2.png");
	cv::Mat vial32 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\11_3.png");
	cv::Mat vial33 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\12_1.png");
	cv::Mat vial34 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\12_2.png");
	cv::Mat vial35 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\12_3.png");
	cv::Mat vial36 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\13_1.png");
	cv::Mat vial37 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\13_2.png");
	cv::Mat vial38 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\13_3.png");
	cv::Mat vial39 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\14_1.png");
	cv::Mat vial40 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\14_2.png");
	cv::Mat vial41 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\14_3.png");
	cv::Mat vial42 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\15_1.png");
	cv::Mat vial43 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\15_2.png");
	cv::Mat vial44 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\15_3.png");
	cv::Mat vial46 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\16_2.png");
	cv::Mat vial47 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\16_3.png");
	cv::Mat vial48 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\1_Color.png");
	cv::Mat vial49 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\2_Color.png");
	cv::Mat vial50 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\3_Color.png");
	cv::Mat vial51 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\4_Color.png");
	cv::Mat vial52 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\5_Color.png");
	cv::Mat vial53 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\6_Color.png");
	cv::Mat vial54 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\7_Color.png");
	cv::Mat vial55 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\8_Color.png");
	cv::Mat vial56 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\9_Color.png");
	cv::Mat vial57 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\10_Color.png");
	cv::Mat vial58 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\11_Color.png");
	cv::Mat vial59 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\12_Color.png");
	cv::Mat vial60 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\13_Color.png");
	cv::Mat vial61 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\14_Color.png");
	cv::Mat vial62 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\15_Color.png");
	cv::Mat vial63 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\16_Color.png");
	cv::Mat vial64 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\17_Color.png");
	cv::Mat vial65 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\18_Color.png");
	cv::Mat vial66 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\19_Color.png");
	cv::Mat vial67 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\20_Color.png");
	cv::Mat vial68 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\21_Color.png");
	cv::Mat vial69 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\22_Color.png");
	cv::Mat vial70 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\23_Color.png");
	cv::Mat vial71 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\24_Color.png");
	cv::Mat vial72 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\25_Color.png");
	cv::Mat vial73 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\26_Color.png");
	cv::Mat vial74 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\27_Color.png");
	cv::Mat vial75 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\28_Color.png");
	cv::Mat vial76 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\29_Color.png");
	cv::Mat vial77 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\30_Color.png");
	cv::Mat vial78 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\31_Color.png");
	cv::Mat vial79 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\32_Color.png");
	cv::Mat vial80 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\33_Color.png");
	cv::Mat vial81 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\34_Color.png");
	cv::Mat vial82 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\35_Color.png");
	cv::Mat vial83 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\36_Color.png");
	cv::Mat vial84 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\37_Color.png");
	cv::Mat vial85 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\38_Color.png");
	cv::Mat vial86 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\39_Color.png");
	cv::Mat vial87 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\40_Color.png");
	cv::Mat vial88 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\42_Color.png");
	cv::Mat vial89 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\43_Color.png");
	cv::Mat vial90 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\44_Color.png");
	cv::Mat vial91 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\45_Color.png");
	cv::Mat vial92 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\47_Color.png");
	cv::Mat vial93 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\48_Color.png");
	cv::Mat vial94 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\49_Color.png");
	cv::Mat vial95 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\50_Color.png");
	cv::Mat vial96 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\51_Color.png");
	cv::Mat vial97 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\52_Color.png");
	cv::Mat vial98 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\53_Color.png");
	cv::Mat vial99 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\54_Color.png");
	cv::Mat vial100 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\55_Color.png");
	cv::Mat vial101 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\56_Color.png");
	cv::Mat vial102 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\57_Color.png");
	cv::Mat vial103 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\58_Color.png");
	cv::Mat vial104 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\59_Color.png");
	cv::Mat vial105 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\60_Color.png");
	cv::Mat vial106 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\61_Color.png");
	cv::Mat vial107 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\62_Color.png");
	cv::Mat vial108 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\63_Color.png");
	cv::Mat vial109 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\64_Color.png");
	cv::Mat vial110 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\65_Color.png");
	cv::Mat vial111 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\66_Color.png");
	cv::Mat vial112 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\67_Color.png");
	cv::Mat vial113 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\68_Color.png");
	cv::Mat vial114 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\69_Color.png");
	cv::Mat vial115 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\70_Color.png");
	cv::Mat vial116 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\71_Color.png");
	cv::Mat vial117 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\72_Color.png");
	cv::Mat vial118 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\73_Color.png");
	cv::Mat vial119 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\74_Color.png");
	cv::Mat vial120 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\75_Color.png");
	cv::Mat vial121 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\76_Color.png");
	cv::Mat vial122 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\77_Color.png");
	cv::Mat vial123 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\78_Color.png");
	cv::Mat vial124 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\79_Color.png");
	cv::Mat vial125 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\80_Color.png");
	cv::Mat vial126 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\81_Color.png");
	cv::Mat vial127 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\82_Color.png");
	cv::Mat vial128 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\83_Color.png");
	cv::Mat vial129 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\84_Color.png");
	cv::Mat vial130 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\85_Color.png");
	cv::Mat vial131 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\86_Color.png");
	cv::Mat vial132 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\87_Color.png");
	cv::Mat vial133 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\88_Color.png");
	cv::Mat vial134 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\89_Color.png");
	cv::Mat vial135 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\90_Color.png");
	cv::Mat vial136 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\91_Color.png");
	cv::Mat vial137 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\92_Color.png");
	cv::Mat vial138 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\93_Color.png");
	cv::Mat vial139 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\94_Color.png");
	cv::Mat vial140 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\95_Color.png");
	cv::Mat vial141 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\96_Color.png");
	cv::Mat vial142 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\97_Color.png");
	cv::Mat vial143 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\98_Color.png");
	cv::Mat vial144 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\99_Color.png");
	cv::Mat vial145 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\100_Color.png");
	cv::Mat vial146 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\101_Color.png");
	cv::Mat vial147 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\102_Color.png");
	cv::Mat vial148 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\103_Color.png");
	cv::Mat vial149 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\104_Color.png");
	cv::Mat vial150 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\105_Color.png");
	cv::Mat vial151 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\106_Color.png");
	cv::Mat vial152 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\107_Color.png");
	cv::Mat vial153 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\108_Color.png");
	cv::Mat vial154 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\109_Color.png");
	cv::Mat vial155 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\110_Color.png");
	cv::Mat vial156 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\111_Color.png");
	cv::Mat vial157 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\112_Color.png");
	cv::Mat vial158 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\114_Color.png");
	cv::Mat vial159 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\115_Color.png");
	cv::Mat vial160 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\116_Color.png");
	cv::Mat vial161 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\117_Color.png");
	cv::Mat vial162 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\118_Color.png");
	cv::Mat vial163 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\119_Color.png");
	cv::Mat vial164 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\120_Color.png");
	cv::Mat vial165 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\121_Color.png");
	cv::Mat vial166 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\122_Color.png");
	cv::Mat vial167 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\123_Color.png");
	cv::Mat vial168 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\124_Color.png");
	cv::Mat vial169 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\125_Color.png");
	cv::Mat vial170 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\126_Color.png");
	cv::Mat vial171 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\127_Color.png");
	cv::Mat vial172 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\128_Color.png");
	cv::Mat vial173 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\129_Color.png");
	cv::Mat vial174 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\130_Color.png");
	cv::Mat vial175 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\131_Color.png");
	cv::Mat vial176 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\132_Color.png");
	cv::Mat vial177 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\133_Color.png");
	cv::Mat vial178 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\135_Color.png");
	cv::Mat vial179 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\136_Color.png");
	cv::Mat vial180 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\137_Color.png");
	cv::Mat vial181 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\138_Color.png");
	cv::Mat vial182 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\139_Color.png");
	cv::Mat vial183 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\140_Color.png");
	cv::Mat vial184 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\141_Color.png");
	cv::Mat vial185 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\142_Color.png");
	cv::Mat vial186 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\143_Color.png");
	cv::Mat vial187 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\144_Color.png");
	cv::Mat vial188 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\145_Color.png");
	cv::Mat vial189 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\146_Color.png");
	cv::Mat vial190 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\147_Color.png");
	cv::Mat vial191 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\148_Color.png");
	cv::Mat vial192 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\150_Color.png");
	cv::Mat vial193 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\151_Color.png");
	cv::Mat vial194 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\152_Color.png");
	cv::Mat vial195 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\153_Color.png");
	cv::Mat vial196 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\154_Color.png");
	cv::Mat vial197 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\155_Color.png");
	cv::Mat vial198 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\156_Color.png");
	cv::Mat vial199 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\157_Color.png");
	cv::Mat vial200 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\158_Color.png");
	cv::Mat vial201 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\159_Color.png");
	cv::Mat vial202 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\160_Color.png");
	cv::Mat vial203 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\161_Color.png");
	cv::Mat vial204 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\162_Color.png");
	cv::Mat vial205 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\164_Color.png");
	cv::Mat vial206 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\165_Color.png");
	cv::Mat vial207 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\166_Color.png");
	cv::Mat vial208 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\167_Color.png");
	cv::Mat vial209 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\168_Color.png");
	cv::Mat vial210 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\169_Color.png");
	cv::Mat vial211 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\170_Color.png");
	cv::Mat vial212 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Mixed\\171_Color.png");

	//TrainingData//Good
	cv::Mat good1 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\1_Color.png");
	cv::Mat good2 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\2_Color.png");
	cv::Mat good3 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\3_Color.png");
	cv::Mat good4 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\4_Color.png");
	cv::Mat good5 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\5_Color.png");
	cv::Mat good6 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\6_Color.png");
	cv::Mat good7 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\7_Color.png");
	cv::Mat good8 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\8_Color.png");
	cv::Mat good9 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\9_Color.png");
	cv::Mat good10 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\10_Color.png");
	cv::Mat good11 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\11_Color.png");
	cv::Mat good12 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\12_Color.png");
	cv::Mat good13 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\13_Color.png");
	cv::Mat good14 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\14_Color.png");
	cv::Mat good15 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\15_Color.png");
	cv::Mat good16 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\16_Color.png");
	cv::Mat good17 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\17_Color.png");
	cv::Mat good18 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\18_Color.png");
	cv::Mat good19 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\19_Color.png");
	cv::Mat good20 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\20_Color.png");
	cv::Mat good21 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\21_Color.png");
	cv::Mat good22 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\22_Color.png");
	cv::Mat good23 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\23_Color.png");
	cv::Mat good24 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\24_Color.png");
	cv::Mat good25 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\25_Color.png");
	cv::Mat good26 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\26_Color.png");
	cv::Mat good27 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\27_Color.png");
	cv::Mat good28 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\28_Color.png");
	cv::Mat good29 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\29_Color.png");
	cv::Mat good30 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Good\\30_Color.png");

	//TrainingData//Scratches 
	cv::Mat scratch1 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\1_Color.png");
	cv::Mat scratch2 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\2_Color.png");
	cv::Mat scratch3 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\3_Color.png");
	cv::Mat scratch4 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\4_Color.png");
	cv::Mat scratch5 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\5_Color.png");
	cv::Mat scratch6 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\6_Color.png");
	cv::Mat scratch7 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\7_Color.png");
	cv::Mat scratch8 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\8_Color.png");
	cv::Mat scratch9 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\9_Color.png");
	//cv::Mat scratch10 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\10_Color.png");
	cv::Mat scratch11 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\11_Color.png");
	cv::Mat scratch12 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\12_Color.png");
	cv::Mat scratch13 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\13_Color.png");
	cv::Mat scratch14 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\14_Color.png");
	cv::Mat scratch15 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\15_Color.png");
	cv::Mat scratch16 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\16_Color.png");
	cv::Mat scratch17 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\17_Color.png");
	cv::Mat scratch18 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\18_Color.png");
	cv::Mat scratch19 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\19_Color.png");
	cv::Mat scratch20 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\20_Color.png");
	cv::Mat scratch21 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\21_Color.png");
	cv::Mat scratch22 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\22_Color.png");
	cv::Mat scratch23 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\23_Color.png");
	cv::Mat scratch24 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\24_Color.png");
	cv::Mat scratch25 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\25_Color.png");
	cv::Mat scratch26 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\26_Color.png");
	cv::Mat scratch27 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\27_Color.png");
	cv::Mat scratch28 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\28_Color.png");
	cv::Mat scratch29 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\29_Color.png");
	cv::Mat scratch30 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\30_Color.png");
	cv::Mat scratch31 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\31_Color.png");
	cv::Mat scratch32 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\32_Color.png");
	cv::Mat scratch33 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\33_Color.png");
	cv::Mat scratch34 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\34_Color.png");
	cv::Mat scratch35 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\35_Color.png");
	cv::Mat scratch36 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\36_Color.png");
	cv::Mat scratch37 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\37_Color.png");
	cv::Mat scratch38 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\38_Color.png");
	cv::Mat scratch39 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\39_Color.png");
	cv::Mat scratch40 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\40_Color.png");
	cv::Mat scratch41 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\42_Color.png");
	cv::Mat scratch42 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\43_Color.png");
	cv::Mat scratch43 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\44_Color.png");
	cv::Mat scratch44 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\45_Color.png");
	cv::Mat scratch45 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\47_Color.png");
	cv::Mat scratch46 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\48_Color.png");
	cv::Mat scratch47 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\49_Color.png");
	cv::Mat scratch48 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\50_Color.png");
	cv::Mat scratch49 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\51_Color.png");
	cv::Mat scratch50 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\52_Color.png");
	cv::Mat scratch51 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\53_Color.png");
	cv::Mat scratch52 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\54_Color.png");
	cv::Mat scratch53 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\55_Color.png");
	cv::Mat scratch54 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\56_Color.png");
	cv::Mat scratch55 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\57_Color.png");
	cv::Mat scratch56 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\58_Color.png");
	cv::Mat scratch57 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\59_Color.png");
	cv::Mat scratch58 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\60_Color.png");
	cv::Mat scratch59 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\61_Color.png");
	cv::Mat scratch60 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\62_Color.png");
	cv::Mat scratch61 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\63_Color.png");
	cv::Mat scratch62 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\64_Color.png");
	cv::Mat scratch63 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\65_Color.png");
	cv::Mat scratch64 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\66_Color.png");
	cv::Mat scratch65 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\67_Color.png");
	cv::Mat scratch66 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\68_Color.png");
	cv::Mat scratch67 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\69_Color.png");
	cv::Mat scratch68 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\70_Color.png");
	cv::Mat scratch69 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\71_Color.png");
	cv::Mat scratch70 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\72_Color.png");
	cv::Mat scratch71 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\73_Color.png");
	cv::Mat scratch72 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\74_Color.png");
	cv::Mat scratch73 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\75_Color.png");
	cv::Mat scratch74 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\76_Color.png");
	cv::Mat scratch75 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\77_Color.png");
	cv::Mat scratch76 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\78_Color.png");
	cv::Mat scratch77 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\79_Color.png");
	cv::Mat scratch78 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\80_Color.png");
	cv::Mat scratch79 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\81_Color.png");
	cv::Mat scratch80 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\82_Color.png");
	cv::Mat scratch81 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\83_Color.png");
	cv::Mat scratch82 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\84_Color.png");
	cv::Mat scratch83 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\85_Color.png");
	cv::Mat scratch84 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\86_Color.png");
	cv::Mat scratch85 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\87_Color.png");
	cv::Mat scratch86 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\88_Color.png");
	cv::Mat scratch87 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\89_Color.png");
	cv::Mat scratch88 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\90_Color.png");
	cv::Mat scratch89 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\91_Color.png");
	cv::Mat scratch90 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\92_Color.png");
	cv::Mat scratch91 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\93_Color.png");
	cv::Mat scratch92 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\94_Color.png");
	cv::Mat scratch93 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\95_Color.png");
	cv::Mat scratch94 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\96_Color.png");
	cv::Mat scratch95 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\97_Color.png");
	cv::Mat scratch96 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\98_Color.png");
	cv::Mat scratch97 = cv::imread("C:\\Users\\artur\\Desktop\\TrainingData\\Scratches\\99_Color.png");

private:
	float topinit[204][4];
	float bottominit[325][4];
	float crackinit[216][4];
	float scratchinit[143][4];

	float top[204][3];
	float bottom[325][3];
	float crack[216][3];
	float scratch[143][3];

	struct boundingBox
	{
		int x;					
		int y;					
		int h;				
		int w;
	};

	struct Vialfeatures
	{
		int contourIndex;
		int area;
		int perimeter;
		int idx;
		float circularity;
		bool hasCrack;
		float elongation;
	};

	vector<vector<cv::Point>> G1contours;
	vector<Vialfeatures> featVec1;
	vector<int> areaVec;
	vector<int> perimeterVec;
	vector<float> circularityVec;
	vector<float> elongationVec;
	vector<int> check1;
	vector<int> check2;
	vector<int> count;
	bool bad;

};

#endif