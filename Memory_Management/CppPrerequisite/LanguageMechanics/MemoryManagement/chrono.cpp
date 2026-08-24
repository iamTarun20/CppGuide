#include <iostream>
#include <chrono>
#include <thread>

void executeJobWithTimeout() {
    std::cout << "--- Job Started ---\n";

    auto start_time = std::chrono::steady_clock::now();

    std::cout << "Worker is processing the job...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));

    auto end_time = std::chrono::steady_clock::now();

    auto time_taken = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

    int timeout_limit = 2;

    std::cout << "Time taken by Job: " << time_taken.count() << " seconds.\n";

    if (time_taken.count() > timeout_limit) {
        std::cout << "ERROR: Job TIMED OUT! It took too long.\n";
    } else {
        std::cout << "SUCCESS: Job finished on time.\n";
    }
}

int main() {
    executeJobWithTimeout();
    return 0;
}