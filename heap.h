#pragma once
#include <vector>


struct BinaryHeap {
    std::vector<int> H; // H[0] kullanilmaz
    int N;              // eleman sayisi

    BinaryHeap();

    bool empty() const;
    int  size() const;

    // min heap islemleri
    int  findMin() const;
    void insertKey(int key);
    int  deleteMin();          // heapify down

    // buildheap
    void buildMinHeap(const std::vector<int>& arr);
    void buildMaxHeap(const std::vector<int>& arr); // sadece gosterim icin

    // key update + deleteKey min heap uzerinden
    void decreaseKey(int index, int newKey);
    void increaseKey(int index, int newKey);
    void deleteKey(int index);

    // merge: iki heap'i birlestir (arr birlestir + buildMinHeap)
    static BinaryHeap mergeHeaps(const BinaryHeap& h1, const BinaryHeap& h2);

private:
    void heapifyDownMin(int node);
    void heapifyUpMin(int node);

    void heapifyDownMax(int node);
    void heapifyUpMax(int node);
};


void run_heap_demo();
