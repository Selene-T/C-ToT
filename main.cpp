#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>
#include <Windows.h>
#include "common/attachment.hpp"
#include "common/materials.hpp"
#include "common/rpm.hpp"

unsigned long base;
RPM emulator;

using namespace cv;

int main() {
	//::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	// Test attaching to project64
	if (attachToProject64()) {
		cout << "Successfully attached to TLoZ:OoT Project64!\n";
	}
	const cv::String totTitle = "Tracker of Time";

	// Test inventory setup
	uint8_t items[24] = { 0,  1,  2,  3,  4,  5,
						 					  6,  8,  9, 11, 12, 13,
						 					 14, 15, 16, 17, 18, 19,
											 20, 20, 20, 20, 33, 33};

	// Gather an inventory image based on all current items
	cv::Mat inv = matInventory(items);
	// INTER_CUBIC: softened image, best option for reduced size
	// INTER_AREA: original pixilated look, awful for reduced size
	cv::resize(inv, inv, cv::Size(), 2.0, 2.0, INTER_AREA);

	namedWindow(totTitle, WINDOW_AUTOSIZE);
	cv::imshow(totTitle, inv);
	cv::moveWindow(totTitle, 100, 100);
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}