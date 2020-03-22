#include <bits/stdc++.h>

using namespace std;

// globals
int N, M; // input dimensions
int Z; // input alphabet size
vector<vector<char>> A;
vector<vector<int>> dfs_state;
vector<int> reqMask;

// constants
const string alpha = "abcdefghijklmnopqrstuvwxyz";
const vector<pair<int,int>> dir = {{1,0},{-1,0},{0,1},{0,-1}};

// mask is the minimum subset of keys we must obtain to reach this point
void dfs(int i, int j, int mask){
    if(!(i>=0 && i<N && j>=0 && j<M)) return;
    if(A[i][j] == '#') return;
    if(dfs_state[i][j] != 0) return;

    if(A[i][j] >= 'a' && A[i][j] <= 'z'){
        reqMask[A[i][j]-'a'] = mask;
    }

    // if we pass a key or gate, we add its key to the mask
    if(A[i][j] >= 'A' && A[i][j] <= 'Z')
        mask |= 1 << (A[i][j]-'A');
    if(A[i][j] >= 'a' && A[i][j] <= 'z')
        mask |= 1 << (A[i][j]-'a');

    // recursion (to fresh vertices only)
    dfs_state[i][j] = 1;
    dfs(i+1, j, mask);
    dfs(i-1, j, mask);
    dfs(i, j+1, mask);
    dfs(i, j-1, mask);
    dfs_state[i][j] = 2;
}

string maskToString(int mask){
    string s;
    for(int i=0;i<Z;i++)
        if(mask&(1<<i))
            s += alpha[i];
    return s;
}

vector<vector<int>> calculate_dist_between_keys(){
    vector<vector<int>> dist(Z+1, vector<int>(Z+1));
    vector<int> keyI(Z+1),keyJ(Z+1);
    // find keys + start
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(A[i][j] >= 'a' && A[i][j] <= 'z'){
                int k = A[i][j]-'a';
                keyI[k] = i; keyJ[k] = j;
            }
            if(A[i][j] == '@') {
                keyI[Z] = i; keyJ[Z] = j;
            }
        }
    }

    // BFS graph traversal from every key
    for(int r=0;r<Z+1;r++){
        queue<tuple<int,int,int>> q;
        // distance to every point from key r
        vector<vector<int>> distance(N, vector<int>(M,-1));
        q.push({keyI[r], keyJ[r], 0});
        while(!q.empty()){
            auto [i,j,d] = q.front(); q.pop();
            if(distance[i][j] != -1) continue;
            distance[i][j] = d;
            for(auto [di,dj] : vector<pair<int,int>>{{1,0},{-1,0},{0,1},{0,-1}}){
                int i1 = i + di; int j1 = j + dj;
                if(!(i1 >= 0 && i1 < N && j >= 0 && j < M)) continue;
                if(A[i1][j1] == '#') continue;
                q.push({i1,j1,d+1});
            }
        }

        for(int k=0;k<Z+1;k++){
            dist[r][k] = distance[keyI[k]][keyJ[k]];
        }
    }

    for(int i=0;i<Z+1;i++)
        for(int j=0;j<Z+1;j++){
            // cout << dist[i][j] << "\t";
            assert(dist[i][j] == dist[j][i]);
        }
        // cout << endl;
    return dist;
}

int main(){
    // Read the dimensions and number of keys from stdin
    cin >> N >> M >> Z;

    // Read the input from stdin
    A = vector<vector<char>>(N, vector<char>(M));
    int start_i,start_j;
    for(int i=0;i<N;i++){
        string s; cin >> s;
        for(int j=0;j<M;j++){
            A[i][j] = s[j];
            if(A[i][j] == '@') { start_i=i; start_j=j; }
        }
    }

    // Calcuate minimum distances between all pairs of keys (ignoring gates)
    // include the start point as a pretend key on the end
    vector<vector<int>> dist = calculate_dist_between_keys();
    cout << "Distances:" << endl;
    for(int i=0;i<=Z;i++){
        cout << alpha[i] << ":\t";
        for(int j=0;j<=Z;j++)
            cout << dist[i][j] << "\t";
        cout << endl;
    }

    // DFS over all tiles on the board,
    // to calculate the direct prerequisites for each key
    dfs_state = vector<vector<int>>(N, vector<int>(M, 0));
    reqMask = vector<int>(Z, 0);
    dfs(start_i,start_j,0);

    cout << "Direct requisites:" << endl;
    for(int i=0;i<Z;i++)
        cout << alpha[i] << ":\t" << maskToString(reqMask[i]) << endl;
    cout << endl;

    // calculate inherited requisites
    for(int k=0;k<Z;k++){
        for(int i=0;i<Z;i++){
            for(int j=0;j<Z;j++)
                // if key i requires key j, add j's requisites to i
                if(reqMask[i]&(1<<j))
                    reqMask[i] |= reqMask[j];
        }
    }
    cout << "Full(Minimum) requisites:" << endl;
    for(int i=0;i<Z;i++)
        cout << alpha[i] << ":\t" << maskToString(reqMask[i]) << endl;
    cout << endl;

    // Get a list of reachable subsets via DFS graph traversal
    set<int> seen;
    stack<int> q;
    q.push(0);
    while(q.size() != 0){
        int X = q.top(); q.pop();
        auto [it,insert] = seen.insert(X);
        if(!insert) continue;

        for(int i=0;i<Z;i++){
            // if i not in X, but i reachable from X
            if(!(X & (1<<i)) && ((~X)&reqMask[i]) == 0){
                q.push(X | (1<<i));
            }
        }
    }
    const int S = seen.size();
    cout << "Number of reachable subsets:" << S << endl;

    // copy set to a vector
    vector<int> subsetVec(seen.begin(), seen.end());
    vector<int> subsetSz(S, 0);
    map<int, int> subsetLookup;
    for(int i=0;i<S; i++){
        for(int j=0;j<Z;j++)
            subsetSz[i] += (subsetVec[i]&(1<<j) ? 1 : 0);
        subsetLookup[subsetVec[i]] = i;
    }

    // obtain an ordering of the subsets by the size of the subset
    vector<int> z(S);
    iota(z.begin(), z.end(),0);
    sort(z.begin(), z.end(), [&subsetSz](int i,int j){return subsetSz[i]<subsetSz[j];});

    // finally we can do the DP recursion to calculate, for each X, i
    // f[X][i] = fastest way to obtain the subset X and finish at key i
    vector<vector<int>> f(S, vector<int>(Z, INT_MAX));
    for(int X_index : z){
        const int X = subsetVec[X_index];
        if(X == 0) continue;
        // cout << maskToString(subsetVec[s]) << "\t" << subsetSz[s] << endl;
        for(int i=0;i<Z;i++){
            if((X & (1<<i)) == 0) continue;
            const int Y = X ^ (1<<i); // Y = X \ {i}
            // only proceed if X is reachable from Y
            if ((~Y) & reqMask[i]) continue;
            auto it = subsetLookup.find(Y);
            if(it == subsetLookup.end()) continue;
            int Y_index = it->second;
            assert(subsetVec[Y_index] == Y);

            int m = INT_MAX;
            // if Y = {}, use distance from start point instead
            if(Y == 0) {
                m = dist[Z][i];
            }
            else {
                for(int j=0;j<Z;j++){
                    if((Y & (1<<j)) == 0) continue;
                    if(f[Y_index][j] == INT_MAX) continue;
                    m = min(m, f[Y_index][j] + dist[j][i]);
                    // cout << f[Y_index][j]  << " + " << dist[j][i] << endl;
                }
            }
            f[X_index][i] = m;

            // cout << "f[" << maskToString(X) << "][" << alpha[i] << "] = " << f[X_index][i] << endl;
        }
    }

    int F_index = z.back();
    cout << maskToString(subsetVec[F_index]) << "\t" << subsetSz[F_index] << endl;
    for(int i=0;i<Z;i++){
        cout << i << "\t" << f[F_index][i] << endl;
    }

    return 0;
}