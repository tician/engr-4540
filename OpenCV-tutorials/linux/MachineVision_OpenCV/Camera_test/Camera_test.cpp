#include "opencv2/core/core.hpp"		// Basic OpenCV structures (cv::Mat, Scalar)
#include "opencv2/highgui/highgui.hpp"	// OpenCV window I/O

#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

// Our window title/name (can be anything you want, obviously)
const char* WIN_DOH = "Yum, donuts";

// A Simple OpenCV C++ Camera Capture Program
int main()
{
	// Use any available capture source/camera
	VideoCapture capitan( CV_CAP_ANY );

	// Check that the capture source was successfully opened
	if ( !capitan.isOpened() )
	{
		cout << "ERROR: capture is NULL \n";
		getchar();
		exit(-1);
	}

	// Create an auto-sizing window using OpenCV 'highgui' library.
	// Will always be identified by its text-string name, so
	//  be sure to use a different name for each window to prevent
	//  trouble.
	namedWindow( WIN_DOH, CV_WINDOW_AUTOSIZE );

	// Start our infinite loop
	while (1)
	{
		// Create empty Mat for storage of the captured image frame
		Mat capture_frame;
		// Capture an image frame from the source
		capitan >> capture_frame;
		// Check that the capture source actually gave us image data
		if (capture_frame.empty())
		{
			cout << "ERROR: frame is null...\n";
			getchar();
			break;
		}

		// Show the captured image frame in the auto-sized window
		imshow( WIN_DOH, capture_frame );

		// We MUST call 'waitKey(n)' occasionally to ensure we continue getting
		//   data from the capture source.  The function waits for approximately
		//   'n' milliseconds for a key press.  If nothing is pressed, it returns
		//   -1 after at least 'n' milliseconds.  Otherwise, it returns the number
		//   of the key that was pressed (ASCII).  Calling waitKey(0) begins
		//   an infinite wait for a key press.
		char temp = waitKey(10);

		// Check what key was pressed
		// if temp==-1, then waitKey() timed out (there was no keypress)
		if (temp>=0)
		{
			// If it was a 'g', then save the frame to a file in the local directory
			if (temp == 'g')
			{
				imwrite("./frame_grab.jpg", capture_frame);
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
