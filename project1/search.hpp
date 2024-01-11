// 50EB44D3F029ED934858FFFCEAC3547C68768FC9
//  search.hpp
//  project1
//
//  Created by 土豆 on 2022/5/5.
//

#ifndef search_hpp
#define search_hpp

#include <stdio.h>
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <utility>



using namespace std;

#endif /* search_hpp */
class sorting{
public:
    //deconstruct
    sorting(){
        stackMode = false;
        queueMode = false;
        stackQueueChosen = false;
        stackQueueNumber = 0;
        
        changeMode = false;
        swapMode = false;
        lengthMode = false;
        
        worldFormate = true;
        modificationFormate = false;
        modeSpecified = 0;
        
        beginIncluded = false;
        endIncluded = false;
        sizeLibrary = 0;
        found = false;
        mode = 'A';
        beginIndex = 0;
        endIndex = 0;
        currentWord = 0;
        finalWord = 0;
        
    }
    
    
    //print error message
    void printHelp(char *argv[]) {
        cout << "Name: " << argv[0] << "\n";
        cout <<
        "This program is to help you"<<
        "learn stack/queue/deque processing,"
        << "\n";
        
        cout <<
        "reading data into a stack/queue/deque,"
        <<"the difference between different STL structures,\n";
        
        cout << "and how to properly read until end-of-file.\n";
    }
    
    //setting mode
    void getMode(int argc, char * argv[]) {
        // These are used with getopt_long()
        opterr = false; // Let us handle all error output for command line options
        string begin;
        string end;
        string output;
        opterr = false; // Let us handle all error output for command line options
        int choice;
        int option_index = 0;
        option long_options[] = {
            // TODO: Fill in two lines, for the "mode" ('m') and
            // the "help" ('h') options.
            {"help", no_argument, nullptr,'h'},
            {"stack", no_argument, nullptr, 's'},
            {"queue", no_argument, nullptr, 'q'},
            {"change", no_argument, nullptr, 'c'},
            {"swap", no_argument, nullptr, 'p'},
            {"length", no_argument, nullptr, 'l'},
            {"begin", required_argument, nullptr, 'b'},
            {"end", required_argument, nullptr,'e'},
            {"output",required_argument, nullptr, 'o' },
            { nullptr, 0,                 nullptr, '\0' }
        };

        // TODO: Fill in the double quotes, to match the mode and help options.
        while ((choice = getopt_long(argc, argv, "hsqcplb:e:o:", long_options, &option_index)) != -1) {
            switch (choice) {
                case 'h':
                    printHelp(argv);
                    exit(0);

                case 's':
                    stackMode = true;
                    queueMode = false;
                    stackQueueNumber++;
                    stackQueueChosen = true;
                    break;
                    
                case 'q':
                    stackMode = false;
                    queueMode = true;
                    stackQueueNumber++;
                    stackQueueChosen = true;
                    break;
                    
                case 'c':
                    changeMode = true;
                    modeSpecified++;
                    break;
                    
                case 'p':
                    swapMode = true;
                    modeSpecified++;
                    break;
                    
                case 'l':
                    lengthMode = true;
                    modeSpecified++;
                    break;
                    
                case 'b':
                    begin = optarg;
                    beginWord = begin;
                    beginIncluded = true;
                    break;
                    
                case 'e':
                    end = optarg;
                    endWord = end;
                    endIncluded = true;
                    break;
                
                case 'o':
                    output = optarg;
                    if(output == "M"){
                        worldFormate = false;
                        modificationFormate = true;
                        break;
                    }
                    
                    if(output == "W"){
                        break;
                    }
                    
                    if (output != "W" && output != "M"){
                        cerr<<"Invalid output mode specified\n";
                        exit(1);
                    }
                    
                default:
                cerr << "Unknown command line option\n";
                exit(1);
            }
        }

        
        
    }
    void error_output(){
        if (stackQueueChosen == false){
            cerr<<"Must specify one of stack or queue\n";
            exit(1);
        }
        
        if (stackQueueNumber > 1){
            cerr<<"Conflicting or duplicate stack and queue specified\n";
            exit(1);
        }
        
        if (modeSpecified == 0){
            cerr<<"Must specify at least one modification mode (change length swap)\n";
            exit(1);
        }
        
        if (beginIncluded == false){
            cerr<<"Beginning word not specified\n";
            exit(1);
        }
        
        if (endIncluded == false){
            cerr<<"Ending word not specified\n";
            exit(1);
        }
        
        
        if(lengthMode == false && beginWord.size() != endWord.size()){
            cerr<<"The first and last words must have the same length when length mode is off\n";
            exit(1);
        }
    }
    
    void beginEndSetting(){
        for (size_t i = 0 ; i < wordLibrary.size(); i++){
            if (endWord == wordLibrary[i].word){
                endIndex = i;
                endFound = true;
            }
            if (beginWord == wordLibrary[i].word){
                beginIndex = i;
                beginFound = true;
            }
        }
    }
    
    void wordContainCheck(){

            if (beginFound == false){
                cerr<<"Beginning word does not exist in the dictionary\n";
                exit(1);
            }
           
            if (endFound == false){
                cerr<<"Ending word does not exist in the dictionary\n";
                exit(1);
            }
        }

   
    void readDict(){
        cin >> mode;
        
        cin >> sizeLibrary;
        string junk;
        getline(cin,junk);
        
        if (mode == 'S'){
            if (lengthMode == true){
                wordLibrary.reserve(sizeLibrary);
            }
            
            while (getline(cin, letter)){
                if (letter[0] == '/') continue;
                if (letter == "") continue;
                if (lengthMode == false && letter.size() != beginWord.size()) continue;
               
                wordSingle a = {letter, false, 0};
                wordLibrary.push_back(a);
            }
        }
        
        else{
            
            if (lengthMode == true){
                wordLibrary.reserve(sizeLibrary);
            }
            
            while (getline(cin, letter)){
                if (letter[0] == '/') continue;
                if (letter == "") continue;
                size_t index = letter.find_first_of("&[!?");
                if(index == string::npos){
                    if (lengthMode == false && letter.size() != beginWord.size()){
                        continue;
                    }
                    else{
                    wordSingle b = {letter, false, 0};
                    wordLibrary.push_back(b);
                }
                }
               //if (lengthMode == false && letter.size() != beginWord.size()) continue
                   
                
                //Reversal (&)
                else if (letter.back() == '&'){
                    
                    letter.pop_back();
                   
                    if (lengthMode == false && letter.size() != beginWord.size()){
                        continue;
                    }
                    
                    else{
                        wordSingle a = {letter, false, 0};
                        wordLibrary.push_back(a);
                        
                        reverse(letter.begin(),letter.end());
                        a.word = letter;
                        //wordSingle b = {letter, false, 0};
                        wordLibrary.push_back(a);
                        
                        sizeLibrary++;
                    }
                }
                
                //Insert-each ([])
                else if (letter[index] == '['){
                    string temp = letter;
                    size_t indexLeft = letter.find("[");
                    size_t indexRight = letter.find("]");
                    size_t distance = 0;
                    size_t finalSize = 0;
                    distance = indexRight - indexLeft + 1 - 2;
                    finalSize = letter.size() - 2 - distance + 1;
                    
                    if (lengthMode == false && finalSize != beginWord.size()){
                        continue;
                    }
                    
                    else{
                    for (size_t i = 0; i < indexRight-1-indexLeft; i++){
                        
                        size_t left = i + 1;
                        size_t right = indexRight - (indexLeft + i + 1 + 1) + 1;
                        
                        if (left != std::string::npos){
                            temp.erase(indexLeft, left);
                        }
                        if (right != std::string::npos){
                        temp.erase(indexLeft + i +2 - left, right);
                        }
                        wordSingle a = {temp, false, 0};
                        wordLibrary.push_back(a);
                        
                        sizeLibrary++;
                        temp = letter;
                    }
                    sizeLibrary--;
                    }
                }
                
                
                //Swap (!)
                else if (letter[index] == '!'){
                    
                    string temp = letter;
                    temp.erase(remove(temp.begin(),temp.end(),'!'),temp.end());
                    
                    if (lengthMode == false && temp.size() != beginWord.size()){
                        continue;
                    }
                    else{
                    wordSingle a = {temp, false, 0};
                    wordLibrary.push_back(a);
                    
                    size_t prevone = letter.find("!") - 1;
                    size_t pretwo = prevone - 1;
                    swap(letter[prevone], letter[pretwo]);
                    letter.erase(remove(letter.begin(),letter.end(),'!'),letter.end());
                        a.word = letter;
                    //wordSingle b = {letter, false, 0};
                    wordLibrary.push_back(a);
                    
                    sizeLibrary++;
                    }
                }
                
               
                //Double (?)
                else if (letter[index] == '?'){
                    string temp = letter;
                    temp.erase(remove(temp.begin(),temp.end(),'?'),temp.end());
                    
                    if(lengthMode == false && temp.size() == beginWord.size()){
                        wordSingle a = {temp, false, 0};
                        wordLibrary.push_back(a);
                    }
                    else if (lengthMode == false && letter.size() == beginWord.size()){
                        size_t prevone = letter.find("?") - 1;
                        char ch = letter[prevone];
                        replace(letter.begin(),letter.end(), '?', ch);
                        wordSingle b = {letter, false, 0};
                        wordLibrary.push_back(b);
                    }
                    else{
                    wordSingle a = {temp, false, 0};
                    wordLibrary.push_back(a);
                    
                    size_t prevone = letter.find("?") - 1;
                    char ch = letter[prevone];
                    replace(letter.begin(),letter.end(), '?', ch);
                    
                    a.word = letter;
                    //wordSingle b = {letter, false, 0};
                    wordLibrary.push_back(a);
                    sizeLibrary++;
                    }
                }
                


                }
            
        }
    }

    
    
      bool changeModeOn(string &b, string  &a){
          //a - current
          // b - investigated
          int num = 0;
            
          if (a.size()!= b.size()){
              return false;
          }
          else{
              for (size_t i = 0; i < a.size(); i++ ){
                  if (a[i] != b[i]){
                      num++;
                      if (num > 1) {
                          return false;
                      }
                   }
              }
              if (num >= 2){
                  return false;
              }
                  
                  return true;
              }
    }

    

    
     bool swapModeOn(string &b, string &a){
         // a current
         //b investigated
         size_t num = 0;
         size_t pos = 0;
        if (a.size()!= b.size()){
            return false;
        }
        else{
            for (size_t i = 0; i < a.size(); i++ ){
                if (a[i] != b[i]){
                    num++;
                    pos = i;
                    if (num > 2){
                        return false;
                    }
                 }
            }
               if(num == 2 && a[pos] == b[pos - 1] && a[pos - 1] == b[pos]){
                    return true;
                }
                else{
                    return false;
                }
            }
    }

    
     
      
    bool lengthModeOn(string &b, string &a){
        
        //a current
        //b investaged
        if(b.size() - a.size() != 1 && a.size() - b.size() != 1){
            return false;
        }
        
        else{
            
            if (a.size() < b.size()){
                
                for (size_t i = 0; i < a.size(); i++){
                    if (a[i] != b[i]){
                        //loop remaining
                        for (size_t m = i; m <a.size(); m++ ){
                            if (a[m] != b[m+1]){
                                return false;
                            }
                        }
                        return true;
                        //loop remaining end
                    }
                }
                return true;
            }
            else{
                for (size_t i = 0; i < b.size(); i++){
                    if (b[i] != a[i]){
                        //loop remaining
                        for (size_t m = i; m <b.size(); m++ ){
                            if (b[m] != a[m+1]){
                                return false;
                            }
                        }
                        return true;
                        //loop remaining end
                    }
                }
                return true;
            }
        }
    }

    
    bool beginEndSameChecker(){
        if (beginIndex == endIndex){
            return true;
        }
        else{
            return false;
        }
    }
    
    string getBeginWord(){
        return beginWord; 
    }
    

 void containerSearching(){
      found = false;
      currentWord = beginIndex;
      finalWord = endIndex;
      wordLibrary[beginIndex].discov = true;
     
     
      while(found == false){
          wordIndex.push_back(currentWord);
          for (size_t i = 0; i <wordLibrary.size(); i++){
              // order
              if (changeMode == true && wordLibrary[i].discov == false && changeModeOn(wordLibrary[i].word, wordLibrary[currentWord].word)){
                  wordLibrary[i].discov = true;
                  wordLibrary[i].pre = currentWord;
                  searchContainer.push_back(i);
                  if (i == endIndex){
                      found = true;
                      wordIndex.push_back(finalWord);
                      break;
                  }
                  
              }
              else if(swapMode == true && wordLibrary[i].discov == false && swapModeOn(wordLibrary[i].word, wordLibrary[currentWord].word) ){
                  wordLibrary[i].discov = true;
                  wordLibrary[i].pre = currentWord;
                  searchContainer.push_back(i);
                 if (i == endIndex){
                      found = true;
                      wordIndex.push_back(finalWord);
                      break;
                  }

              }
              else if(lengthMode == true &&wordLibrary[i].discov == false && lengthModeOn(wordLibrary[i].word, wordLibrary[currentWord].word)){
                  wordLibrary[i].discov = true;
                  wordLibrary[i].pre = currentWord;
                  searchContainer.push_back(i);
                  if (i == endIndex){
                      found = true;
                      wordIndex.push_back(finalWord);
                      break;
                  }
              }
          }
          
          
          if (searchContainer.empty()){
              break;
          }
          
          
          if (found == false){
              if (stackMode == true){
                  currentWord = searchContainer.back();
                  searchContainer.pop_back();
              }
              else if (queueMode == true){
                  currentWord = searchContainer.front();
                  searchContainer.pop_front();
          }
           
          
   }
 }
 }
    
    void finalWordEdit(){
        if (found == true){
            size_t prev = 0;
            prev = wordIndex[wordIndex.size()-1];
            
            while (wordLibrary[prev].pre != beginIndex){
                WordOutput.push_front(prev);
                prev = wordLibrary[prev].pre;
            }
            WordOutput.push_front(prev);
            WordOutput.push_front(beginIndex);
        }
    }
    
    
    bool difference(string &a, string &b){
        size_t number = 0;
        for (size_t i = 0; i < a.size();i++){
            
            if (a[i] != b[i]){
                number++;
                if (number > 1) return false;
                temp = i;
            }
        }
        return true;
    }
    
    void printhelper(string &a, string &b){
        //a pre
        //b curr
        
        if (a.size() > b.size()){
            size_t pos = 0;
            for (size_t i = 0; i < b.size(); i++){
                if(b[i] != a[i]){
                    pos = i;
                break;
                }
                else{
                    pos = a.size()-1;
                }
            }
            cout << "d," << pos <<"\n";
        }
        
        
        else if(a.size() < b.size()){
            size_t pos = 0;
            char letter = b[0];
            for (size_t i = 0; i < a.size(); i++){
                if(a[i]!=b[i]){
                    pos = i;
                    letter = b[i];
                   break;
                }
                else{
                    pos = b.size() - 1;
                    letter = b[pos];
                }
            }
            cout << "i," << pos <<","<< letter <<"\n";
        }
        
        else if (difference(a, b) == false){
            size_t pos = 0;
            pos = temp;
            cout<< "s,"<< pos <<"\n";
        }
        
        else{
            size_t pos = 0;
            char letter = b[0];
            pos = temp;
            letter = b[pos];
            cout <<"c,"<< pos <<","<< letter <<"\n";
        }
    }
    void finalOutput(){
        if (worldFormate == true && found == true){
            cout<<"Words in morph: "<<WordOutput.size()<<"\n";
        for(auto iter = WordOutput.begin(); iter != WordOutput.end(); ++iter) {
           
            cout << wordLibrary[*iter].word<<"\n";
            }
        }
        else if(modificationFormate == true && found == true){
            cout<<"Words in morph: "<<WordOutput.size()<<"\n";
            size_t prev = WordOutput.front();
            
            cout << wordLibrary[prev].word<<"\n";
            WordOutput.pop_front();
            size_t curr = WordOutput.front();
            while ( WordOutput.size()!= 1){
                printhelper(wordLibrary[prev].word, wordLibrary[curr].word);
                prev = curr;
                WordOutput.pop_front();
                curr = WordOutput.front();
            }
            printhelper(wordLibrary[prev].word, wordLibrary[curr].word);
        }
        
        else{
            cout << "No solution, " << wordIndex.size()<<" words discovered.\n";
        }
   }
    
   
private:
    //STLS
    bool stackMode = false;
    bool queueMode = false;
    bool stackQueueChosen = false;
    size_t  stackQueueNumber = 0;
    
    //Three mode
    bool changeMode = false;
    bool swapMode = false;
    bool lengthMode = false;
    
    //word
    bool worldFormate = true;
    bool modificationFormate = false;
    int modeSpecified = 0;
    
    //begin End
    bool beginIncluded = false;
    bool endIncluded = false;
    bool beginFound = false;
    bool endFound = false;
    
    string beginWord = "";
    string endWord = "";
    
    //dictionary container
    
    struct wordSingle{
        string word = "";
        bool discov = false;
        size_t  pre = 0;
    };
    
    vector<wordSingle> wordLibrary;
    
    char mode = 'A';
    size_t sizeLibrary = 0;
    string letter = "";
    
    //search container
    //using pair_type = pair<int,int>;
    deque<size_t> searchContainer;
    vector <size_t> wordIndex;
    
    //size_t index;
    bool found = false;
    //vector <size_t> smallIndex;
    deque <size_t> WordOutput;
    size_t  beginIndex = 0;
    size_t  endIndex = 0;
    size_t currentWord = 0;
    size_t  finalWord = 0;
    size_t temp = 0;
    vector<size_t> differentIndex;
};

