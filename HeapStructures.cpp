#include "heap.h"
#include <iostream>
#include <climits>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;


// basliklar icin
static void print_line(char ch, int w) {
    cout << string(w, ch) << "\n";
}

static void print_header(const string& title) {
    cout << "\n";
    print_line('=', 60);
    cout << " " << title << "\n";
    print_line('=', 60);
}

// heapi kutulu serit halinde yazdirma
// ustte indeksler, altta degerler
static void print_heap_box(const BinaryHeap& h, const string& label) {
    int n = h.size();
    cout << "\n-> " << label << " (Boyut: " << n << ")\n";

    if (n == 0) {
        cout << "[BOS HEAP]\n";
        return;
    }

    const int cellW = 6;

    cout << "  +";
    for (int i = 0; i < n; i++) cout << string(cellW, '-') << "+";
    cout << "\n";

    cout << "  |";
    for (int i = 1; i <= n; i++) {
        cout << right << setw(cellW) << i << "|";
    }
    cout << "\n";

    cout << "  +";
    for (int i = 0; i < n; i++) cout << string(cellW, '-') << "+";
    cout << "\n";

    cout << "  |";
    for (int i = 1; i <= n; i++) {
        cout << right << setw(cellW) << h.H[i] << "|";
    }
    cout << "\n";

    cout << "  +";
    for (int i = 0; i < n; i++) cout << string(cellW, '-') << "+";
    cout << "\n";
}

// tekil islem sonucu yazdirma
static void print_action_result(const string& action, int result) {
    cout << "\n   [ISLEM] " << left << setw(20) << action << " : " << result << "\n" << right;
}




BinaryHeap::BinaryHeap() : H(1, 0), N(0) {
    // H[0] bos kalsin 1-indexed heap
}

bool BinaryHeap::empty() const { return N == 0; }
int  BinaryHeap::size()  const { return N; }

int BinaryHeap::findMin() const {
    if (N <= 0) return INT_MAX;
    return H[1];
}

// MIN HEAP: insert / deleteMin
// InsertKey(H,key,N) mantigi:
// N = N+1; H[N]=key; node=N; while(...) parent=node/2; swap...
void BinaryHeap::insertKey(int key) {
    N = N + 1;
    if ((int)H.size() <= N) H.push_back(0);
    H[N] = key;

    int node = N;
    while (1) {
        int parent = node / 2;
        if (parent < 1) return;
        if (H[parent] < H[node]) return;
        int tmp = H[node];
        H[node] = H[parent];
        H[parent] = tmp;
        node = parent;
    }
}

// DeleteMin(H,N) mantigi:
// minKey=H[1]; H[1]=H[N]; N--; node=1; heapify-down...
int BinaryHeap::deleteMin() {
    if (N <= 0) return INT_MAX;

    int minKey = H[1];
    H[1] = H[N];
    N = N - 1;
    if (N <= 0) return minKey;

    heapifyDownMin(1);
    return minKey;
}

void BinaryHeap::heapifyDownMin(int node) {
    while (1) {
        int left = 2 * node;
        int right = 2 * node + 1;

        int smallest = node;
        if (left <= N && H[left] < H[smallest]) smallest = left;
        if (right <= N && H[right] < H[smallest]) smallest = right;

        if (smallest == node) return;

        int tmp = H[node];
        H[node] = H[smallest];
        H[smallest] = tmp;

        node = smallest;
    }
}

void BinaryHeap::heapifyUpMin(int node) {
    while (node > 1) {
        int parent = node / 2;
        if (H[parent] <= H[node]) break;
        swap(H[parent], H[node]);
        node = parent;
    }
}


// Bottomup build,  N/2 den 1'e heapifyDown
void BinaryHeap::buildMinHeap(const vector<int>& arr) {
    N = (int)arr.size();
    H.assign(N + 1, 0);
    for (int i = 0; i < N; i++) H[i + 1] = arr[i];

    for (int i = N / 2; i >= 1; i--) {
        heapifyDownMin(i);
    }
}


void BinaryHeap::buildMaxHeap(const vector<int>& arr) {
    N = (int)arr.size();
    H.assign(N + 1, 0);
    for (int i = 0; i < N; i++) H[i + 1] = arr[i];

    for (int i = N / 2; i >= 1; i--) {
        heapifyDownMax(i);
    }
}

void BinaryHeap::heapifyDownMax(int node) {
    while (1) {
        int left = 2 * node;
        int right = 2 * node + 1;

        int largest = node;
        if (left <= N && H[left] > H[largest]) largest = left;
        if (right <= N && H[right] > H[largest]) largest = right;

        if (largest == node) return;

        swap(H[node], H[largest]);
        node = largest;
    }
}

void BinaryHeap::heapifyUpMax(int node) {
    while (node > 1) {
        int parent = node / 2;
        if (H[parent] >= H[node]) break;
        swap(H[parent], H[node]);
        node = parent;
    }
}


void BinaryHeap::decreaseKey(int index, int newKey) {
    if (index < 1 || index > N) return;
    if (newKey > H[index]) return;
    H[index] = newKey;
    heapifyUpMin(index);
}

void BinaryHeap::increaseKey(int index, int newKey) {
    if (index < 1 || index > N) return;
    if (newKey < H[index]) return;
    H[index] = newKey;
    heapifyDownMin(index);
}

void BinaryHeap::deleteKey(int index) {
    if (index < 1 || index > N) return;

    decreaseKey(index, INT_MIN);
    deleteMin();
}

//MERGE(H1,H2)
BinaryHeap BinaryHeap::mergeHeaps(const BinaryHeap& h1, const BinaryHeap& h2) {
    vector<int> all;
    all.reserve(h1.N + h2.N);

    for (int i = 1; i <= h1.N; i++) all.push_back(h1.H[i]);
    for (int i = 1; i <= h2.N; i++) all.push_back(h2.H[i]);

    BinaryHeap out;
    out.buildMinHeap(all);
    return out;
}




void run_heap_demo() {
    print_header("HEAP YAPILARI");

    BinaryHeap h;
    h.insertKey(10);
    h.insertKey(4);
    h.insertKey(7);
    h.insertKey(1);
    h.insertKey(15);

    print_heap_box(h, "Insert Islemleri Sonrasi");

    print_action_result("findMin()", h.findMin());
    print_action_result("deleteMin()", h.deleteMin());

    print_heap_box(h, "DeleteMin Sonrasi");

    if (h.size() >= 3) {
        h.decreaseKey(3, 0);
        print_heap_box(h, "decreaseKey(idx=3, val=0)");
    }

    if (h.size() >= 2) {
        h.increaseKey(2, 99);
        print_heap_box(h, "increaseKey(idx=2, val=99)");
    }

    if (h.size() >= 2) {
        h.deleteKey(2);
        print_heap_box(h, "deleteKey(idx=2)");
    }

    print_header("Build Heap & Merge Demo");

    vector<int> arr = { 9, 3, 8, 2, 6, 5 };

    cout << "\n   Girdi Dizisi: { ";
    for (int x : arr) cout << x << " ";
    cout << "}\n";

    BinaryHeap hMin;
    hMin.buildMinHeap(arr);
    print_heap_box(hMin, "buildMinHeap Sonucu");

    BinaryHeap hMax;
    hMax.buildMaxHeap(arr);
    print_heap_box(hMax, "buildMaxHeap Sonucu");

    BinaryHeap a, b;
    a.insertKey(5); a.insertKey(12); a.insertKey(1);
    b.insertKey(7); b.insertKey(2);

    print_heap_box(a, "Heap A");
    print_heap_box(b, "Heap B");

    BinaryHeap m = BinaryHeap::mergeHeaps(a, b);
    print_heap_box(m, "Merge(A, B) Sonucu (Min-Heap)");
}
