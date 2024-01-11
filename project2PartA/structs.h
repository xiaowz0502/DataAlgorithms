//0E04A31E0D60C01986ACB20081C9D8722A1899B6
//  structs.h
//  project2PartA
//
//  Created by 土豆 on 2022/5/17.
//

#ifndef structs_h
#define structs_h


#endif /* structs_h */
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <utility>
#include<queue>

using namespace std;

struct post{
    int sequence;
    int trader_ID;
    int price;
    mutable int quantity;
};


enum class Timesatus:char{
    N,
    B,
    C,
    P
};

class sortbySeller{
public:
    bool operator()(const post &o1, const post &o2)
        {
        if (o1.price == o2.price){
            return o1.sequence > o2.sequence;
        }
        
        return o1.price > o2.price;
        }
};
class sortbyBuyer{
public: 
    bool operator()(const post &o1, const post &o2)
        {
        if (o1.price == o2.price){
            return o1.sequence > o2.sequence;
        }
        
        return o1.price < o2.price;
        }
};


class Trader{
public:
    Trader():sold(0),bought(0),account(0){}
    
    void BuyerSet(const int &num,  const int &price){
        bought = bought + num;
        account = num * (-1)*price + account;
    }
    void  SellerSet(const int &num,  const int &price){
        sold = sold + num;
        account = num * price + account;
    }
    int getSold(){
        return sold;
    }
    int getBought(){
        return bought;
    }
    int getAccound(){
        return account;
    }
private:
    int sold;
    int bought;
    int account;
};

class Stock{
public:
    Stock(){
        buyPrice = -1;
        buyTime = -1;
        sellPrice = -1;
        sellTime = -1;
        potentialBuyPrice = -1;
        potentialBuyTime = -1;
        status = Timesatus::N;
    }
    
    Timesatus status;
    
    priority_queue <post, vector<post>,sortbySeller> seller; // custom comparator
    priority_queue<post, vector<post>,sortbyBuyer> buyer; // custom comparator
    
    priority_queue<int, vector<int>> large;
    priority_queue<int, vector<int>,greater<>> small;
    
    void buyTimeSetting(int &time, int&price){
        buyPrice = price;
        buyTime  = time;
    }
    void sellTimeSetting(int &time, int&price){
        sellTime = time;
        sellPrice = price;
    }
    
    void potentialSet(int &time, int&price){
        potentialBuyPrice = price;
        potentialBuyTime = time;
    }
    
    
    int getBuyPrice(){
        return buyPrice;
    }
    int getBuyTime(){
        return buyTime;
    }
    
    int getSellPrice(){
        return sellPrice; 
    }
    int getSellTime(){
        return sellTime;
    }
    int getProfit(){
        return sellPrice - buyPrice; 
    }
    int getPotential(){
        return potentialBuyPrice;
    }
    int getPotentialTime(){
        return potentialBuyTime;
    }
private:
    int buyPrice;
    int buyTime;
    int sellPrice;
    int sellTime;
    int potentialBuyPrice;
    int potentialBuyTime;
};

