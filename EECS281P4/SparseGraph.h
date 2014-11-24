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
#include <fstream>
using namespace std;

class SparseGraph {
public:
    class Facility {
    public:
        int facNum;
        int x;
        int y;
        int rep;
        // how to fix this?
//        Facility *rep;
        
        Facility() : facNum(0), x(0), y(0), rep(0) {}
        
        Facility(int fac, int xc, int yc) : facNum(fac), x(xc), y(yc), rep(fac) {}
    };
    
    class Path {
    public:
        Facility *fac1 = nullptr;
        Facility *fac2 = nullptr;
        double distance = 0;
        
        Path() {}
        
        Path(Facility *f1, Facility *f2) : fac1(f1), fac2(f2), distance(0) {
            setDistance();
        }
        
        void setDistance() {
            double x = pow((fac1->x - fac2->x), 2);
            double y = pow((fac1->y - fac2->y), 2);
            distance = sqrt(x+y);
        }
        
        ~Path() {
            cout << "object is being deleted" << endl;
        }
        
    };
    
    struct leastDistance {
        bool operator() (const Path *p1, const Path *p2) const {
            return p1->distance > p2->distance;
        }
    };
    
    vector<Facility> facilities;
    vector<Path> edges;
    priority_queue<Path*, vector<Path*>, leastDistance> paths;
    queue<Path*> printPaths;
    double totalDistance = 0;
    
    void getInput() {
        string flush;
        int facNum;
        cin >> flush >> facNum;
        
        for(int i = 0; i < facNum; ++i) {
            int x, y;
            cin >> x >> y;
            facilities.push_back(Facility(i, x, y));
        }
        
        int pathNum;
        cin >> flush >> pathNum;
        
        for(int i = 0; i < pathNum; ++i) {
            
            // maybe dynamic memory??
            
            int idx1, idx2;
            cin >> idx1 >> idx2;
//            Facility *f1 = &facilities[idx1];
//            Facility *f2 = &facilities[idx2];
//            Path path(&facilities[idx1], &facilities[idx2]);
//            Path *p = &path;
//            edges.push_back(Path(&facilities[idx1], &facilities[idx2]));
//            Path *p = &edges[edges.size() - 1];
            Path *p = new Path(&facilities[idx1], &facilities[idx2]);
            paths.push(p);
        }
    }
    
    bool canTravel(Path *path) {
        Facility *f1 = path->fac1;
        Facility *f2 = path->fac2;
        
        while(f1->facNum != f1->rep) {
            f1 = &facilities[f1->rep];
        }
        
        while(f2->facNum != f2->rep) {
            f2 = &facilities[f2->rep];
        }
        
        if(f1->facNum != f2->facNum) {
            setReps(path, f1->facNum, f2->facNum);
            return true;
        } else {
            return false;
        }
//
//        
//        while(f1 != f1->rep) {
//            f1 = f1->rep;
//        }
//        
//        while(f2 != f2->rep) {
//            f2 = f2->rep;
//        }
//        
//        if(f1 != f2) {
//            setReps(path, f1, f2);
//            return true;
//        } else {
//            return false;
//        }
    }
    
    void setReps(Path *path, int rep1, int rep2) {
        int temp;
        Facility *parent;
        
        if(rep1 < rep2) {
            parent = path->fac2;
            while(parent->rep != rep1) {
                temp = path->fac2->rep;
                path->fac2->rep = rep1;
                parent = &facilities[temp];
            }
        } else {
            parent = path->fac1;
            while(parent->rep != rep2) {
                temp = path->fac1->rep;
                path->fac1->rep = rep2;
                parent = &facilities[temp];
            }
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
        
        cout << os.str();
    }
    
    void testPrint() {
        for(int i = 0; i < facilities.size(); ++i) {
            Facility *f = &facilities[i];
            cout << "Facility " << f->facNum << ": " << f->x << " " << f->y << endl;
        }
        
        for(int i = 0; i < paths.size(); ++i) {
            Path *p = &edges[i];
            cout << "Path: " << p->fac1->facNum << " " << p->fac2->facNum << " " << p->distance << endl;
        }
    }
};

#endif
