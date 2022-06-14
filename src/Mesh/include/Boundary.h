#ifndef Boundary_H
#define Boundary_H

#include "IODictionary.h"
#include "Mesh.h"
#include "RunTime.h"

///@brief Boundary Class stores the field data for a patch (faces on domain boundary).
/// provides attributes to store patch information.

template<typename vectorType>
class Boundary
:
    public IODictionary
{
    public:
    
        // Constructor by Reading Input file to initialize data members 
        ///@brief Boundary constructor by reading Input file  
        ///@param fileName name of the file to read field data from
        ///@param patch reference to the Patch
        ///@param time reference to the RunTime object
        ///@param action Enum fileAction ( MUST_READ or NO_READ)
        Boundary(std::string fileName, const Patch& patch, const RunTime& time, fileAction action);

        // Constructing with a default value passed by argument
        ///@brief Boundary constructor by setting a default value for the field 
        ///@param fileName name of the file to read field data from
        ///@param patch reference to the Patch
        ///@param time reference to the RunTime object
        ///@param action Enum fileAction ( MUST_READ or NO_READ)
        ///@param defaultValue is a scalar, vector or a tensor with which the field must be initialized. \note Vectors and tensors must be initialized in braces like: {value1,value2, ...,etc. }.
        Boundary(std::string fileName, const Patch& patch, const RunTime& time, fileAction action, const typename vectorType::value_type& defaultValue);

        // Destructor
        virtual ~Boundary(){} ;

        // Read Data
        template <typename primitiveType>
        primitiveType readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter);

        // Read Boundary field
        ///@brief this function reads from a specified patch and returns the information to construct the object.
        ///@param patchName the name of patch for reading information. 
        void readBoundaryPatch( const std::string& patchName);

        ///@brief Member function to access the boundary patch defined values
        vectorType& definedValues();

        ///@brief Member function to access the boundary patch defined name
        const std::string& name();

        ///@brief Member function to access the boundary patch defined type ( fixedValue, fixedGradient, symmetry, and etc. )
        std::string& type();
    
        ///@brief Member function to access the boundary patch field type ( uniform and non-uniform )
        bool& uniformField();

        ///@brief Member function to access the boundary patch supplementary data content.
        const std::map<std::string, std::string>& otherInfo();

        // Operator Overloading templated
        // Setter
        ///@brief Operator [] to modify the content set for a given position 
        ///@param posI position of a face given by a positive integer. 
        typename vectorType::value_type& operator[](unsigned int posI);

        // Getter
        ///@brief Operator [] to retrieve the content set for a given position 
        ///@param posI position of a face given by a positive integer. 
        typename vectorType::value_type operator[](unsigned int posI) const;
                
    private:

      // Private Data Members
      
        // The naming given to the patch
        const std::string& name_;
        // The type name of the Boundary condition.
        std::string type_;
        // The field if it is uniform or not.
        bool uniformField_;
        // The values for the faces in the patch.
        vectorType definedValues_;
        // The supplementary data content.
        std::map<std::string, std::string> otherInfo_;

};

#include "BoundaryI.h"

#endif 