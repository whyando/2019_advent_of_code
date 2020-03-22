#include <bits/stdc++.h>

using namespace std;

const vector<int64_t> program = {109,424,203,1,21101,0,11,0,1105,1,282,21101,18,0,0,1105,1,259,2101,0,1,221,203,1,21101,31,0,0,1105,1,282,21102,38,1,0,1106,0,259,20101,0,23,2,21201,1,0,3,21101,1,0,1,21101,0,57,0,1105,1,303,2101,0,1,222,21001,221,0,3,21001,221,0,2,21101,259,0,1,21101,0,80,0,1106,0,225,21102,117,1,2,21102,91,1,0,1105,1,303,2101,0,1,223,20102,1,222,4,21102,1,259,3,21101,0,225,2,21102,1,225,1,21101,0,118,0,1105,1,225,21001,222,0,3,21102,1,77,2,21102,133,1,0,1105,1,303,21202,1,-1,1,22001,223,1,1,21102,1,148,0,1105,1,259,2102,1,1,223,21002,221,1,4,20101,0,222,3,21102,20,1,2,1001,132,-2,224,1002,224,2,224,1001,224,3,224,1002,132,-1,132,1,224,132,224,21001,224,1,1,21102,195,1,0,106,0,109,20207,1,223,2,20102,1,23,1,21101,0,-1,3,21101,0,214,0,1106,0,303,22101,1,1,1,204,1,99,0,0,0,0,109,5,1202,-4,1,249,21201,-3,0,1,21201,-2,0,2,22101,0,-1,3,21102,250,1,0,1106,0,225,22101,0,1,-4,109,-5,2105,1,0,109,3,22107,0,-2,-1,21202,-1,2,-1,21201,-1,-1,-1,22202,-1,-2,-2,109,-3,2106,0,0,109,3,21207,-2,0,-1,1206,-1,294,104,0,99,21202,-2,1,-2,109,-3,2105,1,0,109,5,22207,-3,-4,-1,1206,-1,346,22201,-4,-3,-4,21202,-3,-1,-1,22201,-4,-1,2,21202,2,-1,-1,22201,-4,-1,1,21202,-2,1,3,21102,1,343,0,1105,1,303,1106,0,415,22207,-2,-3,-1,1206,-1,387,22201,-3,-2,-3,21202,-2,-1,-1,22201,-3,-1,3,21202,3,-1,-1,22201,-3,-1,2,21202,-4,1,1,21102,384,1,0,1106,0,303,1105,1,415,21202,-4,-1,-4,22201,-4,-3,-4,22202,-3,-2,-2,22202,-2,-4,-4,22202,-3,-2,-3,21202,-4,-1,-2,22201,-3,-2,1,22101,0,1,-4,109,-5,2105,1,0};

class Computer {
public:
    Computer(const vector<int64_t> program)
        :v(program)
    {}

    queue<int64_t> in;
    queue<int64_t> out;
    bool halted = false;

    // returns true if the computer actually did anything this step
    // only time this is false if it is waiting for an input
    // or it halts
    bool step(){
        int64_t opcode = v[ip] % 100;
        // parameter modes
        int64_t pm1 = (v[ip]/100)%10;
        int64_t pm2 = (v[ip]/1000)%10;
        int64_t pm3 = (v[ip]/10000)%10;
        // parameters
        int64_t *p1,*p2,*p3;

        // load the correct number of parameters
        switch(opcode){
            case 1:
            case 2:
            case 7:
            case 8:
                p3 = get_param(ip+3, pm3);
            case 5:
            case 6:
                p2 = get_param(ip+2, pm2);
            case 3:
            case 4:
            case 9:
                p1 = get_param(ip+1, pm1);
            case 99:
                break;
            default:
                cout << "unknown parameter count for opcode " << opcode << endl;
                exit(-1);
        }

        if(opcode == 1) {
            assert(pm3 != 1);
            *p3 = *p1 + *p2;
            ip += 4;
        }
        else if(opcode == 2) {
            assert(pm3 != 1);
            *p3 = *p1 * *p2;
            ip += 4;
        }
        else if(opcode == 3) {
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
        else if(opcode == 9) {
            // cout << "rebase" << endl;
            relative_base += *p1;
            ip += 2;
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
    int64_t ip=0;
    // memory
    vector<int64_t> v;
    int64_t relative_base = 0;

    int64_t *get_param(int64_t param_ip, int64_t param_mode){
        int index;
        if(param_mode == 0) index = v[param_ip];
        if(param_mode == 1) index = param_ip;
        if(param_mode == 2) index = v[param_ip] + relative_base;
        if(index >= v.size()){
            cout << "Expanding to size " << index+1 << endl;
            v.resize(index+1);
        }
        return &v[index];
    }
};

int main(){
    int hit = 0;
    vector<vector<int>> ret(50, vector<int>(50));
    for(int x = 0; x < 50; x++){
    for(int y=0;y<50;y++){
        Computer pc(program);
        pc.in.push(x);
        pc.in.push(y);

        int steps = 0;
        while(pc.step()){
            steps++;
        }
        cout << "took " << steps << " steps" << endl;

        while(pc.out.size() != 0){
            int out = pc.out.front(); pc.out.pop();
            cout << out << endl;
            ret[x][y] = out;
            hit += out;
        }

    }}

    for(int y=49;y>=0;y--){
        for(int x=0;x<=49;x++)
            cout << ret[x][y];
        cout << endl;
    }
    cout << "HIT:" << hit << endl;

    return 0;
}