#include "heap.h"
#include <iostream>
#include <climits>

using namespace std;

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
        if (parent < 1) return;              // root'a geldik
        if (H[parent] < H[node]) return;     // parent zaten kucuk > min-heap ok
        int tmp = H[node];
        H[node] = H[parent];
        H[parent] = tmp;
        node = parent;                       // bir seviye yukari
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
    if (newKey > H[index]) return; // decrease olmasi lazim
    H[index] = newKey;
    heapifyUpMin(index);
}

void BinaryHeap::increaseKey(int index, int newKey) {
    if (index < 1 || index > N) return;
    if (newKey < H[index]) return; // increase olmasi lazim
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


static void printHeapArray(const BinaryHeap& h) {
    cout << "H[1..N]: ";
    for (int i = 1; i <= h.N; i++) cout << h.H[i] << " ";
    cout << "\n";
}

void run_heap_demo() {
    cout << "\n--- Heap Yapilari Demo (min-heap) ---\n";

    BinaryHeap h;
    h.insertKey(10);
    h.insertKey(4);
    h.insertKey(7);
    h.insertKey(1);
    h.insertKey(15);

    cout << "InsertKey sonrasi:\n";
    printHeapArray(h);

    cout << "findMin: " << h.findMin() << "\n";
    cout << "deleteMin: " << h.deleteMin() << "\n";
    cout << "deleteMin sonrasi:\n";
    printHeapArray(h);

    // decrease n increase
   
    if (h.size() >= 3) {
        cout << "decreaseKey(index=3, newKey=0)\n";
        h.decreaseKey(3, 0);
        printHeapArray(h);
    }

    if (h.size() >= 2) {
        cout << "increaseKey(index=2, newKey=99)\n";
        h.increaseKey(2, 99);
        printHeapArray(h);
    }

    if (h.size() >= 2) {
        cout << "deleteKey(index=2)\n";
        h.deleteKey(2);
        printHeapArray(h);
    }

    // buildheap min,max
    vector<int> arr = { 9, 3, 8, 2, 6, 5 };
    BinaryHeap hMin;
    hMin.buildMinHeap(arr);
    cout << "\nbuildMinHeap:\n";
    printHeapArray(hMin);

    BinaryHeap hMax;
    hMax.buildMaxHeap(arr);
    cout << "buildMaxHeap:\n";
    printHeapArray(hMax);

    // merge
    BinaryHeap a, b;
    a.insertKey(5); a.insertKey(12); a.insertKey(1);
    b.insertKey(7); b.insertKey(2);

    BinaryHeap m = BinaryHeap::mergeHeaps(a, b);
    cout << "\nMerge(H1,H2) sonucu (min-heap):\n";
    printHeapArray(m);

    cout << "Demo bitti.\n";
}
