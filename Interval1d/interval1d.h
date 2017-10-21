#ifndef INTERVAL1D_H
#define INTERVAL1D_H

#include <sstream>
#include<iostream>;

class Interval1d {
public:
    Interval1d() = default;
    ~Interval1d() = default;
    Interval1d(const Interval1d& i);
    Interval1d(const bool& ileftBraceisRound, const double& ileft, const double& iright, const bool& irightBraceisRound);

    std::ostream& writeTo(std::ostream& ostrm) const;
    //std::istream& readFrom(std::istream& istrm);

    double length();
    bool isIntersepting(const Interval1d& i);
    Interval1d interseptionWith(Interval1d& i);


private:
    bool leftBraceisRound = 0;
    double left = 0.0;
    double right = 0.0;
    bool rightBraceisRound = 0;
    bool isNull = false;
    const char dotcomma = ';';

};


std::ostream& operator<<(std::ostream& ostrm, Interval1d& i);
#endif