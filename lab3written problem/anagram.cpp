/*
 * anagram.cpp
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 3 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convenience.
// No need to use them.
// Remove any of them if you want.
#include <algorithm>
#include <cassert>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
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

#include "anagram.h"

using namespace std;

bool isAnagram(const string &s1, const string &s2) {
  // TODO
    string first = s1;
    string second = s2;
    first.erase(remove(first.begin(),first.end(),' '),first.end());
    second.erase(remove(second.begin(),second.end(),' '),second.end());
    size_t a = first.length();
    size_t b = second.length();
    
    if (a!=b){
        return false;
    }
    sort(first.begin(),first.end());
    sort(second.begin(),second.end());
    
    if (first != second){
        return false;
    }
    else{
        return true;
    }
}
