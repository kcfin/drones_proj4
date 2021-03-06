//
//  ClientB.h
//  EECS281P4
//
//  Created by kcfin on 12/3/14.
//  Copyright (c) 2014 kcfin. All rights reserved.
//

#ifndef EECS281P4_ClientB_h
#define EECS281P4_ClientB_h

class ClientB : public Client {
public:
    
    struct Facility {
        int facNum;
        int x;
        int y;
        double minDist;
        Facility *parent;
        
        Facility() : facNum(0), x(0), y(0), minDist(DBL_MAX), parent(nullptr) {}
        
        Facility(int fac, int xc, int yc) : facNum(fac), x(xc), y(yc), minDist(DBL_MAX), parent(nullptr) {}
        
    };
    
    vector<Facility*> unvisited;
    vector<Facility> facilities;
    double totalDistance = 0;
    int facs = 0;
    
    virtual void getInput() {
        string flush;
        cin >> flush >> facs;
        unvisited.reserve(facs);
        facilities.reserve(facs);
        
        for(int i = 0; i < facs; ++i) {
            double x, y;
            cin >> x >> y;
            addFacilities(i, x, y);
        }
    }
    
    double findDistance(Facility *fac1, Facility *fac2) {
        return pow((fac1->x-fac2->x), 2) + pow((fac1->y-fac2->y), 2);
    }
    
    void addFacilities(int fac, int xc, int yc) {
        facilities.push_back(Facility(fac, xc, yc));
        unvisited.push_back(&facilities.back());
    }
    
    virtual void findPath() {
        uint facsVisited = 0;
        facilities[0].minDist = 0;

        while(facsVisited < facilities.size()) {
            
            uint nextIdx = 0;
            
            for(uint i = 0; i < unvisited.size(); ++i) {
                if(unvisited[i]->minDist < unvisited[nextIdx]->minDist) {
                    nextIdx = i;
                }
            }

            for(uint i = 0; i < unvisited.size(); i++) {
                if(i != nextIdx) {
                    double dist = findDistance(unvisited[nextIdx], unvisited[i]);
                    if(dist < unvisited[i]->minDist) {
                        unvisited[i]->minDist = dist;
                        unvisited[i]->parent = unvisited[nextIdx];
                    }
                }
            }
            
            totalDistance += sqrt(unvisited[nextIdx]->minDist);
            unvisited.erase(unvisited.begin() + nextIdx);
            facsVisited++;
        }
    }
    
    virtual void printPath() {
        cout << totalDistance << '\n';

        for(uint i = 0; i < facilities.size(); ++i) {
            Facility *f = &facilities[i];
            if(f->parent != nullptr) {
                if(f->facNum < f->parent->facNum) {
                    cout << f->facNum << " " << f->parent->facNum << '\n';
                } else {
                    cout << f->parent->facNum << " " << f->facNum << '\n';
                }
            }
        }
    }
};

#endif
