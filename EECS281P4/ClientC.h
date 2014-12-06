//
//  ClientC.h
//  EECS281P4
//
//  Created by kcfin on 12/6/14.
//  Copyright (c) 2014 kcfin. All rights reserved.
//

#ifndef EECS281P4_ClientC_h
#define EECS281P4_ClientC_h

class ClientC : public Client {
public:
    
    class Facility {
    public:
        int facNum;
        double x;
        double y;
        Facility *parent;
        
        Facility() : facNum(0), x(0), y(0), parent(nullptr) {}
        
        Facility(int fac, double xc, double yc) : facNum(fac), x(xc), y(yc), parent(nullptr) {}
    };
    
    vector<Facility> path;
    queue<Facility> unvisited;
    int facs = 0;
    
    virtual void getInput() {
        string flush;
        cin >> flush >> facs;
        
        for(int i = 0; i < facs; ++i) {
            double x, y;
            cin >> x >> y;
            unvisited.push(Facility(i, x, y));
        }
    }
    
    virtual void findPath() {
        permute();
    }
    
    void permute() {
        if(!unvisited.empty()) {
            for(int i = 0; i < unvisited.size(); ++i) {
                path.push_back(unvisited.front());
                unvisited.pop();
                permute();
                unvisited.push(path.back());
                path.pop_back();
            }
        }
    }
    
    virtual void printPath() {
        
    }
    
};


#endif
