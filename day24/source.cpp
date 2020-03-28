#include <bits/stdc++.h>

using namespace std;

const int N = 5;

#define BIT_SET_BOOL(X, i, j)        ((X & (1<<(5*(i)+(j)))) ? 1 : 0)
#define BIT(i, j)   (1<<(5*i+j))

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

int f(const int S){
    int T = 0;
    for(int i =0; i < 5;i++){
        for(int j=0;j<5;j++){
            // count adj
            int count = 0;
            count += (i-1>=0 && BIT_SET_BOOL(S, i-1, j));
            count += (j-1>=0 && BIT_SET_BOOL(S, i, j-1));
            count += (i+1<=4 && BIT_SET_BOOL(S, i+1, j));
            count += (j+1<=4 && BIT_SET_BOOL(S, i, j+1));


            if (BIT_SET_BOOL(S, i, j) && count == 1) {
                T += BIT(i, j);
            }
            else if (!BIT_SET_BOOL(S, i, j) && (count == 1 || count==2)){
                T += BIT(i, j);
            }
        }
    }
    return T;
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

    set<int> s;
    while(true){
        if(s.count(S)){
            cout << S << endl;
            print(S);
            break;
        }
        s.insert(S);
        S = f(S);
    }

    return 0;
}