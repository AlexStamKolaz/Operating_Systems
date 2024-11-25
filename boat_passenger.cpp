#include <iostream>
#include <list>
#include <thread>
#include <semaphore>
#include <mutex>
#include <sstream>
#define MAX_CAP 4
#define BOATS_NUM 2
#define PASS_NUM 10
using namespace std;

int psaved=0;
int capacity;
counting_semaphore<10> sem_boat(BOATS_NUM), sem_pass(0);
mutex mtx1, mtx2, mtx_print1, mtx_print2;

class passenger{
public:
    static list<passenger> pass_queue;
    int id;
    bool wants;
    thread* th;

    passenger(int id){
        this->id=id;
        wants=true;
        th=new thread(&passenger::get_boat, this);
    }



    void get_boat(){
        sem_boat.acquire();
        mtx1.lock();
        psaved++;
        sem_pass.release();
        mtx1.unlock();
        reach_coast();
    }

    void reach_coast(){
        ostringstream oss;
        oss<<"Passenger: "<<id<<" reached the coast\n";
        mtx_print2.lock();
        cout<<oss.str();
        mtx_print2.unlock();
    }

    void join() const{
        if(th->joinable())
            th->join();
    }

    ~passenger(){
        delete th;
    }

};

list<passenger> passenger::pass_queue;

class boat{
public:
    int id;
    thread* th;
    static list<boat> boats;

    boat(int id){
        this->id=id;
        th=new thread(&boat::get_passenger, this);
    }

    void get_passenger(){
        while(true){
            mtx2.lock();
            if(psaved>=PASS_NUM){
                mtx2.unlock();
                break;
            }
            else
                mtx2.unlock();
            sem_pass.acquire();
            reach_coast();
            sem_boat.release();
        }
    }

    void reach_coast(){
        ostringstream oss;
        oss<<"Boat: "<<id<<" reached coast\n";
        mtx_print1.lock();
        cout<<oss.str();
        mtx_print1.unlock();
    }

    void join() const{
        if(th->joinable())
            th->join();
    }

    ~boat(){
        delete th;
    }
};

list<boat> boat::boats;


