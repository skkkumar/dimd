/*
 * collectdata.cpp
 *
 *  Created on: Jul 21, 2015
 *      Author: sriram
 */

#include "collectdata.h"

namespace collect{

collectdata::collectdata(){}

collectdata::collectdata(string moduleName_ = "imd"): moduleName(moduleName_) {}

void collectdata::open(){
	iLeftIn.open(("/" + moduleName + "/iLeft:i").c_str());
	iDepthIn.open(("/" + moduleName + "/iDisparity:i").c_str());
	vPortIn.open(("/" + moduleName + "/vPort:i").c_str());
	iPortIn.open(("/" + moduleName + "/iPort:i").c_str());
}

void collectdata::collectImage() {
	iLeft = (IplImage *) iLeftIn.read()->getIplImage();
	if (iLeft == NULL) // this is the case if module is requested to quit while waiting for image
		return; // will have to change
	if (!iLeftIn.getEnvelope(s_iLeft))
		cout << "iLeft : No stamp found in input image. Will use private stamp"
				<< endl << flush;
	else
		cout << "iLeft image received at :" << s_iLeft.getTime() << endl
				<< flush;
	return;
}

void collectdata::collectImage(collectdata &O_t2) {
	iLeft = O_t2.getImage();
	return;
}

void collectdata::collectDisparity() {
	iDepth = (IplImage *) iDepthIn.read()->getIplImage();
	if (iDepth == NULL) // this is the case if module is requested to quit while waiting for image
		return; // will have to change
	if (!iDepthIn.getEnvelope(s_iDepth))
		cout << "iDepth : No stamp found in input image. Will use private stamp"
				<< endl << flush;
	else
		cout << "iDepth image received at :" << s_iDepth.getTime() << endl
				<< flush;
	return;
}
void collectdata::collectVelocity() {
	Bottle *message = vPortIn.read();
	for (int n = 0; n < 6; n++) {
		velocityArray[n] = message->get(n).asDouble();
	}
	if (!vPortIn.getEnvelope(s_vPort))
		cout
				<< "vPortIn : No stamp found in input image. Will use private stamp"
				<< endl << flush;
	else
		cout << "vPortIn image received at :" << s_vPort.getTime() << endl
				<< flush;
	return;
}

void collectdata::collectInertia() {
	Bottle *message = iPortIn.read();
	for (int n = 0; n < 6; n++) {
		inertiaArray[n] = message->get(n).asDouble();
	}
	if (!iPortIn.getEnvelope(s_iPort))
		cout
				<< "iPortIn : No stamp found in input image. Will use private stamp"
				<< endl << flush;
	else
		cout << "iPortIn image received at :" << s_iPort.getTime() << endl
				<< flush;
	return;
}

void collectdata::collectImage(cv::Mat &iLeft_) {
	iLeft = iLeft_;
	return;
}
void collectdata::collectDisparity(cv::Mat &iDepth_) {
	iDepth = iDepth_;
	return;
}
void collectdata::collectVelocity(double *vPort_) {
	for (int i = 0; i < 6; i++)
		velocityArray[i] = *(vPort + i);
	return;
}
void collectdata::collectInertia(double *iPort_){
	for (int i = 0; i < 6; i++)
		inertiaArray[i] = *(iPort + i);
	return;
}

bool collectdata::interruptModule(){
	iLeftIn.interrupt();
	iDepthIn.interrupt();
	vPortIn.interrupt();
	iPortIn.interrupt();
	return true;
}
bool collectdata::close(){
	iLeft.close();
	iDepthIn.close();
	vPortIn.close();
	iPortIn.close();
	return true;
}

collectdata::~collectdata() {
	if (interruptModule()){
		close();
	}
}

} /* namespace collect */
