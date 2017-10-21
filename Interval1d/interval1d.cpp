#include "interval1d.h"

Interval1d::Interval1d(const bool& ileftBraceisRound, const double& ileft, const double& iright, const bool& irightBraceisRound)
    : leftBraceisRound{ ileftBraceisRound }
    , left{ ileft }
    , right{ iright }
    , rightBraceisRound{ irightBraceisRound }

{
    this->isNull = (left == right) && (leftBraceisRound || rightBraceisRound);
}

Interval1d::Interval1d(const Interval1d& i) 
    : leftBraceisRound {i.leftBraceisRound}
    , left{ i.left }
    , right{ i.right }
    , rightBraceisRound{ i.rightBraceisRound }
{
    this->isNull = (left == right) && (leftBraceisRound || rightBraceisRound);
}


double Interval1d::length() {
    return (right - left);
}


bool Interval1d::isIntersepting(const Interval1d& i) {
    if ((right < i.left) || (i.right < left)) { return false; }
    if (((right == i.left) && (rightBraceisRound || i.leftBraceisRound)) || ((i.right == left) && (i.rightBraceisRound || leftBraceisRound)))
    {
        return false;
    }
    return true;
}

std::ostream& Interval1d::writeTo(std::ostream& ostrm) const {
    if (isNull) { ostrm << "null"; }
        else {
        ostrm << (leftBraceisRound ? "(" : "[") << " ";
        ostrm << left << dotcomma << " " << right;
        ostrm << (rightBraceisRound ? ")" : "]") << " ";
        }
    return ostrm;
};

std::ostream& operator<<(std::ostream& ostrm, Interval1d& i) {
    return (i.writeTo(ostrm));
};

/*
Interval1d Interval1d::interseptionWith(Interval1d& i) {
    if (left < i.right) { return Interval1d(leftBraceisRound, left, i.right, i.rightBraceisRound); }
    if (i.left < right) { return Interval1d(i.leftBraceisRound, i.left, right, rightBraceisRound); }
    return Interval1d(true, 0, 0, true); // null interval;
}
*/
/*
std::istream& Interval1d::readFrom(std::istream& istrm) {

};
*/

//subinterval
//interseptionwith
//concatenation