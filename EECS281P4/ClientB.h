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
        double x;
        double y;
        bool visited;
        double minDist;
        Facility *parent;
        
        Facility() : facNum(0), x(0), y(0), visited(false), minDist(DBL_MAX), parent(nullptr) {}
        
        Facility(int fac, double xc, double yc) : facNum(fac), x(xc), y(yc), visited(false), minDist(DBL_MAX), parent(nullptr) {}
        
    };
    
    struct leastDistance {
        bool operator() (const Facility *f1, const Facility *f2) const {
            if(f1->minDist == f2->minDist) {
                return f1->facNum > f2->facNum;
            }else {
                return f1->minDist > f2->minDist;
            }
        }
    };
    
    vector<Facility> facilities;
    priority_queue<Facility*, vector<Facility*>, leastDistance> paths;
    double totalDistance = 0;
    int facs = 0;
    
    virtual void getInput() {
        string flush;
        cin >> flush >> facs;
        
        for(int i = 0; i < facs; ++i) {
            double x, y;
            cin >> x >> y;
            facilities.push_back(Facility(i, x, y));
        }
    }
    
    double findDistance(Facility *fac1, Facility *fac2) {
        return sqrt(pow((fac1->x-fac2->x), 2) + pow((fac1->y-fac2->y), 2));
    }

    
    virtual void findPath() {
        Facility *curFac = &facilities[0];
        curFac->minDist = 0;
        paths.push(curFac);
        int count = 0;
        
        while(count != facs) {
            
            curFac = paths.top();
            curFac->visited = true;
            totalDistance += curFac->minDist;
            count++;
            paths.pop();
            updateDistances(curFac);
        }
    }
    
    void updateDistances(Facility *curFac) {
        for(int i = 0; i < facs; i++) {
            Facility *update = &facilities[i];
            if(i != curFac->facNum && update->visited == false) {
                double dist = findDistance(curFac, update);
                if(dist < update->minDist) {
                    update->minDist = dist;
                    update->parent = curFac;
                    paths.push(update);
                }
            }
        }
    }
    
    virtual void printPath() {
        cout << totalDistance << '\n';
        
        for(int i = 0; i < facs; ++i) {
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
