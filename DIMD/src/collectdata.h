/*
 * collectdata.h
 *
 *  Created on: Jul 21, 2015
 *      Author: sriram
 */

#ifndef SRC_COLLECTDATA_H_
#define SRC_COLLECTDATA_H_
#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <yarp/sig/all.h>
#include <cv.h>
#include <iostream>
using namespace std;
using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::sig;
using namespace cv;

namespace collect {

class collectdata {
    Stamp s_iLeft, s_iDepth, s_vPort, s_iPort;
    BufferedPort<ImageOf<PixelRgb> > iLeftIn;
    BufferedPort<ImageOf<PixelRgb> > iDepthIn;
    BufferedPort<Bottle> vPortIn, iPortIn;
    string moduleName;
protected:
    cv::Mat iLeft;
    cv::Mat iDepth;
    double velocityArray[6];
    double inertiaArray[6];
public:
    collectdata();
	collectdata(string moduleName_ = "imd");
	void open();
	void collectImage();
	void collectDisparity();
	void collectVelocity();
	void collectInertia();
	void collectImage(cv::Mat &iLeft_);
	void collectDisparity(cv::Mat &iDepth_);
	void collectVelocity(double *vPort_);
	void collectInertia(double *iPort_);
	bool interruptModule();
	bool close();
	virtual ~collectdata();
};

} /* namespace collect */

#endif /* SRC_COLLECTDATA_H_ */
