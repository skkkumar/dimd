/*
 * DIMD.h
 *
 *  Created on: Jul 22, 2015
 *      Author: sriram
 */

#ifndef SRC_DIMD_H_
#define SRC_DIMD_H_
#include "compute.h"
#include <yarp/os/RFModule.h>
using namespace comp;
namespace dimd {

class DIMD : public RFModule{
	compute data_t1, data_t2;
public:
	double getPeriod();
	bool updateModule();
	bool respond(const Bottle& command, Bottle& reply);
	bool configure(ResourceFinder &rf);
	bool interruptModule();
	bool close();
};

} /* namespace dimd */

#endif /* SRC_DIMD_H_ */
