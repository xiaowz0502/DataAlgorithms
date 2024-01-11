/* 
 * sort012.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 5 Written.
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

#include "sort012.h"

using namespace std;

void sort012(vector<int>& nums) {
    int one = 0;
    int two = 0;
    int three = 0;
    for (size_t i = 0; i < nums.size(); i++){
        if (nums[i] == 0){
            one ++;
        }
        else if (nums[i] == 1){
            two ++;
        }
        else if (nums[i] == 2){
            three ++;
        }
    }
    
    for (size_t i = 0; i < nums.size(); i++){
        if (i < one){
            nums[i] = 0;
        }
        else if (i < two + one){
            nums[i] = 1;
        }
        else if (i <three + two + one){
            nums[i] = 2;
        }
    }
}


