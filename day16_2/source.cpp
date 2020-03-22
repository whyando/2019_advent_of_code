#include <bits/stdc++.h>

using namespace std;

const vector<int> base = {0, 1, 0, -1};

int main(){
    string input_string = "59773590431003134109950482159532121838468306525505797662142691007448458436452137403459145576019785048254045936039878799638020917071079423147956648674703093863380284510436919245876322537671069460175238260758289779677758607156502756182541996384745654215348868695112673842866530637231316836104267038919188053623233285108493296024499405360652846822183647135517387211423427763892624558122564570237850906637522848547869679849388371816829143878671984148501319022974535527907573180852415741458991594556636064737179148159474282696777168978591036582175134257547127308402793359981996717609700381320355038224906967574434985293948149977643171410237960413164669930";
    int R = 10000; // Repeats of input string
    int P = 100;   // Number of phases

    int N1 = input_string.size();

    vector<int> input(N1);
    for(int i=0;i<N1;i++)
        input[i] = input_string[i]-'0';

    int N = R * N1;
    vector<int> A(N);
    for(int i = 0; i < N; i++){
        A[i] = input[i % N1];
    }

    for(int p=1;p<=P;p++){
        cout << p << endl;
        vector<int> B(N,0);
        vector<int> S(N+1,0); // S[i] = sum from A[0] to A[i-1]
        for(int i=1;i<=N;i++)
            S[i] = S[i-1] + A[i-1];

        for(int i=0;i<N;i++){
            int num_intervals = 0;

            int val = 1;
            int interval_start = i;
            int interval_sz = i+1;
            int interval_end = min(interval_start + interval_sz - 1, N-1);

            while(interval_start < N){
                // do stuff
                // cout << "add " << val << " * " << "S[" << interval_start << ":" << interval_end << "]" << endl;
                B[i] += val*(S[interval_end+1] - S[interval_start]);
                // cout << val*(S[interval_end+1] - S[interval_start]) << endl;
                num_intervals++;

                val *= -1;
                interval_start += 2*(i+1);
                interval_end = min(interval_start + interval_sz - 1, N-1);
            }
            // cout << i << "\t" << B[i] << "\t" << num_intervals << endl;
            B[i] = abs(B[i])%10;
        }
        A = B;
    }

    int offset = stoi(input_string.substr(0, 7));
    for(int i=0;i<8;i++){
        cout << A[offset+i];
    }
    cout << endl;

    return 0;
}