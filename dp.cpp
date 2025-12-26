#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
#include <string>

using namespace std;


// [A] Fibonacci: TopDown + Bottomup DP 


static int FibTopDownAux(int n, vector<int>& solTable) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    if (solTable[n] != -1) return solTable[n];

    solTable[n] = FibTopDownAux(n - 1, solTable) + FibTopDownAux(n - 2, solTable);
    return solTable[n];
}

static int FibTopDown(int n, vector<int>& solTable) {
    solTable.assign(n + 1, -1);
    return FibTopDownAux(n, solTable);
}


static int BottomUpDP(int n, vector<int>& solTable) {
    solTable.assign(n + 1, 0);
    if (n >= 1) solTable[1] = 1;

    for (int i = 2; i <= n; i++) {
        solTable[i] = solTable[i - 1] + solTable[i - 2];
    }
    return solTable[n];
}

// BottomUpDP2(int n) (O(1) space)
static int BottomUpDP2(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int a = 0; // F(n-2)
    int b = 1; // F(n-1)
    int result = 0; // F(n)

    for (int i = 2; i <= n; i++) {
        result = a + b;
        a = b;
        b = result;
    }
    return result;
}

static void print_1d_table(const vector<int>& t, const string& name) {
    cout << name << " index: ";
    for (int i = 0; i < (int)t.size(); i++) cout << setw(4) << i;
    cout << "\n" << name << " value: ";
    for (int v : t) cout << setw(4) << v;
    cout << "\n";
}


// [B] Minimum Cost Path TopDown
// T[i][j] = 0 if (i==N-1 && j==N-1)
// T[i][j] = min(T[i+1][j], T[i][j+1]) + M[i][j] otherwise

static int MinCostAux(const vector<vector<int>>& M, int i, int j, vector<vector<int>>& T) {
    int N = (int)M.size();

    if (i == N - 1 && j == N - 1) {
        return 0; //goal state 0
    }

    if (T[i][j] != INT_MAX) return T[i][j];

    int downCost = INT_MAX;
    if (i + 1 <= N - 1) {
        downCost = MinCostAux(M, i + 1, j, T);
    }

    int rightCost = INT_MAX;
    if (j + 1 <= N - 1) {
        rightCost = MinCostAux(M, i, j + 1, T);
    }

    int minCost = downCost;
    if (rightCost < minCost) minCost = rightCost;

    // INT_MAX ile toplama yapma
    if (minCost == INT_MAX) {
        T[i][j] = INT_MAX;
    }
    else {
        T[i][j] = M[i][j] + minCost;
    }
    return T[i][j];
}

static int MinimumCostPath_TopDown(const vector<vector<int>>& M, vector<vector<int>>& T) {
    int N = (int)M.size();
    T.assign(N, vector<int>(N, INT_MAX));
    return MinCostAux(M, 0, 0, T);
}

static void print_2d_table(const vector<vector<int>>& T, const string& name) {
    cout << name << ":\n";
    for (int i = 0; i < (int)T.size(); i++) {
        for (int j = 0; j < (int)T[i].size(); j++) {
            if (T[i][j] == INT_MAX) cout << setw(6) << "INF";
            else cout << setw(6) << T[i][j];
        }
        cout << "\n";
    }
}


// [C] 0-1 Knapsack

//BottomUp DP tablosu yapim

static int Knapsack01_BottomUp(const vector<int>& v, const vector<int>& w, int W,
    vector<vector<int>>& dp) {
    int n = (int)v.size() - 1; // 1..n kullaniyoruz
    dp.assign(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int cap = 0; cap <= W; cap++) {
            int leave_val = dp[i - 1][cap];
            int take_val = INT_MIN;

            if (w[i] <= cap) {
                take_val = v[i] + dp[i - 1][cap - w[i]];
            }

            dp[i][cap] = max(leave_val, take_val);
        }
    }
    return dp[n][W];
}

static vector<int> Knapsack_Reconstruct(const vector<int>& v, const vector<int>& w, int W,
    const vector<vector<int>>& dp) {
    int n = (int)v.size() - 1;
    vector<int> picked;

    int cap = W;
    for (int i = n; i >= 1; i--) {
        if (dp[i][cap] != dp[i - 1][cap]) {
            picked.push_back(i);
            cap -= w[i];
        }
    }
    // ters geldi, duzelt
    reverse(picked.begin(), picked.end());
    return picked;
}

static void print_knapsack_table(const vector<vector<int>>& dp) {
    cout << "DP tablosu (satir=item, sutun=kapasite):\n";
    for (int i = 0; i < (int)dp.size(); i++) {
        for (int j = 0; j < (int)dp[i].size(); j++) {
            cout << setw(4) << dp[i][j];
        }
        cout << "\n";
    }
}


void run_dp_demo() {
  
    // [A] Fibonacci
    {
        cout << "\n[A] Fibonacci: Top-Down vs Bottom-Up\n";
        int n = 10;

        vector<int> solTop;
        int f_td = FibTopDown(n, solTop);

        vector<int> solBU;
        int f_bu = BottomUpDP(n, solBU);

        int f_bu2 = BottomUpDP2(n);

        cout << "F(" << n << ") Top-Down = " << f_td << "\n";
        print_1d_table(solTop, "SolTable(TD)");

        cout << "F(" << n << ") BottomUpDP = " << f_bu << "\n";
        print_1d_table(solBU, "SolTable(BU)");

        cout << "F(" << n << ") BottomUpDP2 = " << f_bu2 << " (O(1) space)\n";
    }

    //[B] Min Cost Path TopDown
    {
        cout << "\n[B] Minimum Cost Path (Top-Down + memo table)\n";

        // orn M matrisi
        vector<vector<int>> M = {
            {1, 3, 1, 2},
            {4, 6, 1, 3},
            {2, 1, 8, 1},
            {2, 1, 2, 1}
        };

        vector<vector<int>> T;
        int minCost = MinimumCostPath_TopDown(M, T);

        cout << "Minimum cost (0,0) -> (N-1,N-1): " << minCost << "\n";
        cout << "M matrisi:\n";
        print_2d_table(M, "M");
        cout << "Memo/DP tablosu (T):\n";
        print_2d_table(T, "T");
    }

    //[C] 0-1 Knapsack
    {
        cout << "\n[C] 0-1 Knapsack (DP tablosu)\n";

       
        // v = {30,20,100,90,160}, w={5,10,20,30,40}, W=60
        int n = 5;
        int W = 60;

        vector<int> v(n + 1), w(n + 1);
        v[1] = 30; v[2] = 20; v[3] = 100; v[4] = 90; v[5] = 160;
        w[1] = 5;  w[2] = 10; w[3] = 20;  w[4] = 30; w[5] = 40;

        vector<vector<int>> dp;
        int best = Knapsack01_BottomUp(v, w, W, dp);

        cout << "bst value = " << best << " (W=" << W << ")\n";
        print_knapsack_table(dp);

        vector<int> picked = Knapsack_Reconstruct(v, w, W, dp);
        cout << "secilen item'lar: ";
        for (int id : picked) cout << id << " ";
        cout << "\n";

        int totalW = 0, totalV = 0;
        for (int id : picked) { totalW += w[id]; totalV += v[id]; }
        cout << "toplam agirlik = " << totalW << ", toplam deger = " << totalV << "\n";
    }

    cout << "\nDP demo bitti.\n";
}
