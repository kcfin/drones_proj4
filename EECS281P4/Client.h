//
//  Client.h
//  EECS281P4
//
//  Created by kcfin on 11/19/14.
//  Copyright (c) 2014 kcfin. All rights reserved.
//

#ifndef EECS281P4_Client_h
#define EECS281P4_Client_h

#include "SparseGraph.h"
#include "DenseGraph.h"

class Client {
public:
    
    SparseGraph sg;
    DenseGraph dg;
    
    virtual void getInput() {
        
    }
    
    virtual void findPath() {
        
    }
    
    virtual void printOutput() {
        sg.printPath();
    }
    
};

#endif
