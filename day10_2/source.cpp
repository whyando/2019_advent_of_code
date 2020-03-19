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

const double PI = 4*atan(1);

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
        // cout << i << " " << j << " " << detectable_count << endl;
        if(detectable_count > bestVal){
            bestVal = detectable_count;
            bestI = i;
            bestJ = j;
        }
    }
    }
    // i,j may be reversed
    cout << bestVal << " at " << bestI << "," << bestJ << endl;

    // part2 starts here
    int laserI = bestI;
    int laserJ = bestJ;

    vector<tuple<int, double>> risk_factor;
    vector<tuple<int,int>> asteroid;

    for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
        if(!A[i][j]) continue;
        if(i == laserI && j == laserJ) continue;

        // is i,j detectable from laserI,laserJ?
        int d = hcf(i-laserI, j-laserJ);
        int dx = (i-laserI)/d;
        int dy = (j-laserJ)/d;
        
        int dist = 0;
        int curX = laserI + dx;
        int curY = laserJ + dy;
        while(!(curX == i && curY == j)){
            if(A[curX][curY]){
                dist++;
            }
            curX += dx;
            curY += dy;
        }

        // could do this with cross product but too lazy
        double theta = atan2(j - laserJ, laserI - i);
        if(theta < 0) theta += 2*PI;

        cout << i << " " << j << " has dist " << dist << endl;
        cout << " and angle " << theta << endl;

        asteroid.push_back({i,j});
        risk_factor.push_back({dist, theta});
    } 
    }

    vector<int> z(asteroid.size());
    iota(z.begin(), z.end(), 0);

    sort(z.begin(), z.end(), [&risk_factor](int i,int j){
        return risk_factor[i]<risk_factor[j];
    });

    for(int i=0;i<200;i++){
        auto [astI, astJ] = asteroid[z[i]];
        cout << i+1 << "\t" << astI << "," << astJ << endl;
    }

    return 0;
}

// in my indexing with i and j
// i is the row number, and j is the column number
// (from top right)
// so basically reversed from problem statements x,y

// north = (-1, 0) etc