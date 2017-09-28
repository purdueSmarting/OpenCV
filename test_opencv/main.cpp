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

	face_cascade_name = "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml"; // ���� �ν� 
	if (!face_cascade.load(face_cascade_name)) {
		printf("--(!)Error loading face cascade\n");
		return -1;
	}

	VideoCapture cam(0); // ī�޶� �������Ͽ��� ĸ�ĸ� �ϴ� Ŭ����
	Mat frame; // 1ä�� �Ǵ� ��ä���� �Ǽ�, ���Ҽ�, ���, ���� ���� ��ġ ������ ǥ���ϴ� N���� ��� Ŭ����

	cam.set(CV_CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
	cam.set(CV_CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);

	if (!cam.isOpened()) {
		printf("--(!)Error opening video cam\n"); return -1;
	}

	// ��ķ���κ��� ��� �������� �޾ƿ� (escape: ESCŰ)
	while (cam.read(frame)) { 
		if (frame.empty()) {
			printf("--(!) No camd frame -- Break!");
			break;
		}
		detectAndDisplay(frame); // �� �����Ӹ��� ���� �������ϴ� �Լ� ����
		char c = (char)waitKey(10); // Ű���� �Է�
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
	// minSize�� maxSize�� �����صθ�, ���� ũ�� ���ϳ� �̻��� ���� ó������ �ʰ� ����

	for (size_t i = 0; i < faces.size(); i++) {
		// PointŬ����: ��, �簢�� �� �������� ��ü�� �����ϴ� Ŭ������ �� �ϳ��� ���� ��ǥ���� �� ���� ������ Ŭ����
		// Point(x, y): ���ο� ���� ����
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		// ellipse: Ÿ�� �׸��� �Լ� (img, center, radius, rotation of ellipse, start angle of arc, end angle of arc, color, thickness)
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(0, 0, 255), 4, 8, 0);
		
	} // for(i)

	imshow(window_name, frame); // Face detection�̶� �̸��� ���� �����찡 ������
}