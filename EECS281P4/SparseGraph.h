//
//  SparseGraph.h
//  EECS281P4
//
//  Created by kcfin on 11/19/14.
//  Copyright (c) 2014 kcfin. All rights reserved.
//

#ifndef EECS281P4_SparseGraph_h
#define EECS281P4_SparseGraph_h

#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;

class SparseGraph {
    
    struct Facility {
        int facNum = 0;
        int x = 0;
        int y = 0;
        
        Facility() {}
        
        Facility(int fac) : facNum(fac) {}
    };
    
    struct Path {
        Facility *fac1 = nullptr;
        Facility *fac2 = nullptr;
        double distance = 0;
        
        Path() {}
        
        Path(Facility *f1, Facility *f2) : fac1(f1), fac2(f2) {
            setDistance();
        }
        
        void setDistance() {
            double x = pow((fac1->x - fac2->x), 2);
            double y = pow((fac1->y - fac2->y), 2);
            distance = sqrt(x+y);
        }
        
    };
    
    vector<Facility> facilities;
    vector<Path> paths;
    
    void getInput() {
        int flush;
        int facNum;
        
        cin >> flush >> facNum;
        
        for(int i = 0; i < facNum; ++i) {
            Facility fac(i);
            cin >> fac.x >> fac.y;
            facilities.push_back(fac);
        }
        
        int pathNum;
        
        cin >> flush >> pathNum;
        
        for(int i = 0; i < pathNum; ++i) {
            Facility *f1;
            Facility *f2;
            int idx1, idx2;
            cin >> idx1 >> idx2;
            f1 = &facilities[idx1];
            f2 = &facilities[idx2];
            paths.push_back(Path(f1, f2));
        }
        
    }
    
};

#endif
