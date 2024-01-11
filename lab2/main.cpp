/**
 * hello.cpp
 *
 * Says hello to the world.
 */
//Project Identifier: 1CAEF3A0FEDD0DEC26BA9808C69D4D22A9962768

#include <iostream>
#include "xcode_redirect.hpp"
#include <vector>
#include <stack>
using namespace std;

bool helper1(vector<size_t> &a, vector<size_t> &b);
bool helper2(vector<char> &a);

int main(int argc, char* argv[]) {
    
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc,argv);
    
    char input;
    stack<char> output;
    
    while (cin >> input){
        if (output.empty()){
            if (input == '}' || input == ')' || input == ']'){
                cout << "Not balanced"<<endl;
                return 0;
            }
        }
            
         if (input == '{' || input == '(' || input == '['){
                output.push(input);
            }
        
            if (input == '}'){
                if(output.top() == '{'){
                    output.pop();
                }
                else{
                    cout << "Not balanced"<<endl;
                    return 0;
                }
            }
        
            if (input == ']'){
                if(output.top() == '['){
                    output.pop();
                }
                else{
                    cout << "Not balanced"<<endl;
                    return 0;
                }
            }
            
            if (input == ')'){
                if(output.top() == '('){
                    output.pop();
                }
                else{
                    cout << "Not balanced"<<endl;
                    return 0;
                }
            }
        }
    
    if(!output.empty()){
        cout << "Not balanced"<<endl;
        return 0;
    }
    
    cout<<"Balanced"<<endl;
    return 0;
    }

