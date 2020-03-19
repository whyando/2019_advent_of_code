#include <bits/stdc++.h>

using namespace std;

int _hcf(int a, int b){
    if(b == 0) return a;
    return _hcf(b, a%b);
}
int hcf(int a, int b){
    a = abs(a);
    b = abs(b);
    if(!(a >= b)) swap(a,b);
    return _hcf(a,b);    
}

int main(){
    int N;
    cin >> N;

    vector<vector<bool>> A(N, vector<bool>(N, false));    

    for(int i=0;i<N;i++){
        string s; cin >> s;
        for(int j=0;j<N;j++){
            if(s[j] == '#')
                A[i][j] = true;
            cout << A[i][j];
        }
        cout << endl;
    }

    int bestVal = 0;
    int bestI,bestJ;
    for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
        if(!A[i][j]) continue;
        int detectable_count = 0;
        for(int k=0;k<N;k++){
        for(int l=0;l<N;l++){
            if(!A[k][l]) continue;
            if(i == k && j == l) continue;

            // is i,j detectable from k,l?
            int d = hcf(i-k, j-l);
            int dx = (k-i)/d;
            int dy = (l-j)/d;
            bool detectable = true;
            int curX = i + dx;
            int curY = j + dy;
            while(!(curX == k && curY == l)){
                if(A[curX][curY]){
                    detectable = false;
                    break;
                }
                curX += dx;
                curY += dy;
            }
            detectable_count += detectable;
        }
        }
        cout << i << " " << j << " " << detectable_count << endl;
        if(detectable_count > bestVal){
            bestVal = detectable_count;
            bestI = i;
            bestJ = j;
        }
    }
    }
    // i,j may be reversed
    cout << bestVal << " at " << bestI << "," << bestJ << endl;

    return 0;
}