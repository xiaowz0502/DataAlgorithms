//0E04A31E0D60C01986ACB20081C9D8722A1899B6
//  market.h
//  project2PartA
//
//  Created by 土豆 on 2022/5/17.
//

#ifndef market_h
#define market_h

#include <iostream>
#include "P2random.h"
#include "xcode_redirect.hpp"
#include <getopt.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <utility>
#include "structs.h"
#include<queue>

#endif /* market_h */
using namespace std;

class market {
    
private:
    //before
    bool verboseMode;
    bool medianMode;
    bool traderMode;
    bool timeTravelerMode;
    vector<Stock> stocks;
    vector<Trader> traders;
    string junk;
    string mode;
    int Num_traders;
    int Num_stocks;
    int seed;
    int num_orders;
    int rate;
    
    //processing
    int timeStamp;
    string BoS;
    bool buyIntent;
    bool sellIntent;
    char title;
    int numTrader;
    int numStock;
    int price;
    int quanitity;
    int order_complete;
    int Time = 0;
    
public:
    
    market(){
        verboseMode = false;
        medianMode = false;
        traderMode = false;
        timeTravelerMode = false;
        seed = -1;
        num_orders = -1;
        rate = -1;
        Num_traders = -1;
        Num_stocks = -1;
        buyIntent = false;
        sellIntent = false;
        order_complete = 0;
        timeStamp = -1;
        numTrader = -1;
        numStock = -1;
        price = -1;
        quanitity = -1;
    }
    
    void getMode(int argc, char * argv[]) {
        // These are used with getopt_long()
        opterr = false; // Let us handle all error output for command line options
        int choice;
        int option_index = 0;
        option long_options[] = {
            // TODO: Fill in two lines, for the "mode" ('m') and
            // the "help" ('h') options.
            {"verbose", no_argument,nullptr,'v'},
            {"median", no_argument,nullptr,'m'},
            {"trader_info",no_argument,nullptr,'i'},
            {"time_travelers",no_argument,nullptr,'t'},
            { nullptr, 0,                 nullptr, '\0' }
        };

        // TODO: Fill in the double quotes, to match the mode and help options.
        while ((choice = getopt_long(argc, argv, "vmit", long_options, &option_index)) != -1) {
            switch (choice) {
                case 'v':
                    verboseMode = true;
                    break;
                    
                case'm':
                    medianMode = true;
                    break;
                    
                case'i':
                    traderMode = true;
                    break;
                
                case't':
                    timeTravelerMode = true;
                    break;
                    
                default:
                cerr << "Unknown command line option\n";
                exit(1);
            }
        }
    }
    
    void readIn(){
        getline(cin,junk);
        cin >> junk  >> mode;
        cin >> junk >> Num_traders;
        cin >> junk >> Num_stocks;
        
        stocks.resize(Num_stocks);
        if (traderMode) traders.resize(Num_traders);
        
        stringstream ss;
        if (mode == "PR"){
        cin >> junk >> seed;
        cin >> junk >> num_orders;
        cin >> junk >> rate;
        P2random::PR_init(ss, seed, Num_traders, Num_stocks, num_orders, rate);
        processOrders(ss);
        }
        
        else{
        processOrders(cin);
    }
 }
    
    
    void processOrders (istream &inputStream){
        int i = 0;
        while(inputStream >> timeStamp >> BoS >> title >> numTrader >> title >> numStock >> title >> price >> title >> quanitity){
            i++;
            
            errorOutPut();
            
            if (medianMode == true && Time != timeStamp){
                medianOutput(Time);
            }
            
            Time = timeStamp;
            
            if (timeTravelerMode == true){
                timeTraveler();
            }
            
            if (BoS == "BUY"){
                //可以买，买家出的价格比最便宜的卖家高
                if (!stocks[numStock].seller.empty() && price >= stocks[numStock].seller.top().price){
                    //买的数量小于卖家有的数量
                    if (quanitity < stocks[numStock].seller.top().quantity){
                        buyLess();
                    }
                    //买的数量超过卖家的数量
                    else if((quanitity > stocks[numStock].seller.top().quantity)){
                        while (quanitity != 0){
                            if (quanitity < stocks[numStock].seller.top().quantity){
                                buyLess();
                                break;
                            }
                            else if (quanitity == stocks[numStock].seller.top().quantity){
                                buyEven();
                                break;
                            }
                            else{
                                buyMore();
                            }
                            if (stocks[numStock].seller.empty() || price < stocks[numStock].seller.top().price){
                                post order = {
                                    i,
                                    numTrader,
                                    price,
                                    quanitity,
                                };
                                stocks[numStock].buyer.push(order);
                                break;
                            }
                        }
                       
                    }
                    //买的数量正好等于卖家有的数量
                    else{
                        buyEven();
                    }
                }
                //不可以买，最便宜的卖家出的价格都比自己的贵
                else{
                post order = {
                    i,
                    numTrader,
                    price,
                    quanitity,
                };
                stocks[numStock].buyer.push(order);
                }
            }
            else{
                //可以卖
                if (!stocks[numStock].buyer.empty() && price <= stocks[numStock].buyer.top().price){
                    //卖家的库存大于买家的数量
                    if(quanitity > stocks[numStock].buyer.top().quantity){
                        while (quanitity!=0){
                            if (quanitity == stocks[numStock].buyer.top().quantity){
                                saleEven();
                                break;
                            }
                            else if (quanitity < stocks[numStock].buyer.top().quantity){
                                saleLess();
                                break;
                            }
                            else{
                                saleMore();
                            }
                            if (stocks[numStock].buyer.empty() || price > stocks[numStock].buyer.top().price){
                                post order = {
                                    i,
                                    numTrader,
                                    price,
                                    quanitity,
                                };
                                stocks[numStock].seller.push(order);
                                break;
                            }
                        }
                      
                    }
                    //卖家的库存小于买家的数量
                    else if(quanitity < stocks[numStock].buyer.top().quantity){
                        saleLess();
                       
                    }
                    //卖家的数量等于买家的数量
                    else{
                        saleEven();
                    }
                }
                
                //不可以卖，出的最高价的买家都比自己出的价钱低
                else{
                    post order = {
                        i,
                        numTrader,
                        price,
                        quanitity,
                    };
                    stocks[numStock].seller.push(order);
                }
            }
        }
        
    }
    
    void summary(){
        cout<< "---End of Day---\n";
        cout << "Trades Completed: "<<order_complete<<"\n";
        if (traderMode == true){
            TraderPrinter();
        }
        if (timeTravelerMode == true){
            timeTravelerPrint();
        }
    }
    void TraderPrinter(){
        cout<< "---Trader Info---\n";
        for (size_t i = 0; i < traders.size(); i++){
            cout << "Trader "<< i << " bought "<< traders[i].getBought()<<" and sold "<<traders[i].getSold()
            <<" for a net transfer of $"<<traders[i].getAccound()<<"\n";
        }
    }
    
    void buyLess(){
        if (quanitity < stocks[numStock].seller.top().quantity){
            stocks[numStock].seller.top().quantity -= quanitity;
            order_complete++;
            
    
           if (verboseMode == true){
               verbosePrintBuyer(quanitity);
            }
            if (medianMode == true){
                priceInsert(stocks[numStock].seller.top().price);
            }
            if (traderMode == true){
                traderModeIncreBuyer(quanitity, stocks[numStock].seller.top().price);
            }
            
    }
    }
    
    void buyEven(){
        
        if (traderMode == true){
            traderModeIncreBuyer(quanitity, stocks[numStock].seller.top().price);
        }
        if (medianMode == true){
            priceInsert(stocks[numStock].seller.top().price);
        }
       if (verboseMode == true){
           verbosePrintBuyer(quanitity);
        }
        
        stocks[numStock].seller.pop();
        order_complete++;
    }
    
    
    void buyMore(){
        quanitity -= stocks[numStock].seller.top().quantity;
        
        
        if (traderMode == true){
            traderModeIncreBuyer(stocks[numStock].seller.top().quantity, stocks[numStock].seller.top().price);
        }
        if (medianMode == true){
            priceInsert(stocks[numStock].seller.top().price);
        }
        if (verboseMode == true){
            verbosePrintBuyer(stocks[numStock].seller.top().quantity);
        }
        
        stocks[numStock].seller.pop();
        order_complete++;
    }
    
    void saleLess(){
        stocks[numStock].buyer.top().quantity -= quanitity;
        order_complete++;
        
        if (traderMode == true){
        traderModeIncreSeller(quanitity, stocks[numStock].buyer.top().price);
        }
        if (medianMode == true){
            priceInsert(stocks[numStock].buyer.top().price);
        }
        if (verboseMode == true){
            verbosePrintSeller(quanitity);
        }
    }
    
    void saleEven(){
        if (verboseMode == true){
            verbosePrintSeller(quanitity);
        }
        if (medianMode == true){
            priceInsert(stocks[numStock].buyer.top().price);
        }
        if (traderMode == true){
        traderModeIncreSeller(quanitity, stocks[numStock].buyer.top().price);
        }
        stocks[numStock].buyer.pop();
        order_complete++;
    }
    void saleMore(){
        quanitity -= stocks[numStock].buyer.top().quantity;
        if (verboseMode == true){
            verbosePrintSeller(stocks[numStock].buyer.top().quantity);
        }
        if (medianMode == true){
            priceInsert(stocks[numStock].buyer.top().price);
        }
        if (traderMode == true){
        traderModeIncreSeller(stocks[numStock].buyer.top().quantity, stocks[numStock].buyer.top().price);
        }
        stocks[numStock].buyer.pop();
        order_complete++;
    }
    
    void verbosePrintBuyer(int &quanitity){
        cout << "Trader " << numTrader << " purchased "<< quanitity << " shares of Stock "<< numStock <<
        " from Trader " << stocks[numStock].seller.top().trader_ID
        <<" for $"<<stocks[numStock].seller.top().price<<"/share\n";
    }
    
    void verbosePrintSeller(int &quanitity){
        cout << "Trader " << stocks[numStock].buyer.top().trader_ID<< " purchased "
        << quanitity
        << " shares of Stock "<< numStock <<
        " from Trader " << numTrader
        <<" for $"<<stocks[numStock].buyer.top().price<<"/share\n";
    }
    
    void traderModeIncreBuyer(const int &quanitity, const int &price){
        traders[numTrader].BuyerSet(quanitity, price);
        traders[stocks[numStock].seller.top().trader_ID].SellerSet(quanitity, price);
    }
    
    void traderModeIncreSeller(const int &quanitity, const int &price){
        traders[stocks[numStock].buyer.top().trader_ID].BuyerSet(quanitity, price);
        traders[numTrader].SellerSet(quanitity, price);
    }
    
    void priceInsert(const int &Inputprice){
        if (stocks[numStock].large.size() == 0 && stocks[numStock].small.size() == 0){
            stocks[numStock].large.push(Inputprice);
        }
        
        else if (stocks[numStock].large.size() - stocks[numStock].small.size() == 1){
            if (stocks[numStock].large.top() > Inputprice){
                int temp = 0;
                temp = stocks[numStock].large.top();
                stocks[numStock].large.pop();
                stocks[numStock].small.push(temp);
                stocks[numStock].large.push(Inputprice);
            }
            else{
                stocks[numStock].small.push(Inputprice);
            }
        }
        else if (stocks[numStock].small.size() - stocks[numStock].large.size() == 1){
            if(Inputprice > stocks[numStock].small.top()){
                int temp = 0;
                temp = stocks[numStock].small.top();
                stocks[numStock].small.pop();
                stocks[numStock].large.push(temp);
                stocks[numStock].small.push(Inputprice);
            }
            else{
                stocks[numStock].large.push(Inputprice);
            }
        }
        
        else{
            if (stocks[numStock].large.top() > Inputprice){
                stocks[numStock].large.push(Inputprice);
            }
            else{
                stocks[numStock].small.push(Inputprice);
            }
        }
    }
    
    void medianOutput(int &currentTime){
        for (size_t i = 0; i < stocks.size(); i++){
            if (stocks[i].small.empty() && stocks[i].large.empty()) continue;
            else{
                cout << "Median match price of Stock "<< i<<" at time "<<currentTime<<" is $"<<medianPrint(i)<<"\n";
            }
        }
    }
    
    int medianPrint(size_t &i){
        if (stocks[i].small.size() == stocks[i].large.size()){
            return (stocks[i].small.top() + stocks[i].large.top()) /2 ;
        }
        else if (stocks[i].small.size() - stocks[i].large.size() == 1){
            return stocks[i].small.top();
        }
        else{
            return stocks[i].large.top();
        }
    }
    
    void medianLast(){
        if (medianMode == true){
            medianOutput(Time);
        }
    }
    
    void timeTraveler(){
        if (stocks[numStock].status == Timesatus::N){
            if (BoS  == "SELL"){
                stocks[numStock].buyTimeSetting(timeStamp, price);
                stocks[numStock].status = Timesatus::B;
            }
        }
        
        else if(stocks[numStock].status == Timesatus::B){
            //卖出的价格大于买进的价格
            if(BoS  == "SELL" && price < stocks[numStock].getBuyPrice()){
                stocks[numStock].buyTimeSetting(timeStamp, price);
            }

            else if(BoS == "BUY"){
                if (price - stocks[numStock].getBuyPrice() > 0){
                stocks[numStock].sellTimeSetting(timeStamp, price);
                stocks[numStock].status = Timesatus::C;
                }
            }
        }
        
        else if(stocks[numStock].status == Timesatus::C){
            if (BoS  == "BUY" && price >  stocks[numStock].getSellPrice()){
                stocks[numStock].sellTimeSetting(timeStamp, price);
            }
            else if (BoS  == "SELL" && price < stocks[numStock].getBuyPrice()){
                stocks[numStock].potentialSet(timeStamp, price);
                stocks[numStock].status = Timesatus::P;
            }
        }

        
        else{
            if (BoS  == "SELL" ){
                if (stocks[numStock].getPotential() > price){
                    stocks[numStock].potentialSet(timeStamp, price);
                }
            }

            else if (BoS  == "BUY"){
                if (price - stocks[numStock].getPotential() > stocks[numStock].getProfit()){
                    int profit  = stocks[numStock].getPotential();
                    int timepro = stocks[numStock].getPotentialTime();
                    stocks[numStock].sellTimeSetting(timeStamp, price);
                    stocks[numStock].buyTimeSetting(timepro, profit);
                    stocks[numStock].status = Timesatus::C;
                }
            }
        }
    }
    
    void timeTravelerPrint(){
        cout << "---Time Travelers---\n" ;
        for (size_t i = 0; i < stocks.size(); i++){
            if (stocks[i].status == Timesatus::N || stocks[i].status == Timesatus::B){
                cout << "A time traveler could not make a profit on Stock "<<i<<"\n";
            }
            else{
                cout<< "A time traveler would buy Stock "<< i<<" at time "<<stocks[i].getBuyTime()<<" for $"<<stocks[i].getBuyPrice()
                <<" and sell it at time " <<stocks[i].getSellTime()<<" for $"<<stocks[i].getSellPrice()<<"\n";
            }
        }
    }
    
    void errorOutPut(){
        if (timeStamp < 0){
            cerr << " Negative timestamp\n";
            exit(1);
        }
        if (timeStamp < Time){
            cerr << "Decreasing timestamp\n";
            exit(1);
        }
        if (numTrader >= Num_traders || numTrader < 0 ){
            cerr <<"Invalid trader ID\n";
            exit(1);
        }
        if (numStock >= Num_stocks || numTrader < 0 ){
            cerr <<"Invalid stock ID\n";
            exit(1);
        }
        if (price <= 0){
            cerr << "Invalid price\n";
            exit(1);
        }
        if (quanitity <= 0){
            cerr << "Invalid quantity\n";
            exit(1);
        }
    }
};
