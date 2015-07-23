/*
 * main.cpp
 *
 *  Created on: Jul 22, 2015
 *      Author: sriram
 */

#include <DIMD.h>
int main(int argc, char *argv[]) {
    Network yarp;
    if (!yarp.checkNetwork())
        return -1;
    dimd::DIMD imd_module;
    ResourceFinder rf;
    rf.configure(argc, argv);
    rf.setVerbose(true);
    return imd_module.runModule(rf);
    return 0;
}


