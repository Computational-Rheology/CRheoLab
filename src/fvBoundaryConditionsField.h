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
        fvBoundaryConditionsField(VolField<vectorType> field, const Mesh& mesh);

        struct coefficients
        {
          // Check if the patch has been updated.
          bool updated;

          // Todo check when it will be needed
          // // The values for the ...
          // vectorType valueInternalCoeffs;
          
          // // The values for the ...
          // vectorType valueBoundaryCoeffs;

          // The values for the ...
          vectorType gradientInternalCoeffs;

          // The values for the ...
          vectorType gradientBoundaryCoeffs;
        };

        // Destructor
        virtual ~fvBoundaryConditionsField(){} ;

        void updateCoeffs();

    private:

      // Private Data Members
      
        // // The naming given to the patch
        // const std::string& name_;
        vector<coefficients> coefficients_;

};

#include "fvBoundaryConditionsFieldI.h"

#endif 