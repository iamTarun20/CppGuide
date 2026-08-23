#include<iostream>

class job {
public:
    job() {
        std::cout<<"JOB CREATION"<<std::endl;
    }
    ~job() {
        std::cout<<"JOB DESTRUCTOR"<<std::endl;
    }
    void dowork() {
        std::cout<<"Job is being proceed"<<std::endl;
    }
};
class jobguard {
private:
    job* realjob;

public:
    jobguard() {
        realjob = new job();
    }
    ~jobguard() {
        delete realjob;
    }
    job* getjob() {
        return realjob;
    }
};
void runschedular() {
    std::cout<<"<---------FUNCTION STARTED--------->"<<std::endl;
    jobguard guard;

    guard.getjob()->dowork();

    bool networkerror = true;
    if (networkerror) {
        std::cout<<"ERROR OCCURRED! EARLY EXIT"<<std::endl;
        return ;
    }
    std::cout<<"<---------FUNCTION COMPLETED--------->"<<std::endl;
}

int main() {
    runschedular();
    std::cout<<"BACK IN MAIN FUNCTION NO LEAKS"<<std::endl;
    return 0;
}
