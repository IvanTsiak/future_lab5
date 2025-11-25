#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <string>
#include <syncstream>

void process(const std::string& name, int duration_sec) {
    std::this_thread::sleep_for(std::chrono::seconds(duration_sec));
    std::osyncstream(std::cout) << name << " completed in " << duration_sec << " s" << std::endl;
}

void work() {
    auto start = std::chrono::steady_clock::now();
    
    auto futureB = std::async(std::launch::async, []() {
        process("B1", 7);
        process("B2", 1);
    });

    auto futureC = std::async(std::launch::async, []() {
        process("C", 7);
        process("F", 1);
    });

    process("A1", 1);
    process("A2", 1);

    futureB.get();

    process("D", 1);
    
    futureC.get();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::osyncstream(std::cout) << "Work is done! Total time: " << elapsed.count() << " seconds" << std::endl;
}

int main() {
    work();
    return 0;
}   