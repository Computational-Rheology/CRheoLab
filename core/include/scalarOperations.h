#ifndef SCALAROPERATIONS_H
#define SCALAROPERATIONS_H

// Output scalarField to screen
inline std::ostream& operator<<(std::ostream& os, const scalarField& v)
{
    os << "[" << std::endl;
    
    for (unsigned int i = 0; i < v.size(); ++i) {
        os << "\t" << v[i] << std::endl;
    }

    os << "]\n";
    return os;
}

// Math Operations

// At the field level

// Multiplication
inline scalarField operator*(const scalarField& v1, const scalarField& v2)
{
    checkSize(v1,v2);
   
   scalarField result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = v1[i] * v2[i];
   }

   return result;
}

// Division
inline scalarField operator/(const scalarField& v1, const scalarField& v2)
{
    checkSize(v1,v2);
   
   scalarField result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = v1[i] / v2[i];
   }

   return result;
}

// Square
inline scalarField sqr(const scalarField& v1)
{   
   scalarField result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = v1[i]*v1[i];
   }
   return result;
}

inline scalarField log(const scalarField& v1)
{   
   scalarField result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = std::log(v1[i]);
   }

   return result;
}

inline scalarField exp(const scalarField& v1)
{   
   scalarField result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = std::exp(v1[i]);
   }
   return result;
}

inline scalarField sin(const scalarField& v1)
{   
   scalarField result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = std::sin(v1[i]);
   }
   return result;
}

inline scalarField cos(const scalarField& v1)
{   
   scalarField result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = std::cos(v1[i]);
   }
   return result;
}

inline scalarField tan(const scalarField& v1)
{   
   scalarField result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = std::tan(v1[i]);
   }
   return result;
}

inline scalarField pow(const scalarField& v1, const int n)
{   
   scalarField result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = std::pow(v1[i], n);
   }
   return result;
}

inline double radToDegree(const double s)
{   

     double degrees = (180/M_PI)*s;
     return degrees;
}

#endif