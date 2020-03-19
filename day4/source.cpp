#include <bits/stdc++.h>

using namespace std;

bool check_double(int n){
    int streak_sz = 0;
    int streak_val = -1;
    while(n != 0){
        int d = n % 10; n/=10;        
        if(d == streak_val){
            streak_sz++;
        }
        else {
            // end of streak here
            if(streak_sz == 2) return true;

            streak_val = d;
            streak_sz = 1;
        }
    }
    // end of streak here
    if(streak_sz == 2) return true;
    return false;
}

bool check_desc(int n){
    int prev = -1;
    while(n != 0){
        int d = n % 10; n/=10;
        if(prev != -1) {
            if(!(d <= prev))
                return false;
        }
        prev = d;
    }
    return true;
}

int main(){
    int A = 382345;
    int B = 843167;

    int count = 0;
    for(int n=A; n <=B;n++){
        if(!check_desc(n)) continue;
        if(!check_double(n)) continue;
        cout << n << endl;
        count++;
    }
    cout << count << endl;

    return 0;
}