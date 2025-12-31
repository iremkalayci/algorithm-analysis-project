#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <random>
#include <climits>
#include <limits>

#include "heap.h"
#include "maxsubseq.h"
#include "ui.h"


using namespace std;

// Diger dosyalarda var
void run_recursive_demo();
void run_search_demo();
void run_sorts_demo();
void run_greedy_demo();
void run_dp_demo();
void run_heap_demo();

// ------------------------------------------------------------
// maxsubseq demo fonksiyonu icin sure olcumu
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

static vector<int> read_csv_1col(const string& path) {
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

static void generate_csv_1col(const string& path, int n, int minV = -100, int maxV = 100) {
    ofstream fout(path);
    mt19937 rng(42);
    uniform_int_distribution<int> dist(minV, maxV);

    for (int i = 0; i < n; i++) {
        fout << dist(rng) << "\n";
    }
}


// 1) Maximum Subsequence demo
void run_maxsubseq_demo() {
    ui::title("1) MAXIMUM SUBSEQUENCE PROBLEMI");

    ofstream fout("maxsubseq_results.txt");
    ui::DualOut out(&fout);

    string path = "maxsubseq_input.csv";
    vector<int> a = read_csv_1col(path);

    if (a.empty()) {
        out << "CSV yok/bos. maxsubseq_input.csv olusturuluyor...\n";
        generate_csv_1col(path, 50000);
        a = read_csv_1col(path);
    }

    if (a.empty()) {
        out << "CSV okunamadi. Program durduruldu.\n";
        return;
    }

    vector<int> Ns = { 200, 500, 1000, 2000, 5000, 10000 };
    if ((int)a.size() < 200) Ns = { (int)a.size() };

    
    out << left
        << setw(8) << "n"
        << setw(10) << "Sonuc"
        << setw(12) << "O(n^3)"
        << setw(12) << "O(n^2)"
        << setw(14) << "O(nlogn)"
        << setw(10) << "O(n)"
        << "\n";
    out << string(66, '-') << "\n";

    for (int n : Ns) {
        if ((int)a.size() < n) break;

        vector<int> sub(a.begin(), a.begin() + n);

        int res = 0;
        string t3 = "-", t2 = "-", tlog = "-", tn = "-";

        if (n <= 500) {
            long long us = measure_us(maxSubseq_O3, sub, res, 1);
            t3 = to_string(us);
        }

        if (n <= 10000) {
            long long us = measure_us(maxSubseq_O2, sub, res, 3);
            t2 = to_string(us);
        }

        long long uslog = measure_us(maxSubseq_Ologn, sub, res, 10);
        tlog = to_string(uslog);

        long long usn = measure_us(maxSubseq_On, sub, res, 30);
        tn = to_string(usn);

        out << left
            << setw(8) << n
            << setw(10) << res
            << setw(12) << t3
            << setw(12) << t2
            << setw(14) << tlog
            << setw(10) << tn
            << "\n";
    }
}

static void print_menu() {
  

    cout << "1) MAXIMUM SUBSEQUENCE PROBLEMI\n";
    cout << "2) REKURSIF ALGORITMALAR\n";
    cout << "3) ARAMA ALGORITMALARI\n";
    cout << "4) SIRALAMA ALGORITMALARI\n";
    cout << "5) HEAP YAPILARI\n";
    cout << "6) GREEDY ALGORITMALAR\n";
    cout << "7) DINAMIK PROGRAMLAMA\n";
    cout << "0) Exit\n\n";
    cout << "Secim: ";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        print_menu();

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nGecersiz giris.\n";
            ui::pause_enter();
            continue;
        }

       

        switch (choice) {
        case 1:
            run_maxsubseq_demo();
            ui::pause_enter();
            break;

        case 2:
            ui::title("2) REKURSIF ALGORITMALAR");
            run_recursive_demo();
            ui::pause_enter();
            break;

        case 3:
            ui::title("3) ARAMA ALGORITMALARI");
            run_search_demo();
            ui::pause_enter();
            break;

        case 4:
            ui::title("4) SIRALAMA ALGORITMALARI");
            run_sorts_demo();
            ui::pause_enter();
            break;

        case 5:
            ui::title("5) HEAP YAPILARI");
            run_heap_demo();
            ui::pause_enter();
            break;

        case 6:
            ui::title("6) GREEDY ALGORITMALAR");
            run_greedy_demo();
            ui::pause_enter();
            break;

        case 7:
            ui::title("7) DINAMIK PROGRAMLAMA");
            run_dp_demo();
            ui::pause_enter();
            break;

        case 0:
            ui::title("CIKIS");
            cout << "Cikis yapiliyor...\n";
            return 0;

        default:
            cout << "\nGecersiz secim.\n";
            ui::pause_enter();
            break;
        }
    }
}
