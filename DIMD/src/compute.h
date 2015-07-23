/*
 * compute.h
 *
 *  Created on: Jul 22, 2015
 *      Author: sriram
 */

#ifndef SRC_COMPUTE_H_
#define SRC_COMPUTE_H_
#include "collectdata.h"
using namespace collect;
//for harris corners
#define maxCorners 200
#define qualityLevel 0.05
#define minDistance 10.0
#define blockSize 10
#define k 0.04
//==================>
//for LK Optical flow
#define window_size 51
#define maxLevel 5
#define max_iter 20
#define epsilon 0.3
#define flags 0
//==================>

namespace comp {

class compute: public collectdata{
    std::vector<cv::Point2f> corners;
    std::vector<cv::Point2f> OFcorners;
    std::vector<uchar> features_found;
    std::vector<float> feature_errors;
public:
    compute(string moduleName = "imd");
	void collectData();
	bool checkDataPresent();
    std::vector<cv::Point2f> getcorners();
	std::vector<cv::Point2f> getOFcorners();
	void collectData_direct();
	void collectData_prev(compute &O_t2);
	void harrisCorner();
	void getOF_LK(compute &O_t2);
	void cleanOF();
	virtual ~compute();
};

} /* namespace comp */

#endif /* SRC_COMPUTE_H_ */
