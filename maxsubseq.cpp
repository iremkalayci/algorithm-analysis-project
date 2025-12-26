#include "maxsubseq.h"
#include <limits>
#include <algorithm>


int maxSubseq_O3(const std::vector<int>& a) {
    int n = a.size();
    int best = std::numeric_limits<int>::min();

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += a[k];
            }
            if (sum > best)
                best = sum;
        }
    }
    return best;
}
int maxSubseq_O2(const std::vector<int>& a) {
    int n = a.size();
    int best = std::numeric_limits<int>::min();

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += a[j];
            if (sum > best)
                best = sum;
        }
    }
    return best;
}
static int maxCrossingSum(const std::vector<int>& a, int left, int mid, int right) {
    int sum = 0;
    int leftMax = std::numeric_limits<int>::min();

    for (int i = mid; i >= left; i--) {
        sum += a[i];
        if (sum > leftMax) leftMax = sum;
    }

    sum = 0;
    int rightMax = std::numeric_limits<int>::min();

    for (int i = mid + 1; i <= right; i++) {
        sum += a[i];
        if (sum > rightMax) rightMax = sum;
    }

    return leftMax + rightMax;
}

static int maxSubseq_DC(const std::vector<int>& a, int left, int right) {
    if (left == right) return a[left];

    int mid = (left + right) / 2;

    int leftSum = maxSubseq_DC(a, left, mid);
    int rightSum = maxSubseq_DC(a, mid + 1, right);
    int crossSum = maxCrossingSum(a, left, mid, right);

    return std::max({ leftSum, rightSum, crossSum });
}

int maxSubseq_Ologn(const std::vector<int>& a) {
    if (a.empty()) return 0; 
    return maxSubseq_DC(a, 0, (int)a.size() - 1);
}
int maxSubseq_On(const std::vector<int>& a) {
    if (a.empty()) return 0;

    int best = a[0];
    int current = a[0];

    for (size_t i = 1; i < a.size(); i++) {
        current = std::max(a[i], current + a[i]);
        best = std::max(best, current);
    }
    return best;
}


