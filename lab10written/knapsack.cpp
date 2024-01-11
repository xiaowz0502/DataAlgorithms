/* 
 * knapsack.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 10 Written.
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

#include "knapsack.h"

using namespace std;
int helper01(const vector<int>& value, const vector<int>& weight,size_t curr, int bag);

int knapsack(int C, const vector<int>& value, const vector<int>& weight) {
  
    //return  helper01(value,weight,0, C);
    int n = static_cast<int>(weight.size());
    
    
    int arr[weight.size() + 1][C + 1];
    for(int i = 0; i < C + 1; i++){
        arr[n][i] = 0;
    }
    
    for(int index = n -1; index >= 0; index--){
        for(int rest = 0; rest <= C; rest ++){
            int p1 = arr[index + 1][rest];
            int p2 = 0;
            int next = rest - weight[index] < 0 ? -1 : arr[index + 1][rest - weight[index]];
            if(next != -1){
                p2 = value[index] + next;
            }
            arr[index][rest] = max(p1,p2);
        }
    }
    
    return arr[0][C];
}



int helper01(const vector<int>& value, const vector<int>& weight,size_t curr, int bag){
    if (bag < 0){
        return -1;
    }
    if(curr == weight.size()){
        return 0;
    }
    
    int p1 = helper01(value, weight, curr+1, bag);
    int p2 = 0;
    int next = helper01(value, weight, curr + 1, bag - weight[curr]);
    if(next != -1){
        p2 = value[curr] + next;
    }
    
    return max(p1,p2);
}

