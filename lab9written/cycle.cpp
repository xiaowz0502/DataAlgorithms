/* 
 * cycle.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 9 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convience.
// No need to use them. 
// Remove any of them if you want.
#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "cycle.h"

using namespace std;

bool is_graph_cyclic(const vector<vector<int>> &adj_list) {
    if(adj_list.size() == 0){
        return false;
    }
    vector<bool> checker;

    checker.resize(adj_list.size());
    for(size_t i = 0; i < adj_list.size(); i++){
        int dup = 0;
        for (size_t m = 0; m < adj_list[i].size(); m++){
            if (checker[adj_list[i][m]] == false){
                checker[adj_list[i][m]] = true;
            }
            else{
                dup++;
            }
            if(dup >= 2){
                return true;
            }
        }
    }
    
    
    return false;
}
