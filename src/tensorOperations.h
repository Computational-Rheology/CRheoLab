#ifndef TENSOROPERATIONS_H
#define TENSOROPERATIONS_H

// Output vectorField to screen
inline std::ostream& operator<<(std::ostream& os, const tensorField& t)
{
    os << "(" << std::endl;
    
    for (unsigned int i = 0; i < t.size(); ++i) {
        
        os << "\t";

        os << "(";

        for (unsigned int j=0; j< t[i].size(); j++)
        {   
            if(j<t[i].size()-1)
            {
                os<< t[i][j] << " ";
            }
            else
            {
                os<< t[i][j];
            }
            
        }
        os << ")" << std::endl;
    }

    os << ")";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symmTensorField& t)
{
    os << "(" << std::endl;
    
    for (unsigned int i = 0; i < t.size(); ++i) {
        
        os << "\t";

        os << "(";

        for (unsigned int j=0; j< t[i].size(); j++)
        {   
            if(j<t[i].size()-1)
            {
                os<< t[i][j] << " ";
            }
            else
            {
                os<< t[i][j];
            }
            
        }
        os << ")" << std::endl;
    }

    os << ")";
    return os;
}


inline std::ostream& operator<<(std::ostream& os, const tensor& t)
{
    os << "(" ;
    
    for (unsigned int i = 0; i < t.size(); ++i)
    {   
        if(i<t.size()-1)
            {
                os<< t[i]<< " ";
            }
            else
            {
                os<< t[i];
            }
    }

    os << ")";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symmTensor& t)
{
    os << "(" ;
    
    for (unsigned int i = 0; i < t.size(); ++i)
    {   
        if(i<t.size()-1)
            {
                os<< t[i]<< " ";
            }
            else
            {
                os<< t[i];
            }
    }

    os << ")";
    return os;
}



// Math Operations

// At the vector level

// Summation
inline tensor operator+(const tensor& t1, const tensor& t2)
{
   tensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] + t2[i];
    }

   return result;
}


// Subtraction
inline tensor operator-(const tensor& t1, const tensor& t2)
{
   tensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] - t2[i];
    }

   return result;
}

// scalar multiplication
inline tensor operator*(const double& d1, const tensor& t1)
{
    tensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] * d1;
    }

   return result;
}

inline tensor operator*(const tensor& t1,const double& d1)
{
    tensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] * d1;
    }
   return result;
}



// scalar division
inline tensor operator/(const tensor& t1, const double& d1)
{
    tensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] / d1;
    }

   return result;
}

inline tensor  operator/(const double& d1, const tensor& t1)
{
    tensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = d1 / t1[i];
    }
   return result;
}

/*//inner product / dot product
tensor operator&(const tensor& t1, const vector3& v1)
{  
   vector3 result;

    result = ( t1[0]*v1[0]+ 
                  
            )

   return result;
}
*/

// At the field level


inline tensorField operator*(const tensorField& t1, const double& d1)
{
    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] * d1;
    }

    return result;
}

inline tensorField operator*( const double& d1, const tensorField& t1)
{

    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] * d1;
    }

    return result;
}

inline tensorField operator*( const scalarField& s1, const tensorField& t1)
{

    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] * s1[i];
    }

    return result;
}

inline tensorField operator/(const tensorField& t1, const double& d1)
{

    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] / d1;
    }

    return result;
}

inline tensorField operator/(const double& d1, const tensorField& t1)
{
    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = d1 / t1[i];
    }

    return result;
}

inline tensorField operator/(const tensorField& t1, const scalarField& s1)
{

    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] / s1[i];
    }

    return result;
}


inline tensorField operator/(const scalarField& s1, const tensorField& t1)
{
    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = s1[i]/t1[i];
    }

    return result;
}
#endif
