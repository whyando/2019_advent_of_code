#include <bits/stdc++.h>

using namespace std;

int main(){
    vector<vector<int>> pos = {{-13, 14, -7}, {-18,9,0},{0,-3,-3},{-15,3,-13}};
    vector<vector<int>> vel = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
    int T = 1000;

    for(int t=1;t<=T;t++){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                for(int k=0;k<3;k++){
                    if(pos[i][k] > pos[j][k]) {
                        vel[i][k] -= 1;
                        vel[j][k] += 1;
                    }
                }      
            }
        }

        for(int i=0;i<4;i++){
            for(int k=0;k<3;k++){
                pos[i][k] += vel[i][k];
            }
        }
    }

    for(int i=0;i<4;i++){
        for(int k=0;k<3;k++)
            cout << pos[i][k] << " ";
        cout << "\t";
        for(int k=0;k<3;k++)
            cout << vel[i][k] << " ";
        cout << endl;
    }

    int total = 0;
    for(int i=0;i<4;i++){
        int pot = abs(pos[i][0]) + abs(pos[i][1]) + abs(pos[i][2]);
        int kin = abs(vel[i][0]) + abs(vel[i][1]) + abs(vel[i][2]);
        total += kin*pot;
    }

    cout << total << endl;

    return 0;
}