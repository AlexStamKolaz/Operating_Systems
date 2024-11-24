#include <thread>
#include "boat_passenger.cpp"
#define PASS_NUM 10
using namespace std;

void initialize();
void join();
void working_pass();
void working_boat();
thread worker_pass(working_pass);
//thread worker_boat(working_boat);

int main(){
    initialize();
    join();
}



void initialize(){
    passenger* ps;
    boat* bt;
    for(int j=0; j<PASS_NUM; j++){
        ps = new passenger(j);
        passenger::pass_queue.push_back(*ps);
    }
    for(int j=0; j<BOATS_NUM; j++){
        bt = new boat(j);
        boat::boats.push_back(*bt);
    }
}

void join(){
    working_boat();
    worker_pass.join();
}


void working_pass(){
    while(!passenger::pass_queue.empty()){
        passenger ps1=passenger::pass_queue.front();
        passenger::pass_queue.pop_front();
        if(ps1.wants)
            ps1.join();
        else
            passenger::pass_queue.push_back(ps1);
    }
}

void working_boat(){
    for(auto& bt : boat::boats)
            bt.join();
}

