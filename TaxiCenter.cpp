#include "TaxiCenter.h"
#include "Socket.h"
#include <boost/foreach.hpp>
#include <iostream>
#include "Driver.h"
#include "Udp.h"
#include "Thread_Manage.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/list.hpp>


/**
 * the empty constructor
 */
TaxiCenter::TaxiCenter() {

}

/**
 * the constructor
 */
TaxiCenter::TaxiCenter(Map *mp) {
    this->map = mp;
    this->time = 0;
}


/**
 * getting a vheicle id attaching to driver in our list a taxi
 * and return a taxi for the client driver
 */
Taxi *TaxiCenter::attachTaxiToDriver(int vhecleId) {
    Taxi *t = NULL;
    for (int i = 0; i < this->notActiveTaxis.size(); i++) {
        t = this->notActiveTaxis.back();
        if (t->getCarId() == vhecleId) {
            this->notActiveTaxis.pop_back();
            return t;
        }
        this->notActiveTaxis.pop_back();
        this->notActiveTaxis.push_front(t);
    }
    return NULL;
}

/**
 * @return - the list of taxi's not attached yet to a driver
 */
list<Taxi *> &TaxiCenter::getNotActiveTaxis() {
    return this->notActiveTaxis;
}

/**
 * @param t - adding a taxi to the center
 */
void TaxiCenter::addTaxi(Taxi *t) {
    this->notActiveTaxis.push_back(t);
}

/**
 * moving all the taxis one step
 */
void TaxiCenter::moveAll() {
    //this->time += 1;
    Thread_Manage *thraed_mannage = Thread_Manage::getInstance();
    std::queue<string> **mymap = thraed_mannage->getThreadMasseges();
    //iterate over the driver*
    for (int i = 0; i < thraed_mannage->getNumDrivers(); i++) {
        //LINFO << " numDrivers: " << thraed_mannage->getNumDrivers();
        //LINFO << " sending driver no:    " << i << " go";
        mymap[i]->push("Go");
    }
}


/**
 * the deconstructor
 */
TaxiCenter::~TaxiCenter() {
    long size = this->notActiveTaxis.size();
    for (int i = 0; i < size; i++) {
        Taxi *t = notActiveTaxis.front();
        notActiveTaxis.pop_front();
        delete t;
    }
    delete this->map;
}

unsigned int TaxiCenter::getTime() const {
    return time;
}

Map *TaxiCenter::getMap() const {
    return map;
}