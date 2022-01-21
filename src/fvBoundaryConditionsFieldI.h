// TODO
// Constructor by Reading a boundary Patch 
template <typename vectorType>
fvBoundaryConditionsField<vectorType>::fvBoundaryConditionsField(BoundaryField<vectorType> boundaryPatches)
{
    this->coefficients_.resize(boundaryPatches.nPatches());
    for ( long unsigned int patchI = 0; patchI < coefficients_.size(); patchI++)
    {
        coefficients_[patchI].valueInternalCoeffs_.resize(boundaryPatches.patchINumberOfFaces(patchI));  
        coefficients_[patchI].valueBoundaryCoeffs_.resize(boundaryPatches.patchINumberOfFaces(patchI));  
        coefficients_[patchI].gradientInternalCoeffs_.resize(boundaryPatches.patchINumberOfFaces(patchI));  
        coefficients_[patchI].gradientBoundaryCoeffs_.resize(boundaryPatches.patchINumberOfFaces(patchI));
        
        int sizeOfPatch(coefficients_[patchI].valueInternalCoeffs_.size());
        std::string patchBCName(boundaryPatches.patchITypeOfBCondition(patchI));
        std::string patchBCType(boundaryPatches.patchITypeOfBCondition(patchI));
        for (int faceI = 0; faceI < sizeOfPatch; faceI++)
        {
          // TODO Check Why empty BC is not being captured as error setup
          // ToDo the Cellcenter dist to faceCenter 
          // Todo input data defined in the boundary Patch
          // ToDo Create a method for Vectors and Tensors  when templated as vectorType 
          
          double value(2.0);
          double delta(3.5);


          if(patchBCType == "fixedValue")
          {
            coefficients_[patchI].valueInternalCoeffs_[faceI] = 0;
            coefficients_[patchI].valueBoundaryCoeffs_[faceI] = value;
            coefficients_[patchI].gradientInternalCoeffs_[faceI] = -delta;
            coefficients_[patchI].gradientBoundaryCoeffs_[faceI] = value*delta;
          }
          else if (patchBCType == "fixedGradient")
          {
            coefficients_[patchI].valueInternalCoeffs_[faceI]= 1;
            coefficients_[patchI].valueBoundaryCoeffs_[faceI]= -value;
            coefficients_[patchI].gradientInternalCoeffs_[faceI]= 0;
            coefficients_[patchI].gradientBoundaryCoeffs_[faceI]= value;
          }
          else if (patchBCType == "symmetry")
          {
            coefficients_[patchI].valueInternalCoeffs_[faceI] = 1;
            coefficients_[patchI].valueBoundaryCoeffs_[faceI] = 0;
            coefficients_[patchI].gradientInternalCoeffs_[faceI] = 0;
            coefficients_[patchI].gradientBoundaryCoeffs_[faceI] = 0;
          }
          else
          {
              std::cerr << "The boundary condition set for the patch named as \" " << patchBCName << " \" for the field " << " AAAfileName " << " in the file " << " AAAtime.Path() " << " AAAfileName " << " as " << patchBCType << " is not available! Please choose one of the options: \" fixedValue \" \" fixedGradient \" \" symmetry \"  " << std::endl;
              throw std::runtime_error(" ");
          }
        }     
    }
}
