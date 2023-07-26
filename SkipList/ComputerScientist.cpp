#include <iostream>
#include "ComputerScientist.h"


ostream& operator << (ostream &out, const ComputerScientist &ComputerScientist) {
    // Since operator << is a friend of the ComputerScientist class, we can access
    // ComputerScientist's members directly.
    out << " id: " << ComputerScientist.id;
    return out;
}

//Initialize class members from constructor arguments
//by using a member initializer list.
//This method uses direct initialization, which is more
//efficient than using assignment operators inside the constructor body.
ComputerScientist::ComputerScientist(const ComputerScientist& rhs)
        : id{ rhs.id } {
    // empty body of constructor
}

//Initialize class members from constructor arguments
//by using a member initializer list.
//This method uses direct initialization, which is more
//efficient than using assignment operators inside the constructor body.
ComputerScientist::ComputerScientist(int id)
        : id{ id } {
    // empty body of constructor
}

//Initialize class members from constructor arguments
//by using a member initializer list.
//This method uses direct initialization, which is more
//efficient than using assignment operators inside the constructor body.
ComputerScientist::ComputerScientist()
        : id{ -1 } {
    // empty body of constructor
}


ComputerScientist::~ComputerScientist() {
    // empty body of destructor
}

bool ComputerScientist::operator==( const ComputerScientist& rhs) const {
    return this->id == rhs.id;
}

bool  ComputerScientist::operator<( const ComputerScientist& rhs) const {
    return this->id < rhs.id;
}

ComputerScientist & ComputerScientist::operator=(const ComputerScientist & rhs) {
    this->id = rhs.id;
    return *this;
}

int ComputerScientist::getID() const {
    return this->id;
}