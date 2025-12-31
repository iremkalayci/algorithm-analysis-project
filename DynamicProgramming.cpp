#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
#include <string>
#include <algorithm> 

using namespace std;



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



// basliklar icin cizgi
static void print_line(char ch, int w) {
    cout << string(w, ch) << "\n";
}

// bolum basligi
static void print_section(const string& title) {
    cout << "\n";
    print_line('#', 60);
    cout << "# " << left << setw(56) << title << " #\n";
    print_line('#', 60);
    cout << "\n";
}

// alt baslik
static void print_subtitle(const string& title) {
    cout << "\n--- " << title << " ---\n";
}

// 1D tabloyu kutu icinde yazdirma
static void print_1d_values(const vector<int>& t, const string& label) {
    cout << "\n" << label << ":\n";

    // ust Cizgi
    cout << "+";
    for (size_t i = 0; i < t.size(); i++) cout << "-----+";
    cout << "\n";

    // degerler
    cout << "|";
    for (int v : t) {
        if (v == -1) cout << "  -  |";
        else cout << setw(4) << v << " |";
    }
    cout << "\n";

    // alt Cizgi
    cout << "+";
    for (size_t i = 0; i < t.size(); i++) cout << "-----+";
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

// 2D tabloyu izgara seklinde yazdirma
static void print_2d_table(const vector<vector<int>>& T, const string& name) {
    if (T.empty()) return;
    int cols = (int)T[0].size();

    cout << "\nTABLO: " << name << "\n";

    // ust Cizgi
    cout << "+";
    for (int c = 0; c < cols; c++) cout << "-------+";
    cout << "\n";

    for (int i = 0; i < (int)T.size(); i++) {
        cout << "|";
        for (int j = 0; j < (int)T[i].size(); j++) {
            if (T[i][j] == INT_MAX) cout << "  INF  |";
            else if (T[i][j] == -1) cout << "   -   |";
            else cout << setw(6) << T[i][j] << " |";
        }
        cout << "\n";

        // Ara/Alt Cizgi
        cout << "+";
        for (int c = 0; c < cols; c++) cout << "-------+";
        cout << "\n";
    }
}


// [C] 0-1 knapsack

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

// Knapsack tablosunun ozetini cizgili yazdirma
static void print_knapsack_table_compact(const vector<vector<int>>& dp, const vector<int>& caps) {
    int n = (int)dp.size() - 1;

    cout << "\nKnapsack Ozet\n";

    // Cizgi
    cout << "+----------+";
    for (size_t i = 0; i < caps.size(); i++) cout << "-------+";
    cout << "\n";

    // Basliklar
    cout << "| Kapasite |";
    for (int c : caps) cout << setw(6) << c << " |";
    cout << "\n";

    // Ara Cizgi
    cout << "+----------+";
    for (size_t i = 0; i < caps.size(); i++) cout << "-------+";
    cout << "\n";

    // Degerler
    cout << "| Deger    |";
    for (int c : caps) cout << setw(6) << dp[n][c] << " |";
    cout << "\n";

    // Alt Cizgi
    cout << "+----------+";
    for (size_t i = 0; i < caps.size(); i++) cout << "-------+";
    cout << "\n";
}

// Knapsack adimli tablo cizgili
static void print_knapsack_table_step(const vector<vector<int>>& dp, int W, int step) {
    cout << "\nDP Tablosu:\n";

    // Sutun sayisi hesaplama
    int cols = 0;
    for (int cap = 0; cap <= W; cap += step) cols++;

    // Ust Cizgi
    cout << "+-------+";
    for (int k = 0; k < cols; k++) cout << "-------+";
    cout << "\n";

    // Header
    cout << "| i \\ W |";
    for (int cap = 0; cap <= W; cap += step) cout << setw(6) << cap << " |";
    cout << "\n";

    // Ara Cizgi
    cout << "+-------+";
    for (int k = 0; k < cols; k++) cout << "-------+";
    cout << "\n";

    for (int i = 0; i < (int)dp.size(); i++) {
        cout << "| Item" << setw(1) << i << " |";
        for (int cap = 0; cap <= W; cap += step) {
            cout << setw(6) << dp[i][cap] << " |";
        }
        cout << "\n";

        // Satir alt cizgisi
        cout << "+-------+";
        for (int k = 0; k < cols; k++) cout << "-------+";
        cout << "\n";
    }
}


void run_dp_demo() {



    // [A] Fibonacci
    {
        print_subtitle("A) Fibonacci Top-Down and Bottom-Up");
        int n = 10;

        vector<int> solTop;
        int f_td = FibTopDown(n, solTop);

        vector<int> solBU;
        int f_bu = BottomUpDP(n, solBU);

        int f_bu2 = BottomUpDP2(n);

        cout << "n = " << n << "\n";
        cout << "Top-Down Result  : " << f_td << "\n";
        print_1d_values(solTop, "TopDown Table");

        cout << "Bottom-Up Result : " << f_bu << "\n";
        print_1d_values(solBU, "BottomUp Table");

        cout << "BottomUpDP2      : " << f_bu2 << " (O(1) space)\n";
    }

    //[B] Min Cost Path TopDown
    {
        print_subtitle("B) Minimum Cost Path (Top-Down + Memo Table)");

        // orn M matrisi
        vector<vector<int>> M = {
            {1, 3, 1, 2},
            {4, 6, 1, 3},
            {2, 1, 8, 1},
            {2, 1, 2, 1}
        };

        vector<vector<int>> T;
        int minCost = MinimumCostPath_TopDown(M, T);

        print_2d_table(M, "M Matrisi (Maliyetler)");
        cout << "\n";
        print_2d_table(T, "Memo/DP Tablosu (T)");
        cout << "\nMinimum cost (0,0) -> (N-1,N-1): " << minCost << "\n";
    }

    //[C] 0-1 Knapsack
    {
        print_subtitle("C) 0-1 knapsack (bottom up DP)");

        // v = {30,20,100,90,160}, w={5,10,20,30,40}, W=60
        int n = 5;
        int W = 60;

        vector<int> v(n + 1), w(n + 1);
        v[1] = 30; v[2] = 20; v[3] = 100; v[4] = 90; v[5] = 160;
        w[1] = 5;  w[2] = 10; w[3] = 20;  w[4] = 30; w[5] = 40;

        vector<vector<int>> dp;
        int best = Knapsack01_BottomUp(v, w, W, dp);

        cout << "W = " << W << "\n";
        cout << "Best value = " << best << "\n";

       
        vector<int> caps = { 0,10,20,30,40,50,60 };
        print_knapsack_table_compact(dp, caps);

        
        int step = 10; 
        print_knapsack_table_step(dp, W, step);

        vector<int> picked = Knapsack_Reconstruct(v, w, W, dp);
        cout << "\nSecilen item'lar: ";
        for (int id : picked) cout << id << " ";
        cout << "\n";

        int totalW = 0, totalV = 0;
        for (int id : picked) { totalW += w[id]; totalV += v[id]; }
        cout << "Toplam agirlik = " << totalW << ", toplam deger = " << totalV << "\n";
    }
}