#include <iostream>
#include <random>
#include <mutex>
#include <thread>

std::mutex cout_m;

void some_cool_calculations(unsigned long long &number, std::mt19937 &rand, bool is_infinite) {
    std::uniform_int_distribution<> dist(1000000, 10000000);

    if (is_infinite) {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            std::string ans;

            std::lock_guard<std::mutex> cout_lock(cout_m);

            std::cout << "You really want to proceed calculation? y/N\n";
            std::cin >> ans;
            if (ans == "n" || ans == "N" || ans == "no") {
                break;
            }
        }
    } else {
        unsigned int iter = dist(rand);
        for (unsigned int i = 0; i < iter; i++) {
            number++;
        }

        std::lock_guard<std::mutex> cout_lock(cout_m);
        std::cout << "Number equals to: " << number << '\n';
    }
}

int main() {
    unsigned long long x = 0;
    unsigned long long y = 0;

    std::mt19937 rand { std::random_device{}() };
    std::uniform_int_distribution<> dist(1, 2);

    std::thread t1 (some_cool_calculations, std::ref(x), std::ref(rand), dist(rand) == 1);
    std::thread t2 (some_cool_calculations, std::ref(y), std::ref(rand), dist(rand) == 1);

    t1.join();
    t2.join();

    std::cout << "First number: " << x << "\nSecond number: " << y << "\n x * y = " << x * y << std::endl;
    return 0;
}
