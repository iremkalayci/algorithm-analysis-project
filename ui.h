#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

namespace ui {

    inline void clear_screen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    inline void pause_enter() {
        std::cout << "\nDevam etmek icin ENTER...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    inline void line(int w = 62, char ch = '-') {
        for (int i = 0; i < w; ++i) std::cout << ch;
        std::cout << "\n";
    }

    inline void title(const std::string& t) {
        clear_screen();
        std::cout << "==============================================================\n";
        std::cout << "  " << t << "\n";
        std::cout << "==============================================================\n\n";
    }

    // Konsol + dosyaya ayni anda yazan mini helper
    struct DualOut {
        std::ofstream* f;
        DualOut(std::ofstream* fp) : f(fp) {}

        template <typename T>
        DualOut& operator<<(const T& x) {
            std::cout << x;
            if (f && f->is_open()) (*f) << x;
            return *this;
        }

        // manipulators (endl, setw vs icin)
        DualOut& operator<<(std::ostream& (*manip)(std::ostream&)) {
            std::cout << manip;
            if (f && f->is_open()) (*f) << manip;
            return *this;
        }
    };

} // namespace ui
