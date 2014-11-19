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
#include <queue>
#include <math.h>
using namespace std;

class SparseGraph {
public:
    struct Facility {
        int facNum = 0;
        int x = 0;
        int y = 0;
        Facility *rep = this;
        
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
    
    struct leastDistance {
        bool operator() (const Path *p1, const Path *p2) const {
            return p1->distance < p2->distance;
        }
    };
    
    vector<Facility> facilities;
    vector<Path> edges;
    priority_queue<Path*, vector<Path*>, leastDistance> paths;
    queue<Path*> printPaths;
    double totalDistance = 0;
    
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
            
            // maybe dynamic memory??
            
            Facility *f1;
            Facility *f2;
            int idx1, idx2;
            cin >> idx1 >> idx2;
            f1 = &facilities[idx1];
            f2 = &facilities[idx2];
            Path path(f1, f2);
            Path *p = &path;
            edges.push_back(path);
            paths.push(p);
        }
    }
    
    bool canTravel(Path *path) {
        Facility *f1 = path->fac1;
        Facility *f2 = path->fac2;
        
        
        while(f1 != f1->rep) {
            f1 = f1->rep;
        }
        
        while(f2 != f2->rep) {
            f2 = f2->rep;
        }
        
        if(f1 != f2) {
            setReps(path, f1, f2);
            return true;
        } else {
            return false;
        }
    }
    
    void setReps(Path *path, Facility *rep1, Facility *rep2) {
        if(rep1->facNum < rep2->facNum) {
            path->fac1->rep = rep1;
            path->fac2->rep = rep1;
        } else {
            path->fac1->rep = rep2;
            path->fac2->rep = rep2;
        }
    }
    
    void findPath() {
        
        while(!paths.empty()) {
            Path *path = paths.top();
            
            if(canTravel(path)) {
                totalDistance += path->distance;
                printPaths.push(path);
            }
            
            paths.pop();
        }
    }
    
    void printPath() {
        
        
        ostringstream os;
        os << totalDistance << '\n';
        
        while(!printPaths.empty()) {
            Path *path = printPaths.front();
            os << path->fac1->facNum << " " << path->fac2->facNum << '\n';
            printPaths.pop();
        }
    }
    
    void testPrint() {
        for(int i = 0; i < facilities.size(); ++i) {
            Facility *f = &facilities[i];
            cout << "Facility " << f->facNum << ": " << f->x << " " << f->y << endl;
        }
    }
};

#endif
