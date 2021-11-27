#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main()
{

	//==============read imgage===========================
	cv::Mat img = cv::imread("C:\\Users\\weijian.huang\\Desktop\\CodeProjects\\TestFiles\\R-C.jpg", -1);
	if (img.empty())
		return -1;
	cv::namedWindow("ShowImage", cv::WINDOW_AUTOSIZE);
	cv::imshow("ShowImage", img);
	cv::waitKey(0);
	cv::destroyWindow("ShowImage");

	////==================read video=======================
	//cv::namedWindow("ShowVideo", cv::WINDOW_AUTOSIZE);
	//cv::VideoCapture cap;
	//cap.open("C:\\Users\\weijian.huang\\Desktop\\CodeProjects\\TestFiles\\test.mp4");
	//cv::Mat frame;
	//for (;;)
	//{
	//	cap >> frame;
	//	if (frame.empty())
	//		break;
	//	cv::imshow("ShowVideo", frame);
	//	if (cv::waitKey(16) >= 0)
	//		break;
	//}

	////========================image simple transform =======================
	//cv::Mat image = cv::imread("C:\\Users\\weijian.huang\\Desktop\\CodeProjects\\TestFiles\\R-C.jpg", -1);
	//cv::namedWindow("SimpleTransform-in", cv::WINDOW_AUTOSIZE);
	//cv::namedWindow("SimpleTransform-out", cv::WINDOW_AUTOSIZE);
	//cv::imshow("SimpleTransform-in", image);
	//cv::Mat out;
	//cv::GaussianBlur(image, out, cv::Size(5, 5), 3, 3);
	//cv::GaussianBlur(out, out, cv::Size(5, 5), 3, 3);
	//cv::imshow("SimpleTransform-out", out);
	//cv::waitKey(0);

	////========================image simple transform V2=======================
	////降采样
	//cv::Mat img1, img2;
	//cv::namedWindow("SimpleTransformV2-in", cv::WINDOW_AUTOSIZE);
	//cv::namedWindow("SimpleTransformV2-out", cv::WINDOW_AUTOSIZE);
	//img1 = cv::imread("C:\\Users\\weijian.huang\\Desktop\\CodeProjects\\TestFiles\\R-C.jpg");
	//cv::imshow("SimpleTransformV2-in", img1);
	//cv::pyrDown(img1, img2);
	//cv::imshow("SimpleTransformV2-out", img2);
	//cv::waitKey(0);

	////========================image simple transform V3=======================
	////canny边缘检测器
	//cv::Mat img_rgb, img_gray, img_cny;
	//cv::namedWindow("SimpleTransformV3-Gray", cv::WINDOW_AUTOSIZE);
	//cv::namedWindow("SimpleTransformV3-Canny", cv::WINDOW_AUTOSIZE);
	//img_rgb = cv::imread("C:\\Users\\weijian.huang\\Desktop\\CodeProjects\\TestFiles\\R-C.jpg");
	//cv::cvtColor(img_rgb, img_gray, cv::COLOR_BGR2GRAY);
	//cv::imshow("SimpleTransformV3-Gray", img_gray);
	//cv::Canny(img_rgb, img_cny, 10, 100, 3, true);
	//cv::imshow("SimpleTransformV3-Canny", img_cny);	
	////读取像素值
	//int x = 16, y = 32;
	//cv::Vec3b intensity = img_rgb.at<cv::Vec3b>(y, x);
	//uchar blue = intensity[0];
	//uchar green = intensity[1];
	//uchar red = intensity[2];

	//std::cout << "At (x, y) = (" << x << ", " << y << "): (blue, green, red) = ("
	//	<< (unsigned int)blue << ", " << (unsigned int)green << ", " << (unsigned int)red << ")" << std::endl;
	//std::cout << "Gray pixel there is: " <<
	//	(unsigned int)img_gray.at<uchar>(y, x) << std::endl;
	//x /= 4;
	//y /= 4;
	//img_cny.at<uchar>(x, y) = 128;
	//cv::waitKey(0);

	////===================read in camera=================
	//cv::VideoCapture cap;
	//cap.open(0);
	//if (!cap.isOpened())
	//{
	//	std::cerr << "Couldn't open capture." << std::endl;
	//	return 0;
	//}
	//cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);
	//cv::Mat frame;
	//for (;;)
	//{
	//	cap >> frame;
	//	if (frame.empty())
	//		break;
	//	cv::imshow("Camera", frame);
	//	if (cv::waitKey(16) >= 0)
	//		break;
	//}

	////=================write in avi file=================
	//cv::namedWindow("origin", cv::WINDOW_AUTOSIZE);
	//cv::namedWindow("LogPolar", cv::WINDOW_AUTOSIZE);
	//cv::VideoCapture capture("C:\\Users\\weijian.huang\\Desktop\\CodeProjects\\TestFiles\\test.mp4");
	//double fps = capture.get(cv::CAP_PROP_FPS);
	//cv::Size size(
	//	(int)capture.get(cv::CAP_PROP_FRAME_WIDTH),
	//	(int)capture.get(cv::CAP_PROP_FRAME_HEIGHT)
	//);
	//cv::VideoWriter writer;
	//writer.open("C:\\Users\\weijian.huang\\Desktop\\CodeProjects\\TestFiles\\test01.mp4",
	//	cv::CAP_OPENCV_MJPEG, fps, size); //以前是CV_FOURCC('M', 'J', 'P', 'G'),后改成cv::CAP_OPENCV_MJPEG
	//if (writer.isOpened())
	//	std::cout << "=====================open=================" << std::endl;
	//cv::Mat logpolar_frame, bgr_frame;
	//for (;;)
	//{
	//	capture >> bgr_frame;
	//	if (bgr_frame.empty())
	//		break;
	//	cv::imshow("origin", bgr_frame);
	//	cv::logPolar(bgr_frame, logpolar_frame,
	//		cv::Point2f(bgr_frame.cols / 2, bgr_frame.rows / 2), 40, cv::WARP_FILL_OUTLIERS);
	//	cv::imshow("LogPolar", logpolar_frame);
	//	writer << logpolar_frame;
	//	char c = cv::waitKey(10);
	//	if (c == 27)
	//		break;
	//}
	//capture.release();


	

	return 0;
}

////=====================show video v2======================
//int g_slider_position = 0;
//int g_run = 1, g_dontset = 0;
//cv::VideoCapture g_cap;
//
//void OnTrackbarSlide(int pos, void*) {
//	g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
//	std::cout << "pos:" << pos << std::endl;
//	if (!g_dontset)
//		g_run = 1;
//	g_dontset = 0;
//}
//
//int main()
//{
//	cv::namedWindow("ShowVideoV2", cv::WINDOW_AUTOSIZE);
//	g_cap.open("C:\\Users\\weijian.huang\\Desktop\\CodeProjects\\TestFiles\\test.mp4");
//	int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
//	int tmpw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
//	int tmph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
//
//	std::cout << "Video has " << frames << "frames of dimensions("
//		<< tmpw << ", " << tmph << ")." << std::endl;
//	cv::createTrackbar("Position", "ShowVideoV2", &g_slider_position, frames, OnTrackbarSlide);
//	cv::Mat frame;
//	for (;;)
//	{
//		if (g_run != 0)
//		{
//			g_cap >> frame;
//			if (frame.empty())
//				break;
//			int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
//			g_dontset = 1;
//			cv::setTrackbarPos("Position", "ShowVideoV2", current_pos);
//			cv::imshow("ShowVideoV2", frame);
//			g_run -= 1;
//		}
//		char c = (char)cv::waitKey(10);
//		if (c == 's')
//		{
//			g_run = 1;
//			std::cout << "Single step, run = " << g_run << std::endl;
//		}
//		if (c == 'r')
//		{
//			g_run = -1;
//			std::cout << "Run mode, run = " << g_run << std::endl;
//		}
//		if (c == 27)
//			break;
//	}
//	return 0;
//}