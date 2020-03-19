#include <bits/stdc++.h>

using namespace std;

int64_t hcf(int64_t a, int64_t b){
    if(b == 0) return a;
    return hcf(b, a%b);
}

int64_t lcm(int64_t a, int64_t b){
    return (a*b)/hcf(a,b);
}

int time_repeat(vector<int> P) {
    for(int k=0;k<4;k++)
        P.push_back(0);
    map<vector<int>,int> m;
    m[P] = 0;
    for(int t=1;;t++){
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                if(P[i] < P[j]){
                    P[i+4]++;
                    P[j+4]--;
                }
        for(int i=0;i<4;i++)
            P[i] += P[i+4];
        
        if(m.find(P) != m.end()){
            cout << m[P] << " = " << t << endl;
            return t;
        }
        m[P] = t;
    }
    
}

int main(){
    int64_t x = time_repeat({-13,-18,0,-15});
    int64_t y = time_repeat({14,9,-3,3});
    int64_t z = time_repeat({-7,0,-3,-13});
    int64_t L = lcm(lcm(x,y),z);
    cout << L << endl;
    return 0;
}