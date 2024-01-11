//IDENTIFIER = 1761414855B69983BD8035097EFBD312EB0527F0
//  main.cpp
//  project4
//
//  Created by 土豆 on 2022/6/12.
//

#include "main.hpp"
#include <iostream>
#include "xcode_redirect.hpp"
#include <getopt.h>
#include <fstream>      // std::ifstream
#include <iomanip>



using namespace std;
void genPerms(vector<int> &path, size_t permLength, vector<int> &out) ;

int main(int argc, char * argv[]) {
    
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    cout << std::setprecision(2); //Always show 2 decimal places
    cout << std::fixed; //Disable scientific notation for large numbers
    
    drone all;
    all.getMode(argc, argv);
    all.Caculator();
    return 0;
     
}
