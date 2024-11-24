#include <iostream>
#include <list>
#include <thread>
#include <semaphore>
#include <mutex>
#define MAX_CAP 4
#define BOATS_NUM 2
using namespace std;

int capacity;
counting_semaphore<10> sem_boat(BOATS_NUM), sem_pass(0);
mutex mtx1, mtx2;

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

    const bool operator < (const passenger& other) const{
        return (this->id<other.id);
    }

    void get_boat(){
        sem_boat.acquire();
        mtx1.lock();
        sem_pass.release();
        capacity--;
        mtx1.unlock();
        reach_coast();
    }

    void reach_coast(){
        cout<<"Passenger: "<<id<<" reached the coast\n";
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
        mtx2.lock();
        while(!passenger::pass_queue.empty()){
            capacity=MAX_CAP;
            while(capacity>0 && !passenger::pass_queue.empty()){
                sem_pass.acquire();
            }
            mtx2.unlock();
            reach_coast();
            sem_boat.release();
        }
    }

    void reach_coast(){
        cout<<"Boat: "<<id<<" reached coast\n";
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


