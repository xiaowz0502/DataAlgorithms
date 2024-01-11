/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *  EECS 281 Lab 9 - Number of Islands                     *
 *  Identifier: 472D3C8289DE4915774A47683EC45FFBA373B980   *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef ISLANDS_H
#define ISLANDS_H

#include <vector>
#include <queue>
using namespace std;
using pair_type = pair<int,int>;
void helper(int &row, int &col, queue<pair_type> &list, int &count, int &ROW, int &COL,vector<std::vector<char>>& grid);

int number_of_islands(std::vector<std::vector<char>>& grid) {
    int count = 0;
    queue<pair_type> list;
    int ROW = static_cast<int>(grid.size());
    int COL = static_cast<int>(grid[0].size());
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0;j < grid[i].size();j++){
            if(grid[i][j] == 'o'){
                helper(i, j, list, count, ROW, COL,grid);
            }
        }
    }
    
    return count;
}

void helper(int &row, int &col, queue<pair_type> &list, int &count, int &ROW, int &COL,vector<std::vector<char>>& grid){
    count++;
    list.push(make_pair(row, col));
    while(!list.empty()){
        pair_type temp = list.front();
        list.pop();
        if (temp.first == 0 && temp.second == 0){
            if (grid[0][1] == 'o'){
                list.push(make_pair(0, 1));
            }
            if (grid[1][0] == 'o'){
                list.push(make_pair(1, 0));
            }
        }
        else if(temp.first == 0 && temp.second == COL - 1){
            if (grid[1][COL - 1] == 'o'){
                list.push(make_pair(1, COL - 1));
            }
            if (grid[0][COL - 2] == 'o'){
                list.push(make_pair(0, COL - 2));
            }
        }
        else if (temp.first == ROW - 1 && temp.second == 0){
            if (grid[ROW - 1][1] == 'o'){
                list.push(make_pair(ROW - 1, 1));
            }
            if (grid[ROW - 2][0] == 'o'){
                list.push(make_pair(ROW - 2, 0));
            }
        }
        
        else if(temp.first == ROW - 1 && temp.second == COL - 1){
            if (grid[ROW - 1][COL - 2] == 'o'){
                list.push(make_pair(ROW - 1, 1));
            }
            if (grid[ROW - 2][COL - 1] == 'o'){
                list.push(make_pair(ROW - 2, 0));
            }
        }
        else if(temp.first == 0){
            if (grid[0][col + 1] == 'o'){
                list.push(make_pair(0, col + 1));
            }
            if (grid[0][col - 1] == 'o'){
                list.push(make_pair(0, col - 1));
            }
            if (grid[1][col] == 'o'){
                list.push(make_pair(1, col));
            }
        }
        else if(temp.first == ROW - 1){
            if (grid[ROW - 1][col + 1] == 'o'){
                list.push(make_pair(ROW - 1, col + 1));
            }
            if (grid[ROW - 1][col - 1] == 'o'){
                list.push(make_pair(ROW - 1, col - 1));
            }
            if (grid[ROW - 2][col] == 'o'){
                list.push(make_pair(ROW - 2, col));
            }
            
        }
        else if(temp.second == 0){
            if (grid[row + 1][0] == 'o'){
                list.push(make_pair(row + 1, 0));
            }
            if (grid[row - 1][0] == 'o'){
                list.push(make_pair(row - 1, 0));
            }
            if (grid[row][1] == 'o'){
                list.push(make_pair(row, 1));
            }
        }
        
        else if(temp.second == COL - 1){
            if (grid[row + 1][COL - 1] == 'o'){
                list.push(make_pair(row + 1, COL - 1));
            }
            if (grid[row - 1][COL - 1] == 'o'){
                list.push(make_pair(row - 1, COL - 1));
            }
            if (grid[row][COL - 2] == 'o'){
                list.push(make_pair(row, COL - 2));
            }
        }
        else{
            if (grid[row + 1][col] == 'o'){
                list.push(make_pair(row + 1, col));
            }
            if (grid[row - 1][col] == 'o'){
                list.push(make_pair(row - 1, col));
            }
            if (grid[row][col - 1] == 'o'){
                list.push(make_pair(row, col - 1));
            }
            if (grid[row][col + 1] == 'o'){
                list.push(make_pair(row, col + 1));
            }
        }
        
        grid[temp.first][temp.second] = char(count);
    }
}

#endif /* ISLANDS_H */
