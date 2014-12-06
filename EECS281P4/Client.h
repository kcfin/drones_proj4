//
//  Client.h
//  EECS281P4
//
//  Created by kcfin on 11/19/14.
//  Copyright (c) 2014 kcfin. All rights reserved.
//

#ifndef EECS281P4_Client_h
#define EECS281P4_Client_h
#include <queue>
#include <vector>
#include <math.h>
#include <float.h>
using namespace std;

class Client {
    
public:
    
    virtual void getInput() { }
    
    virtual void findPath() { }
    
    virtual void printPath() { }
    
    //    void testPrint() {
    //        for(unsigned int i = 0; i < facilities.size(); ++i) {
    //            Facility *f = &facilities[i];
    //            cout << "Facility " << f->facNum << ": " << f->x << " " << f->y << endl;
    //        }
    //
    //        for(unsigned int i = 0; i < paths.size(); ++i) {
    //            Path *p = &edges[i];
    //            cout << "Path: " << p->fac1->facNum << " " << p->fac2->facNum << " " << p->distance << endl;
    //        }
    //    }
};


#endif
