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
	void classify(cv::Mat vial);
	void loadDataTop();
	void loadDataBottom();
	void loadDataCrack();
	void loadDataScratch();
	void alldata(cv::Mat vial);
	cv::Mat rotate(cv::Mat src, double angle);

	cv::Mat vial1 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\1_1.png");
	cv::Mat vial2 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\1_2.png");
	cv::Mat vial3 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\1_3.png");
	cv::Mat vial4 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\2_1.png");
	cv::Mat	vial5 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\2_2.png");
	cv::Mat vial6 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\2_3.png");
	cv::Mat vial7 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\3_1.png");
	cv::Mat	vial8 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\3_2.png");
	cv::Mat vial9 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\3_3.png");
	cv::Mat vial10 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\4_1.png");
	cv::Mat	vial11 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\4_2.png");
	cv::Mat vial12 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\4_3.png");
	cv::Mat vial13 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\5_1.png");
	cv::Mat	vial14 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\5_2.png");
	cv::Mat vial15 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\5_3.png");
	cv::Mat vial16 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\6_1.png");
	cv::Mat vial17 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\6_2.png");
	cv::Mat vial18 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\6_3.png");
	cv::Mat vial19 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\7_1.png");
	cv::Mat vial20 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\7_2.png");
	cv::Mat vial21 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\7_3.png");
	cv::Mat vial22 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\8_1.png");
	cv::Mat vial23 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\8_2.png");
	cv::Mat vial24 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\8_3.png");
	cv::Mat vial25 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\9_1.png");
	cv::Mat vial26 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\9_3.png");
	cv::Mat vial29 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\10_3.png");
	cv::Mat vial31 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\11_2.png");
	cv::Mat vial32 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\11_3.png");
	cv::Mat vial33 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\12_1.png");
	cv::Mat vial34 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\12_2.png");
	cv::Mat vial35 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\12_3.png");
	cv::Mat vial36 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\13_1.png");
	cv::Mat vial37 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\13_2.png");
	cv::Mat vial38 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\13_3.png");
	cv::Mat vial39 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\14_1.png");
	cv::Mat vial40 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\14_2.png");
	cv::Mat vial41 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\14_3.png");
	cv::Mat vial42 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\15_1.png");
	cv::Mat vial43 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\15_2.png");
	cv::Mat vial44 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\15_3.png");
	cv::Mat vial46 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\16_2.png");
	cv::Mat vial47 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\16_3.png");
	cv::Mat vial48 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\1_Color.png");
	cv::Mat vial49 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\2_Color.png");
	cv::Mat vial50 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\3_Color.png");
	cv::Mat vial51 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\4_Color.png");
	cv::Mat vial52 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\5_Color.png");
	cv::Mat vial53 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\6_Color.png");
	cv::Mat vial54 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\7_Color.png");
	cv::Mat vial55 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\8_Color.png");
	cv::Mat vial56 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\9_Color.png");
	cv::Mat vial57 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\10_Color.png");
	cv::Mat vial58 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\11_Color.png");
	cv::Mat vial59 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\12_Color.png");
	cv::Mat vial60 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\13_Color.png");
	cv::Mat vial61 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\14_Color.png");
	cv::Mat vial62 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\15_Color.png");
	cv::Mat vial63 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\16_Color.png");
	cv::Mat vial64 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\17_Color.png");
	cv::Mat vial65 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\18_Color.png");
	cv::Mat vial66 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\19_Color.png");
	cv::Mat vial67 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\20_Color.png");
	cv::Mat vial68 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\21_Color.png");
	cv::Mat vial69 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\22_Color.png");
	cv::Mat vial70 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\23_Color.png");
	cv::Mat vial71 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\24_Color.png");
	cv::Mat vial72 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\25_Color.png");
	cv::Mat vial73 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\26_Color.png");
	cv::Mat vial74 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\27_Color.png");
	cv::Mat vial75 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\28_Color.png");
	cv::Mat vial76 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\29_Color.png");
	cv::Mat vial77 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\30_Color.png");
	cv::Mat vial78 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\31_Color.png");
	cv::Mat vial79 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\32_Color.png");
	cv::Mat vial80 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\33_Color.png");
	cv::Mat vial81 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\34_Color.png");
	cv::Mat vial82 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\35_Color.png");
	cv::Mat vial83 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\36_Color.png");
	cv::Mat vial84 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\37_Color.png");
	cv::Mat vial85 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\38_Color.png");
	cv::Mat vial86 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\39_Color.png");
	cv::Mat vial87 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\40_Color.png");
	cv::Mat vial88 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\42_Color.png");
	cv::Mat vial89 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\43_Color.png");
	cv::Mat vial90 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\44_Color.png");
	cv::Mat vial91 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\45_Color.png");
	cv::Mat vial92 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\47_Color.png");
	cv::Mat vial93 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\48_Color.png");
	cv::Mat vial94 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\49_Color.png");
	cv::Mat vial95 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\50_Color.png");
	cv::Mat vial96 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\51_Color.png");
	cv::Mat vial97 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\52_Color.png");
	cv::Mat vial98 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\53_Color.png");
	cv::Mat vial99 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\54_Color.png");
	cv::Mat vial100 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\55_Color.png");
	cv::Mat vial101 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\56_Color.png");
	cv::Mat vial102 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\57_Color.png");
	cv::Mat vial103 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\58_Color.png");
	cv::Mat vial104 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\59_Color.png");
	cv::Mat vial105 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\60_Color.png");
	cv::Mat vial106 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\61_Color.png");
	cv::Mat vial107 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\62_Color.png");
	cv::Mat vial108 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\63_Color.png");
	cv::Mat vial109 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\64_Color.png");
	cv::Mat vial110 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\65_Color.png");
	cv::Mat vial111 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\66_Color.png");
	cv::Mat vial112 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\67_Color.png");
	cv::Mat vial113 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\68_Color.png");
	cv::Mat vial114 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\69_Color.png");
	cv::Mat vial115 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\70_Color.png");
	cv::Mat vial116 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\71_Color.png");
	cv::Mat vial117 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\72_Color.png");
	cv::Mat vial118 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\73_Color.png");
	cv::Mat vial119 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\74_Color.png");
	cv::Mat vial120 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\75_Color.png");
	cv::Mat vial121 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\76_Color.png");
	cv::Mat vial122 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\77_Color.png");
	cv::Mat vial123 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\78_Color.png");
	cv::Mat vial124 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\79_Color.png");
	cv::Mat vial125 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\80_Color.png");
	cv::Mat vial126 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\81_Color.png");
	cv::Mat vial127 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\82_Color.png");
	cv::Mat vial128 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\83_Color.png");
	cv::Mat vial129 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\84_Color.png");
	cv::Mat vial130 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\85_Color.png");
	cv::Mat vial131 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\86_Color.png");
	cv::Mat vial132 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\87_Color.png");
	cv::Mat vial133 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\88_Color.png");
	cv::Mat vial134 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\89_Color.png");
	cv::Mat vial135 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\90_Color.png");
	cv::Mat vial136 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\91_Color.png");
	cv::Mat vial137 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\92_Color.png");
	cv::Mat vial138 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\93_Color.png");
	cv::Mat vial139 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\94_Color.png");
	cv::Mat vial140 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\95_Color.png");
	cv::Mat vial141 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\96_Color.png");
	cv::Mat vial142 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\97_Color.png");
	cv::Mat vial143 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\98_Color.png");
	cv::Mat vial144 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\99_Color.png");
	cv::Mat vial145 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\100_Color.png");
	cv::Mat vial146 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\101_Color.png");
	cv::Mat vial147 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\102_Color.png");
	cv::Mat vial148 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\103_Color.png");
	cv::Mat vial149 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\104_Color.png");
	cv::Mat vial150 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\105_Color.png");
	cv::Mat vial151 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\106_Color.png");
	cv::Mat vial152 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\107_Color.png");
	cv::Mat vial153 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\108_Color.png");
	cv::Mat vial154 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\109_Color.png");
	cv::Mat vial155 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\110_Color.png");
	cv::Mat vial156 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\111_Color.png");
	cv::Mat vial157 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\112_Color.png");
	cv::Mat vial158 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\114_Color.png");
	cv::Mat vial159 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\115_Color.png");
	cv::Mat vial160 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\116_Color.png");
	cv::Mat vial161 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\117_Color.png");
	cv::Mat vial162 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\118_Color.png");
	cv::Mat vial163 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\119_Color.png");
	cv::Mat vial164 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\120_Color.png");
	cv::Mat vial165 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\121_Color.png");
	cv::Mat vial166 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\122_Color.png");
	cv::Mat vial167 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\123_Color.png");
	cv::Mat vial168 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\124_Color.png");
	cv::Mat vial169 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\125_Color.png");
	cv::Mat vial170 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\126_Color.png");
	cv::Mat vial171 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\127_Color.png");
	cv::Mat vial172 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\128_Color.png");
	cv::Mat vial173 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\129_Color.png");
	cv::Mat vial174 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\130_Color.png");
	cv::Mat vial175 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\131_Color.png");
	cv::Mat vial176 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\132_Color.png");
	cv::Mat vial177 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\133_Color.png");
	cv::Mat vial178 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\135_Color.png");
	cv::Mat vial179 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\136_Color.png");
	cv::Mat vial180 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\137_Color.png");
	cv::Mat vial181 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\138_Color.png");
	cv::Mat vial182 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\139_Color.png");
	cv::Mat vial183 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\140_Color.png");
	cv::Mat vial184 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\141_Color.png");
	cv::Mat vial185 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\142_Color.png");
	cv::Mat vial186 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\143_Color.png");
	cv::Mat vial187 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\144_Color.png");
	cv::Mat vial188 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\145_Color.png");
	cv::Mat vial189 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\146_Color.png");
	cv::Mat vial190 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\147_Color.png");
	cv::Mat vial191 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\148_Color.png");
	cv::Mat vial192 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\150_Color.png");
	cv::Mat vial193 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\151_Color.png");
	cv::Mat vial194 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\152_Color.png");
	cv::Mat vial195 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\153_Color.png");
	cv::Mat vial196 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\154_Color.png");
	cv::Mat vial197 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\155_Color.png");
	cv::Mat vial198 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\156_Color.png");
	cv::Mat vial199 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\157_Color.png");
	cv::Mat vial200 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\158_Color.png");
	cv::Mat vial201 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\159_Color.png");
	cv::Mat vial202 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\160_Color.png");
	cv::Mat vial203 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\161_Color.png");
	cv::Mat vial204 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\162_Color.png");
	cv::Mat vial205 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\164_Color.png");
	cv::Mat vial206 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\165_Color.png");
	cv::Mat vial207 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\166_Color.png");
	cv::Mat vial208 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\167_Color.png");
	cv::Mat vial209 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\168_Color.png");
	cv::Mat vial210 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\169_Color.png");
	cv::Mat vial211 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\170_Color.png");
	cv::Mat vial212 = cv::imread("C:\\Users\\artur\\Desktop\\Harmed\\171_Color.png");

private:
	float top[1][3];
	float bottom[1][3];
	float crack[1][3];
	float scratch[1][3];

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

	vector<Vialfeatures> featVec1;

	vector<int> areaVec;
	vector<int> perimeterVec;
	vector<float> circularityVec;
	vector<float> elongationVec;

	cv::Mat ContourIMG;
	cv::Mat drawingfinal;
	cv::Mat rotated;
	cv::Mat everything;
	vector<vector<cv::Point>> G1contours;

};

#endif
