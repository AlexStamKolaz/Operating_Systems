#include "boat_passenger.cpp"
#include <mutex>
#define PASS_NUM 10
using namespace std;

void initialize();
void join();
void working_pass();
void working_boat();
mutex mtx;

int main(){
    initialize();
    join();
}



void initialize(){
    passenger* ps;
    boat* bt;
    for(int j=0; j<PASS_NUM; j++){
        passenger::pass_queue.emplace_back(j);
    }
    for(int j=0; j<BOATS_NUM; j++){
        boat::boats.emplace_back(j);
    }
}

void join(){
    working_boat();
    working_pass();
}


void working_pass(){
    for(auto& ps : passenger::pass_queue){
        ps.join();
    }
}

void working_boat(){
    for(auto& bt : boat::boats){
        bt.join();
    }
}

