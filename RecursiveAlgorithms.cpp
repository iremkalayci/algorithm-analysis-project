#include <iostream>
#include <vector>

using namespace std;

// Rekursif cagri sayaclari
long long cnt_sumN = 0;
long long cnt_arraySum = 0;
long long cnt_power = 0;
long long cnt_fib = 0;
long long cnt_hanoi = 0;
long long cnt_digitSum = 0;

/* 1) 1 + 2 + ... + N */
int sumN(int n) {
    cnt_sumN++;





















    if (n == 0)
        return 0;
    return n + sumN(n - 1);
}

/* 2) Dizi toplami */
int arraySum(const vector<int>& a, int n) {
    cnt_arraySum++;
    if (n == 0)
        return 0;
    return a[n - 1] + arraySum(a, n - 1);
}

/* 3) a^n */
long long power(int a, int n) {
    cnt_power++;
    if (n == 0)
        return 1;
    return a * power(a, n - 1);
}

/* 4) Fibonacci*/
long long fibonacci(int n) {
    cnt_fib++;
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/* 5) Tower of Hanoi */
void hanoi(int n, char from, char to, char aux) {
    cnt_hanoi++;
    if (n == 1) {
        return;
    }
    hanoi(n - 1, from, aux, to);
    hanoi(n - 1, aux, to, from);
}

/* 6) Recursive Digit Sum */
int digitSum(int n) {
    cnt_digitSum++;
    if (n < 10)
        return n;
    return (n % 10) + digitSum(n / 10);
}


void run_recursive_demo() {

    int N = 10;
    cnt_sumN = 0;
    cout << "Sum 1..N = " << sumN(N)
         << " | Recursive calls = " << cnt_sumN << endl;

    vector<int> arr = {1, 2, 3, 4, 5};
    cnt_arraySum = 0;
    cout << "Array sum = " << arraySum(arr, (int)arr.size())
         << " | Recursive calls = " << cnt_arraySum << endl;

    cnt_power = 0;
    cout << "2^5 = " << power(2, 5)
         << " | Recursive calls = " << cnt_power << endl;

    cnt_fib = 0;
    cout << "Fibonacci(6) = " << fibonacci(6)
         << " | Recursive calls = " << cnt_fib << endl;

    cnt_hanoi = 0;
    hanoi(3, 'A', 'C', 'B');
    cout << "Hanoi (n=3) recursive calls = " << cnt_hanoi << endl;

    cnt_digitSum = 0;
    cout << "Digit sum(12345) = " << digitSum(12345)
         << " | Recursive calls = " << cnt_digitSum << endl;
}

