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
        double minDist;
        
        Facility() : facNum(0), x(0), y(0), minDist(DBL_MAX), visited(false) {}
        
        Facility(int fac, double xc, double yc) : facNum(fac), x(xc), y(yc), minDist(DBL_MAX), visited(false) {}
    };
    
    vector<int> path;
    vector<int> unvisited;
    vector<Facility> facilities;
    vector<vector<double>> distances;
    vector<int> finalPath;
    double currBest = 0;
    double curPath = 0;
    double mstDistance = 0;
    double connect = 0;
    double lowerBound = 0;
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
            facilities.push_back(Facility(i, x, y));
            unvisited.push_back(i);
        }
    }
    
    void getMatrix() {
        
        
//        int size = pow(facs, 2)/2 + (facs/2) + (facs%2);
        distances = vector<vector<double>>(facs, vector<double>(facs, 0));
        
        for(int i = 0; i < facs; ++i) {
            double smallestDist = DBL_MAX;
            for(int j = 0; j < facs; ++j) {
                // think about only storing half of this
                distances[i][j] = findDistance(&facilities[i], &facilities[j]);
                if( i != j && distances[i][j] < smallestDist) {
                    smallestDist = distances[i][j];
                }
            }
            facilities[i].minDist = smallestDist;
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
        permute();

    }
    
    void permute() {
        
        if(lowerBound > currBest) {
            return;
        }
        
        if(unvisited.empty()) {
            currBest = lowerBound;
        }
        
        for(unsigned int i = 0; i < unvisited.size(); ++i) {
            path.push_back(unvisited.front());
            unvisited.erase(unvisited.begin());
            getLowerBound();
            permute();
            unvisited.push_back(path.back());
            path.pop_back();
        }
    }

    void getLowerBound() {
        // current path
        // mst of unvisited
        // min dist to connect beg and end of path to unvisited
        
        getCurPath();
        getMST();
        getConnection();
        
        lowerBound = curPath + mstDistance + connect;
    }
    
    void getCurPath() {
        if(path.size() == 1) {
            curPath = 0;
        } else {
            curPath += distances[path.back()][path.back()-1];
        }
    }
    
    void getMST() {

        vector<Facility*> partMST;
        
        for(uint i = 0; i < unvisited.size(); i++) {
            partMST.push_back(&facilities[unvisited[i]]);
        }
        
        
        mstDistance = 0;
        int facsVisited = 0;
        
        while(facsVisited < (int)unvisited.size()) {
            
            uint nextIdx = 0;
            
            for(uint i = 0; i < partMST.size(); ++i) {
                if(partMST[i]->minDist < partMST[nextIdx]->minDist) {
                    nextIdx = i;
                }
            }

//            for(uint i = 0; i < unvisited.size(); i++) {
//                if(i != nextIdx) {
//                    double dist = distances[nextIdx][i];
//                    if(dist < facilities[unvisited[i]].minDist) {
//                        facilities[unvisited[i]].minDist = dist;
//                    }
//                }
//            }
            
            mstDistance += partMST[nextIdx]->minDist;
            partMST.erase(partMST.begin()+nextIdx);
            facsVisited++;
        }
    }
    
    void getConnection() {
        
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
    
    
//    double minPath() {
//        
//        if(unvisited.empty()) {
//            // done
//        }
//        
//        int idx = path.back().facNum;
//        double totalCost = DBL_MAX;
//        
//        for (Facility fac: unvisited) {
//            double cost = distances[idx][fac.facNum];
//            
//            path.push_back(unvisited.front());
//            unvisited.erase(unvisited.begin());
//            
//            double costRest = minPath();
//            double curCost = cost + costRest;
//            
//            if(curCost < totalCost) {
//                totalCost = curCost;
//            }
//        }
//        
//        return totalCost;
//        
//    }
    
//    void getLower() {
//        
//        currDistance = 0;
//        for(uint i = 0; i < path.size(); ++i) {
//            currDistance += distances[path[i].facNum][path[(i+1)%path.size()].facNum];
//        }
//    }
    
//    void updateCurrBest() {
//        currDistance = 0;
//        
//        for(int i = 0; i < facs; ++i) {
//            currDistance += distances[path[i].facNum][path[(i+1)%facs].facNum];
//        }
        
//        if(currDistance < currBest) {
//            currBest = currDistance;
//            finalPath.clear();
//            for(int i = 0; i < facs; ++i) {
//                finalPath.push_back(path[i].facNum);
//            }
//        }
//    }
    
    virtual void printPath() {
        cout << currBest << endl;
        
        for(int i = 0; i < facs; ++i) {
            cout << path[i] << " ";
        }
        
        cout << endl;
    }
    
};


#endif
