#include <bits/stdc++.h>

using namespace std;

const vector<int> base = {0, 1, 0, -1};

vector<vector<int>> matrix_mult(
    const vector<vector<int>> A,
    const vector<vector<int>> B)
{
    assert(A[0].size() ==  B.size());
    vector<vector<int>> C(A.size(), vector<int>(B[0].size(),0));
    for(int i=0;i<A.size();i++){
        for(int j=0;j<B[0].size();j++){
            for(int k=0;k<A[0].size();k++){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    return C;
}

int main(){
    string input_string = "03036732577212944063491565474664";
    int N = input_string.size();
    cout << N << endl;

    vector<int> input(N);
    for(int i=0;i<N;i++)
        input[i] = input_string[i]-'0';

    vector<vector<int>> A(N, vector<int>(N));

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            // periodicity (i+1)*4
            // (j+1) % (4*i + 4)
            int pos = ((j+1) % (4*i + 4))/(i+1);
            A[i][j] = base[pos];
            // cout << pos << "\t";
        }
        // cout << endl;
    }


    vector<vector<int>> x(N);
    for(int i=0;i<N;i++)
        x[i] = {input[i]};

    for(int p=1;p<=100;p++){
        x = matrix_mult(A, x);
        for(int i=0;i<N;i++){
            x[i][0] = abs(x[i][0]) % 10;
            // cout << x[i][0];
        }
        // cout << endl;
    }

    for(int i=0;i<8;i++){
        cout << x[i][0];
    }
    cout << endl;

    return 0;
}