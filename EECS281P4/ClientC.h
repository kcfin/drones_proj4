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
        int x;
        int y;
        bool visited;
        
        Facility() : facNum(0), x(0), y(0), visited(false) {}
        
        Facility(int fac, double xc, double yc) : facNum(fac), x(xc), y(yc), visited(false) {}
    };
    
    vector<Facility> path;
    vector<Facility> unvisited;
    vector<vector<double>> distances;
    vector<int> finalPath;
    double currBest = 0;
    double currDistance = 0;
    int facs = 0;
    
    
    double findDistance(Facility *fac1, Facility *fac2) {
        return sqrt(pow((fac1->x-fac2->x), 2) + pow((fac1->y-fac2->y), 2));
    }
    
    
    virtual void getInput() {
        string flush;
        cin >> flush >> facs;
        
        for(int i = 0; i < facs; ++i) {
            double x, y;
            cin >> x >> y;
            // make dynamic i think
            unvisited.push_back(Facility(i, x, y));
        }
    }
    
    void getMatrix() {
        
        
//        int size = pow(facs, 2)/2 + (facs/2) + (facs%2);
        
        distances = vector<vector<double>>(facs, vector<double>(facs, 0));
        
        for(int i = 0; i < facs; ++i) {
            for(int j = i; j < facs; ++j) {
                // think about only storing half of this
                distances[i][j] = distances[j][i] = findDistance(&unvisited[i], &unvisited[j]);
            }
        }
    }
    
    virtual void getGreedy() {
        getMatrix();
        
        int curIdx = 0;
        int nextIdx = 0;
        int facsVisited = 1;
        finalPath.push_back(0);
        unvisited[0].visited = true;
        
        while(facsVisited < facs) {
            double distance = DBL_MAX;
            for(int i = 0; i < facs; ++i) {
                if(i != curIdx && unvisited[i].visited == false) {
                    if(distances[curIdx][i] < distance) {
                        distance = distances[curIdx][i];
                        nextIdx = i;
                    }
                }
            }
            
            
            curIdx = nextIdx;
            finalPath.push_back(curIdx);
            currBest += distance;
            unvisited[curIdx].visited = true;
            facsVisited++;
        }
        
        currBest += distances[0][curIdx];
    }
    
    virtual void findPath() {
        
        getGreedy();
        permute();

    }
    
    void permute() {
        
        if(currDistance > currBest) {
            return;
        }
        if(unvisited.empty()) {
            updateCurrBest();
        }
        for(unsigned int i = 0; i < unvisited.size(); ++i) {
            path.push_back(unvisited.front());
            unvisited.erase(unvisited.begin());
            getLower();
            permute();
            unvisited.push_back(path.back());
            path.pop_back();
        }
    }
    
    void getLower() {
        
        currDistance = 0;
        for(uint i = 0; i < path.size(); ++i) {
            currDistance += distances[path[i].facNum][path[(i+1)%path.size()].facNum];
        }
    }
    
    void updateCurrBest() {
//        currDistance = 0;
//        
//        for(int i = 0; i < facs; ++i) {
//            currDistance += distances[path[i].facNum][path[(i+1)%facs].facNum];
//        }
        
        if(currDistance < currBest) {
            currBest = currDistance;
            finalPath.clear();
            for(int i = 0; i < facs; ++i) {
                finalPath.push_back(path[i].facNum);
            }
        }
    }
    
    virtual void printPath() {
        cout << currBest << endl;
        
        for(int i = 0; i < facs; ++i) {
            cout << finalPath[i] << " ";
        }
        
        cout << endl;
    }
    
};


#endif
