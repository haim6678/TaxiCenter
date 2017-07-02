//
// Created by haim6678 on 11/01/17.
//

#ifndef EX3_TM_THREAD_MANAGE_H
#define EX3_TM_THREAD_MANAGE_H


#include <sys/types.h>
#include <map>
#include <queue>
#include "Searchable.h"
#include "Mutex_Locker.h"
#include "Driver.h"


using namespace std;
/**
 * a singelton that holds every info that is needed for dealing with the thread
 */
class Thread_Manage {

private:
    //
    bool inUse;
    static Thread_Manage* instance;
    static bool created;
    int numDrivers;
    queue<string>** threadMasseges;
    //map<pthread_t, Thread_Class*> threadInfo;
    map<int, int> threadDes;
    list<pthread_t*>* threadList;
    static Mutex_Locker* threadInfoLocker;
    static Mutex_Locker* instanceLocker;
    static Mutex_Locker* threadMessagesLocker;
    static Mutex_Locker* descriptorsMapLocker;
    static Mutex_Locker* threadListLocker;

public:
    void addDriverDescriptor(int id,int des);
    void setThreadList(list <pthread_t*> *threadList);
    int getNumDrivers() const;
    ~Thread_Manage();
    static Thread_Manage* getInstance();
    queue<string> **getThreadMasseges() ;
    list <pthread_t*> *getThreadList() ;
    void setInitialMessagesQueues(int numOfDrivers);
    queue<string>* getThreadsQueue(int t);
    void addThread(pthread_t* t);
    //void addDriver(Driver* d,int sockDes);
    void addDriverAndPthread(pthread_t t, Driver* d);
    void popMessage(int d);
    int getThreadsSocketDescriptor(int id);
    bool Occupy();
};


#endif //EX3_TM_THREAD_MANAGE_H