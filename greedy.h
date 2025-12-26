#pragma once
#include <string>
#include <vector>


void run_greedy_demo();

// Aktivite zamanlama
struct Activity {
    int id;
    int s; // start
    int f; // finish
};
std::vector<Activity> activityScheduling(std::vector<Activity> a);

// Is zamanlama
struct Job {
    int id;
    int deadline;
    int profit;
};
struct JobScheduleResult {
    int totalProfit;
    std::vector<int> slotToJobId; // slot job id (-1 bos)
};
JobScheduleResult jobSequencing(std::vector<Job> jobs);

// Huffman encode,decode
struct HuffmanResult {
    std::string encodedBits;
    std::string decodedText;
};
HuffmanResult huffman_demo(const std::string& text);
