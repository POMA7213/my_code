#include <vector>
#include <iostream>

class SudokuSolver {
public:
    void solveSudoku(std::vector<std::vector<char>>& board) {
        Setup(board);
        Solve(board);
        //Print(board);
    }
private:

    void SetConds(int i, int j, char num, bool val){
        rows[i][num]=val;
        cols[j][num]=val;
        blocks[(i/3)*3+j/3][num]=val;
    }

    void Setup(std::vector<std::vector<char>>& board){
        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                if(board[i][j]=='.'){
                    empties.emplace_back(i, j);
                }
                else{
                    char num=board[i][j]-'1';
                    SetConds(i, j, num, true);
                }
            }
        }
    }

    bool isValid(int i, int j, char c){
        char a=c-'1';
        return !rows[i][a]
               && !cols[j][a]
               && !blocks[(i/3)*3+j/3][a];
    }

    bool Solve(std::vector<std::vector<char>>& board){
        if(empties.empty()){
            return true;
        }
        auto [i, j]=empties.back();
        for(char c='1'; c<='9'; ++c){
            if(!isValid(i, j, c)){
                continue;
            }
            board[i][j]=c;
            empties.pop_back();
            char a=c-'1';
            SetConds(i, j, a, true);
            if(Solve(board)){
                return true;
            }

            board[i][j]='.';
            SetConds(i, j, a, false);
            empties.emplace_back(i, j);
        }
        return false;
    }

    void Print(std::vector<std::vector<int>>& board){
        for(auto& line: board){
            for(auto c: line){
                std::cout<<c<<' ';
            }
            std::cout<<'\n';
        }
        std::cout<<'\n';
    }

    bool rows[9][9];
    bool cols[9][9];
    bool blocks[9][9];
    std::vector<std::pair<int, int>> empties;
};

//int main(){
//    std::vector<std::vector<char>> task={
//            {'.', '.','5','2','.','3','1','.','.'},
//            {'2', '.','.','6','.','9','.','.','8'},
//            {'.', '.','9','5','.','1','2','.','.'},
//            {'1', '.','.','.','.','.','.','.','7'},
//            {'.', '4','.','.','9','.','.','8','.'},
//            {'.', '.','.','3','.','7','.','.','.'},
//            {'.', '.','4','.','.','.','6','.','.'},
//            {'6', '7','.','.','.','.','.','3','9'},
//            {'.', '.','2','.','.','.','8','.','.'},
//    };
//    SudokuSolver sol;
//    sol.solveSudoku(task);
//    return 0;
//}