#include <bits/stdc++.h>

using namespace std;

const vector<int> program = {3,8,1001,8,10,8,105,1,0,0,21,38,63,88,97,118,199,280,361,442,99999,3,9,1002,9,3,9,101,2,9,9,1002,9,4,9,4,9,99,3,9,101,3,9,9,102,5,9,9,101,3,9,9,1002,9,3,9,101,3,9,9,4,9,99,3,9,1002,9,2,9,1001,9,3,9,102,3,9,9,101,2,9,9,1002,9,4,9,4,9,99,3,9,102,2,9,9,4,9,99,3,9,102,4,9,9,101,5,9,9,102,2,9,9,101,5,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,99,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,99,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,99,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,99};

class Computer {
public:
    Computer(const vector<int> program)
        :v(program)
    {}

    queue<int> in;
    queue<int> out;
    bool halted = false;

    // returns true if the computer actually did anything this step
    // only time this should be false is if it is waiting for an input
    bool step(){
        int opcode = v[ip] % 100;
        // parameter modes
        int pm1 = (v[ip]/100)%10;
        int pm2 = (v[ip]/1000)%10;
        int pm3 = (v[ip]/10000)%10;
        // parameters
        int *p1,*p2,*p3;

        // load the correct number of parameters
        switch(opcode){
            case 1:
            case 2:
            case 7:
            case 8:
                p3 = pm3 ? &v[ip+3] : &v[v[ip+3]];
            case 5:
            case 6:
                p2 = pm2 ? &v[ip+2] : &v[v[ip+2]];
            case 3:
            case 4:
                p1 = pm1 ? &v[ip+1] : &v[v[ip+1]];
            case 99:
                break;
            default:
                cout << "unknown parameter count for opcode " << opcode << endl;
                exit(-1);
        }

        if(opcode == 1) {
            assert(pm3 == 0);
            *p3 = *p1 + *p2;
            ip += 4;
        }
        else if(opcode == 2) {
            assert(pm3 == 0);
            *p3 = *p1 * *p2;
            ip += 4;
        }
        else if(opcode == 3) {
            assert(pm3 == 0);
            if(in.size() == 0){
                cout << "\tWAIT" << endl;
                return false;
            }
            *p1 = in.front(); in.pop();
            ip += 2;
        } 
        else if(opcode == 4) {
            out.push(*p1);
            // cout << "output:" << *p1 << endl;
            ip += 2;
        } 
        else if(opcode == 5) {
            // cout << "jump-if-true" << endl;
            if(*p1 != 0)    ip = *p2;
            else            ip += 3;       
        } 
        else if(opcode == 6) {
            // cout << "jump-if-false" << endl;
            if(*p1 == 0)    ip = *p2;
            else            ip += 3;
        }
        else if(opcode == 7) {
            // cout << "less than" << endl;
            if(*p1 < *p2)   *p3 = 1;
            else            *p3 = 0;
            ip += 4;
        }
        else if(opcode == 8) {
            // cout << "equal" << endl;
            if(*p1 == *p2)  *p3 = 1;
            else            *p3 = 0;
            ip += 4;
        }
        else if(opcode == 99) {
            cout << "\tHALT" << endl;
            halted = true;
            return false; 
            ip+=1; // technically instruction point gets stuck on 99 opcode
        }
        else {
            cout << "ERROR opcode=" << v[ip] << endl;
            exit(-1);
        }
        return true;   
    }
private:
    // instruction pointer
    int ip=0;
    // memory
    vector<int> v;
};

int main(){
    vector<int> phase(5);
    iota(phase.begin(), phase.end(), 5);

    int m = 0;
    vector<int> m_index;
    do {
        vector<Computer> pc(5, program);
        for(int i=0;i<5;i++)
            pc[i].in.push(phase[i]);
        pc[0].in.push(0);

        int power;

        int unit = 0;
        for(int unit = 0;; unit = (unit + 1) % 5){
            if(pc[unit].halted) continue;

            int steps = 0;
            cout << "PC " << unit << endl;
            while(pc[unit].step()){
                steps++;
            }
            cout << "\ttook " << steps << " steps" << endl;
            if(unit == 4 && pc[unit].halted){
                power = pc[4].out.front();
                cout << "UNIT E HAS HALTED, WITH OUTPUT " << power << endl;
                break;
            }
           
            while(pc[unit].out.size() != 0){
                int val = pc[unit].out.front();
                pc[unit].out.pop();
                pc[(unit+1)%5].in.push(val);
                cout << "move val " << val << " from " << unit << endl;
            }

        }

        if(power > m){
            m = power;
            m_index = phase;
        }
    } while(next_permutation(phase.begin(), phase.end()));

    cout << "max power: "<< m << endl; 
    for(int i=0;i<5;i++)
        cout << m_index[i] << " ";
    cout << endl;

    return 0;
}