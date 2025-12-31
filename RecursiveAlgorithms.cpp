#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

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

static void line(int w = 74, char ch = '-') {
    for (int i = 0; i < w; i++) cout << ch;
    cout << "\n";
}

// 4 Sutunlu tablo cizgisi cizen yardimci fonksiyon
void drawRecLine(int w1, int w2, int w3, int w4) {
    // +----------------+------------+----------+----------+ seklinde cizer
    cout << "+" << string(w1, '-') << "+" << string(w2, '-')
        << "+" << string(w3, '-') << "+" << string(w4, '-') << "+\n";
}

void run_recursive_demo() {
    // Sutun Genislikleri
    const int c1 = 26; // Problem
    const int c2 = 18; // Girdi
    const int c3 = 14; // Sonuc
    const int c4 = 14; // Cagri

    cout << "\n   RECURSIVE ALGORITMALAR\n";

    
    drawRecLine(c1, c2, c3, c4);

   
    cout << "| " << left << setw(c1 - 2) << "Problem"
        << " | " << left << setw(c2 - 2) << "Girdi"
        << " | " << left << setw(c3 - 2) << "Sonuc"
        << " | " << left << setw(c4 - 2) << "Cagri"
        << " |\n";

    
    drawRecLine(c1, c2, c3, c4);

    //Sum 1..N
    int N = 10;
    cnt_sumN = 0;
    int s1 = sumN(N);

    cout << "| " << left << setw(c1 - 2) << "Sum 1..N"
        << " | " << left << setw(c2 - 2) << ("N=" + to_string(N))
        << " | " << left << setw(c3 - 2) << s1
        << " | " << left << setw(c4 - 2) << cnt_sumN
        << " |\n";
    drawRecLine(c1, c2, c3, c4);

    //array sum
    vector<int> arr = { 1, 2, 3, 4, 5 };
    cnt_arraySum = 0;
    int s2 = arraySum(arr, (int)arr.size());

    cout << "| " << left << setw(c1 - 2) << "Array sum"
        << " | " << left << setw(c2 - 2) << ("n=" + to_string((int)arr.size()))
        << " | " << left << setw(c3 - 2) << s2
        << " | " << left << setw(c4 - 2) << cnt_arraySum
        << " |\n";
    drawRecLine(c1, c2, c3, c4);

    //a^n
    cnt_power = 0;
    long long s3 = power(2, 5);

    cout << "| " << left << setw(c1 - 2) << "Power a^n"
        << " | " << left << setw(c2 - 2) << "a=2, n=5"
        << " | " << left << setw(c3 - 2) << s3
        << " | " << left << setw(c4 - 2) << cnt_power
        << " |\n";
    drawRecLine(c1, c2, c3, c4);

   
    cnt_fib = 0;
    long long s4 = fibonacci(6);

    cout << "| " << left << setw(c1 - 2) << "Fibonacci"
        << " | " << left << setw(c2 - 2) << "n=6"
        << " | " << left << setw(c3 - 2) << s4
        << " | " << left << setw(c4 - 2) << cnt_fib
        << " |\n";
    drawRecLine(c1, c2, c3, c4);

    //Hanoi
   
    cnt_hanoi = 0;
   
    hanoi(3, 'A', 'C', 'B');

    cout << "| " << left << setw(c1 - 2) << "Tower of Hanoi"
        << " | " << left << setw(c2 - 2) << "n=3"
        << " | " << left << setw(c3 - 2) << "-"
        << " | " << left << setw(c4 - 2) << cnt_hanoi
        << " |\n";
    drawRecLine(c1, c2, c3, c4);

    
    cnt_digitSum = 0;
    int s6 = digitSum(12345);

    cout << "| " << left << setw(c1 - 2) << "Recursive Digit Sum"
        << " | " << left << setw(c2 - 2) << "n=12345"
        << " | " << left << setw(c3 - 2) << s6
        << " | " << left << setw(c4 - 2) << cnt_digitSum
        << " |\n";

    
    drawRecLine(c1, c2, c3, c4);
    cout << "\n";
}