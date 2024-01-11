//01BD41C3BF016AD7E8B6F837DF18926EC3E83350
//  logman.h
//  project3
//
//  Created by 土豆 on 2022/5/30.
//

#ifndef logman_h
#define logman_h


#endif /* logman_h */

#include <iostream>
#include "xcode_redirect.hpp"
#include <getopt.h>
#include <fstream>      // std::ifstream
#include <deque>
#include <vector>
#include<algorithm>
#include <inttypes.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* strtoll */
#include <iterator>
#include <unordered_map>
#include <cctype>
#include <string>
#include <set>

using namespace std;

class logman{
public:
    logman(){
        checker = 0;
        LogIndex = 0;
    }
    
    void getMode(int argc, char * argv[]) {
        // These are used with getopt_long()
        opterr = false; // Let us handle all error output for command line options
        int choice;
        int option_index = 0;
        option long_options[] = {
            {"help",no_argument,nullptr,'h'},
            { nullptr, 0,       nullptr, '\0' }
        };

        // TODO: Fill in the double quotes, to match the mode and help options.
        while ((choice = getopt_long(argc, argv, "h", long_options, &option_index)) != -1) {
            switch (choice) {
                case 'h':
                    cout<< "There are several command option provided as following\n";
                    cout<<"For more detailed information please see the spec\n";
                    exit(0);
            }
        }
    }
    
    void Output(){
        char cmd;
        do{
            cout << "% ";
            cin >> cmd;
            
        // t - timestamps search
            if(cmd == 't'){
                string temp;
                cin >> ws;
                getline(cin,temp,'|');
                if (temp.length() == 14){
                temp.erase(remove(temp.begin(),temp.end(),':'), temp.end());
                intervalStart.ts = stoull(temp);
                temp = "";
                getline(cin,temp,'\n');
                    if(temp.length() == 14){
                temp.erase(remove(temp.begin(),temp.end(),':'), temp.end());
                intervalEnd.ts = stoull(temp);
                cout<< "Timestamps search: "<<tModeOn()<<" entries found\n";
                        searchType = 't';
                        checker++;
                    }
                    else{
                        cerr<<"not 15 characters\n";
                    }
                }
                else{
                    cerr<<"not 15 characters\n";
                }
            }
            
        // m - matching search
            else if(cmd == 'm'){
                searchType = 'm';
                checker++;
                string temp;
                getline(cin,temp);
                temp.erase(remove(temp.begin(),temp.end(),':'), temp.end());
                intervalStart.ts = stoull(temp);
                temp = "";
                cout<<"Timestamp search: "<<mModeOn()<<" entries found\n";
            }
            
        // c - category search
           else if (cmd == 'c'){
                searchType = 'c';
                checker++;
                cin >> ws;
                getline(cin, cat);
               cout<< "Category search: "<< cModeOn() <<" entries found\n";
            }
            
        // a - append log entry
            else if (cmd == 'a'){
                cin >> LogIndex;
                if(LogIndex < data.size()){
                aModeON();
                }
                else{
                    cerr<<"Invalid index\n";
                }
            }
        // k - keyword search
            else if(cmd == 'k'){
                searchType = 'k';
                checker++;
                cin >> ws;
                getline(cin, longline);
                transform(longline.begin(), longline.end(), longline.begin(), ::tolower);
                targetSeparator(longline);
                cout << "Keyword search: " <<kmodeOn()<<" entries found\n";
            }
        // r - append search results;
            else if(cmd == 'r'){
                if(checker == 0){
                    cerr<<"no previous search\n";
                }
                else{
                preUpdated();
                for (size_t i = 0; i < prevResult.size(); i++){
                    List.push_back(prevResult[i]);
                }
                cout <<prevResult.size()<<" log entries appended\n";
                }
            }
            
        // d - delete log entry (by excerpt list number);
            else if(cmd == 'd'){
                size_t target;
                cin >> target;
                if(target<List.size()){
                auto it = List.begin() + target;
                List.erase(it);
                cout << "Deleted excerpt list entry " << target<<"\n";
                }
                else{
                    cerr<<"Invalid Index\n";
                }
            }
        // b - move to beginning (by excerpt list number);
            else if(cmd == 'b'){
                size_t target;
                cin >> target;
                if(target<List.size()){
                cout << "Moved excerpt list entry "<<target<<"\n";
                auto it = List.begin() + target;
                
                size_t frontNum = List[target];
                List.erase(it);
                List.push_front(frontNum);
                }
                
                else{
                    cerr<<"Invalid Index\n";
                }
            }
        // e - move to end (by excerpt list number);
            else if(cmd == 'e'){
                size_t target;
                cin >> target;
                if(target<List.size()){
                cout << "Moved excerpt list entry "<<target<<"\n";
                auto it = List.begin() + target;
                
                size_t backNum = List[target];
                List.erase(it);
                List.push_back(backNum);
                }
                
                else{
                    cerr<<"Invalid Index\n";
                }
            }
            
        // s - sort excerpt list (by timestamp);
            else if(cmd == 's'){
                cout << "excerpt list sorted\n";
                if(List.empty()){
                    cout << "(previously empty)\n";
                }
                else{
                cout << "previous ordering:\n";
                    printOneEntry(0);
                    cout<<"...\n";
                    printOneEntry(List.size() - 1);
                sort(List.begin(),List.end());
                    cout<<"new ordering:\n";
                    printOneEntry(0);
                    cout<<"...\n";
                    printOneEntry(List.size() - 1);
                }
            }
        // l - clear excerpt list (this is a lowercase "L" as in "clear");
            else if(cmd == 'l'){
                cout << "excerpt list cleared\n";
                if(List.empty()){
                    cout << "(previously empty)\n";
                }
                
                else{
                    cout << "previous contents:\n";
                    printOneEntry(0);
                    cout<<"...\n";
                    printOneEntry(List.size() - 1);
                    List.clear();
                }
            }
        // g - print most recent search results;
            else if(cmd == 'g'){
                if(checker == 0){
                    cerr<<"no previous search\n";
                }
                else{
                preUpdated();
                for (size_t i = 0; i < prevResult.size(); i++){
                    cout<<data[prevResult[i]].position<<"|";
                    cout<<data[prevResult[i]].whole<<"\n";
                }
                }
            }

        // p - print excerpt list; O(e) complexity (eis the size of the excerpt list)
            else if(cmd == 'p'){
                for (size_t i = 0; i < List.size(); i++){
                    cout<<i<<"|";
                    cout<<data[List[i]].position<<"|";
                    cout<<data[List[i]].whole<<"\n";
                }
            }

            
        // # - no operation (useful for adding comments to command files)
            else if (cmd == '#'){
                string trashline;
                getline(cin, trashline);
            }
            
            else if(cmd != 'q'){
                string trash;
                getline(cin,trash);
                cerr << "wrong commanding requests\n";
            }

            
        }while(cmd != 'q'); // q - quit
    }
    
    void readIn(char * argv[]){
        size_t index = 0;
        infile.open(argv[1]);
        string input;
        entry inputs;
        while(getline(infile, input,'|')){
            inputs.whole = input;
            
            input.erase(remove(input.begin(),input.end(),':'), input.end());
            inputs.ts = stoull(input);
            input = "";
            
            inputs.position = index;
            
            getline(infile, inputs.cat, '|');
            
            getline(infile, input);
            inputs.whole = inputs.whole + "|"+ inputs.cat + "|" + input;
            transform(inputs.cat.begin(), inputs.cat.end(), inputs.cat.begin(), ::tolower);
            input = "";
            data.push_back(inputs);
            index++;
        }
        sort(data.begin(), data.end(), timeCompare());
        
        for(size_t i = 0; i < data.size(); i++){
            if (category.find(data[i].cat) == category.end() || category[data[i].cat].back()!=i){
            category[data[i].cat].push_back(i);
            }
            
            size_t start = data[i].whole.find_first_of('|');
            string catMes = data[i].whole.substr(start,string::npos );
            transform(catMes.begin(), catMes.end(), catMes.begin(), ::tolower);
            stringSeparator(catMes, i);
        }
        
        cout << data.size()<<" entries read\n";
    }
    
    size_t tModeOn(){
        size_t count = 0;
        vector<entry>::iterator low;
        if (!data.empty() && intervalStart.ts < data[0].ts){
            low = data.begin();
        }
        else{
        low = lower_bound(data.begin(), data.end(),intervalStart,boundary());
        }
        
        vector<entry>::iterator up;
        if (!data.empty() && intervalEnd.ts > data.back().ts){
            up = data.end();
        }
        else{
            up = upper_bound(low, data.end(), intervalEnd, boundary());
        }
        
        tSearchRange.first = low;
        tSearchRange.second = up;
        
        count = distance(low, up);
        return count;
    }
    
    size_t mModeOn(){
        size_t count = 0;
        vector<entry>::iterator low;
        low = lower_bound(data.begin(), data.end(),intervalStart,boundary());
        vector<entry>::iterator up;
        up = upper_bound(low, data.end(), intervalStart, boundary());
        
        count = up - low;
    
        tSearchRange.first = low;
        tSearchRange.second = up;
    
        return count;
    }
    
    size_t cModeOn(){
        transform(cat.begin(), cat.end(), cat.begin(), ::tolower);
        catName = cat;
        auto got = category.find(cat);
        if (got == category.end()){
            return 0;
        }
        else{
            return got->second.size();
        }
    }
    
    void aModeON(){
        List.push_back(getInitialPos(LogIndex));
        cout<<"log entry "<<LogIndex<<" appended\n";
    }

    void translator(){
        initialPos.resize(data.size());
        for (size_t i = 0; i < data.size(); i++){
            initialPos[data[i].position] = i;
        }
    }
    
    size_t getInitialPos(size_t const &pos){
        return initialPos[pos];
    }
    
    void stringSeparator(string &line, size_t pos){
        size_t left = 0;
        size_t right = 0;
        for (;left<line.length();left++){
            if (isalnum(line[left]) == 0){
            }
            else{
                if (left == line.length() - 1){
                    string temp;
                    temp.push_back(line[left]);
                    if(keyWords.find(temp) == keyWords.end()|| keyWords[temp].back()!=pos){
                    keyWords[temp].push_back(pos);
                    }
                    
                }
                else{
                    right = left + 1;
                    while(right < line.length()){
                        if (isalnum(line[right]) == 0) break;
                        else{
                            right ++;
                        }
                    }
                    if (right == line.length() - 1 && isalnum(line[right]) != 0){
                        string temp;
                        temp = line.substr(left,right - left + 1);
                        if(keyWords.find(temp) == keyWords.end()|| keyWords[temp].back()!=pos){
                        keyWords[temp].push_back(pos);
                        }
                    }
                    else{
                        string temp;
                        temp = line.substr(left,right - left);
                        if(keyWords.find(temp) == keyWords.end()|| keyWords[temp].back()!=pos){
                        keyWords[temp].push_back(pos);
                        }
                        left = right;
                    }
                }
            }
        }
    }
    
    void targetSeparator(string &line){
        size_t left = 0;
        size_t right = 0;
        
        for (;left<line.length();left++){
            if (isalnum(line[left]) == 0){
            }
            else{
                if (left == line.length() - 1){
                    string temp;
                    temp.push_back(line[left]);
                    if(targetWords.empty() || find(targetWords.begin(),targetWords.end(),temp) == targetWords.end()){
                        targetWords.push_back(temp);
                    }
                }
                else{
                    right = left + 1;
                    while(right < line.length()){
                        if (isalnum(line[right]) == 0) break;
                        else{
                            right ++;
                        }
                    }
                    if (right == line.length() - 1 && isalnum(line[right]) != 0){
                        string temp;
                        temp = line.substr(left,right - left + 1);
                        if(targetWords.empty() || find(targetWords.begin(),targetWords.end(),temp) == targetWords.end()){
                            targetWords.push_back(temp);
                        }
                    }
                    else{
                        string temp;
                        temp = line.substr(left,right - left);
                        if(targetWords.empty() || find(targetWords.begin(),targetWords.end(),temp) == targetWords.end()){
                            targetWords.push_back(temp);
                        }
                        left = right;
                    }
                }
            }
        }
    }
    
    size_t kmodeOn(){
        size_t count = 0;
        vector<size_t> result;
        prevResult.clear();
        if(targetWords.empty()){
            count = 0;
        }
        
        else if(targetWords.size() == 1){
            if(keyWords.find(targetWords[0]) == keyWords.end()){
                targetWords.clear();
                count = 0;
                return count;
            }
            
            prevResult = keyWords[targetWords[0]];
            count = keyWords[targetWords[0]].size();
            targetWords.clear();
            return count;
            
        }
        
        else if(targetWords.size() == 2){
            if(keyWords.find(targetWords[0]) == keyWords.end() || keyWords.find(targetWords[1]) == keyWords.end()){
                targetWords.clear();
                count = 0;
                return count;
            }
            set_intersection(keyWords[targetWords[0]].begin(), keyWords[targetWords[0]].end(), keyWords[targetWords[1]].begin(), keyWords[targetWords[1]].end(), back_inserter(result));
            prevResult = result;
            count = result.size();
            targetWords.clear();
            return count;
        }
        
        
        else{
            vector<size_t> result2;
            
            if(keyWords.find(targetWords[0]) == keyWords.end() || keyWords.find(targetWords[1]) == keyWords.end()){
                targetWords.clear();
                count = 0;
                return count;
            }
            set_intersection(keyWords[targetWords[0]].begin(), keyWords[targetWords[0]].end(), keyWords[targetWords[1]].begin(), keyWords[targetWords[1]].end(), back_inserter(result));
            
            for(size_t i = 2; i < targetWords.size(); i++){
                if(keyWords.find(targetWords[i]) == keyWords.end()){
                    targetWords.clear();
                    count = 0;
                    return count;
                }
                set_intersection(result.begin(), result.end(), keyWords[targetWords[i]].begin(),
                                 keyWords[targetWords[i]].end(), back_inserter(result2));
                result = result2;
                result2.clear();
            }
            prevResult = result;
            count = result.size();
            targetWords.clear();
            return count;
        }
        return count;
    }
    
    void preUpdated(){
        if (searchType == 't'){
            prevResult.clear();
            //after sorted
            for(auto i = tSearchRange.first; i != tSearchRange.second; i++){
                prevResult.push_back(i - data.begin());
            }
        }
        else if(searchType == 'm'){
            prevResult.clear();
            //after sorted
            for (auto i = tSearchRange.first; i != tSearchRange.second; i++){
                prevResult.push_back(i - data.begin());
            }
        }
        
        //index
        else if(searchType == 'c'){
            prevResult.clear();
            prevResult = category[catName];
        }
        
        else if(searchType == 'k'){
        }
    }
    
    void printOneEntry(size_t i){
        cout<<i<<"|";
        cout<<data[List[i]].position<<"|";
        cout<<data[List[i]].whole<<"\n";
    }

private:
    
    //struct
    struct entry{
        string whole;
        string cat;
        int64_t ts;
        size_t position;
    };
    
    
    //prev result
        char searchType;
        using pair_type1 = pair<vector<entry>::iterator,vector<entry>::iterator>;

    
        pair_type1 tSearchRange;
    
        string catName;
        int checker = 0;
        vector<size_t> prevResult;
        
    
    //deque list
    deque<size_t> List;
    vector<entry> data;
    unordered_map<string, vector<size_t>> category;
    unordered_map<string, vector<size_t>> keyWords;
    vector<size_t> initialPos;
    vector<string> targetWords;
    
    
    //command
    ifstream infile;
    
    entry intervalStart = {"", "", 0,0};
    entry intervalEnd = {"","", 0,0};
    
    string cat;
    size_t LogIndex = 0;
    string longline;
    
    //comaprator
   class boundary{
    public:
       bool  operator()(const entry& object1, const entry& object2)const {
               return object1.ts < object2.ts;
       }
    };

    
    class timeCompare{
    public:
         bool operator()(entry& object1, entry& object2){
             
             if(object1.ts != object2.ts){
                 return object1.ts < object2.ts;
             }
             else if (object1.cat != object2.cat){
                 return object1.cat < object2.cat;
             }
             else{
                 return object1.position < object2.position;
             }
        }
    };
    
};

