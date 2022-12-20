#include <opencv2/core\core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
	IplImage* image = cvLoadImage("image/god.jpg");
	namedWindow("显示窗口");
	cvShowImage("显示窗口", image);
	cvWaitKey();
	cvReleaseImage(&image);
	cvDestroyAllWindows();
	return 0;
}
