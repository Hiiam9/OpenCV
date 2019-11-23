/*
	功能：实现对窗口是频加入滑动条并实现跳转
	code by she11
*/

//#include<opencv2/opencv.hpp> 使用这个会导致程序运行减慢，建议直接使用调用函数对应的模块
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<fstream>
#include<iostream>

using namespace std;
using namespace cv;

/*
	
*/
int g_slider_position = 0;
int g_run = 1;
int g_dontset = 0;
cv::VideoCapture g_cap;



//回调函数
void onTrackbarSlide(int pos,void *) {
	g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
	if (!g_dontset)
		g_run = -1;
	g_dontset = 0;
}

int main(int argc, char **argv)
{
	cv::namedWindow("Hi i am She11", cv::WINDOW_AUTOSIZE);
	g_cap.open("E:\\video\\1.mp4");
	int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
	int tempw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int temph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	cout << "Video has " << frames << "frames of dimensions(" << tempw << "," << temph << ")." << endl;
	cv::createTrackbar("Position", "Hi i am She11", &g_slider_position, frames, onTrackbarSlide);
	cv::Mat frame;
	for (;;) {
		if (g_run != 0) {
			g_cap >> frame;
			if (frame.empty()) break;
			int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
			g_dontset = 1;
			cv::setTrackbarPos("Position", "Hi i am She11", current_pos);
			cv::imshow("Hi i am She11", frame);
			g_run-= 1;

		}
		char c = (char)cv::waitKey(10);
		if (c == 's') {
			g_run = 1; cout << "Run mode , run = "<< g_run<<endl;
		}
		if (c == 'r')
		{
			g_run = -1; cout << "Rnn mode ,run =" << g_run << endl;
		}
		if (c == 'v') {
			break;
		}
	}
	//              cv::waitKey(0);
	return(0);
}
