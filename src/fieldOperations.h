#ifndef FIELDOPERATIONS_H
#define FIELDOPERATIONS_H


// Check if both vectors have the same size
template <typename T1>
inline void checkSize(const std::vector<T1>& v1, const std::vector<T1>& v2)
{
    if(v1.size() != v2.size() )
    {
        throw std::length_error("Vectors do not have the same dimensions");
    }
}

// Math Operations

// At the field level
// Summation
template <typename T>
inline std::vector<T> operator+(const std::vector<T> & v1, const std::vector<T> & v2)
{

    checkSize(v1,v2);
   
   std::vector<T> result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = v1[i] + v2[i];
   }

   return result;
}


template <typename T>
inline std::vector<T> operator-(const std::vector<T> & v1, const std::vector<T> & v2)
{

    checkSize(v1,v2);
   
   std::vector<T> result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = v1[i] - v2[i];
   }

   return result;
}

#endif
