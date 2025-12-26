#include <iostream>
#include <vector>
#include <algorithm>

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

    cout << "\n--- Arama Algoritmalari ---\n";
    cout << "Aranan deger: " << key << "\n\n";

    int idx1 = linearSearchForward(data, key);
    cout << "Ileri Lineer Arama -> index: " << idx1
        << " | karsilastirma: " << cnt_linear_fwd << endl;

    int idx2 = linearSearchBackward(data, key);
    cout << "Geri Lineer Arama  -> index: " << idx2
        << " | karsilastirma: " << cnt_linear_bwd << endl;

    
    //sirali olmaasini garantiledim.
    vector<int> sorted = data;
    sort(sorted.begin(), sorted.end());

    int idx3 = binarySearchIter(sorted, key);
    cout << "Ikili Arama        -> index: " << idx3
        << " | karsilastirma: " << cnt_binary << endl;
}
