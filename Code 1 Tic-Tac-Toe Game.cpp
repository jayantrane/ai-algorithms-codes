#include<bits/stdc++.h>
using namespace std;

#define AI 'x'
#define USER 'o'
bool win = false;

struct pos
{
    int row, col;
};

bool isBoardNotFull(char board[3][3])
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]=='_')
                return true;
    return false;
}

bool checkValidity(char board[3][3], int x, int y) {
    if (x >= 0 && x <= 3 && y >= 0 && y <= 3 && board[x][y] == '_') return true;
    return false;
}

int calculateScore(char board[3][3])
{
    for (int row = 0; row<3; row++)
    {
        if (board[row][0]==board[row][1] && board[row][1]==board[row][2])
        {
            if (board[row][0]==AI)
                return 1;
            else if (board[row][0]==USER)
                return -1;
        }
    }

    for (int col = 0; col<3; col++)
    {
        if (board[0][col]==board[1][col] && board[1][col]==board[2][col])
        {
            if (board[0][col]==AI)
                return 1;
            else if (board[0][col]==USER)
                return -1;
        }
    }

    if (board[0][0]==board[1][1] && board[1][1]==board[2][2])
    {
        if (board[0][0]==AI)
            return 1;
        else if (board[0][0]==USER)
            return -1;
    }

    if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        if (board[0][2]==AI)
            return 1;
        else if (board[0][2]==USER)
            return -1;
    }

    return 0;
}

void printWinner(int val, char board[3][3]) {
    if (!isBoardNotFull(board)) {
        cout << "*********************************\nGame Draw\n************************************";

    }
    else if (val == 0) return;
    else if (val > 0) {
        cout << "*********************************\nAI Wins\n************************************";

    }
    else if (val < 0) {
        cout << "*********************************\nUSER Wins\n************************************";
    }
    cout << endl;
    win = true;
    return;
}

void printBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int recursion(char board[3][3], int depth, bool isMax)
{
    int score = calculateScore(board);

    if (score == 1)
        return score;
    if (score == -1)
        return score;

    if (isBoardNotFull(board)==false)
        return 0;

    if (isMax)
    {
        int best = -100;

        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (board[i][j]=='_')
                {
                    board[i][j] = AI;

                    best = max( best,
                        recursion(board, depth+1, !isMax) );

                    board[i][j] = '_';
                }
            }
        }
        return best;
    }


    else
    {
        int best = 100;
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (board[i][j]=='_')
                {
                    board[i][j] = USER;

                    best = min(best,
                           recursion(board, depth+1, !isMax));

                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}



pos findBestMove(char board[3][3])
{
    int bestVal = -100;
    pos bpos;
    bpos.row = -1;
    bpos.col = -1;


    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (board[i][j]=='_')
            {
                board[i][j] = AI;

                int moveVal = recursion(board, 0, false);


                board[i][j] = '_';


                if (moveVal > bestVal)
                {
                    bpos.row = i;
                    bpos.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    printWinner(bestVal, board);

    return bpos;
}

int main()
{
    char board[3][3] =
    {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };

    while(isBoardNotFull(board)) {
        int x, y;
        cout << "Enter user move position: \n x : " ;
        cin >> x;
        cout << " y : ";
        cin >> y;
        x--; y--;
        if (!checkValidity(board, x, y)) {
            continue;
        }
        board[x][y] = USER;
        pos bpos = findBestMove(board);
        board[bpos.row][bpos.col] = AI;
        printBoard(board);
        cout << endl;
        if (win) {
            cout << "Games Ended" << endl;
            break;
        }

    }
    return 0;
}
