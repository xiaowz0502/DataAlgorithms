// 50EB44D3F029ED934858FFFCEAC3547C68768FC9

// EECS 281, Project 1


#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "search.hpp"
#include "xcode_redirect.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc,argv);
    
    sorting letterman;
    letterman.getMode(argc, argv);
    letterman.error_output();
    letterman.readDict();
    
    letterman.beginEndSetting();
    letterman.wordContainCheck();
    
    if(letterman.beginEndSameChecker() == true){
        cout<<"Words in morph: 1\n";
        cout<< letterman.getBeginWord() <<"\n";
    }
    
    else{
    letterman.containerSearching();
    letterman.finalWordEdit();
    letterman.finalOutput();
    }
   
    
    
}


