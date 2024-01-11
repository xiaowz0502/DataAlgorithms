/* 
 * two_pair_sums.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 6 Written.
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

#include "two_pair_sums.h"

using namespace std;

void two_pair_sums(const vector<int>& nums, ostream& os) {
    unordered_map<int, pair<int,int>> sum;
    for(size_t i = 0; i < nums.size();i++){
        for(size_t a = i + 1; a < nums.size();a++){
            int sum1 = nums[i] + nums[a];
            auto it = sum.find(sum1);
            if(it == sum.end()){
                sum[sum1] = make_pair(nums[i], nums[a]);
            }
            else{
                int a, b;
                tie(a,b) = it->second;
                cout << "<"<<a<<", "<<b<<") and ("<<nums[i]<<", "<<nums[a]<<")\n";
            }
        }
    }
}
