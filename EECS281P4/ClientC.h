//
//  ClientC.h
//  EECS281P4
//
//  Created by kcfin on 12/6/14.
//  Copyright (c) 2014 kcfin. All rights reserved.
//

#ifndef EECS281P4_ClientC_h
#define EECS281P4_ClientC_h
#include "ClientB.h"

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
    
    vector<int> path;
    deque<int> unvisited;
    vector<Facility> facilities;
    vector<vector<double>> distances;
    vector<int> finalPath;
    double currBest = 0;
    double curPath = 0;
    double mstDistance = 0;
    double connect = 0;
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
            facilities.push_back(Facility(i, x, y));
            unvisited.push_back(i);
        }
    }
    
    void getMatrix() {
        
        distances = vector<vector<double>>(facs, vector<double>(facs, 0));
        
        for(int i = 0; i < facs; ++i) {
            for(int j = i; j < facs; ++j) {
                distances[i][j] = distances[j][i] = findDistance(&facilities[i], &facilities[j]);
            }
        }
    }
    
    virtual void getGreedy() {
        
        int curIdx = 0;
        int nextIdx = 0;
        int facsVisited = 1;
        finalPath.push_back(0);
        facilities[0].visited = true;
        
        while(facsVisited < facs) {
            double distance = DBL_MAX;
            for(int i = 0; i < facs; ++i) {
                if(i != curIdx && facilities[i].visited == false) {
                    if(distances[curIdx][i] < distance) {
                        distance = distances[curIdx][i];
                        nextIdx = i;
                    }
                }
            }
            
            
            curIdx = nextIdx;
            finalPath.push_back(curIdx);
            currBest += distance;
            facilities[curIdx].visited = true;
            facsVisited++;
        }
        
        currBest += distances[0][curIdx];
    }
    
    virtual void findPath() {
        
        getMatrix();
        getGreedy();
        path.push_back(0);
        unvisited.pop_front();
        permute();

    }
    
    void permute() {
        
        if(prunePath()) {
            return;
        }
        
        if(unvisited.empty()) {
            updateCurrBest();
        }
        
        for(unsigned int i = 0; i < unvisited.size(); ++i) {
            path.push_back(unvisited.front());
            unvisited.pop_front();
            permute();
            unvisited.push_back(path.back());
            path.pop_back();
        }
    }

    bool prunePath() {
        
        getCurPath();
        
        if(curPath + distances[0][path.back()] >= currBest) {
            return true;
        }
        
        getMST();
        getConnection();
        
        if((curPath + mstDistance + connect) >= currBest) {
            return true;
        } else {
            return false;
        }
    }
    
    void getCurPath() {
        curPath = 0;
        if(path.size() > 1) {
            for(uint i = 1; i < path.size(); ++i) {
                curPath += distances[path[i-1]][path[i]];
            }
        }
    }
    
    void getMST() {
        
        mstDistance = 0;
        if(unvisited.size() <= 0) {
            return;
        }
        
        ClientB cb;
        cb.facilities.reserve(unvisited.size());
        cb.unvisited.reserve(unvisited.size());
        
        for(uint i = 0; i < unvisited.size(); ++i) {
            cb.addFacilities(unvisited[i], facilities[unvisited[i]].x, facilities[unvisited[i]].y);
        }
        
        cb.findPath();
        mstDistance = cb.totalDistance;
    }
    
    void getConnection() {
        
        connect = 0;
        if(path.size() > 0  && unvisited.size() > 0) {
            double connectFront = DBL_MAX;
            double connectBack = DBL_MAX;
            
            for(uint i = 0; i < unvisited.size(); i++) {
                
                double front = distances[path.front()][unvisited[i]];
                double back = distances[path.back()][unvisited[i]];
                
                if(front < connectFront) {
                    connectFront = front;
                }
                if(back < connectBack) {
                    connectBack = back;
                }
            }
            connect = connectFront + connectBack;
        }
    }
    
    void updateCurrBest() {
        curPath += distances[0][path.back()];
        
        
        if(curPath < currBest) {
            currBest = curPath;
            finalPath = path;
        }
    }
    
    virtual void printPath() {
        cout << currBest << endl;
        
        for(uint i = 0; i < finalPath.size(); ++i) {
            cout << finalPath[i] << " ";
        }
        
        cout << endl;
    }
    
};


#endif
