/*
 * DIMD.cpp
 *
 *  Created on: Jul 22, 2015
 *      Author: sriram
 */

#include "DIMD.h"

namespace dimd {

double DIMD::getPeriod(){
	return 0;
}


bool DIMD::updateModule(){
	return true;
}
bool DIMD::respond(const Bottle& command, Bottle& reply){
	return true;
}
bool DIMD::configure(ResourceFinder &rf){
	data_t1 = compute("imd");
	data_t2 = compute("imd");
	data_t1.open();
	data_t2.open();
	return true;
}
bool DIMD::interruptModule(){
	return true;
}
bool DIMD::close(){
//	delete data_t1;
//	delete data_t2;
	return true;
}

} /* namespace dimd */


