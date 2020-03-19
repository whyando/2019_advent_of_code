#include <bits/stdc++.h>

using namespace std;

int main(){
    int W,H;
    cin >> H >> W; cin.ignore();

    vector<int> image(H*W, 2);

    int minZero = INT_MAX;
    int ans;
    for(int layer = 0; layer < 100 ;layer++){
        vector<int> count(3, 0);
        for(int i=0;i<H*W;i++){
            char d; cin >> d;
            int val = d - '0';
            count[val]++;
            if(image[i] == 2)
                image[i] = val;
        }
        cout << layer << "\t" << count[0] << " " << count[1] << " " << count[2] << endl;
        if(count[0] < minZero){
            minZero = count[0];
            ans = count[1]*count[2];
        }
    }
    cout << ans << endl;

    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){            
            cout << (image[W*i + j] ? "XX" : "  ");
        }
        cout << endl;
    }

    return 0;
}