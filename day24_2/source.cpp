#include <bits/stdc++.h>

using namespace std;

const int N = 5;

#define BIT_SET_BOOL(X, i, j)        ((X & (1<<(5*(i)+(j)))) ? 1 : 0)
#define BIT(i, j)       (1<<(5*(i)+(j)))
#define VALID(i,j)      ((i)>=0&&(i)<=4&&(j)>=0&&(j)<=4&&((i)!=2||(j)!=2))
#define VALID_ALL(i,j)      ((i)>=0&&(i)<=4&&(j)>=0&&(j)<=4)

#define CENTER(i,j)     (((i)==2&&(j)==2)?1:0)


void print(int S) {
    for(int i=0;i<5;i++) {
        for(int j=0;j<5;j++) {
            if(BIT_SET_BOOL(S, i, j))
                cout << '#';
            else
                cout << '.';
        }
        cout << endl;
    }
    cout << endl;
}

void printAll(vector<int> v){
    for(auto x : v)
        print(x);
}

int count_edge(int x, int di, int dj){
    int ret = 0;
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(!VALID_ALL(i-di, j-dj))
                ret += BIT_SET_BOOL(x, i, j);
    return ret;
}

vector<int> f(const vector<int> S){
    vector<int> out(S.size());
    int out_bot, out_top;
    for(int layer = -1; layer <= (int)S.size(); layer++){
        int T = 0;
        for(int i =0; i < 5;i++){
        for(int j=0;j<5;j++){
            if(i==2&&j==2) continue;
            // count
            int count = 0;
            count += (VALID(i-1,j) && BIT_SET_BOOL(S[layer], i-1, j));
            count += (VALID(i,j-1) && BIT_SET_BOOL(S[layer], i, j-1));
            count += (VALID(i+1,j) && BIT_SET_BOOL(S[layer], i+1, j));
            count += (VALID(i,j+1) && BIT_SET_BOOL(S[layer], i, j+1));

            // if adjacent to center
            if(layer+1 < S.size() && CENTER(i-1,j))
                count += count_edge(S[layer+1], -1, 0);
            if(layer+1 < S.size() && CENTER(i+1,j))
                count += count_edge(S[layer+1], 1, 0);
            if(layer+1 < S.size() && CENTER(i,j-1))
                count += count_edge(S[layer+1], 0, -1);
            if(layer+1 < S.size() && CENTER(i,j+1))
                count += count_edge(S[layer+1], 0, 1);

            // if adjacent to outside edge
            if(layer-1>=0 && !(i+1<5))
                count += BIT_SET_BOOL(S[layer-1], 3, 2);
            if(layer-1>=0 && !(j+1<5))
                count += BIT_SET_BOOL(S[layer-1], 2, 3);
            if(layer-1>=0 && !(i-1>=0))
                count += BIT_SET_BOOL(S[layer-1], 1, 2);
            if(layer-1>=0 && !(j-1>=0))
                count += BIT_SET_BOOL(S[layer-1], 2, 1);

            if (BIT_SET_BOOL(S[layer], i, j) && count == 1) {
                T += BIT(i, j);
            }
            else if (!BIT_SET_BOOL(S[layer], i, j) && (count == 1 || count==2)){
                T += BIT(i, j);
            }
        }}

        if(layer == -1)
            out_bot = T;
        else if(layer == S.size())
            out_top = T;
        else
            out[layer] = T;
    }
    if(out_bot != 0)
        out.insert(out.begin(), out_bot);
    if(out_top != 0)
        out.push_back(out_top);
    return out;
}

int main(){
    int S = 0;
    for(int i =0; i < N;i++){
        string s; getline(cin, s);
        // cout << s << endl;
        for(int j=0;j<5;j++){
            if(s[j] == '#'){
                S += BIT(i, j);
            }
        }
    }
    vector<int> V;
    V.push_back(S);

    // printAll(V);

    for(int i=0;i<200;i++)
        V = f(V);

    printAll(V);

    int total=0;
    for(int k=0;k<V.size();k++){
        for(int i=0;i<5;i++)
            for(int j=0;j<5;j++)
                total += BIT_SET_BOOL(V[k], i,j);
    }
    cout << "total:" << total << endl;

    return 0;
}