#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<vector<char>> A;
vector<vector<int>> state;
vector<vector<int>> dist;

int Z = 26;

const string alpha = "abcdefghijklmnopqrstuvwxyz";

const vector<pair<int,int>> dir = {{1,0},{-1,0},{0,1},{0,-1}};

vector<vector<char>> directReq(Z);
vector<vector<char>> allReq(Z);
vector<vector<int>> dirBlocking(Z);

vector<int> reqMask(Z,0);

void dfs(int i, int j, int fromI, int fromJ, vector<char> req){
    if(state[i][j] == 0){
        // cout << i << "," << j << endl;
        state[i][j] = 1;
        if(A[i][j] >= 'A' && A[i][j] <= 'Z'){
            req.push_back(A[i][j]);
        }
        if(A[i][j] >= 'a' && A[i][j] <= 'z'){
            directReq[A[i][j]-'a'] = req;
            cout << A[i][j] << " => ";
            for(auto c : req)
                cout << c;
            cout << endl;
        }
        if(A[i][j] >= 'a' && A[i][j] <= 'z'){
            req.push_back(A[i][j]-'a'+'A');
        }

        for(auto [di, dj] : dir){
            int i1 = i+di;
            int j1 = j+dj;
            if(i1 == fromI && j1 == fromJ) continue;
            if(A[i1][j1] == '#') continue;

            dfs(i1, j1, i, j, req);
        }
        state[i][j] = 2;
    }
    else if(state[i][j] == 1){
        // then already on the dfs 'path' = LOOP
        cout << i << "," << j << " LOOP" << endl;

    }
    else if(state[i][j] == 2){
        cout << i << "," << j << " ERROR" << endl;
    }
}

set<int> s;

void go(int X) {
    if(s.count(X) != 0) return;
    cout << X << endl;
    s.insert(X);
    for(int i=0;i<Z;i++){
        // if i not in X, but i reachable from X
        if(!(X & (1<<i)) && ((~X)&reqMask[i]) == 0){
            go(X | (1<<i));
        }
    }
}

int main(){
    cin >> N >> M;
    A = vector<vector<char>>(N, vector<char>(M));
    state = vector<vector<int>>(N, vector<int>(M,0));
    dist = vector<vector<int>>(N, vector<int>(M));

    int s_i,s_j;

    for(int i=0;i<N;i++){
        string s; cin >> s;
        for(int j=0;j<M;j++){
            A[i][j] = s[j];
            if(A[i][j] == '@'){
                s_i=i; s_j=j;
            }
        }
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cout << A[i][j];
        }
        cout << endl;
    }

    dfs(s_i,s_j,-1,-1, {});

    // for(int i=0;i<Z;i++){
    //     cout << alpha[i] << "\t";
    //     for(auto c : directReq[i]){
    //         cout << c;
    //     }
    //     cout << endl;
    // }

    for(int i=0;i<Z;i++){
        for(auto c : directReq[i]){
            int j = c - 'A';
            reqMask[i] |= (1<<j);
        }
    }

    // // backtracking
    // vector<int> init(Z, 0);
    // for(int i=0;i<Z;i++){
    //     init[i] = directReq[i].size();
    //     cout << alpha[i] << "\t" << init[i] << endl;
    // }
    // for(int i=0;i<Z;i++){
    //     for(auto r : directReq[i]){
    //         dirBlocking[r-'A'].push_back(i);
    //     }
    // }
    // go(0, init, -1);

    // how many subsets can we reach?
    for(int i=0;i<Z;i++)
        cout << i << "\t" << reqMask[i] << endl;
    go(0);
    cout << "s:" << s.size() << endl;

    return 0;
}