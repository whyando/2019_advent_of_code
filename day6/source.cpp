#include <bits/stdc++.h>

using namespace std;

map<string, string> par;
map<string, int> depth;

void compute_depth(string s){
    if(depth[s] != -1) return; // we already know depth[s]
    compute_depth(par[s]);
    depth[s] = depth[par[s]] + 1;
}

int main(){
    int N;
    cin >> N;
    
    par["COM"] = "N/A";
    depth["COM"] = 0;

    for(int i=0;i<N;i++){
        string s; cin >> s;
        int split = s.find(')');

        string A = s.substr(0, split);
        string B = s.substr(split+1);

        // cout << A << " " << B << endl;
        // then A is parent of B
        par[B] = A;
        depth[B] = -1;
    }

    int total = 0;
    for(auto [a, b] : par){
        compute_depth(a);
        total += depth[a];
        cout << a << ":" << depth[a] << endl;
    }
    cout << total << endl;

    int transfers = 0;
    string iterA = "YOU";
    int depthA = depth[iterA];
    string iterB = "SAN";
    int depthB = depth[iterB];

    // swap so B is at least as deep as A
    if(!(depthA <= depthB)){
        swap(depthA, depthB);
        swap(iterA, iterB);
    } 
    for(int k=0;k<depthB-depthA;k++){
        iterB = par[iterB];
        transfers++;
    }
    // now A and B at the same level
    while(iterA != iterB){
        iterA = par[iterA];
        iterB = par[iterB];
        transfers += 2;
    }
    cout << transfers-2 << endl;

    return 0;
}