#include <bits/stdc++.h>

using namespace std;

const vector<int64_t> program = {3,8,1005,8,299,1106,0,11,0,0,0,104,1,104,0,3,8,102,-1,8,10,101,1,10,10,4,10,108,1,8,10,4,10,102,1,8,28,1006,0,85,1,106,14,10,3,8,102,-1,8,10,1001,10,1,10,4,10,1008,8,0,10,4,10,101,0,8,58,1,1109,15,10,3,8,1002,8,-1,10,1001,10,1,10,4,10,1008,8,0,10,4,10,1002,8,1,84,3,8,102,-1,8,10,1001,10,1,10,4,10,108,1,8,10,4,10,1002,8,1,105,1006,0,48,3,8,1002,8,-1,10,1001,10,1,10,4,10,108,0,8,10,4,10,102,1,8,130,1006,0,46,1,1001,17,10,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,0,10,4,10,1002,8,1,160,2,109,20,10,3,8,102,-1,8,10,1001,10,1,10,4,10,108,0,8,10,4,10,1002,8,1,185,3,8,102,-1,8,10,1001,10,1,10,4,10,108,1,8,10,4,10,1001,8,0,207,1006,0,89,2,1002,6,10,1,1007,0,10,3,8,102,-1,8,10,101,1,10,10,4,10,1008,8,1,10,4,10,101,0,8,241,2,4,14,10,3,8,102,-1,8,10,101,1,10,10,4,10,1008,8,1,10,4,10,101,0,8,267,1,1107,8,10,1,109,16,10,2,1107,4,10,101,1,9,9,1007,9,1003,10,1005,10,15,99,109,621,104,0,104,1,21101,0,387239486208,1,21102,316,1,0,1106,0,420,21101,0,936994976664,1,21102,327,1,0,1105,1,420,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,21102,1,29192457307,1,21102,1,374,0,1106,0,420,21101,0,3450965211,1,21101,0,385,0,1106,0,420,3,10,104,0,104,0,3,10,104,0,104,0,21102,1,837901103972,1,21101,408,0,0,1106,0,420,21102,867965752164,1,1,21101,0,419,0,1105,1,420,99,109,2,22102,1,-1,1,21102,40,1,2,21102,451,1,3,21102,1,441,0,1106,0,484,109,-2,2106,0,0,0,1,0,0,1,109,2,3,10,204,-1,1001,446,447,462,4,0,1001,446,1,446,108,4,446,10,1006,10,478,1102,0,1,446,109,-2,2105,1,0,0,109,4,1201,-1,0,483,1207,-3,0,10,1006,10,501,21101,0,0,-3,22101,0,-3,1,22102,1,-2,2,21101,1,0,3,21101,520,0,0,1106,0,525,109,-4,2106,0,0,109,5,1207,-3,1,10,1006,10,548,2207,-4,-2,10,1006,10,548,21201,-4,0,-4,1105,1,616,22101,0,-4,1,21201,-3,-1,2,21202,-2,2,3,21101,0,567,0,1106,0,525,22101,0,1,-4,21101,1,0,-1,2207,-4,-2,10,1006,10,586,21102,1,0,-1,22202,-2,-1,-2,2107,0,-3,10,1006,10,608,21202,-1,1,1,21102,608,1,0,106,0,483,21202,-2,-1,-2,22201,-4,-2,-4,109,-5,2105,1,0};

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

// standard cartesian x,y
const vector<int> dx = {0,1,0,-1};
const vector<int> dy = {1,0,-1,0};

int main(){

    Computer pc(program);

    // robot pos
    int x=0,y=0;
    int rot = 0; // 0 = north, 1 = east etc

    map<tuple<int,int>, int> colour;
    colour[{0,0}] = 1;

    while(true){
        cout << colour.size() << endl;
        cout << "pos: "<< x << "," << y << endl;
        int current_colour = colour[{x,y}];
        assert(current_colour == 0 || current_colour == 1);
        pc.in.push(current_colour);
        int steps = 0;
        while(pc.step()){
            steps++;
        }
        cout << "took " << steps << " steps" << endl;
        if(pc.halted) break;
        assert(pc.out.size() == 2);
        int c = pc.out.front(); pc.out.pop();
        int d = pc.out.front(); pc.out.pop();
        assert(d == 0 || d == 1);
        assert(c == 0 || c == 1);

        cout << "Paint " << x << "," << y << "\t" << c << endl;
        colour[{x,y}] = c;
        cout << "!" << endl;
        rot = (4 + rot + (2*d-1))%4;
        x += dx[rot];
        y += dy[rot];
        cout << "Moved to " << x << "," << y << endl;
    }

    cout << colour.size() << endl;

    int minX=0,maxX=0,minY=0,maxY=0;
    for(auto [k,v] : colour){
        auto [x,y] = k;
        minX = min(minX, x);
        minY = min(minY, y);
        maxX = max(maxX, x);
        maxY = max(maxY, y);
    }

    for(int y=maxY;y>=minY;y--){
        for(int x=minX; x<=maxX; x++){
            auto it = colour.find({x,y});
            if(it == colour.end())
                cout << "  ";
            else
                cout << (colour[{x,y}] ? "##" : "..");
        }
        cout << endl;
    }

    return 0;
}