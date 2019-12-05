#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

// 描述定义一些辅助宏
#define WINDOW_NAME "[shi-Tomasi角点检测]"
//　全局变量
Mat g_srcImage;
Mat g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
RNG g_rng(122345);

//　回调函数
void on_GoodFeaturesToTrack(int,void*)
{
    if(g_maxCornerNumber <= 1)
    {
	g_maxCornerNumber = 1;
    }
    // Shi-Tomasi算法
    vector<Point2f> corner;
    //　角点检测可接受的最小特征
    double qualityLevel = 0.01;
    // 角点之间的最小的距离
    double minDistance = 10;
    // 计算导数自相关矩阵是指定的邻域范围
    int blockSize = 3;
    // 权重系数
    double k = 0.04;
    Mat copy = g_srcImage.clone();
    // 进行角点检测
    goodFeaturesToTrack(g_grayImage,corner,g_maxCornerNumber,qualityLevel,minDistance,Mat(),blockSize,false,k);
    //　输出文字信息
    cout << ">此次检测到的角点数量为：　" << corner.size() << endl;
    //　绘制角点
    int r = 4;
    for(unsigned int i = 0; i < corner.size(); i++)
    {
	circle(copy,corner[i],r,Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255),g_rng.uniform(0,255)),-1,8,0);
    }
    //　显示更新窗口
    imshow(WINDOW_NAME,copy);
}
int main(int argc, char **argv) {
    g_srcImage = imread("../data/1.jpg",IMREAD_COLOR);
    if(g_srcImage.empty())
    {
	cout << "can't load the image" << endl;
    }
    cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);
    
    //　创建窗口和滑动条
    namedWindow(WINDOW_NAME,CV_WINDOW_FREERATIO);
    createTrackbar("最大角点数：　",WINDOW_NAME,&g_maxCornerNumber,g_maxTrackbarNumber,on_GoodFeaturesToTrack);
    imshow(WINDOW_NAME,g_srcImage);
    on_GoodFeaturesToTrack(0,0);
    waitKey(0);
    return 0;
}
