#include <bits/stdc++.h>

using namespace std;

int64_t MOD;

int64_t m(int64_t a, int64_t b){
    a %= MOD; if(a<0) a += MOD;
    b %= MOD; if(b<0) b += MOD;
    int64_t c=0;
    int64_t pow=a;
    while(b!=0){
        if(b&1) c += pow;
        b >>= 1;
        pow = (pow << 1) % MOD;
    }
    c %= MOD; if(c<0) c+= MOD;
    return c;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int64_t N, I, R;
    cin >> I >> N >> R; cin.ignore();
    // N = 10007;
    // R = 1;
    MOD = N;

    // int x = 2019;
    // Ax + B
    int64_t A = 1;
    int64_t B = 0;
    for(int i=0;i<I;i++){
        string s;
        getline(cin, s);
        // cout << s << endl;

        if(s == "deal into new stack"){
            // cout << "FLIP" << endl;
            // x = (-(x+1)) % N;

            B += 1;
            A = m(A,-1);
            B = m(B,-1);
        }
        else if(s.substr(0, 4) == "cut "){
            int64_t y = stoi(s.substr(4));
            // cout << "CUT "<< y << endl;
            // x = (x-y)%N;

            B -= y;
        }
        else if(s.substr(0, 19) == "deal with increment"){
            int64_t y = stoi(s.substr(19));
            // cout << "INCREMENT "<< y << endl;
            // x = (y*x) % N;

            A = m(A,y);
            B = m(B,y);
        }
        else {
            cout << "unknown" << endl;
        }
        // cout << "f(x) = " << A << "x + " << B << endl;
    }
    // if(x<0) x+=N;
    if(A<0) A+=N;
    if(B<0) B+=N;

    // f applied 2^i times
    vector<int64_t> pow2;
    int64_t p = 1;
    vector<int64_t> f_2i_A;
    vector<int64_t> f_2i_B;

    int64_t R1 = R;
    int64_t RA = 1; int64_t RB = 0;
    while(R1 != 0){
        f_2i_A.push_back(A);
        f_2i_B.push_back(B);
        pow2.push_back(p);
        cout << "f^" << p << "(x) = " << A << "x + " << B << endl;

        if(R1 & 1){
            int64_t A1 = m(RA,A);
            int64_t B1 = m(RA,B) + RB;
            assert((m(RA,B) + RB) % N == (m(A,RB) + B) %N);

            RA = A1; RB = B1;
        }
        R1 >>= 1;
        p *= 2;
        int64_t A1 = m(A,A);
        int64_t B1 = m(A, B) + B;
        A = A1; B = B1;
    }
    cout << endl;
    cout << "f^" << R << "(x) = " << RA << "x + " << RB << endl;


    return 0;
}