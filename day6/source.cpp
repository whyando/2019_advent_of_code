#include <bits/stdc++.h>

using namespace std;

// Data Structures
map<string, string> par;
map<string, int> depth_cache;

int get_depth(string s){
    if(depth_cache.count(s) != 0) return depth_cache[s];

    int d = get_depth(par[s]) + 1;
    depth_cache[s] = d;
    return d;
}

int main() {
    // COM, (Center of Mass planet) is the root of the tree
    // ie it has no parent, and is at depth 0.
    par["COM"] = "N/A";
    depth_cache["COM"] = 0;

    // INPUT PARSING - construct tree
    int N; cin >> N;
    for(int i=0;i<N;i++) {
        string s; cin >> s;
        int split = s.find(')');

        // A ) B
        // planet B orbits planet A
        // we say A is parent of B
        string A = s.substr(0, split);
        string B = s.substr(split+1);
        par[B] = A;
    }

    // PART ONE - find the depth of every vertex in the tree rooted at "COM"
    int total = 0;
    for(auto [a, a_parent] : par) {
        total += get_depth(a);
    }
    cout << "Total direct/indirect orbits: " << total << endl;

    // PART TWO - find the distance to the first common ancestor of "YOU" and "SAN"
    int transfers = 0;
    string iterA = "YOU";
    string iterB = "SAN";
    int depthA = depth_cache[iterA];
    int depthB = depth_cache[iterB];

    // swap if necessary to achieve invariant (depthA <= depthB)
    if(!(depthA <= depthB)){
        swap(depthA, depthB);
        swap(iterA, iterB);
    }
    // travel up the chain (towards the root) from B, until we are at matching depth
    while(depthA != depthB) {
        iterB = par[iterB];
        depthB--;
        transfers++;
    }
    // now A and B at the same depth, travel towards the root in both
    while (iterA != iterB) {
        iterA = par[iterA];
        iterB = par[iterB];
        transfers += 2;
    }

    // Since we actually want the distance between par["YOU"] and par["SAN"], we subtract 2
    cout << "Number of transfers: " << transfers-2 << endl;

    return 0;
}