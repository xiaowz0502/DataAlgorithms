/* 
 * join_ropes.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 4 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convience.
// No need to use them. 
// Remove any of them if you want.
#include <algorithm>
#include <cassert>
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
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "join_ropes.h"

using namespace std;


int join_ropes(const vector<int>& rope_lengths) {
  // TODO
    vector<int> input = rope_lengths;
    
    make_heap(input.begin(), input.end(), greater<int>());
    vector<int> pre;
    int output = input[0];
    int a = 0;
    
    if (input.size()%2 == 1){
    while(!input.empty()){
    output = input[0];
    pop_heap(input.begin(), input.end(),greater<int>());
    input.pop_back();
    output += input[0];
    pre.push_back(output);
    pop_heap(input.begin(), input.end(),greater<int>());
    input.pop_back();
        input.push_back(output);
        push_heap(input.begin(), input.end(),greater<int>());
        output = 0;
    }
    }
    
    else{
        while(input.size() != 2){
            output = input[0];
            pop_heap(input.begin(), input.end(),greater<int>());
            input.pop_back();
            output += input[0];
            pre.push_back(output);
            pop_heap(input.begin(), input.end(),greater<int>());
            input.pop_back();
            input.push_back(output);
            push_heap(input.begin(), input.end(),greater<int>());
            output = 0;
        }
        pre.push_back(input[0]);
        pre.push_back(input[1]);
    }
    
    for (int i = 0; i < pre.size(); i++){
        a= a+pre[i];
    }
    
  return a;
}
