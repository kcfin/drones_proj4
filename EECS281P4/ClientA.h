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


class ClientA : public Client {

public:
    
    virtual void getInput() {
        sg.getInput();
    }
    
    virtual void findPath() {
        sg.findPath();
    }

};

#endif
