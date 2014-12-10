//
//  project4.cpp
//  EECS281P4
//
//  Created by kcfin on 11/19/14.
//  Copyright (c) 2014 kcfin. All rights reserved.
//

#include "project4.h"

int main(int argc, char * argv[]) {
    ios_base::sync_with_stdio(false);
    cout << setprecision(2);
    cout << fixed;
    
//    ifstream in("test-7-C.txt");
//    cin.rdbuf(in.rdbuf());
    
    getOpts(argc, argv);
    client->getInput();
    client->findPath();
    client->printPath();
}

//testing again

void getOpts(int argc, char * argv[]) {
    struct option longOpts[] = {
        {"clientType", required_argument, 0, 'c'},
        {"help", no_argument, 0, 'h'}
    };
    
    char opt = 0;
    int index = 0;
    char type;
    
    while ((opt = getopt_long(argc, argv, "c:h", longOpts, &index)) != -1) {
        switch(opt) {
            case 'c':
                type = *optarg;
                if(type == 'A') {
                    client = &ca;
                } else if (type == 'B') {
                    client = &cb;
                } else if (type == 'C') {
                    client = &cc;
                    //set client C
                } else {
                    cerr << "Not a valid client type!" << endl;
                    exit(1);
                }
                break;
            case 'h':
                //print help message
                cout << "help me\n";
                exit(0);
            default:
                cout << "Flag not recognized!\n";
                exit(1);
        }
    }
}