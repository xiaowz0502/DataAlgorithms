//IDENTIFIER = 1761414855B69983BD8035097EFBD312EB0527F0
//  main.hpp
//  project4
//
//  Created by 土豆 on 2022/6/12.
//

#ifndef main_hpp
#define main_hpp


#endif /* main_hpp */

#include <iostream>
#include "xcode_redirect.hpp"
#include <getopt.h>
#include <vector>
#include <limits>
#include <math.h>
#include <deque>

using namespace std;

class drone{
public:
    
    void getMode(int argc, char * argv[]) {
        // These are used with getopt_long()
        opterr = false; // Let us handle all error output for command line options
        int choice;
        int option_index = 0;
        option long_options[] = {
            {"help",no_argument,nullptr,'h'},
            {"mode",required_argument,nullptr,'m'},
            { nullptr, 0,       nullptr, '\0' }
        };

        // TODO: Fill in the double quotes, to match the mode and help options.
        while ((choice = getopt_long(argc, argv, "hm:", long_options, &option_index)) != -1) {
            switch (choice) {
                case 'h':
                {
                    cout<< "There are several command option provided as following\n";
                    cout<<"For more detailed information please see the spec\n";
                    exit(0);
                }
                    
                case 'm':
                {
                    string mode;
                    mode = optarg;
                    if(mode == "MST"){
                        mst = true;
                        break;
                    }
                    else if(mode == "FASTTSP"){
                        fasttsp = true;
                        break;
                    }
                    else if(mode == "OPTTSP"){
                        opttsp = true;
                        break;
                    }
                    else{
                        cerr<<"Invalid mode\n";
                        exit(1);
                    }
                }
                    
                default:
                    if ((string(argv[1]) == "-m"||string(argv[1]) == "--mode")&& argc < 3){
                        cerr<<"No mode specified\n";
                        exit(1);
                    }
                    cerr<<"Invalid command line option\n";
                    exit(1);
            }
        }
    }
    
    void Caculator(){
        if (mst == true){
            MSTreadIn();
            mstMode();
        }
        else if(fasttsp == true){
            fasttspReadIn();
            fasttspMode();
        }
        else{
            outtspReadIn();
            opttspStartSetting(bestPath,bestDistance);
            bestPath.pop_back();
            
            outties = bestPath;
            
            // keep first index unchangable as 0
            genPerms(1);
            
            cout<<bestDistance<<endl;
            
            for(size_t i = 0; i < bestPath.size(); i++){
                cout << bestPath[i]<< " ";
            }
        }
    }
    void genPerms(size_t permLength) {
    
        if (permLength == outties.size()) {
            double temp1 = distanceCaculator(outties[0], outties[permLength - 1]);
            currDistance += temp1;
            
            if(currDistance < bestDistance){
                bestPath = outties;
                bestDistance = currDistance;
            }
            
            //make a temp
            currDistance -= temp1;
            return;
      }
        
        if (!promising(permLength)){
            return;
        }
        
      for (size_t i = permLength; i < outties.size(); ++i) {
        
        swap(outties[permLength], outties[i]);
          // make a temp variable
          double temp2 = distanceCaculator(outties[permLength - 1], outties[permLength]);
        currDistance += temp2;
        
        genPerms(permLength + 1);
        
        currDistance -= temp2;
        
        swap(outties[permLength], outties[i]);
      }
        
    }
    
    bool promising(size_t permLength){
       //delete following-done
        
        if(outties.size() - permLength < 5){
            return true;
        }
       
        double connection = minDistance(outties[0], outties[permLength - 1],permLength);
        
        double lowerBound = connection + estimateLowerBound(permLength);
       
        if (lowerBound + currDistance > bestDistance){
            return false;
        }
        return true;
    }
    
    double estimateLowerBound(size_t &permLength){
        double total_distance = 0;
        deque<size_t> temp;
        MSTgraphTable.clear();
        MSTgraphTable.resize(outties.size());
        
        for(size_t i = permLength; i < outties.size(); i++){
            temp.push_back(outties[i]);
        }
        
        MSTgraphTable[0].distance = 0;
        size_t falseNum = temp.size();
        
        while(falseNum != 0){
            size_t minTemp = 0;
            minTemp = smallestIndexC(temp);
            
            MSTgraphTable[minTemp].visted = true;
            falseNum-- ;
            total_distance += sqrt(MSTgraphTable[minTemp].distance);

            updatedC(temp, minTemp);
        }
        return total_distance;
    }
    
    
    double minDistance(size_t start, size_t end, size_t permLength){
        double minforStart = numeric_limits<double>::infinity();
        double minforEnd = numeric_limits<double>::infinity();
        
        double distanceStart = 0.0;
        double distanceEnd = 0.0;
        
        for(size_t i = permLength; i < outties.size(); i++){
            distanceStart = distanceCaculator(start, outties[i]);
            distanceEnd = distanceCaculator(end, outties[i]);
            
            if(distanceStart < minforStart){
                minforStart = distanceStart;
            }
            
            if(distanceEnd < minforEnd){
                minforEnd = distanceEnd;
            }
        }
        
        return minforStart + minforEnd;
    }
    
    size_t smallestIndexC(deque<size_t> &temp){
        double distanceMin = numeric_limits<double>::infinity();
        size_t IndexMin = 0;

         for (size_t i = 0; i < temp.size(); i++){
             
             /*
             if(distanceMin == numeric_limits<double>::infinity() && MSTgraphTable[i].distance == numeric_limits<double>::infinity() && MSTgraphTable[i].visted == false){
                 IndexMin = i;
             }*/
             
             if(MSTgraphTable[i].distance < distanceMin && MSTgraphTable[i].visted == false){
                 distanceMin = MSTgraphTable[i].distance;
                IndexMin = i;
             }
         }
         
         return IndexMin;
    }
    
    void updatedC(deque<size_t> &temp, size_t a){
        for (size_t i = 0; i < temp.size(); i++){
            if(MSTgraphTable[i].visted == false){
                double dis = MSTcaculatorForC(temp[a], temp[i]) ;
                if(dis < MSTgraphTable[i].distance){
                    MSTgraphTable[i].distance = dis;
                }
            }
        }
    }
    
    void outtspReadIn(){
        int temp1;
        int temp2;
        cin >> num;
        points.reserve(num);
        
        int count = 0;
        while(cin >> temp1 >> temp2){
            outties.emplace_back(count);
            points.emplace_back(temp1,temp2);
            count++;
        }
    }
    
    void opttspStartSetting(deque<size_t> &bestPath, double &bestDistance){
        
        bestPath.push_back(outties[0]);
        bestPath.push_back(outties[1]);
        bestPath.push_back(outties[2]);
        bestPath.push_back(outties[0]);
        outties.pop_front();
        outties.pop_front();
        outties.pop_front();
        //outties.pop_front();
    
        while(!outties.empty()){
            size_t temp = outties.front();
            outties.pop_front();
            size_t desired_position = minPath(temp,bestPath);
            bestPath.insert(bestPath.begin()+desired_position + 1, temp);
        }
        
        for (size_t i = 0; i < bestPath.size() - 1; i++){
            bestDistance += distanceCaculator(bestPath[i], bestPath[i+1]);
        }
        
    }
    
    void fasttspMode(){
        vector<size_t> path;
        totalCost = 0.0;
        
        path.push_back(0);
        path.push_back(1);
        path.push_back(2);
        path.push_back(0);
        totalCost += distanceCaculator(path[0], path[1]);
        totalCost += distanceCaculator(path[1], path[2]);
        totalCost += distanceCaculator(path[2], path[0]);
    
        
        for(size_t i = 3; i < points.size();i++){
            size_t desired_position = minPathforB(i,path);
            path.insert(path.begin()+desired_position + 1, i);
        }
        
        
        cout << totalCost<<"\n";
        
        for (size_t i = 0; i < path.size() - 1; i++){
            cout << path[i] << " ";
        }
        
    }
    
    
    size_t minPathforB(size_t temp, vector<size_t> &path){
        size_t desired_position = 0;
        double minDistance = numeric_limits<double>::infinity();
        double distance = 0.0;
        
        for(size_t i = 0; i < path.size() - 1 ; i++){
            distance = distanceCaculator(path[i], temp) +
                       distanceCaculator(path[i + 1], temp) -
                       distanceCaculator(path[i], path[i + 1]);
            
            if(distance < minDistance){
                minDistance = distance;
                desired_position = i;
            }
        }
        totalCost += minDistance;
        return desired_position;
    }
    
    
    size_t minPath(size_t temp, deque<size_t> &path){
        size_t desired_position = 0;
        double minDistance = numeric_limits<double>::infinity();
        double distance = 0.0;
        
        for(size_t i = 0; i < path.size() - 1 ; i++){
            distance = distanceCaculator(path[i], temp) +
                       distanceCaculator(path[i + 1], temp) -
                       distanceCaculator(path[i], path[i + 1]);
            
            if(distance < minDistance){
                minDistance = distance;
                desired_position = i;
            }
        }
        totalCost += minDistance;
        return desired_position;
    }
    
    void fasttspReadIn(){
        int temp1;
        int temp2;
        cin >> num;
        points.reserve(num);
        
        int count = 0;
        while(cin >> temp1 >> temp2){
            outties.emplace_back(count);
            points.emplace_back(temp1,temp2);
            count++;
        }
    }
    
    
    void MSTreadIn(){
        int temp1;
        int temp2;
        cin >> num;
        
        cat.reserve(num);
        MSTgraphTable.reserve(num);
        points.reserve(num);
        
        int count = 0;
        while(cin >> temp1 >> temp2){
            outties.emplace_back(count);
            points.emplace_back(temp1,temp2);
            catChecker(temp1, temp2, cat);
            MSTgraphTable.emplace_back();
            count++;
        }
    }
    
    void mstMode(){
        double total_distance = 0;
        if(normalPoint == true && medicalPoint == true && boardPoint == false){
            cerr<<"Cannot construct MST\n";
            exit(1);
        }
        
        MSTgraphTable[0].distance = 0;
        
        while(!outties.empty()){
            size_t minTemp = 0;
            minTemp = smallestIndex(outties);
            
            MSTgraphTable[outties[minTemp]].visted = true;
            total_distance += sqrt(MSTgraphTable[outties[minTemp]].distance);

            updated(outties, minTemp);
            outties.erase(outties.begin()+minTemp);
        }
        
   
        cout << total_distance<<"\n";
        
        for(size_t i = 1; i < MSTgraphTable.size(); i++){
            if(MSTgraphTable[i].prev > static_cast<int>(i)){
                cout << i <<" "<< MSTgraphTable[i].prev<<"\n";
            }
            else{
                cout <<  MSTgraphTable[i].prev <<" "<<i<<"\n";
            }
        }
        
    }
    

    
private:
    int num = 0;
    bool mst = false;
    bool fasttsp = false;
    bool opttsp = false;
    double totalCost= 0;
    bool boardPoint = false;
    bool medicalPoint = false;
    bool normalPoint = false;
    
    
    struct Data{
        int x;
        int y;
        Data(int a, int b){
            x = a;
            y = b;
        }
    };
    vector<Data> points;
    deque<size_t> outties;
    
    //partC
    deque<size_t> bestPath;
    double bestDistance = 0;
    double currDistance = 0;
    
    //MST
    vector<char> cat;
    void catChecker(int &x, int &y, vector<char> &cat){
        if (x < 0 && y < 0){
            cat.emplace_back('m');
            medicalPoint = true;
        }
        else if ((x == 0 && y <= 0) || (y == 0 && x <= 0)){
            cat.emplace_back('b');
            boardPoint = true;
        }
        else{
            cat.emplace_back('n');
            normalPoint = true;
        }
    }
    
        struct mstgraph{
        double distance;
        bool visted;
        int prev;
            
        mstgraph(){
            distance = numeric_limits<double>::infinity();
            visted = false;
            prev = -1;
        }
    };
       vector<mstgraph> MSTgraphTable;
    
    
    size_t smallestIndex(deque<size_t> &outties){
        double distanceMin = numeric_limits<double>::infinity();
        size_t IndexMin = 0;

         for (size_t i = 0; i < outties.size(); i++){
             if(MSTgraphTable[outties[i]].distance < distanceMin){
                 distanceMin = MSTgraphTable[outties[i]].distance;
                IndexMin = i;
             }
         }
         
         return IndexMin;
    }
    
    void updated(deque<size_t> &outties, size_t &a){
        for (size_t i = 0; i < outties.size(); i++){
            if(outties[a] != outties[i]){
                double dis = MSTcaculator(outties[a], outties[i]) ;
                if(dis < MSTgraphTable[outties[i]].distance){
                    MSTgraphTable[outties[i]].distance = dis;
                    MSTgraphTable[outties[i]].prev = static_cast<int>(outties[a]);
                }
            }
        }
    }
    
    double MSTcaculator(size_t &a, size_t&b){
        double dis = 0;
       
        if((cat[a] == 'm' &&cat[b] == 'n') || (cat[a] == 'n' && cat[b] == 'm')){
            dis = numeric_limits<double>::infinity();
            return dis;
        }
        
        double dis1 =  points[a].x - points[b].x;
        double dis2 = points[a].y - points[b].y;
        dis = dis1 * dis1 + dis2 * dis2;
        return dis;
    }
    
    double MSTcaculatorForC(size_t &a, size_t&b){
        double dis = 0;
        double dis1 =  points[a].x - points[b].x;
        double dis2 = points[a].y - points[b].y;
        dis = dis1 * dis1 + dis2 * dis2;
        return dis;
    }
    
    
    double distanceCaculator(size_t &a, size_t&b){
        double dis = 0;
        double dis1 =  points[a].x - points[b].x;
        double dis2 = points[a].y - points[b].y;
        
        dis = dis1 * dis1 + dis2 * dis2;
        dis = sqrt(dis);
        return dis;
    };
    
};


