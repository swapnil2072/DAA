#include<iostream>
#include<set>
#include<vector>

using namespace std;


void printBoard(vector<vector<char>> board){
    for(auto &row:board){
        for(auto &cell : row){
            cout<<cell<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}


void placeRemainingQueens(int row,int num,vector<vector<char>> &board,set<int> &upward,set<int> &diagonal1,set<int>& diagonal2){
    if(row >= num){
        printBoard(board);
        return;
    }
    for(int col = 0; col < num; col++){
        if(!upward.count(col) && !diagonal2.count(col + row) && !diagonal1.count(row - col)){
            board[row][col] = 'Q';
            upward.insert(col);
            diagonal1.insert(row - col);
            diagonal2.insert(row + col);

            placeRemainingQueens(row+1,num,board,upward,diagonal1,diagonal2);

            board[row][col] = '.';
            upward.erase(col);
            diagonal1.erase(row - col);
            diagonal2.erase(row + col);
        }
    }
}




int main(){
    int n; 
    cout<<"Enter the number of Queens to place: ";
    cin>>n;

    vector<vector<char>> board(n,vector<char>(n,'.'));

    int firstQueenRow, firstQueenCol;
    cout<<"Enter the row and column for the first Queen: ";
    cin>>firstQueenRow>>firstQueenCol;
    board[firstQueenRow][firstQueenCol] = 'Q';

    set<int> col,diagonal1,diagonal2;
    col.insert(firstQueenCol);
    diagonal1.insert(firstQueenRow-firstQueenCol);
    diagonal2.insert(firstQueenRow+firstQueenCol);

    placeRemainingQueens(firstQueenRow+1,n,board,col,diagonal1,diagonal2);
    return 0;
}