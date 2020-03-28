#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> m;
map<pair<int,int>, pair<int,int>> paired_point;
map<pair<int,int>, bool> innerBool;
map<string, vector<pair<int,int>>> label;

void printMap(int I_start, int J_start, int I_finish, int J_finish){
    for(int i=I_start; i<=I_finish;i++){
        for(int j=J_start; j<=J_finish;j++){
            cout << m[i][j];
        }
        cout << endl;
    }
}

void findLabel(int i0, int j0, int di, int dj, bool inner){
    int i1=i0+di; int j1=j0+dj;
    int i2=i1+di; int j2=j1+dj;
    assert(m[i0][j0] == '#' || m[i0][j0] == '.');

    assert(m[i1][j1] != '#' && m[i1][j1] != '.');
    assert(m[i2][j2] != '#' && m[i2][j2] != '.');

    if(m[i1][j1] != ' '){
        innerBool[{i0, j0}] = inner;
        if(!(i1 <= i2)) swap(i1, i2);
        if(!(j1 <= j2)) swap(j1, j2);
        // cout << i0 << "," << j0 << ":\t" << m[i1][j1] << m[i2][j2] << endl;
        label[string()+m[i1][j1] + m[i2][j2]].push_back({i0, j0});
    }
}

int main(){
    int N, M, W; // W = wall width
    cin >> N >> M >> W; cin.ignore();

    m = vector<vector<char>>(N, vector<char>(M, ' '));
    for(int i = 0;i< N;i++){
        string s; getline(cin, s);
        for(int j=0;j<s.size();j++)
            m[i][j] = s[j];
    }

    printMap(0, 0, N-1, M-1);
    printMap(2, 2, N-3, M-3);
    printMap(2+W, 2+W, N-3-W, M-3-W);

    // find labels of points that are paired (act like adjacent)
    // each label should be seen twice, except AA and ZZ
    for(int i=2; i <= N-3; i++){
        findLabel(i, 2, 0, -1, false);
        findLabel(i, M-3, 0, 1, false);
    }
    for(int i=2+W; i <= N-3-W; i++) {
        findLabel(i, (2+W)-1, 0, 1, true);
        findLabel(i, (M-3-W)+1, 0, -1, true);
    }

    for(int j=2; j <= M-3; j++){
        findLabel(2, j, -1, 0, false);
        findLabel(N-3, j, 1, 0, false);
    }
    for(int j=2+W; j <= M-3-W; j++) {
        findLabel((2+W)-1, j , 1, 0, true);
        findLabel((N-3-W)+1, j , -1, 0, true);
    }

    for(auto [s, pointVec] : label){
        cout << s << ":\t" << pointVec.size() << endl;
        if(pointVec.size() == 2){
            paired_point[pointVec[0]] = pointVec[1];
            paired_point[pointVec[1]] = pointVec[0];
            assert(innerBool[pointVec[0]] != innerBool[pointVec[1]]);
        }
    }

    // bfs time
    auto [AA_i, AA_j] = label["AA"][0];
    auto [ZZ_i, ZZ_j] = label["ZZ"][0];
    // vector<vector<int>> dist(N, vector<int>(M, INT_MAX));
    vector<vector<vector<int>>> dist;
    dist.emplace_back(N, vector<int>(M, INT_MAX));
    queue<tuple<int,int,int, int>> q;
    q.push({AA_i, AA_j, 0, 0});

    while(!q.empty()){
        auto [i, j, depth, d] = q.front(); q.pop();
        if(depth >= dist.size()){
            dist.emplace_back(N, vector<int>(M, INT_MAX));
        }
        if(dist[depth][i][j] != INT_MAX) continue;
        dist[depth][i][j] = d;

        if(i == ZZ_i && j == ZZ_j){
            cout << "dist(" << depth <<  "):\t" << dist[depth][ZZ_i][ZZ_j] << endl;
            if(depth == 0) break;
        }

        // adjacencies
        for(auto [di, dj] : vector<pair<int,int>>{{0,1},{0,-1},{1,0},{-1,0}}){
            int i1=i+di; int j1=j+dj;
            if(m[i1][j1] != '.') continue;
            q.push({i1, j1, depth, d+1});
        }
        if(paired_point.count({i,j})){
            // don't use outside portals at depth 0
            if(!innerBool[{i,j}] && depth == 0) continue;

            int d_depth = innerBool[{i,j}] ? 1 : -1;

            auto [i1, j1] = paired_point[{i,j}];
            q.push({i1, j1, depth + d_depth, d+1});
        }
    }



    return 0;
}