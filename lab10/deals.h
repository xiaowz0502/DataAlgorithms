#ifndef DEALS_H
#define DEALS_H

// EECS 281 LAB 10: DYNAMIC PROGRAMMING
// Identifier: D7E20F91029D0CB08715A2C54A782E0E8DF829BF

// Your favorite restaurant has a customer loyalty program. It works like this: whenever you buy a
// meal, you can add one holepunch to your punchcard. Once you have 5 punches, you can turn in the
// card for a free meal (and a new, unmarked punchcard).

// For example, if your meals cost [3, 3, 3, 3, 3, 3, 3, 120] then you should earn hole punches
// from the first 5 meals ($15), pay normally for the next two, and then turn in the punchcard
// so that the $120 meal is free! The total cost would be $21 (or with coupons [see below] $19).

// However, you ALSO have a lot of coupons to this restaurant. In fact, you have enough coupons
// that you can apply one to any and every meal! If you apply a coupon, you get a 25% discount
// on that meal. HOWEVER, you don't get to add a holepunch to your card if you use a coupon!

// For example, if your meals cost [2, 2, 2, 2, 1000, 100], then if you use the first 5 meals to
// earn holepunches, you'll need to spend $1008. Then you'll get $100 free. It would be much better
// to just apply the 25% discount to each item, so that you pay a total of $829.

// There are, however, many cases where it makes sense to use a mixture of punchcard discounts and
// discounting coupons. This is where your program comes in!

// You will be given a list of meal prices. For the given meal prices, find the LEAST POSSIBLE
// cost needed to pay for all the meals using the holepunch loyalty program and coupons.

// Notes/Clarifications/Hints:
// * use the "discounted" function below to compute discount
//    (so that you round the same way as the instructor solution).
// * you should always EITHER use a coupon, or apply the punchcard
// * you have an unlimited number of coupons
// * your program should be able to run in linear time.
// * greedy solutions will not work
// * use dynamic programming

#include <iostream>
#include <vector>
#include <functional>
#include <limits>
using namespace std;

// TODO: import whatever you want

// This is a type synonym.
using cost = long long;
int helper2(const std::vector<cost>& prices, int points, size_t curr,  vector<vector<int>> &memo);
int helper(const std::vector<cost>& prices, int points, size_t curr);

// How much you pay for a discounted (25% off) meal.
cost discounted(cost full_price) {
    return full_price * 3 / 4;
}

// TODO: add any helpers you want here.

cost best_price(const std::vector<cost>& prices) {
    // TODO: put your code here
    // NOTE: if you use a bottom-up approach, initialize your table with
    // std::numeric_limits<cost>::max()/4 ... you MUST divide by 4!
 size_t N = prices.size() + 1;
    vector<vector<int>> memo;
    memo.resize(N);
    
    for (int i = 0; i <N; i ++){
        memo[i].resize(6);
        for(int m = 0; m < 6; m++){
            memo[i][m] = -1;
        }
    }
    return helper2(prices,0, 0, memo);
 
    //return helper(prices, 0, 0);
}

// top down

int helper2(const std::vector<cost>& prices, int points, size_t curr, vector<vector<int>> &memo){
    if (curr == prices.size()){
        return 0;
    }
    
    if(memo[curr][points % 6] != -1){
        return memo[curr][points % 6];
    }
    
    //choice 1, pay full meal
    int p1 = prices[curr] + helper2(prices, (points + 1) % 6, curr + 1,memo);
    
    //choice 2, pay discount meal
    int p2 = discounted(prices[curr]) + helper2(prices, points % 6, curr + 1, memo);
    
    //choice 3, free and restart points
    if(points % 6 == 5){
        int p3 = 0 + helper2(prices, (points + 1) % 6, curr + 1,memo);
        memo[curr][points % 6] = min(p3,min(p1,p2));
        return memo[curr][points % 6];
    }

    memo[curr][points % 6] = min(p1,p2);
    return  memo[curr][points % 6];
}


// brute force
//error: module 6 instead of 5
int helper(const std::vector<cost>& prices, int points, size_t curr){
    if (curr == prices.size()){
        return 0;
    }
    
    //choice 1, pay full meal
    int p1 = prices[curr] + helper(prices, (points + 1)%6, curr + 1);
    
    //choice 2, pay discount meal
    int p2 = discounted(prices[curr]) + helper(prices, points%6, curr + 1);
    
    //choice 3, free and restart points
    if(points % 5 == 0 && points != 0){
        int p3 = 0 + helper(prices, (points + 1)%6, curr + 1);
        return min(p3,min(p1,p2));
    }
    
        return min(p1,p2);
}



#endif
