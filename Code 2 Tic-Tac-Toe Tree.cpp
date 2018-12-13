#include<bits/stdc++.h>
using namespace std;

#define SIZE 3
#define USER1 'x'
#define USER2 'o'
#define NEXTUSER1 1
#define NEXTUSER2 0


struct state {
    char board[SIZE][SIZE];
    int level;
    int remainpos;
    bool nextUser;

};


state* newstate()
{
    state* sempty = new state;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sempty->board[i][j] = '_';
        }
    }
    sempty->level = 0;
    sempty->remainpos = SIZE*SIZE;
    sempty->nextUser = NEXTUSER1;
    return sempty;
}

state* makecopystate(state* copystate)
{
    state* sempty = new state;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sempty->board[i][j] = copystate->board[i][j];
        }
    }
    sempty->level = copystate->level;
    sempty->remainpos = copystate->remainpos;
    sempty->nextUser = copystate->nextUser;
    return sempty;
}

void printBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int calculateScore(char board[3][3])
{
    for (int row = 0; row<3; row++)
    {
        if (board[row][0]==board[row][1] && board[row][1]==board[row][2])
        {
            if (board[row][0]==USER1)
                return 1;
            else if (board[row][0]==USER2)
                return -1;
        }
    }

    for (int col = 0; col<3; col++)
    {
        if (board[0][col]==board[1][col] && board[1][col]==board[2][col])
        {
            if (board[0][col]==USER1)
                return 1;
            else if (board[0][col]==USER2)
                return -1;
        }
    }

    if (board[0][0]==board[1][1] && board[1][1]==board[2][2])
    {
        if (board[0][0]==USER1)
            return 1;
        else if (board[0][0]==USER2)
            return -1;
    }

    if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        if (board[0][2]==USER1)
            return 1;
        else if (board[0][2]==USER2)
            return -1;
    }

    return 0;
}

class XOTree {

public:
    state* root;
    static int count;
    set<vector<int> > setvec;

    XOTree();
    void computeTree();
    void insertstate(state* curr, queue<state*> &levelqueue);
    void fillstate(state* nstate, char user, int* pos);

};
XOTree::XOTree() {
    root = newstate();
}

int XOTree::count = 0;

void XOTree::fillstate(state* nstate, char user, int* pos)
{
    int x, y;
    while (true) {
        x = (*pos)/SIZE;
        y = (*pos)%SIZE;
        if (nstate->board[x][y] == USER1 || nstate->board[x][y] == USER2)   (*pos)++;
        else break;
    }
    nstate->board[x][y] = user;
    (*pos)++;
    count++;
    //cout << "Inner count : " << count << endl;

}

void XOTree::insertstate(state* curr, queue<state*> &levelqueue)
{
    int remainpos = curr->remainpos;
    if (remainpos == 0) return;

    char user;
    if (curr->nextUser) user = USER1;
    else user = USER2;

    int level = curr->level;
    int pos = 0;

    for (int i = 0; i < remainpos; i++) {
        state* nstate = makecopystate(curr);

        fillstate(nstate, user, &pos);

        vector<int> vec;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                vec.push_back((int)nstate->board[i][j]);
              //  cout<<(int)nstate->board[i][j]<<endl;
            }
        }
        //cout<<"comp"<<endl;
        if (XOTree::setvec.find(vec) == XOTree::setvec.end()) {
            XOTree::setvec.insert(vec);
        }
        else {
            continue;
        }
        if (calculateScore(nstate->board) != 0) continue;

        nstate->remainpos = remainpos-1;
        nstate->level = level+1;
        nstate->nextUser = !curr->nextUser;
        printBoard(nstate->board);
        //getchar();

        levelqueue.push(nstate);
    }

    //cout << "insert state complete"<< endl;
}

void XOTree::computeTree()
{
    queue<state*> levelqueue;
    levelqueue.push(root);
    vector<int> vec;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                vec.push_back((int)root->board[i][j]);
              //  cout<<(int)nstate->board[i][j]<<endl;
            }
        }
    setvec.insert(vec);
    int ccount[SIZE*SIZE+1];
    memset(ccount, 0, sizeof(ccount));

    while (!levelqueue.empty()) {
        state* curr = levelqueue.front();
        levelqueue.pop();
        ccount[curr->level]++;

        insertstate(curr, levelqueue);

    }
    for (int i = 0; i < SIZE*SIZE+1; i++) {
        cout << "At level " << i << " states are : " << ccount[i] << "\n";
    }
    cout << "Total nodes: " << setvec.size() << "\n";
}

int main() {

    XOTree* tree = new XOTree();
    tree->computeTree();

    return 0;
}
