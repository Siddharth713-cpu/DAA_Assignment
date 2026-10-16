#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <iomanip>
#include <algorithm>
using namespace std;

struct TestCase { int n, W; vector<int> wt, val; };

void clearScreen(){ cout << "\033[2J\033[H"; }
void drawTable(const vector<vector<int>>& dp, int upto, int W, int testNo){
    clearScreen();
    cout << "0/1 KNAPSACK - LIVE DP TABLE | Test " << testNo << "\n\n";
    cout << setw(6) << "i\\w";
    for(int w=0; w<=W; ++w) cout << setw(5) << w;
    cout << '\n' << string(6 + 5*(W+1), '-') << '\n';
    for(int i=0; i<=upto; ++i){
        cout << setw(6) << i;
        for(int w=0; w<=W; ++w) cout << setw(5) << dp[i][w];
        cout << '\n';
    }
    cout.flush();
}

int solve(const TestCase& t, int testNo, bool animate){
    vector<vector<int>> dp(t.n+1, vector<int>(t.W+1, 0));
    for(int i=1; i<=t.n; ++i){
        for(int w=0; w<=t.W; ++w){
            dp[i][w] = dp[i-1][w];
            if(t.wt[i-1] <= w)
                dp[i][w] = max(dp[i][w], t.val[i-1] + dp[i-1][w-t.wt[i-1]]);
        }
        if(animate){ drawTable(dp, i, t.W, testNo); this_thread::sleep_for(chrono::milliseconds(250)); }
    }
    return dp[t.n][t.W];
}

int main(int argc, char* argv[]){
    string input = (argc > 1 ? argv[1] : "Knapsack data (2).txt");
    ifstream fin(input);
    if(!fin){ cerr << "Cannot open input file: " << input << "\n"; return 1; }
    vector<TestCase> tests;
    string line;
    while(getline(fin,line)){
        if(line.rfind("#Test",0) != 0) continue;
        do { if(!getline(fin,line)){ cerr << "Missing n W after #Test\n"; return 1; } } while(line.empty());
        stringstream ss(line); TestCase t; ss >> t.n >> t.W;
        for(int i=0;i<t.n;i++){
            if(!getline(fin,line)){ cerr << "Incomplete test case\n"; return 1; }
            if(line.empty()){ --i; continue; }
            stringstream item(line); int w,v; item >> w >> v; t.wt.push_back(w); t.val.push_back(v);
        }
        tests.push_back(t);
    }

    ofstream fout("result.txt");
    cout << "Loaded " << tests.size() << " test cases.\n";
    for(size_t i=0;i<tests.size();++i){
        // Animate all tests; disable by passing --fast as second argument.
        bool animate = !(argc > 2 && string(argv[2]) == "--fast");
        int ans = solve(tests[i], (int)i+1, animate);
        cout << "\nTest " << i+1 << " (n=" << tests[i].n << ", W=" << tests[i].W << ") => " << ans << "\n";
        fout << "#Test " << i+1 << " (" << tests[i].n << " " << tests[i].W << ") " << ans << "\n";
        if(animate) this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "\nAll results saved to result.txt\n";
}
