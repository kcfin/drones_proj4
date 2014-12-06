//
//  ClientA.h
//  EECS281P4
//
//  Created by kcfin on 11/19/14.
//  Copyright (c) 2014 kcfin. All rights reserved.
//

#ifndef EECS281P4_ClientA_h
#define EECS281P4_ClientA_h

class ClientA : public Client {

public:
    
    class Facility {
    public:
        int facNum;
        int x;
        int y;
        int rep;
        
        Facility() : facNum(0), x(0), y(0), rep(0) {}
        
        Facility(int fac, int xc, int yc) : facNum(fac), x(xc), y(yc), rep(fac) {}
        
        ~Facility() {
            //            cout << "object is being deleted" << endl;
        }
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
            //            cout << "object is being deleted" << endl;
        }
        
    };
    
    queue<Path*> printPaths;
    vector<Facility*> facilities;
    double totalDistance = 0;
    
    struct leastDistance {
        bool operator() (const Path *p1, const Path *p2) const {
            return p1->distance > p2->distance;
        }
    };
    
    priority_queue<Path*, vector<Path*>, leastDistance> paths;
    
    virtual void getInput() {
        string flush;
        int facNum;
        cin >> flush >> facNum;
        
        for(int i = 0; i < facNum; ++i) {
            int x, y;
            cin >> x >> y;
            facilities.push_back(new Facility(i, x, y));
        }
        
        int pathNum;
        cin >> flush >> pathNum;
        
        for(int i = 0; i < pathNum; ++i) {
            
            int idx1, idx2;
            cin >> idx1 >> idx2;
            paths.push(new Path(facilities[idx1], facilities[idx2]));
        }
    }
    
    bool canTravel(Path *path) {
        Facility *f1 = path->fac1;
        Facility *f2 = path->fac2;
        
        while(f1->facNum != f1->rep) {
            f1 = facilities[f1->rep];
        }
        
        while(f2->facNum != f2->rep) {
            f2 = facilities[f2->rep];
        }
        
        if(f1->facNum != f2->facNum) {
            setReps(path, f1->facNum, f2->facNum);
            return true;
        } else {
            return false;
        }
    }
    
    void setReps(Path *path, int rep1, int rep2) {
        int temp;
        Facility *parent;
        
        if(rep1 < rep2) {
            parent = path->fac2;
            while(parent->rep != rep1) {
                temp = parent->rep;
                parent->rep = rep1;
                parent = facilities[temp];
            }
        } else {
            parent = path->fac1;
            while(parent->rep != rep2) {
                temp = parent->rep;
                parent->rep = rep2;
                parent = facilities[temp];
            }
        }
    }
    
    virtual void findPath() {
        
        while(!paths.empty()) {
            Path *path = paths.top();
            
            if(canTravel(path)) {
                totalDistance += path->distance;
                printPaths.push(path);
            } else {
                delete path;
            }
            
            paths.pop();
        }
    }
    
    virtual void printPath() {
        
        cout << totalDistance << '\n';
        
        while(!printPaths.empty()) {
            Path *path = printPaths.front();
            cout << path->fac1->facNum << " " << path->fac2->facNum << '\n';
            delete path;
            printPaths.pop();
        }
        
        deleteFacilities();
    }
    
    void deleteFacilities() {
        while(!facilities.empty()) {
            delete facilities.back();
            facilities.pop_back();
        }
    }

};

#endif
