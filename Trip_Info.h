//
// Created by haim6678 on 10/01/17.
//

#ifndef EX3_TM_TRIP_INFO_H
#define EX3_TM_TRIP_INFO_H


#include "Searchable.h"
/**
 * class that contain trip's time and route
 */
class Trip_Info {

private:
    unsigned int tripTime;
    pthread_t* pt;
    list<Searchable*>* routh;
public:
    unsigned int getTripTime() ;
    ~Trip_Info();
    int validate();
    list<Searchable *>* getRouth() ;
    Trip_Info(unsigned int time, pthread_t* pt);
    void setRoute(std::list<Searchable *> *route);
    pthread_t* getPthread();
    Point getStart();
};


#endif //EX3_TM_TRIP_INFO_H
