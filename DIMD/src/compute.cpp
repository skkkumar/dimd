/*
 * compute.cpp
 *
 *  Created on: Jul 22, 2015
 *      Author: sriram
 */

#include "compute.h"

namespace comp {

compute::compute(string moduleName):collectdata(moduleName) {
}

bool compute::checkDataPresent() {
	if (iLeft.data == NULL and iDepth.data == NULL)
		return false;
	else
		return true;
}

void compute::collectData_direct() {
	collectImage();
	collectDisparity();
	collectVelocity();
	collectInertia();
}

void compute::collectData_prev(compute &O_t2) {
	collectImage(O_t2.iLeft);
	collectDisparity(O_t2.iDepth);
	collectVelocity(O_t2.velocityArray);
	collectInertia(O_t2.inertiaArray);
}

std::vector<cv::Point2f> compute::getcorners() {
	return corners;
}

std::vector<cv::Point2f> compute::getOFcorners() {
	return OFcorners;
}

void compute::harrisCorner() {
	cv::Mat src;
	cv::cvtColor(iLeft, src, CV_BGR2GRAY);
	goodFeaturesToTrack(src, corners, maxCorners, qualityLevel, minDistance,
			cv::Mat(), blockSize, false, k);
	return;
}

void compute::getOF_LK(compute &O_t2) {
	cv::Mat imageL1;
	cv::Mat imageL2;
	cv::cvtColor(O_t2.iLeft, imageL2, CV_BGR2GRAY);
	cv::cvtColor(iLeft, imageL1, CV_BGR2GRAY);
	blur(imageL2, imageL2, Size(3, 3));
	blur(imageL1, imageL1, Size(3, 3));
	calcOpticalFlowPyrLK(imageL1, imageL2, corners, OFcorners, features_found,
			feature_errors, Size(window_size, window_size), maxLevel,
			cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, max_iter,
			epsilon), flags);
	cleanOF();
	return;
}

void compute::cleanOF() {
	std::vector<cv::Point2f> temp_corners = corners;
	std::vector<cv::Point2f> temp_OFcorners = OFcorners;
	corners.clear();
	OFcorners.clear();
	for (int i = 0; i < features_found.size(); i++) {
		if (features_found[i] != 0 && feature_errors[i] < 45) {
			corners.push_back(temp_corners[i]);
			OFcorners.push_back(temp_OFcorners[i]);
		}
	}
	return;
}


compute::~compute() {

}

} /* namespace comp */
