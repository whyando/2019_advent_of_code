#include <bits/stdc++.h>

using namespace std;

int main(){
    int N;
    cin >> N;
    
    // direct requisites
    map<string, vector<string>> req;

    for(int i=0;i!=N;){
        string s; cin >> s;
        if(s == "=>"){
            string s; cin >> s;
            string t; cin >> t;
            cout << " = " << t << " " << s << endl;
            i++;            
        }
        else {
            string t; cin >> t;
            cout << t << " "<< s << endl;
        }
    }

    // get topological ordering for products


    return 0;
}