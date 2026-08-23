#include<iostream>
#include<memory>

class job {
private:
    int id;
public:
    job(int i) {
        id  = i;
        std::cout<<"job id "<<id<<" is being created"<<std::endl;
    }
    ~job() {
        std::cout<<"job id "<<id<<" is destroyed"<<std::endl;
    }
    void execute() {
        std::cout<<"job id "<<id<<" is executed"<<std::endl;
    }
};
void workerThread(std:: unique_ptr<job> workerjob) {
    std::cout<<"Worker Thread received the job"<<std::endl;
    workerjob->execute();
    std::cout<<"Worker Thread completed successfully"<<std::endl;
}

int main() {
    std::cout<<"Main Thread received the job"<<std::endl;
    std::unique_ptr<job>dispatcherjob = std::make_unique<job>(1);

    std::cout<<"Transferring ownership to worker"<<std::endl;
    workerThread(std::move(dispatcherjob));


    if (dispatcherjob == nullptr) {
        std::cout<<"Dispatcher empty , worker stole it"<<std::endl;
    }

    std::cout<<"Schedular is emptied"<<std::endl;
}