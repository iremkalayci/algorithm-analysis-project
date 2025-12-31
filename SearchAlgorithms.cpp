#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// karsilastirma sayilari
long long cnt_linear_fwd = 0;
long long cnt_linear_bwd = 0;
long long cnt_binary = 0;

/* 1)ileri yonlu lineer arama */
int linearSearchForward(const vector<int>& a, int key) {
    cnt_linear_fwd = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        cnt_linear_fwd++;
        if (a[i] == key)
            return i;
    }
    return -1;
}

/* 2) geri yonlu lineer arama */
int linearSearchBackward(const vector<int>& a, int key) {
    cnt_linear_bwd = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        cnt_linear_bwd++;
        if (a[i] == key)
            return i;
    }
    return -1;
}

/* 3) ikili arama-dizi sirali olmali */
int binarySearchIter(const vector<int>& a, int key) {
    cnt_binary = 0;
    int l = 0, r = (int)a.size() - 1;

    while (l <= r) {
        cnt_binary++;
        int m = l + (r - l) / 2;
        if (a[m] == key)
            return m;
        else if (a[m] < key)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

void run_search_demo() {

    vector<int> data = { 3, 7, 12, 18, 25, 31, 42, 56, 63, 78 };
    int key = 42;

  
    cout << "Aranan deger: " << key << "\n\n";

    cout << left
        << setw(28) << "Algoritma"
        << setw(12) << "Index"
        << setw(16) << "Karsilastirma"
        << "\n";
    cout << string(56, '-') << "\n";

    int idx1 = linearSearchForward(data, key);
    cout << left
        << setw(28) << "Ileri Lineer Arama"
        << setw(12) << idx1
        << setw(16) << cnt_linear_fwd
        << "\n";

    int idx2 = linearSearchBackward(data, key);
    cout << left
        << setw(28) << "Geri Lineer Arama"
        << setw(12) << idx2
        << setw(16) << cnt_linear_bwd
        << "\n";

    vector<int> sorted = data;
    sort(sorted.begin(), sorted.end());

    int idx3 = binarySearchIter(sorted, key);
    cout << left
        << setw(28) << "Ikili Arama"
        << setw(12) << idx3
        << setw(16) << cnt_binary
        << "\n";

    cout << string(56, '-') << "\n";
}
