#include "Point.h"

Point::Point(double x, double y, double z)
:  
    p_{x,y,z}
{}

Point::Point()
:   
    p_{-1, -1 ,-1}
{}

void Point::setCoord(double x, double y, double z)
{
    p_[0] = x;
    p_[1] = y;
    p_[2] = z;
}

// Setter
double& Point::operator[](int entry)
{
    if (entry==0)
        return p_[0];
    else if(entry==1)
        return p_[1];
    else if(entry==2)
        return p_[2];
    else
        throw std::out_of_range("Point does not have index " + std::to_string(entry));
}

// Getter
double Point::operator[](int entry) const 
{
    if (entry==0)
        return p_[0];
    else if(entry==1)
        return p_[1];
    else if(entry==2)
        return p_[2];
    else
        throw std::out_of_range("Point does not have index " + std::to_string(entry));
}

Point Point::operator+(Point const &obj) const
{
    Point result;
    result.p_[0] = p_[0] + obj.p_[0];
    result.p_[1] = p_[1] + obj.p_[1];
    result.p_[2] = p_[2] + obj.p_[2];

    return result;
}

Point Point::operator-(Point const &obj) const
{
    Point result;
    result.p_[0] = p_[0] - obj.p_[0];
    result.p_[1] = p_[1] - obj.p_[1];
    result.p_[2] = p_[2] - obj.p_[2];

    return result;
}

const vector3& Point::getPoint() const
{
    return p_;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "[ " << p[0] << ", " << p[1] << ", " << p[2] << " ]" << std::endl;
    return os;
}
