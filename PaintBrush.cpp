#include <opencv2/opencv.hpp>
#include "OpenFileDialog.h"
#include "SaveFileDialog.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace cv;

Mat icon, Campus, Campus_buff, palette;

int B = 255;
int G = 0;
int R = 0;

int MenuSelect = 0;
int ColorSelect = 0;
int drawing_pencil = false;      
int drawing_line = false;
int drawing_rect = false;
int drawing_circle = false;
int drawing_ellipse = false;
int drawing_erase = false;
int text_start = false;

float rad;
float rad_x, rad_y;

int start_x, start_y;
int move_x, move_y;

int large_axe, small_axe;
int x_axe, y_axe;


void InverseIcon(int MenuSelect)
{
	int sx, sy;
	sy = (MenuSelect - 1) / 5;
	sx = (MenuSelect - 1) % 5;
	Rect r(sx * 154, sy * 150, 154, 150);
	Mat D = icon(r); // 사각형을 사용하여 관심 영역을 지정한다. 
	bitwise_not(D, D);
	imshow("Menu", icon);
}
void Inver_seIcon(int ColorSelect)
{
	int px, py;
	py = (ColorSelect - 1) / 8;
	px = (ColorSelect - 1) % 8;
	Rect pr(px * 100, py * 100, 100, 100);
	Mat PD = palette(pr); // 사각형을 사용하여 관심 영역을 지정한다. 
	bitwise_not(PD, PD);
	imshow("palette", palette);
}

void onMousePalette(int event, int x, int y, int flags, void* param)
{
	int px, py;
	if (event == EVENT_LBUTTONDOWN) {
		px = x / 100; 
		py = y / 100;

		if (ColorSelect != 0) {
			Inver_seIcon(ColorSelect);
		}

		ColorSelect = py * 8 + px + 1;
		Inver_seIcon(ColorSelect);
		
		switch (ColorSelect) {
		case 1:
			B = 255;
			G = 255;
			R = 255;
			break;

		case 2:
			B = 195;
			G = 195;
			R = 195;
			break;

		case 3:
			B = 21;
			G = 0;
			R = 136;
			break;

		case 4:
			B = 36;
			G = 28;
			R = 237;
			break;

		case 5:
			B = 39;
			G = 127;
			R = 255;
			break;

		case 6:
			B = 0;
			G = 242;
			R = 255;
			break;

		case 7:
			B = 76;
			G = 177;
			R = 34;
			break;

		case 8:
			B = 204;
			G = 72;
			R = 63;
			break;

		case 9:
			B = 0;
			G = 0;
			R = 0;
			break;

		case 10:
			B = 127;
			G = 127;
			R = 127;
			break;
		
		case 11:
			B = 87;
			G = 122;
			R = 185;
			break;

		case 12:
			B = 201;
			G = 174;
			R = 255;
			break;

		case 13:
			B = 176;
			G = 228;
			R = 239;
			break;

		case 14:
			B = 29;
			G = 230;
			R = 181;
			break;

		case 15:
			B = 190;
			G = 146;
			R = 112;
			break;

		case 16:
			B = 231;
			G = 191;
			R = 200;
			break;
		}
	}
}

void onMouseCampus(int event, int x, int y, int flags, void* param)
{
	Mat Campus_buff = Campus.clone();
	

	/* MenuSelect 2 PECNIL 그리기 */
	if (event == CV_EVENT_LBUTTONDOWN && MenuSelect == 2) {
		drawing_pencil = true;
	}
	else if (event == CV_EVENT_MOUSEMOVE && MenuSelect == 2) {
		if (drawing_pencil == true) {
			circle(Campus, Point(x, y), 3, Scalar(B, G, R), 5);
			imshow("Campus", Campus);
		}
	}
	else if (event == CV_EVENT_LBUTTONUP && MenuSelect == 2) {
		drawing_pencil = false;
		circle(Campus_buff, Point(x, y), 3, Scalar(B, G, R), 5);
		imshow("Campus", Campus);
	}

	/* MenuSelect 3  Text 입력 */
	if (event == CV_EVENT_LBUTTONDOWN && MenuSelect == 3) {
		text_start = true;
		putText(Campus, "text_test", Point(x, y), FONT_HERSHEY_PLAIN, 2.0, Scalar(B, G, R), 2);
		imshow("Campus", Campus);
	} 

	/* MenuSelect 4  직선 그리기 */

	if (event == CV_EVENT_LBUTTONDOWN && MenuSelect == 4) {
		drawing_line = true;
		start_x = x;
		start_y = y;
	}
	else if (event == CV_EVENT_MOUSEMOVE && MenuSelect == 4) {
		if (drawing_line == true) {
			move_x = x;
			move_y = y;
			line(Campus_buff, Point(start_x, start_y), Point(move_x, move_y), Scalar(B, G, R), 5);
			imshow("Campus", Campus_buff);
		}
	}
	else if (event == CV_EVENT_LBUTTONUP && MenuSelect == 4) {
		drawing_line = false;
		line(Campus, Point(start_x, start_y), Point(x, y), Scalar(B, G, R), 5);
		imshow("Campus", Campus);
	}

	/* MenuSelect 5  사각형 그리기 */
	if (event == CV_EVENT_LBUTTONDOWN && MenuSelect == 5) {
		drawing_rect = true;
		start_x = x;
		start_y = y;
	}
	else if (event == CV_EVENT_MOUSEMOVE && MenuSelect == 5) {
		if (drawing_rect == true) {
			move_x = x;
			move_y = y;
			rectangle(Campus_buff, Point(start_x, start_y), Point(move_x, move_y), Scalar(B, G, R), 5);
			imshow("Campus", Campus_buff);
		}
	}
	else if (event == CV_EVENT_LBUTTONUP && MenuSelect == 5) {
		drawing_rect = false;
		rectangle(Campus, Point(start_x, start_y), Point(x, y), Scalar(B, G, R), 5);
		imshow("Campus", Campus);
	}

	/* MenuSelect 7  지우개 */
	if (event == CV_EVENT_LBUTTONDOWN && MenuSelect == 7) {
		drawing_erase = true;
	}
	else if (event == CV_EVENT_MOUSEMOVE && MenuSelect == 7) {
		if (drawing_erase == true) {
			rectangle(Campus, Point(x, y), Point(x + 10, y + 10), Scalar(255, 255, 255), 20);
			imshow("Campus", Campus);
		}
	}
	else if (event == CV_EVENT_LBUTTONUP && MenuSelect == 7) {
		drawing_erase = false;
		rectangle(Campus, Point(x, y), Point(x + 10, y + 10), Scalar(255, 255, 255), 20);
		imshow("Campus", Campus);
	}

	/* MenuSelect  8    원 그리기 */
	if (event == CV_EVENT_LBUTTONDOWN && MenuSelect == 8) {
		drawing_circle = true;
		start_x = x;
		start_y = y;
	}
	else if (event == CV_EVENT_MOUSEMOVE && MenuSelect == 8) {
		if (drawing_circle == true) {
			move_x = x;
			move_y = y;
			rad_x = start_x - move_x;
			rad_y = start_y - move_y;
			rad = sqrt((rad_x) * (rad_x)+(rad_y) * (rad_y));
			circle(Campus_buff, Point(start_x, start_y), rad, Scalar(B, G, R), 5);
			imshow("Campus", Campus_buff);
		}
	}
	else if (event == CV_EVENT_LBUTTONUP && MenuSelect == 8) {
		drawing_circle = false;
		move_x = x;
		move_y = y;
		rad_x = start_x - move_x;
		rad_y = start_y - move_y;
		rad = sqrt((rad_x) * (rad_x)+(rad_y) * (rad_y));
		circle(Campus, Point(start_x, start_y), rad, Scalar(B, G, R), 5);
		imshow("Campus", Campus);
	}


	/* MenuSelect 9  타원 그리기 */
	if (event == CV_EVENT_LBUTTONDOWN && MenuSelect == 9) {
		drawing_ellipse = true;
		start_x = x;
		start_y = y;
	}
	else if (event == CV_EVENT_MOUSEMOVE && MenuSelect == 9) {
		if (drawing_ellipse == true) {
			move_x = x;
			move_y = y;
			x_axe = abs(start_x - move_x);
			y_axe = abs(start_y - move_y);
			ellipse(Campus_buff, Point(start_x, start_y), Size(x_axe, y_axe), 0, 0, 360, Scalar(B, G, R), 5);
			imshow("Campus", Campus_buff);
		}
	}
	else if (event == CV_EVENT_LBUTTONUP && MenuSelect == 9) {
		drawing_ellipse = false;
		move_x = x;
		move_y = y;
		x_axe = abs(start_x - move_x);
		y_axe = abs(start_y - move_y);
		ellipse(Campus, Point(start_x, start_y), Size(x_axe, y_axe), 0, 0, 360, Scalar(B, G, R), 5);
		imshow("Campus", Campus);
	}

}

void onMouseMenu(int event, int x, int y, int flags, void* param)
{
	OpenFileDialog* openFileDialog = new OpenFileDialog();
	SaveFileDialog* saveFileDialog = new SaveFileDialog();
	int sx, sy;
	if (event == EVENT_LBUTTONDOWN) {
		sx = x / 154; sy = y / 150;
		if (MenuSelect != 0) {
			InverseIcon(MenuSelect);
		}
		MenuSelect = sy * 5 + sx + 1;
		InverseIcon(MenuSelect);

		switch (MenuSelect) {
		case 1: if (openFileDialog->ShowDialog()) {
			Campus = imread(openFileDialog->FileName);
			imshow("Campus", Campus);
		}
			  InverseIcon(MenuSelect);
			  MenuSelect = 0;
			  break;
		case 2: //연필 그리기

			break;
		case 3: // 텍스트 입력

			break;
		case 4:  // 직선 그리기
			break;
		case 5: // 사각형 그리기
			break;

		case 6: if (saveFileDialog->ShowDialog()) {
			imwrite(saveFileDialog->FileName, Campus);
		}
			  InverseIcon(MenuSelect);
			  MenuSelect = 0;
			  break;
		case 7: //지우개 기능
			break;

		case 8: //원 그리기
			break;


		case 9: //타원 그리기
			break;


		case 10: //색상 파레트
			break;


		case 11: //실행 취소
			break;


		case 12: //다시 실행
			break;
		}

	}
}

int main()
{
	int key;
	icon = imread("icon-small.png", IMREAD_COLOR);
	imshow("Menu", icon);

	Campus = Mat::zeros(600, 800, CV_8UC3);
	imshow("Campus", Campus);

	palette = imread("palette.jpg", IMREAD_COLOR);
	if (palette.empty()) { cout << "Palette를 불러올 수 없음" << endl; }
	imshow("palette", palette);

	setMouseCallback("palette", onMousePalette, &palette);
	setMouseCallback("Menu", onMouseMenu, &icon);
	setMouseCallback("Campus", onMouseCampus, &icon);

	do {

		key = waitKey(100);
	} while (key != 'q');
	waitKey(0);

	return 0;
}