#include <bits/stdc++.h>

using namespace std;

map<string, int> state;
map<string, set<string>> uses;

vector<string> order;

map<string, int64_t> quantity;
map<string, vector<pair<string,int64_t>>> cost;

void dfs(string s){
    if(state[s] == 1) { // would mean a loop
        cout << "?!" << endl;
        exit(0);
    }
    if(state[s] == 2) return;

    cout << "dfs(\"" << s << "\")" << endl;
    state[s] = 1;
    for(auto t : uses[s]){
        dfs(t);
    }
    state[s] = 2;
    order.push_back(s);
}

bool can_make_f_fuel(int f){
    map<string, int64_t> required;
    required["FUEL"] = f;
    for(auto s : order){
        if(s == "ORE") break;
        int64_t purchases = (required[s] + quantity[s] - 1)/quantity[s];
        // cout << s << "\trequire " << required[s] << ": ";
        // cout << purchases << " purchases of " << quantity[s] << " each" << endl;
        for(auto [item, amm] : cost[s]){
            required[item] += amm*purchases;
        }
    }
    // cout << "require " << required["ORE"] << " ORE" << endl;
    cout << f << " FUEL COSTS\t" << required["ORE"] << endl;
    return required["ORE"] <= 1000000000000;
}

int main(){
    int N;
    cin >> N;
    
    vector<string> itemList;

    vector<pair<string,int64_t>> c;
    for(int i=0;i!=N;){
        string s; cin >> s;
        if(s == "=>"){
            string s; cin >> s;
            string t; cin >> t;
            // cout << " = " << t << " " << s << endl;
            cost[t] = c;
            quantity[t] = stoi(s);
            itemList.push_back(t);

            for(auto [item, amm] : c){
                uses[item].insert(t);
            }
            c.clear();
            i++;            
        }
        else {
            string t; cin >> t;
            if(t.back() == ',') t = t.substr(0, t.size()-1);
            // cout << t << " "<< s << endl;
            c.push_back({t, stoi(s)});
        }
    }

    // ORE is the only item you cannot make
    // every other item has exactly one recipe
    itemList.push_back("ORE");

    // init state for dfs
    for(auto s : itemList)
        state[s] = 0;

    // get topological ordering for products
    dfs("ORE");

    cout << itemList.size() << endl;
    cout << order.size() << endl;

    // map<string, int> required;
    // required["FUEL"] = 1;
    // for(auto s : order){
    //     if(s == "ORE") break;
    //     int purchases = (required[s] + quantity[s] - 1)/quantity[s];
    //     cout << s << "\trequire " << required[s] << ": ";
    //     cout << purchases << " purchases of " << quantity[s] << " each" << endl;
    //     for(auto [item, amm] : cost[s]){
    //         required[item] += amm*purchases;
    //     }
    // }
    // cout << "require " << required["ORE"] << " ORE" << endl;

    int a = 1;
    int b = 1;
    while(can_make_f_fuel(b)) b*=2;
    
    // BINARY SEARCH
    // can_make_f_fuel(a) always true
    // can_make_f_fuel(b) always false
    while(a + 1 != b){
        // cout << a << " " << b << endl;
        int m = (a + b)/2;
        bool fm = can_make_f_fuel(m);
        if(fm)  
            a = m;
        else
            b = m;     
    }
    cout << "(" << a << "," << b << ")" << endl;

    return 0;
}