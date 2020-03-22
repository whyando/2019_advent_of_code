#include <bits/stdc++.h>

using namespace std;

// globals
int N, M; // input dimensions
int Z; // input alphabet size
vector<vector<char>> A;
vector<vector<int>> dfs_state;
vector<int> reqMask;

vector<int> homeQuad;
vector<int> quadMask;

// constants
const string alpha = "abcdefghijklmnopqrstuvwxyz";
const vector<pair<int,int>> dir = {{1,0},{-1,0},{0,1},{0,-1}};

// mask is the minimum subset of keys we must obtain to reach this point
void dfs(int quadrant, int i, int j, int mask){
    if(!(i>=0 && i<N && j>=0 && j<M)) return;
    if(A[i][j] == '#') return;
    if(dfs_state[i][j] != 0) return;

    if(A[i][j] >= 'a' && A[i][j] <= 'z'){
        reqMask[A[i][j]-'a'] = mask;
        homeQuad[A[i][j]-'a'] = quadrant;
        quadMask[quadrant] |= 1 << (A[i][j]-'a');
    }

    // if we pass a key or gate, we add its key to the mask
    if(A[i][j] >= 'A' && A[i][j] <= 'Z')
        mask |= 1 << (A[i][j]-'A');
    if(A[i][j] >= 'a' && A[i][j] <= 'z')
        mask |= 1 << (A[i][j]-'a');

    // recursion (to fresh vertices only)
    dfs_state[i][j] = 1;
    dfs(quadrant, i+1, j, mask);
    dfs(quadrant, i-1, j, mask);
    dfs(quadrant, i, j+1, mask);
    dfs(quadrant, i, j-1, mask);
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
    vector<vector<int>> dist(Z+4, vector<int>(Z+4));
    vector<int> keyI(Z),keyJ(Z); // expands to size Z+4
    // find keys + start
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(A[i][j] >= 'a' && A[i][j] <= 'z'){
                int k = A[i][j]-'a';
                keyI[k] = i; keyJ[k] = j;
            }
            if(A[i][j] == '@') {
                keyI.push_back(i);
                keyJ.push_back(j);
            }
        }
    }

    // BFS graph traversal from every key
    for(int r=0;r<Z+4;r++){
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

        for(int k=0;k<Z+4;k++){
            dist[r][k] = distance[keyI[k]][keyJ[k]];
        }
    }

    for(int i=0;i<Z+4;i++)
        for(int j=0;j<Z+4;j++){
            // cout << dist[i][j] << "\t";
            assert(dist[i][j] == dist[j][i]);
        }
        // cout << endl;
    return dist;
}

bool nextTuple(vector<int> &z, const vector<int> sz){
    int i = 3;
    while(i!=-1 && z[i] + 1 == sz[i]) i--;
    if(i == -1) return false;
    z[i]++;
    while(++i < 4){
        z[i] = (sz[i] == 0) ? -1 : 0;
    }
    return true;
}

int main(){
    // Read the dimensions and number of keys from stdin
    cin >> N >> M >> Z;

    // Read the input from stdin
    A = vector<vector<char>>(N, vector<char>(M));
    vector<int> start_i,start_j;
    for(int i=0;i<N;i++){
        string s; cin >> s;
        for(int j=0;j<M;j++){
            A[i][j] = s[j];
            if(A[i][j] == '@') {
                start_i.push_back(i);
                start_j.push_back(j);
            }
        }
    }

    // Calcuate minimum distances between all pairs of keys (ignoring gates)
    // include the start point as a pretend key on the end
    vector<vector<int>> dist = calculate_dist_between_keys();
    cout << "Distances:" << endl;
    for(int i=0;i<Z+4;i++){
        cout << (i<Z ? string(1,alpha[i]) : "spawn" + string(1,'A'+i-Z))<< ":\t";
        for(int j=0;j<Z+4;j++){
            if(dist[i][j] != -1)
                cout << (j<Z ? string(1,alpha[j]) : "spawn" + string(1,'A'+j-Z)) << dist[i][j] << "\t";
        }
        cout << endl;
    }

    // DFS over all tiles on the board,
    // to calculate the direct prerequisites for each key
    dfs_state = vector<vector<int>>(N, vector<int>(M, 0));
    reqMask = vector<int>(Z, 0);
    homeQuad = vector<int>(Z, 0);
    quadMask = vector<int>(4,0);
    for(int k=0;k<4;k++)
        dfs(k, start_i[k],start_j[k],0);

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
    // vector<vector<int>> f(S, vector<int>(Z, INT_MAX));
    map<pair<int,vector<int>>, int> f;
    f[{0, {-1,-1,-1,-1}}] = 0;
    for(int X_index : z){
        const int X = subsetVec[X_index];
        if(X == 0)continue;

        // consider every 4-tuple that could be a finish point on X
        vector<vector<int>> X_pop(4);
        for(int i=0;i<Z;i++)
            if(X & (1<<i))
                X_pop[homeQuad[i]].push_back(i);

        cout << "(";
        for(int q=0;q<4;q++){
            for(auto i : X_pop[q])
                cout << alpha[i];
            if(q!=3)cout << ",";
        }
        cout << ")\t" << subsetSz[X_index] << endl;

        vector<int> X_pop_sz(4);
        vector<int> I_index(4);
        for(int q=0;q<4;q++){
            X_pop_sz[q] = X_pop[q].size();
            I_index[q] = (X_pop_sz[q] == 0) ? -1 : 0;
        }

        do {
            vector<int> I(4);
            for(int q=0;q<4;q++)
                I[q] = (X_pop_sz[q] == 0) ? -1 : X_pop[q][I_index[q]];

            // cout << "!";
            // CALCULATE f[X, I] HERE -- START
            // f[{X,I}] = ...

            int m = INT_MAX;
            for(int lastMoveQ = 0; lastMoveQ < 4; lastMoveQ++){
                int i = I[lastMoveQ];
                if(i == -1) continue;
                const int Y = X ^ (1<<i); // Y = X \ {i}
                const int Y_quad = Y & quadMask[lastMoveQ];
                // only proceed if X is reachable from Y
                if ((~Y) & reqMask[i]) continue;
                auto it = subsetLookup.find(Y);
                // only proceed if Y is reachable from anywhere
                if(it == subsetLookup.end()) continue;

                int Y_index = it->second;
                assert(subsetVec[Y_index] == Y);

                /* logic
                // consider Y with mask lastMoveQ applied,
                // either its empty, in which case we must have come from spawn
                // OR, its not empty, in which case we may have come from any of the N places,
                // so we take minimum of those N values + distance to i
                */
                if(Y_quad == 0){
                    vector<int> I1 = I;
                    I1[lastMoveQ] = -1;
                    if(f.count({Y_index,I1}) == 0) continue;
                    // cout << "!\t" << f[{Y_index,I1}] << " + "<< dist[Z + lastMoveQ][i] << endl;
                    m = min(m, f[{Y_index,I1}] + dist[Z + lastMoveQ][i]);
                }
                else {
                    for(int j=0;j<Z;j++){
                        if((Y_quad & (1<<j)) == 0) continue;
                        vector<int> I1 = I;
                        I1[lastMoveQ] = j;
                        if(f.count({Y_index,I1}) == 0) continue;
                        // cout << "\t" << f[{Y_index,I1}] << " + "<< dist[j][i] << endl;
                        m = min(m, f[{Y_index,I1}] + dist[j][i]);
                        assert(dist[j][i] != -1);
                        // cout << f[Y_index][j]  << " + " << dist[j][i] << endl;
                    }
                }
            }
            if(m != INT_MAX){
                f[{X_index,I}] = m;

                cout << "f[" << maskToString(X) << "][";
                for(auto i : I)
                    cout << (i == -1 ? '.' : alpha[i]);
                cout << "] = " << f[{X_index,I}] << endl;
                // assert(m != INT_MAX);
            }

            // CALCULATE f[X, I] HERE -- END
        } while (nextTuple(I_index, X_pop_sz));
        cout << endl;
    }

    return 0;
}