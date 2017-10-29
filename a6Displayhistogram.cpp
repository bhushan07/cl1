#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
	Mat image, dst;
	Vec3b intensity;
	image = imread("/home/bhushan/Labs/CL1/CL1/A6/image.tiff", 1 );
	if( !image.data )
	{ return -1; }
	cvtColor(image, image, cv::COLOR_BGR2GRAY);
	Mat new_image = Mat::zeros( 320,520, image.type() );
	long int *count=new long int[256];
	for(int j=0;j<256;j++)
	{
		count[j]=0;
	}
	for( int y = 1; y < image.rows-1; y++ )
	{ 
		for( int x = 1; x < image.cols-1; x++ )
		{
			int p=image.at<Vec3b>(y,x)[0];
			count[p]++;
		}
	}
	long int max=0;
	for(int j=0;j<256;j++)
	{
		//cout<<count[j]<<"\t";
		if(count[j]>max)
		max=count[j];
	}
	cout<<max;
	long int d=max/300;
	Scalar col;
	col=Scalar(255,255,255);
	for(int j=0;j<254;j++)
	{
		line( new_image, Point( j*2, 310-(count[j]/d) ), Point((j+1)*2, 310-(count[j+1]/d)), col, 2, 8 );
	}

	namedWindow("Image", WINDOW_NORMAL);
	imshow("Image",image);
	imshow("Histogram",new_image);
	waitKey(0);
	return 0;
}
