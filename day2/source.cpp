#include <bits/stdc++.h>

using namespace std;

int f(int a,int b){
    vector<int> v = {1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,13,19,1,9,19,23,2,13,23,27,2,27,13,31,2,31,10,35,1,6,35,39,1,5,39,43,1,10,43,47,1,5,47,51,1,13,51,55,2,55,9,59,1,6,59,63,1,13,63,67,1,6,67,71,1,71,10,75,2,13,75,79,1,5,79,83,2,83,6,87,1,6,87,91,1,91,13,95,1,95,13,99,2,99,13,103,1,103,5,107,2,107,10,111,1,5,111,115,1,2,115,119,1,119,6,0,99,2,0,14,0};
    
    v[1] = a;
    v[2] = b;

    int ip = 0;
    while(true){
        if(v[ip] == 1) {
            // cout << "v[" << v[ip+3] << "] = " << "v[" << v[ip+1] << "] + " << "v[" << v[ip+2] << "]" << endl;
            // cout << "\t = " << v[v[ip+1]] << " + " << v[v[ip+2]] << endl;
            v[v[ip+3]] = v[v[ip+1]] + v[v[ip+2]];
        }
        else if(v[ip] == 2) {
            //cout << "v[" << v[ip+3] << "] = " << "v[" << v[ip+1] << "] * " << "v[" << v[ip+2] << "]" << endl;
            // cout << "\t = " << v[v[ip+1]] << " * " << v[v[ip+2]] << endl;
            v[v[ip+3]] = v[v[ip+1]] * v[v[ip+2]];
        }
        else if(v[ip] == 99) {
            // cout << "halt " << v[0] << endl;     
            return v[0]; 
        }
        else {
            cout << "ERROR opcode=" << v[ip] << endl;
            break;
        }
        ip+=4;
    }
}

int main(){
    for(int a=0;a<=99;a++){
        for(int b=0;b<=99;b++){
            int f_a_b = f(a,b);
            cout << a << "\t" << b << "\t" << f_a_b << endl;
            if(f_a_b == 19690720){
                cout << "a=" << a << " b=" << b << endl;
                return 0;
            }
        }
    }

    return 0;
}