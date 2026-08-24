#include <iostream>
#include <thread>
#include <atomic>
int normal_counter = 0;

std::atomic<int> atomic_counter{0};

void workerTask() {
    for (int i = 0; i < 100000; i++) {
        normal_counter++;
        atomic_counter++; 
    }
}

int main() {
    std::thread worker1(workerTask);
    std::thread worker2(workerTask);

    worker1.join();
    worker2.join();

    std::cout << "--- Scheduler Stats ---\n";
    std::cout << "Expected Jobs Done: 200000\n";
    std::cout << "Normal Counter: " << normal_counter << " (FAILED! Data Lost)\n";
    std::cout << "Atomic Counter: " << atomic_counter << " (SUCCESS! Perfect Sync)\n";

    return 0;
}