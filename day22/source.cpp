#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, I;
    cin >> I >> N; cin.ignore();

    int x = 2019;
    for(int i=0;i<I;i++){
        string s;
        getline(cin, s);
        // cout << s << endl;

        if(s == "deal into new stack"){
            cout << "FLIP" << endl;
            x = (N-1) - x;
        }
        else if(s.substr(0, 4) == "cut "){
            int y = stoi(s.substr(4));
            cout << "CUT "<< y << endl;
            x = (x - y + N)%N;
        }
        else if(s.substr(0, 19) == "deal with increment"){
            int y = stoi(s.substr(19));
            cout << "INCREMENT "<< y << endl;
            x = (y*x) % N;
        }
        else {
            cout << "unknown" << endl;
        }
    }
    cout << x << endl;



    return 0;
}