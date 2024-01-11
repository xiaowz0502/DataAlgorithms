//0E04A31E0D60C01986ACB20081C9D8722A1899B6
//  main.cpp
//  project2PartA
//
//  Created by 土豆 on 2022/5/17.
//

#include <iostream>
#include "P2random.h"
#include "xcode_redirect.hpp"
#include <getopt.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <utility>
#include "market.h"
#include<queue>

using namespace std;

int main(int argc, char* argv[]) {
    
    // This should be in all of your projects, speeds up I/O
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    market all;
    all.getMode(argc, argv);
    cout << "Processing orders...\n";
    all.readIn();
    all.medianLast();
    all.summary();
   
    
   /* int timeStamp = 0;
    int totalNameTrader = 20;
    int totalSock = 30;
    string BoS;
    char title = '&';
    int numTrader = 0;
    int numStock = 0;
    int price = 0;
    int quanitity = 0;
    // comment
    cout <<  "COMMENT" <<endl;
    cout << "MODE: TL" <<endl;
    cout <<"NUM_TRADERS: "<<totalNameTrader<<endl;
    cout << "NUM_STOCKS: "<<totalSock<<endl;
    stringstream ss;
    //P2random::PR_init(ss, seed, Num_traders, Num_stocks, num_orders, rate);
    P2random::PR_init(ss, 2345, 3, 1, 20, 15);
    while(ss >> timeStamp >> BoS >> title >> numTrader >> title >> numStock >> title >> price >> title >> quanitity){
        cout <<timeStamp<<" "<<BoS<<" "<<"T"<<numTrader<<" S"<<numStock<<" $"<<price<<" #"<<quanitity << endl;
    
    }
    */
}


