#include "greedy.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>

//Activity Scheduling
// 1) finish time'a gore sirala
// 2) ilk aktiviteyi al
// 3) s[i] >= f[prev] ise sec
std::vector<Activity> activityScheduling(std::vector<Activity> a) {
    std::sort(a.begin(), a.end(), [](const Activity& x, const Activity& y) {
        return x.f < y.f;
        });

    std::vector<Activity> chosen;
    if (a.empty()) return chosen;

    chosen.push_back(a[0]);
    int prev = 0;

    for (int i = 1; i < (int)a.size(); i++) {
        if (a[i].s >= a[prev].f) {
            chosen.push_back(a[i]);
            prev = i;
        }
    }
    return chosen;
}

//Job Sequencing with Deadlines

// 1) profit'a gore azalan sirala
// 2) her isi kendi deadlineina kadar en gec bos slota koy
JobScheduleResult jobSequencing(std::vector<Job> jobs) {
    std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.profit > b.profit;
        });

    int maxD = 0;
    for (auto& j : jobs) if (j.deadline > maxD) maxD = j.deadline;

    std::vector<int> slots(maxD + 1, -1); // 1..maxD kullanacagiz
    int total = 0;

    for (auto& job : jobs) {
        for (int t = job.deadline; t >= 1; t--) {
            if (slots[t] == -1) {
                slots[t] = job.id;
                total += job.profit;
                break;
            }
        }
    }

    JobScheduleResult res;
    res.totalProfit = total;
    res.slotToJobId = slots;
    return res;
}

//Huffman
struct HNode {
    char ch;
    int freq;
    HNode* left;
    HNode* right;

    HNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    HNode(HNode* l, HNode* r) : ch('\0'), freq(l->freq + r->freq), left(l), right(r) {}
};

struct CmpNode {
    bool operator()(const HNode* a, const HNode* b) const {
        return a->freq > b->freq; // min-heap
    }
};

static void buildCodes(HNode* root, const std::string& path,
    std::unordered_map<char, std::string>& code) {
    if (!root) return;

    // leaf
    if (!root->left && !root->right) {
        // tek karakterli metin durumunda bos kod olmasin diye 0 ver
        code[root->ch] = path.empty() ? "0" : path;
        return;
    }

    buildCodes(root->left, path + "0", code);
    buildCodes(root->right, path + "1", code);
}

static void freeTree(HNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

static HNode* buildHuffmanTree(const std::string& text) {
    std::unordered_map<char, int> freq;
    for (char c : text) freq[c]++;

    std::priority_queue<HNode*, std::vector<HNode*>, CmpNode> pq;

    // her sembol icin leaf node olustur, Q.insert
    for (auto& kv : freq) {
        pq.push(new HNode(kv.first, kv.second));
    }

    if (pq.empty()) return nullptr;

   
    // while Q has more than 1 element:
    //   x = extractMin
    //   y = extractMin
    //   z = new internal node, z.left=x, z.right=y
    //   z.freq = x.freq + y.freq
    //   Q.insert(z)
    while ((int)pq.size() > 1) {
        HNode* x = pq.top(); pq.pop();
        HNode* y = pq.top(); pq.pop();
        HNode* z = new HNode(x, y);
        pq.push(z);
    }

    return pq.top();
}

static std::string huff_encode(const std::string& text,
    const std::unordered_map<char, std::string>& code) {
    std::string bits;
    bits.reserve(text.size() * 2);
    for (char c : text) bits += code.at(c);
    return bits;
}

static std::string huff_decode(const std::string& bits, HNode* root) {
    if (!root) return "";

    // tek leaf varsa,bit sayisi kadar ayni harf
    if (!root->left && !root->right) {
        return std::string(bits.size(), root->ch);
    }

    std::string out;
    HNode* cur = root;

    for (char b : bits) {
        cur = (b == '0') ? cur->left : cur->right;
        if (!cur->left && !cur->right) {
            out.push_back(cur->ch);
            cur = root;
        }
    }
    return out;
}

HuffmanResult huffman_demo(const std::string& text) {
    HuffmanResult r;

    HNode* root = buildHuffmanTree(text);
    std::unordered_map<char, std::string> code;
    buildCodes(root, "", code);

    r.encodedBits = huff_encode(text, code);
    r.decodedText = huff_decode(r.encodedBits, root);

    freeTree(root);
    return r;
}


void run_greedy_demo() {
    using std::cout;


    // A) Aktivite Zamanlama
    {
        cout << "\n[A] Activity Scheduling\n";
        std::vector<Activity> a = {
            {1, 1, 4}, {2, 3, 5}, {3, 0, 6}, {4, 5, 7},
            {5, 3, 9}, {6, 5, 9}, {7, 6,10}, {8, 8,11},
            {9, 8,12}, {10,2,14}, {11,12,16}
        };

        auto chosen = activityScheduling(a);
        cout << "Secilen aktiviteler (id, s, f):\n";
        for (auto& x : chosen) {
            cout << "  (" << x.id << ", " << x.s << ", " << x.f << ")\n";
        }
    }

    // B) Is Zamanlama 
    {
        cout << "\n[B] Job Sequencing (deadline + profit)\n";
        std::vector<Job> jobs = {
            {1, 2, 100}, {2, 1, 19}, {3, 2, 27}, {4, 1, 25}, {5, 3, 15}
        };

        auto res = jobSequencing(jobs);
        cout << "Total profit: " << res.totalProfit << "\n";
        cout << "Slot -> jobId:\n";
        for (int t = 1; t < (int)res.slotToJobId.size(); t++) {
            cout << "  t=" << t << " : " << res.slotToJobId[t] << "\n";
        }
    }

    // C) Huffman encode decode
    {
        cout << "\n[C] Huffman (encode/decode)\n";
        std::string text = "huffman coding demo";
        auto r = huffman_demo(text);
        cout << "Text   : " << text << "\n";
        cout << "Encoded: " << r.encodedBits.substr(0, 80);
        if ((int)r.encodedBits.size() > 80) cout << "...";
        cout << "\n";
        cout << "Decoded: " << r.decodedText << "\n";
    }

    cout << "\ngreedy demo bitti.\n";
}
