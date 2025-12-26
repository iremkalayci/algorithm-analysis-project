#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>
#include <climits>
#include <fstream>
#include <queue>
#include <string>
#include <algorithm>


using namespace std;

template <typename Func>
long long measure_us(Func f, int repeat = 1) {
    using namespace std::chrono;
    long long best = LLONG_MAX;
    for (int r = 0; r < repeat; r++) {
        auto t1 = high_resolution_clock::now();
        f();
        auto t2 = high_resolution_clock::now();
        long long us = duration_cast<microseconds>(t2 - t1).count();
        if (us < best) best = us;
    }
    return best;
}


vector<int> make_random_ints(int n, int minV = -100000, int maxV = 100000) {
    mt19937 rng(42);
    uniform_int_distribution<int> dist(minV, maxV);
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = dist(rng);
    return a;
}


// 1) Selection Sort
void selectionSort(vector<int>& A) {
    int N = (int)A.size();
    for (int i = 0; i < N - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < N; j++) {
            if (A[j] < A[minIndex]) minIndex = j;
        }
        if (i != minIndex) swap(A[i], A[minIndex]);
    }
}

// 2) Bubble Sort
void bubbleSort(vector<int>& A) {
    int N = (int)A.size();
    for (int i = 0; i < N; i++) {
        for (int j = 1; j < (N - i); j++) {
            if (A[j - 1] > A[j]) swap(A[j - 1], A[j]);
        }
    }
}

// 3) Insertion Sort
void insertionSort(vector<int>& A) {
    int N = (int)A.size();
    int j, P, Tmp;
    for (P = 1; P < N; P++) {
        Tmp = A[P];
        for (j = P; j > 0 && A[j - 1] > Tmp; j--) {
            A[j] = A[j - 1];
        }
        A[j] = Tmp;
    }
}


// 4) Merge Sort Divide Conquer
static void mergeParts(vector<int>& A, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = A[left + i];
    for (int i = 0; i < n2; i++) R[i] = A[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) A[k++] = L[i++];
        else A[k++] = R[j++];
    }
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];
}

static void mergeSortRec(vector<int>& A, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSortRec(A, left, mid);
    mergeSortRec(A, mid + 1, right);
    mergeParts(A, left, mid, right);
}

void mergeSort(vector<int>& A) {
    if (!A.empty()) mergeSortRec(A, 0, (int)A.size() - 1);
}


// 5) Quick Sort 
// QS(int A[], int N):
//   index = Partition(A,N)
//   QS(A, index-1)
//   QS(&A[index+1], N-index-1)

static int PartitionFirstPivot(int A[], int N) {
    if (N <= 1) return 0;

    int pivot = A[0];        // pivot is the first element
    int i = 1, j = N - 1;

    while (1) {
        while (A[j] > pivot) j--;
        while (A[i] < pivot && i < j) i++;
        if (i >= j) break;
        swap(A[i], A[j]);
        i++; j--;
    }
    swap(A[j], A[0]);        // estore the pivot
    return j;                // return pivot index
}

static void QS_firstPivot(int A[], int N) {
    if (N <= 1) return;
    int index = PartitionFirstPivot(A, N);
    QS_firstPivot(A, index);
    QS_firstPivot(&A[index + 1], N - index - 1);
}

void quickSort_firstPivot(vector<int>& A) {
    if (!A.empty()) QS_firstPivot(A.data(), (int)A.size());
}

//medianOf3
static int MedianOf3(int A[], int N) {
    int left = 0;
    int right = N - 1;
    int center = (left + right) / 2;

    if (A[left] > A[center]) swap(A[left], A[center]);
    if (A[left] > A[right])  swap(A[left], A[right]);
    if (A[center] > A[right]) swap(A[center], A[right]);

    swap(A[center], A[right - 1]); // hide the pivot
    return A[right - 1];           // return pivot value
}

static int PartitionMedianOf3(int A[], int N) {
    // assumes N >= 3
    int pivot = MedianOf3(A, N);

    int i = 0;
    int j = N - 2; // pivot at N-2

    while (1) {
        while (A[++i] < pivot) {}
        while (A[--j] > pivot) {}
        if (i < j) swap(A[i], A[j]);
        else break;
    }
    swap(A[i], A[N - 2]); // restore the pivot
    return i;
}

static void QS_medianOf3(int A[], int N) {
    if (N <= 1) return;
    if (N == 2) { if (A[0] > A[1]) swap(A[0], A[1]); return; }

    int index = PartitionMedianOf3(A, N);
    QS_medianOf3(A, index);
    QS_medianOf3(&A[index + 1], N - index - 1);
}

void quickSort_medianOf3(vector<int>& A) {
    if (!A.empty()) QS_medianOf3(A.data(), (int)A.size());
}


// 6) Heap Sort
static void heapify(vector<int>& A, int N, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < N && A[l] > A[largest]) largest = l;
    if (r < N && A[r] > A[largest]) largest = r;

    if (largest != i) {
        swap(A[i], A[largest]);
        heapify(A, N, largest);
    }
}

void heapSort(vector<int>& A) {
    int N = (int)A.size();
    for (int i = N / 2 - 1; i >= 0; i--) heapify(A, N, i);
    for (int i = N - 1; i > 0; i--) {
        swap(A[0], A[i]);
        heapify(A, i, 0);
    }
}

struct SatRec {
    int key;
    int sat;
};

void countingSortSatellite(vector<SatRec>& A, int maxKey) {
  
    vector<int> C(maxKey + 1, 0);

    for (auto& x : A) C[x.key]++;

    // prefx sum - stable icin pozisyon
    for (int i = 1; i <= maxKey; i++) C[i] += C[i - 1];

    vector<SatRec> B(A.size());

    // stable-sondan basa
    for (int i = (int)A.size() - 1; i >= 0; i--) {
        int k = A[i].key;
        B[--C[k]] = A[i];
    }
    A.swap(B);
}


// radix Sort - int icin (negatif destekli)
// negatifleri ve pozitifleri ayir, abs ile radix, sonra birlestir.
static void countingPassBase10(vector<int>& A, int exp) {
    int N = (int)A.size();
    vector<int> out(N);
    int count[10] = { 0 };

    for (int i = 0; i < N; i++) {
        int digit = (A[i] / exp) % 10;
        count[digit]++;
    }
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = N - 1; i >= 0; i--) {
        int digit = (A[i] / exp) % 10;
        out[--count[digit]] = A[i];
    }
    A.swap(out);
}

static void radixSortNonNegative(vector<int>& A) {
    if (A.empty()) return;
    int mx = A[0];
    for (int x : A) if (x > mx) mx = x;

    for (int exp = 1; mx / exp > 0; exp *= 10) {
        countingPassBase10(A, exp);
    }
}

void radixSortInt(vector<int>& A) {
    vector<int> neg, pos;
    neg.reserve(A.size());
    pos.reserve(A.size());

    for (int x : A) {
        if (x < 0) neg.push_back(-x); // abs
        else pos.push_back(x);
    }

    radixSortNonNegative(pos);
    radixSortNonNegative(neg);

    // negatifler;abs siralandiktan sonra ters cevirip tekrar - yap
    A.clear();
    for (int i = (int)neg.size() - 1; i >= 0; i--) A.push_back(-neg[i]);
    for (int x : pos) A.push_back(x);
}

// ------------------------------------------------------------
// External Sorting
// 1) input dosyasini chunk'lara bol
// 2) her chunk'i memory icinde sirala, run dosyasina yaz
// 3) run'lari k-way merge ile output'a yaz
//


static void write_run_file(const string& path, const vector<int>& chunk) {
    ofstream fout(path);
    for (int x : chunk) fout << x << "\n";
}

static bool read_int(ifstream& fin, int& out) {
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        try { out = stoi(line); return true; }
        catch (...) { continue; }
    }
    return false;
}

void externalSortFile(const string& inputPath, const string& outputPath, int chunkSize) {
    ifstream fin(inputPath);
    if (!fin) {
        cout << "externalSort: input acilamadi: " << inputPath << "\n";
        return;
    }

    vector<string> runs;
    vector<int> chunk;
    chunk.reserve(chunkSize);

    int x;
    while (read_int(fin, x)) {
        chunk.push_back(x);
        if ((int)chunk.size() == chunkSize) {
            sort(chunk.begin(), chunk.end());
            string runName = "run_" + to_string((int)runs.size()) + ".txt";
            write_run_file(runName, chunk);
            runs.push_back(runName);
            chunk.clear();
        }
    }
    if (!chunk.empty()) {
        sort(chunk.begin(), chunk.end());
        string runName = "run_" + to_string((int)runs.size()) + ".txt";
        write_run_file(runName, chunk);
        runs.push_back(runName);
        chunk.clear();
    }

    // k way merge
    struct Node { int val; int runId; };
    struct Cmp { bool operator()(const Node& a, const Node& b) const { return a.val > b.val; } };

    vector<ifstream> fins(runs.size());
    for (int i = 0; i < (int)runs.size(); i++) fins[i].open(runs[i]);

    priority_queue<Node, vector<Node>, Cmp> pq;
    for (int i = 0; i < (int)runs.size(); i++) {
        int v;
        if (read_int(fins[i], v)) pq.push({ v, i });
    }

    ofstream fout(outputPath);
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        fout << cur.val << "\n";

        int v;
        if (read_int(fins[cur.runId], v)) pq.push({ v, cur.runId });
    }


}

void run_sorts_demo() {
    int n = 5000; 
    vector<int> base = make_random_ints(n);

    cout << "\n--- Siralama Algoritmalari (chrono, us) n=" << n << " ---\n";
    cout << left << setw(22) << "Algoritma" << "Sure(us)\n";
    cout << string(34, '-') << "\n";

    
    cout << left << setw(22) << "Selection" << measure_us([&] {
        auto a = base; selectionSort(a);
        }, 1) << "\n";

    cout << left << setw(22) << "Bubble" << measure_us([&] {
        auto a = base; bubbleSort(a);
        }, 1) << "\n";

    cout << left << setw(22) << "Insertion" << measure_us([&] {
        auto a = base; insertionSort(a);
        }, 1) << "\n";

    // nlogn olanlar 3 tekrar min al
    cout << left << setw(22) << "Merge" << measure_us([&] {
        auto a = base; mergeSort(a);
        }, 3) << "\n";

    cout << left << setw(22) << "Quick (first pivot)" << measure_us([&] {
        auto a = base; quickSort_firstPivot(a);
        }, 3) << "\n";

    cout << left << setw(22) << "Quick (medianOf3)" << measure_us([&] {
        auto a = base; quickSort_medianOf3(a);
        }, 3) << "\n";

    cout << left << setw(22) << "Heap" << measure_us([&] {
        auto a = base; heapSort(a);
        }, 3) << "\n";

    // counting sort satellite demo (key 0..999)
    vector<SatRec> sat(20000);
    {
        mt19937 rng(42);
        uniform_int_distribution<int> keyDist(0, 999);
        uniform_int_distribution<int> satDist(100000, 999999);
        for (auto& r : sat) { r.key = keyDist(rng); r.sat = satDist(rng); }
    }
    cout << left << setw(22) << "Counting (satellite)" << measure_us([&] {
        auto a = sat; countingSortSatellite(a, 999);
        }, 3) << "\n";

    // radix demo
    cout << left << setw(22) << "Radix (int)" << measure_us([&] {
        auto a = base; radixSortInt(a);
        }, 3) << "\n";

    // External sort demo: input ve output dosya olusturur,
    // bu dosyalar proje klasorune geliyor.
    {
        string inF = "external_input.txt";
        string outF = "external_output.txt";
        ofstream fout(inF);
        for (int i = 0; i < 50000; i++) fout << base[i % (int)base.size()] << "\n";
        fout.close();

        cout << left << setw(22) << "External sort (file)" << measure_us([&] {
            externalSortFile(inF, outF, 5000);
            }, 1) << "\n";
    }

    cout << string(34, '-') << "\n";
   
}
