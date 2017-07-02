#ifndef TM_TAXI_H
#define TM_TAXI_H

#include <vector>
#include <list>
#include "Searchable.h"
#include "Passenger.h"

/**
 * a class that represent a taxi
 */
class Taxi{
public:
    typedef enum {
        HONDA, SUBARO, TESLA, FIAT,WRONGMANUFATURER
    } manufacturer;
    typedef enum {
        RED, BLUE, GREEN, PINK, WHITE,WRONGCOLOR
    } color;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & carId;
        ar & mnfctr;
        ar & clr;
        ar & tarrif;
        ar & routh;
        ar & location;
    }

    int validate();

    static manufacturer parseMnfctr(string s);

    static color parseColor(string s);

    Taxi();

    ~Taxi();

    Taxi(int idNum, manufacturer mnfctr, color clr, int taarif);

    Point getLocation();

    void setLocation(Point newLocation);

    int getTarrif();

    void addPassengers(vector<Passenger> psngrs);

    int getCarId() const;

    manufacturer getMnfctr() const;

    color getClr() const;

    virtual void move() = 0;

    bool operator==(const Taxi &other) {
        return this->carId == other.carId && this->mnfctr == other.mnfctr && this->clr == other.clr
               && this->tarrif == other.tarrif;
    }

    vector<Passenger> getPassengers();

    void setRouth(std::list<Searchable *>* routhFromClientToDes);

    list<Searchable *>* getRouth();

protected:
    list<Searchable *>* routh;
    int carId;
    manufacturer mnfctr;
    int tarrif;
    color clr;
    Point location;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Taxi)

#endif //TM_TAXI_H