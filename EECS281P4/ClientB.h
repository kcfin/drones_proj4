//
//  ClientB.h
//  EECS281P4
//
//  Created by kcfin on 12/3/14.
//  Copyright (c) 2014 kcfin. All rights reserved.
//

#ifndef EECS281P4_ClientB_h
#define EECS281P4_ClientB_h
#include <float.h>

class ClientB : public Client {
public:
    
    
    
//    start with 2 sets of vertices, ins and outs
//    select first in arbitrarily
//    iteratively until no more outs
//    choose out with smallest distance from any in
//    move v from outs to ins
//    
//    for each v record
//        kv - has k been visited (initially false)
//        dv - minimal edge weight to v (initially infinity)
//        pv - what vertex is parent of v (initially unknown)
//        
//    repeat until every kv is true
//        from the set of vertices for which kv is false, select the vertex v having the smallest tentative distance dv
//        set kv to true
//        for each vertex w adjacent to v for which kw is false
//        test whether dw is greater than dv.  if it is, set dw to dv and set pw to v
    
    
    virtual void getInput() {
        string flush;
        int facNum;
        cin >> flush >> facNum;
        
        for(int i = 0; i < facNum; ++i) {
            int x, y;
            cin >> x >> y;
            Facility *f = new Facility(i, x, y);
            facilities.push_back(f);
        }
    }
    
    struct Facility {
        int facNum;
        int x;
        int y;
        bool visited;
        double minDist;
        Facility *parent;
        
        Facility() : facNum(0), x(0), y(0), visited(false), minDist(DBL_MAX), parent(nullptr) {}
        
        Facility(int fac, int xc, int yc) : facNum(fac), x(xc), y(yc), visited(false), minDist(DBL_MAX), parent(nullptr) {}
        
        ~Facility() {
            delete parent;
        }
        
    };
    
    double findDistance(Facility *fac1, Facility *fac2) {
        double x = pow((fac1->x - fac2->x), 2);
        double y = pow((fac1->y - fac2->y), 2);
        return sqrt(x+y);
    }
    
    virtual void findPath() {
        
        Facility *f = facilities[0];
        
        // how to check if all are true
        while(true) {
            
            for(int i = 0; i < facilities.size(); ++i) {
                if(facilities[[i].visited == false) {
                    double distance = findDistance(f, facilities[i]);
                    
                }
            }
        }
    }
    
    
//    virtual void findPath() {
//        Facility *f = facilities[0];
//        Facility *nextFac;
//        f->visited = true;
//        double min = DBL_MAX;
//        double nextDist = DBL_MAX;
//        
//        while(true) {
//            for(int i = 0; i < facilities.size(); ++i) {
//                if(facilities[i].visited == false) {
//                    nextDist = findDistance(f, facilities[i]);
//                    
//                    if(minDist < nextDist) {
//                        minDist = nextDist;
//                        nextFac = facilities[i];
//                    }
//                }
//            }
//            
//            nextFac->minDist = minDist;
//            nextFac->visited = true;
//            
//            for(int i = 0; i < facilities.size(); ++i) {
//                if(facilities[i].visited == false) {
//                    
//                }
//            }
//        }
//        
//    }
    
    
//    virtual void findPath() {
//        
//        Facility *f = facilities[0];
//        int nextFac = 0;
//        double minDist = DBL_MAX;
//        double nextDist;
//        
//        while(!facilities.empty()) {
//            visited.push_back(f);
//            facilities.erase(f);
//            
//            for(int i = 0; i < facilities.size(); ++i) {
//                nextDist = findDistance(f, facilities[i]);
//                
//                if(dist < minDist) {
//                    minDist = dist;
//                    nextFac = i;
//                }
//            }
//            
//            f = facilities[nextFac];
//
//        }
//
//    }
};

#endif
