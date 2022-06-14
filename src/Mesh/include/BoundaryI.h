#include "readBoundary.h"

// Constructor by Reading Input file to initialize data members 
template <typename vectorType>
Boundary<vectorType>::Boundary(std::string fileName, const Patch& patch, const RunTime& time, fileAction action)
    : IODictionary(time.Path(), fileName),
      name_(patch.name())
{
    if (action == MUST_READ)
    {
        readBoundaryPatch(patch.name());
    }
    else if (action == NO_READ)
    {
        this->type_="calculated";
        this->uniformField_=false;
        this->definedValues_.resize(patch.nFaces());
        // Initializing the field to zeros.
        // Zeroed ref value
        typename vectorType::value_type dataToVector{0};
        // Zeroing the vector members with the ref data
        std::fill(this->definedValues_.begin(),this->definedValues_.end(), dataToVector);
    }
    else
    {
        // Verifying if the fileAction not one of the available options
        throw std::runtime_error("Unrecognized action for boundaryField! Please choose MUST_READ or NO_READ!");
    }

    // Verifying if the patch size is in agreement with the mesh Patch size
    if ((!this->uniformField_) && (this->type_!="empty") && this->definedValues_.size() != (long unsigned int)patch.nFaces())
    {
        std::cerr << "The input data for the patch named as \" " << patch.name() << " \" for the field " << fileName << " in the file " << time.Path() << fileName << " has " << this->definedValues_.size() << " entries, while this patch allows only " << patch.nFaces()  << " face!" << std::endl;
        throw std::runtime_error(" ");
    }
}

// Constructing with a default value passed by argument
template <typename vectorType>
Boundary<vectorType>::Boundary(std::string fileName, const Patch& patch, const RunTime& time, fileAction action, const typename vectorType::value_type& defaultValue)
    : IODictionary(time.Path(), fileName),
      name_(patch.name())
{
    this->type_="calculated";
    this->uniformField_=false;
    this->definedValues_.resize(patch.nFaces(), defaultValue);
}


// Member function to access the boundary patch defined values
template <typename vectorType>
vectorType& Boundary<vectorType>::definedValues()
{
  return definedValues_;
}

// Member function to access the boundary patch defined name
template <typename vectorType>
const std::string& Boundary<vectorType>::name()
{
  return name_;
}

// Member function to access the boundary patch defined type ( fixedValue, fixedGradient, symmetry, and etc. )
template <typename vectorType>
std::string& Boundary<vectorType>::type()
{
  return type_;
}

// Member function to access the boundary patch field type ( uniform and non-uniform )
template <typename vectorType>
bool& Boundary<vectorType>::uniformField()
{
  return uniformField_;
}


// Member function to access the boundary patch supplementary data content.
template <typename vectorType>
const std::map<std::string, std::string>& Boundary<vectorType>::otherInfo()
{
  return otherInfo_;
}

// Operator Overloading templated
// Setter 
template <typename vectorType>
typename vectorType::value_type& Boundary<vectorType>::operator[](unsigned int posI)
{
  if (posI >= this->definedValues_.size())
  {
      std::cout << "The given index " << posI << " is out of bound, exiting" << std::endl;
      exit(0);
  }
  return definedValues().at(posI);
}

// Operator Overloading templated
// Getter 
template <typename vectorType>
typename vectorType::value_type Boundary<vectorType>::operator[](unsigned int posI) const
{
  if (posI >= definedValues().size())
  {
      std::cout << "The given index " << posI << " is out of bound, exiting" << std::endl;
      exit(0);
  }
  return this->definedValues_.at(posI);
}
