//
// Created by haim on 11/27/16.
//
#define BUUFER_SIZE 4096

#include <iostream>
#include "Driver.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include "LuxuryTaxi.h"
#include "StandardTaxi.h"
#include <boost/archive/binary_oarchive.hpp>

//
/**
 * the destructor
 */
Driver::~Driver() {
    if (this->taxi != NULL) {
        delete this->taxi;
    }
}

/**
 * the empty constructor
 */
Driver::Driver() {

}

/**
 * the connstructor
 */
Driver::Driver(int idNum, int ag, Driver::martialStatus martialStatus, int expY, int vehicle_ide) {
    this->age = ag;
    this->expYears = expY;
    this->id = idNum;
    this->martialStat = martialStatus;
    this->satisCounter = 0;
    this->averageSatisfaction = 0;
    this->vehicle_id = vehicle_ide;
    this->taxi = NULL;
}

/**
 * @return - the driver id
 */
int Driver::getId() {
    return this->id;
}

/**
 * assign a taxi to the driver
 * @param t - the taxi
 */

/**
 * @param newSatis - the driver satisfaction from client
 */
void Driver::updateSatis(int newSatis) {
    double newSatisSum = (this->averageSatisfaction * this->satisCounter) + newSatis;
    this->satisCounter++;
    this->averageSatisfaction = newSatisSum / satisCounter;

}

/**
 * @return - the drivers experience
 */
int Driver::getExpYears() {
    return this->expYears;
}

/**
 * @return - the drivers age
 */
int Driver::getAge() {
    return this->age;
}

/**
 * @return - the drivers taxi
 */
Taxi *Driver::getTaxi() const {
    return taxi;
}

/**
 * make shure that the drivers info are logical ang correct
 */
int Driver::validate() {
    if ((this->getAge() < 0) || (this->getExpYears() < 0) ||
        (this->getId() < 0) || (this->martialStat == WRONGSTATUS)
        || (this->getVehicle_id() < 0)) {
        return -1;
    }
    return 0;
}

/**
 * @return - the drivers location
 */
Point Driver::getLocation() {
    return this->taxi->getLocation();
}


/**
 * movs the driver around
 */
void Driver::move() {
    this->taxi->move();
}


/**
 * @return - the drivers vehicle id
 */
int Driver::getVehicle_id() {
    return vehicle_id;
}

/**
 * getting a letter and parsing it into a martial status
 * @return - the martial status
 */
Driver::martialStatus Driver::parseMartialStatus(string martialStatus) {
    switch (martialStatus[0]) {
        case 'W':
            return WIDOWED;
        case 'D':
            return DIVORCED;
        case 'S':
            return SINGLE;
        case 'M':
            return MARRIED;
        default:
            break;
    }
    return WRONGSTATUS;
}


/**
 * @return - the driver's satisfaction
 */
double Driver::getSatis() {
    return this->averageSatisfaction;
}

/**
 * when the trip ends tive the driver
 * remove from active list and put in not active list
 */
void Driver::inactivate(std::list<Driver *> *inActDrivers, list<Driver *> *actDrivers) {
    Driver *d;
    for (int i = 0; i < actDrivers->size(); ++i) {
        d = actDrivers->front();
        if (d->getId() == this->id) {
            actDrivers->pop_front();
            break;
        }
        actDrivers->pop_front();
        actDrivers->push_back(d);
    }
    inActDrivers->push_back(d);
}

/**
 * @param list - set the routh of the driver
 */
void Driver::setRouth(std::list<Searchable *> *list) {
    this->getTaxi()->setRouth(list);
}

/**
 * the constructor.
 * getting a string and parsing it
 */
Driver::Driver(string input) {
    stringstream tempStr(input);
    string streamCut;
    int i = 0;
    string strArray[5];
    //parse string
    while (std::getline(tempStr, streamCut, ',')) {
        string strAfterFirstCut = streamCut;
        strArray[i] = strAfterFirstCut;
        i++;
    }
    //save the val in an array
    const char *c = strArray[1].c_str();
    this->age = atoi(c);
    c = strArray[0].c_str();
    this->id = atoi(c);
    c = strArray[3].c_str();
    this->expYears = atoi(c);
    c = strArray[4].c_str();
    this->vehicle_id = atoi(c);
    this->martialStat = Driver::parseMartialStatus(strArray[2]);

}

/**
 * @param t - set the driver's texi
 */
void Driver::setTaxi(Taxi *t) {
    this->taxi = t;
}


