//
//  ClientA.h
//  EECS281P4
//
//  Created by kcfin on 11/19/14.
//  Copyright (c) 2014 kcfin. All rights reserved.
//

#ifndef EECS281P4_ClientA_h
#define EECS281P4_ClientA_h
#include <queue>
#include "SparseGraph.h"
using namespace std;

// deliver as fast as possible
// drone type I
// cost efficient installation of beacons for drones to reach any facility
// from any other facility
// mst in the form of beacon installation costs
// facility can be unreachable

//sparse graph
//E much smaller than V2
//adj list
//kruskal

class ClientA : public Client {

public:
    SparseGraph map;
    
    void setMap() {
        map.getInput();
    }
    
    void findPath() {
    }

};

#endif
