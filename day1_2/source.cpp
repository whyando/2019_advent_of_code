#include <bits/stdc++.h>

using namespace std;

int64_t fuel_cost(int64_t m){
    int64_t f = max((m/3)-2,(int64_t)0);
    if(f == 0)
        return 0;
    else
        return f+ fuel_cost(f);
}

int main(){
    int N;
    cin >> N;
    int64_t sum = 0;
    for(int i=0;i<N;i++){
        int64_t x; cin >> x;
        sum += fuel_cost(x);
    }
    cout << sum << endl;
    return 0;
}