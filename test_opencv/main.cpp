#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

#define CAM_WIDTH 1080
#define CAM_HEIGHT 480

/** Function Headers */
void detectAndDisplay(Mat frame);

/** Global variables */
String face_cascade_name;
CascadeClassifier face_cascade;
String window_name = "Face detection";

/** @function main */
int main(void) {

	face_cascade_name = "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml"; // 정면 인식 
	if (!face_cascade.load(face_cascade_name)) {
		printf("--(!)Error loading face cascade\n");
		return -1;
	}

	VideoCapture cam(0); // 카메라나 비디오파일에서 캡쳐를 하는 클래스
	Mat frame; // 1채널 또는 다채널의 실수, 복소수, 행렬, 영상 등의 수치 데이터 표현하는 N차원 행렬 클래스

	cam.set(CV_CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
	cam.set(CV_CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);

	if (!cam.isOpened()) {
		printf("--(!)Error opening video cam\n"); return -1;
	}

	// 웹캠으로부터 계속 프레임을 받아옴 (escape: ESC키)
	while (cam.read(frame)) { 
		if (frame.empty()) {
			printf("--(!) No camd frame -- Break!");
			break;
		}
		detectAndDisplay(frame); // 매 프레임마다 얼굴을 디텍팅하는 함수 실행
		char c = (char)waitKey(10); // 키보드 입력
		if (c == 27) { break; } // escape condition!
	}

	return 0;

} // main()

/** @function detectAndDisplay */
void detectAndDisplay(Mat frame) {
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	imwrite("C:\\Users\\happy_jh\\Desktop\\new.jpg", frame_gray);

	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	// minSize와 maxSize를 설정해두면, 일정 크기 이하나 이상의 얼굴은 처리하지 않고 무시

	for (size_t i = 0; i < faces.size(); i++) {
		// Point클래스: 점, 사각형 등 기하학적 객체를 정의하는 클래스들 중 하나로 직교 좌표계의 한 점을 가지는 클래스
		// Point(x, y): 새로운 점을 만듦
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		// ellipse: 타원 그리기 함수 (img, center, radius, rotation of ellipse, start angle of arc, end angle of arc, color, thickness)
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(0, 0, 255), 4, 8, 0);
		
	} // for(i)

	imshow(window_name, frame); // Face detection이란 이름을 가진 윈도우가 보여짐
}