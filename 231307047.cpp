#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <random>
#include <climits>
#include "heap.h"

#include "maxsubseq.h"

using namespace std;

// recursive.cpp icinde var
void run_recursive_demo();
void run_search_demo();
void run_sorts_demo();
void run_greedy_demo();
void run_dp_demo();

// heap.cpp icinde var (run_heap_demo'yu commentten cikarmak istersen lazim)
void run_heap_demo();

// maxsubseq demo fonksiyonu 
template <typename Func>
long long measure_us(Func f, const vector<int>& a, int& outResult, int repeat = 1) {
    using namespace std::chrono;

    long long best = LLONG_MAX;
    for (int r = 0; r < repeat; r++) {
        auto t1 = high_resolution_clock::now();
        outResult = f(a);
        auto t2 = high_resolution_clock::now();

        long long us = duration_cast<microseconds>(t2 - t1).count();
        if (us < best) best = us;
    }
    return best;
}

vector<int> read_csv_1col(const string& path) {
    ifstream fin(path);
    vector<int> a;
    if (!fin) return a;

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        size_t comma = line.find(',');
        if (comma != string::npos) line = line.substr(0, comma);

        while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\t'))
            line.pop_back();

        size_t start = 0;
        while (start < line.size() && (line[start] == ' ' || line[start] == '\t'))
            start++;
        line = line.substr(start);

        try {
            a.push_back(stoi(line));
        }
        catch (...) {
            continue;
        }
    }
    return a;
}

void generate_csv_1col(const string& path, int n, int minV = -100, int maxV = 100) {
    ofstream fout(path);
    mt19937 rng(42);
    uniform_int_distribution<int> dist(minV, maxV);

    for (int i = 0; i < n; i++) {
        fout << dist(rng) << "\n";
    }
}

void run_maxsubseq_demo() {
    ofstream fout("maxsubseq_results.txt");

    string path = "maxsubseq_input.csv";
    vector<int> a = read_csv_1col(path);

    if (a.empty()) {
        cout << "CSV yok/bos. maxsubseq_input.csv olusturuluyor...\n";
        fout << "CSV yok/bos. maxsubseq_input.csv olusturuluyor...\n";
        generate_csv_1col(path, 50000);
        a = read_csv_1col(path);
    }

    if (a.empty()) {
        cout << "CSV okunamadi. Program durduruldu.\n";
        fout << "CSV okunamadi. Program durduruldu.\n";
        return;
    }

    vector<int> Ns = { 200, 500, 1000, 2000, 5000, 10000 };
    if ((int)a.size() < 200) {
        Ns = { (int)a.size() };
    }

    cout << left << setw(8) << "n"
        << setw(12) << "Algoritma"
        << setw(10) << "Sonuc"
        << "Sure(us)\n";
    fout << left << setw(8) << "n"
        << setw(12) << "Algoritma"
        << setw(10) << "Sonuc"
        << "Sure(us)\n";

    cout << string(46, '-') << "\n";
    fout << string(46, '-') << "\n";

    for (int n : Ns) {
        if ((int)a.size() < n) break;

        vector<int> sub(a.begin(), a.begin() + n);
        int res = 0;

        if (n <= 500) {
            auto t3 = measure_us(maxSubseq_O3, sub, res, 1);
            cout << left << setw(8) << n << setw(12) << "O(n^3)" << setw(10) << res << t3 << "\n";
            fout << left << setw(8) << n << setw(12) << "O(n^3)" << setw(10) << res << t3 << "\n";
        }
        else {
            cout << left << setw(8) << n << setw(12) << "O(n^3)" << setw(10) << "-" << "-" << "\n";
            fout << left << setw(8) << n << setw(12) << "O(n^3)" << setw(10) << "-" << "-" << "\n";
        }

        if (n <= 10000) {
            auto t2 = measure_us(maxSubseq_O2, sub, res, 3);
            cout << left << setw(8) << n << setw(12) << "O(n^2)" << setw(10) << res << t2 << "\n";
            fout << left << setw(8) << n << setw(12) << "O(n^2)" << setw(10) << res << t2 << "\n";
        }
        else {
            cout << left << setw(8) << n << setw(12) << "O(n^2)" << setw(10) << "-" << "-" << "\n";
            fout << left << setw(8) << n << setw(12) << "O(n^2)" << setw(10) << "-" << "-" << "\n";
        }

        auto tlog = measure_us(maxSubseq_Ologn, sub, res, 10);
        cout << left << setw(8) << n << setw(12) << "O(nlogn)" << setw(10) << res << tlog << "\n";
        fout << left << setw(8) << n << setw(12) << "O(nlogn)" << setw(10) << res << tlog << "\n";

        auto tn = measure_us(maxSubseq_On, sub, res, 30);
        cout << left << setw(8) << n << setw(12) << "O(n)" << setw(10) << res << tn << "\n";
        fout << left << setw(8) << n << setw(12) << "O(n)" << setw(10) << res << tn << "\n";

        cout << string(46, '-') << "\n";
        fout << string(46, '-') << "\n";
    }
}

int main() {


    //run_maxsubseq_demo();     
     //run_recursive_demo();  
     //run_search_demo();
     //run_sorts_demo();
    //run_heap_demo();
    //run_greedy_demo();
    run_dp_demo();
    return 0;
}
