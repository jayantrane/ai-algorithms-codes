#include<bits/stdc++.h>
#include<stdlib.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef pair< int, ii > iii;
typedef pair< int, string > pis;
typedef vector<ii> vii;
typedef vector<int> vi;
#define INF 1000000000
#define MOD 1000000007

int findHeuristic(string s)
{
    bool a = s[0]-48;
    bool b = s[1]-48;
    bool c = s[2]-48;
    bool d = s[3]-48;
    bool e = s[4]-48;

    int heuristic = 0;
    (b | !c) ? heuristic += 1 : heuristic += 0;
    (c | !d) ? heuristic += 1 : heuristic += 0;
    (!b) ? heuristic += 1 : heuristic += 0;
    (!a | !e) ? heuristic += 1 : heuristic += 0;
    (e | !c) ? heuristic += 1 : heuristic += 0;
    (!c | !d) ? heuristic += 1 : heuristic += 0;

    return heuristic;
}

bool comparePis(const pis& one,const pis& two)
{
    if (one.first > two.first)
        return true;
    return false;
}

vector< string > generateSuccessors(string s, map < string, string >& parent)
{
    vector< string > vec;
    for (int i = 0; i < s.size(); i++) {
        string next = "";
        if (s[i] == '0') {
            next += s.substr(0,i);
            next += '1';
            next += s.substr(i+1, s.size());
            vec.push_back(next);

        }
        else {
            next += s.substr(0,i);
            next += '0';
            next += s.substr(i+1, s.size());
            vec.push_back(next);
        }
    //    parent[next] = s;

//        cout<< "String : "<< next << endl;
    }
    return vec;
}

void printLine()
{
    for (int i = 0; i < 50; i++) printf("*");
    printf("\n");
}

int main()
{
    cout << "Beam Search\nSAT Problem is (b v ~c)^(c v ~d)^(~b)^(~a v ~e)^(e v ~c)^(~c v ~d)\n";
    cout << "Enter initial Candidate String: ";
    string cands; cin >> cands;
    int beamwidth = 2;
    vector< pis > open;
    bool solution = false;
    int minheuristic = -1;
    int maxheuristic = 6;
    open.push_back(make_pair(findHeuristic(cands), cands));
    int prevMin = findHeuristic(cands);
    map < string, string > parent;

    while (!solution) {
        priority_queue< pis > successors;

        for (int i = 0; i < open.size(); i++) {
            vector< string > next = generateSuccessors(open[i].second, parent);

            for (int j = 0; j < next.size(); j++) {
                int heuristic = findHeuristic(next[j]);
                pis x = make_pair(heuristic, next[j]);
                cout << "String : " << next[j] << " : " << heuristic << endl;
                if (parent.find(next[j]) == parent.end())
                    parent[next[j]] = open[i].second;
                successors.push(x);

            }
            minheuristic = open[i].first > minheuristic ? open[i].first : minheuristic;

        }
        printLine();
        open.clear();
        bool flag = false;
        for (int j = 0; j < beamwidth; j++) {
                pis x = successors.top();
                successors.pop();
                if (x.first == maxheuristic) {

                    cout << "Goal node found as : " << x.second << endl;
                    printLine();

                    cout << "Path is as follows : " << endl;
                    stack < string > path;
                    string y = x.second;
                    while (y != (cands)) {
                        path.push(y);
                        y = parent.at(y);
                    }
                    path.push(cands);
                    int count = 1;
                    while (!path.empty()) {
                        cout <<"Step "<< count << " : " << path.top() << endl;
                        count++;
                        path.pop();
                    }
                    flag = true;
                    solution = true;
                    break;
                }
                if (x.first > prevMin) {
                    flag = true;
                    cout << "Strings in beam are : " << x.second << " : " << x.first << endl;
                    open.push_back(x);
                }

        }
        prevMin = minheuristic;
        cout << "Prev : " << prevMin << endl;
        printLine();
        if (!flag) {
            cout << "Search Terminated due to false lead" << endl;
            break;
            solution = true;
        }

    }

    return 0;
}
