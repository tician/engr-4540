#include "opencv2/core/core.hpp"		// Basic OpenCV structures (cv::Mat, Scalar)
#include "opencv2/highgui/highgui.hpp"	// OpenCV window I/O
#include "opencv2/imgproc/imgproc.hpp"	// Basic Image Processing functions

#include <cstdio>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

// Our window titles/names (can be anything you want, obviously)
const char* WIN_DOH = "Yum, donuts";
const char* WIN_DER = "Holy macaroni";
const char* WIN_DUP = "Whee!!";


int main( int argc, char** argv )
{
	// Use any available capture source/camera
	VideoCapture capitan( CV_CAP_ANY );

	// Check that the capture source was successfully opened
	if ( !capitan.isOpened() )
	{
		cout << "ERROR: capture is NULL \n";
		getchar();
		return -1;
	}

	// Get size of capture source's image output (usually 640x480)
	Size capitanSz = Size(	(int) capitan.get(CV_CAP_PROP_FRAME_WIDTH),
							(int) capitan.get(CV_CAP_PROP_FRAME_HEIGHT));
	// Create our first window
	namedWindow( WIN_DOH, CV_WINDOW_AUTOSIZE );
	// Create our second window
	namedWindow( WIN_DER, CV_WINDOW_AUTOSIZE );
	// Create our third window
	namedWindow( WIN_DUP, CV_WINDOW_AUTOSIZE );
	// Move the first window to top left corner of screen
	cvMoveWindow(WIN_DOH, 0, 0);
	// Move the second window below the first window
	cvMoveWindow(WIN_DER, 0, capitanSz.height);
	// Move the third window to right side of first window
	cvMoveWindow(WIN_DUP, capitanSz.width, 0);

	// Variables to control the filter settings
	unsigned int blur_uniform = 1;
	unsigned int blur_gaussian = 1;
	unsigned int blur_median = 1;
	unsigned int blur_bilateral = 1;

	// Very easy way to create strings from variables
	stringstream strstr (stringstream::in | stringstream::out );

	while (1)
	{
		// Create the empty Mat objects we will be using in the loop
		Mat capture_frame, gray_frame, filtered_frame, captions;

		// Capture an image frame from the source
		capitan >> capture_frame;

		// Convert the raw color image to a grayscale image
		cvtColor( capture_frame, gray_frame, CV_BGR2GRAY );


// Window the First
		// Show the raw captured image frame in the first auto-sized window
//		imshow( WIN_DOH, capture_frame );

	// Show Framerate
		// Clear the stringstream of data
		strstr.clear(); strstr.str("");
		// Get framerate from camera if supported
		strstr << "FPS: " << (double)capitan.get(CV_CAP_PROP_FPS);

		captions = capture_frame.clone();
		putText( captions, strstr.str().c_str(),
			Point( 20, 40 ),
			CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255) );
		imshow( WIN_DOH, captions );


// Window the Second
		// Clear the stringstream of data
		strstr.clear(); strstr.str("");

		// Copy the raw image data to another Mat object
		filtered_frame = capture_frame.clone();

		// Apply a Uniform/Box blur
		if (blur_uniform>1)
		{
			// Makes all changes to our copy of the image
			blur( filtered_frame, filtered_frame, Size(blur_uniform, blur_uniform), Point(-1,-1) );
			strstr << "Uniform Blur: " << blur_uniform;
		}
		// Apply a Gaussian blur
		if (blur_gaussian>1)
		{
			// Makes all changes to our copy of the image
			GaussianBlur( filtered_frame, filtered_frame, Size(blur_gaussian, blur_gaussian), 0, 0 );
			strstr << "Gaussian Blur: " << blur_gaussian;
		}
		// Apply a Median blur
		if (blur_median>1)
		{
			// Makes all changes to our copy of the image
			medianBlur( filtered_frame, filtered_frame, blur_median );
			strstr << "Median Blur: " << blur_median;
		}
		// Apply a Bilateral blur
		if (blur_bilateral>1)
		{
			// Makes all changes to our copy of the image
			bilateralFilter (gray_frame, filtered_frame, blur_bilateral, blur_bilateral*2, blur_bilateral/2 );
			strstr << "Bilateral Blur: " << blur_bilateral;
		}

		captions = filtered_frame.clone();
		putText( captions, strstr.str().c_str(),
			Point( 20, 40 ),
			CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255) );
		imshow( WIN_DUP, captions );

		// Show the filtered image in the second auto-sized window
//		imshow( WIN_DUP, filtered_frame );


// Window the Third

		// Down-scale the grayscale image by 2 (640x480 -> 320x240)
		pyrDown( gray_frame, gray_frame, Size( gray_frame.cols/2, gray_frame.rows/2) );

		// Show the grayscale and downsized image in the third auto-sized window
		imshow( WIN_DER, gray_frame );


// User Input

		// Always make a call to waitKey() somewhere in the loop to
		//   keep getting image data from capture source.
		// We can completely disregard the returned value, but
		//   it MUST be called to get new frames from the source.
		char temp = waitKey(30);

		if(temp >= 0)
		{
			// If it was a 'f', then save the frame to a file in the local directory
			if (temp == 'f')
			{
				imwrite("./frame_grab.jpg", capture_frame);
			}
			// Increase Uniform Blurring
			else if (temp == 'U')
			{
//				blur_uniform=1;
				blur_gaussian=1;
				blur_median=1;
				blur_bilateral=1;
				if (blur_uniform<31)
					blur_uniform+=2;
			}
			// Decrease Uniform Blurring
			else if (temp == 'u')
			{
				if (blur_uniform>2)
					blur_uniform-=2;
			}
			// Increase Gaussian Blurring
			else if (temp == 'G')
			{
				blur_uniform=1;
//				blur_gaussian=1;
				blur_median=1;
				blur_bilateral=1;
				if (blur_gaussian<31)
					blur_gaussian+=2;
			}
			// Decrease Gaussian Blurring
			else if (temp == 'g')
			{
				if (blur_gaussian>2)
					blur_gaussian-=2;
			}
			// Increase Median Blurring
			else if (temp == 'M')
			{
				blur_uniform=1;
				blur_gaussian=1;
//				blur_median=1;
				blur_bilateral=1;
				if (blur_median<31)
					blur_median+=2;
			}
			// Decrease Median Blurring
			else if (temp == 'm')
			{
				if (blur_median>2)
					blur_median-=2;
			}
			// Increase Bilateral Blurring
			else if (temp == 'B')
			{
				blur_uniform=1;
				blur_gaussian=1;
				blur_median=1;
//				blur_bilateral=1;
				if (blur_bilateral<31)
					blur_bilateral+=2;
			}
			// Decrease Bilateral Blurring
			else if (temp == 'b')
			{
				if (blur_bilateral>2)
					blur_bilateral-=2;
			}
			// Otherwise, break the loop and exit the program
			else
			{
				break;
			}
		}
	}
	return 0;
}
