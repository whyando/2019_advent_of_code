#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    int64_t sum = 0;
    for(int i=0;i<N;i++){
        int64_t x; cin >> x;
        sum += (x/3)-2;
    }
    cout << sum << endl;

    return 0;
}