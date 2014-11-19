//
//  project4.h
//  EECS281P4
//
//  Created by kcfin on 11/19/14.
//  Copyright (c) 2014 kcfin. All rights reserved.
//

#ifndef __EECS281P4__project4__
#define __EECS281P4__project4__

#include <stdio.h>
#include <getopt.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Client.h"
#include "ClientA.h"
using namespace std;

Client * client;
ClientA ca;

void getOpts(int argc, char * argv[]);

#endif /* defined(__EECS281P4__project4__) */
