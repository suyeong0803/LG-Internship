#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img;
	VideoCapture capture("Ocean - 74888.mp4");	// 동영상 불러오기

	if (!capture.isOpened())
	{
		cout << "can't find" << endl;
		return -1;
	}

	double fps = capture.get(CAP_PROP_FPS);
	double width = capture.get(CAP_PROP_FRAME_WIDTH);
	double height = capture.get(CAP_PROP_FRAME_HEIGHT);
	double fourcc = capture.get(CAP_PROP_FOURCC);

	VideoWriter save;
	save.open("save_video.mpeg", VideoWriter::fourcc('m', 'p', '2', 'v'), fps, Size(width, height), true);	// mpeg2 파일로 변환
	save.open("save_video.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'), fps, Size(width, height), true);	// mpeg4 파일로 변환

	while (true)
	{
		capture >> img;
		if (img.empty()) { cout << "img empty" << endl; break; }
		
		save << img;
	}
}
