#ifndef fvFixedValuePatchField_H
#define fvFixedValuePatchField_H

// #include "IODictionary.h"
// #include "Mesh.h"
// #include "RunTime.h"
#include "BoundaryField.h"


///@brief Boundary Class stores the field data for a patch (faces on domain boundary).
/// provides attributes to store patch information.

template<typename vectorType>
class fvBoundaryConditionsField
{
    public:
    
        // Constructor constructing a 
        fvBoundaryConditionsField(VolField<vectorType> field);

        struct coefficients
        {
          // The values for the ...
          vectorType valueInternalCoeffs_;
          
          // The values for the ...
          vectorType valueBoundaryCoeffs_;

          // The values for the ...
          vectorType gradientInternalCoeffs_;

          // The values for the ...
          vectorType gradientBoundaryCoeffs_;
        };

        // Destructor
        virtual ~fvBoundaryConditionsField(){} ;

        void updateCoeffs();


    private:

      // Private Data Members
      
        // // The naming given to the patch
        // const std::string& name_;
        vector<coefficients> coefficients_;

        // Check if the patch has been updated.
        bool updated_;

};

#include "fvBoundaryConditionsFieldI.h"

#endif 