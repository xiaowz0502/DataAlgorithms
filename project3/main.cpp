//01BD41C3BF016AD7E8B6F837DF18926EC3E83350
//  main.cpp
//  project3
//

#include <iostream>
#include "xcode_redirect.hpp"
#include <getopt.h>
#include <fstream>      // std::ifstream
#include "logman.h"


using namespace std;

int main(int argc, char * argv[]) {
    
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    logman all;
    all.getMode(argc, argv);
    all.readIn(argv);
    all.translator(); 
    all.Output(); 
    return 0;
}



