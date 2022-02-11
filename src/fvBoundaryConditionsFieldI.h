// TODO
// Constructor by Reading a boundary Patch 
template <typename vectorType>
fvBoundaryConditionsField<vectorType>::fvBoundaryConditionsField(VolField<vectorType> field,  const Mesh& mesh)
{
  BoundaryField<vectorType>& boundaryPatches=field.boundaryField();
  this->coefficients_.resize(boundaryPatches.nPatches());
  for ( long unsigned int patchI = 0; patchI < coefficients_.size(); patchI++)
  {
    // This is to calculate the value of a variable in a patch (used in the divergent)
    // coefficients_[patchI].valueInternalCoeffs.resize(mesh.patchList_[patchI].nFaces());  
    // coefficients_[patchI].valueBoundaryCoeffs.resize(mesh.patchList_[patchI].nFaces());

    // This is to calculate the gradient of a variable in a patch (used in the laplacian)
    coefficients_[patchI].gradientInternalCoeffs.resize(mesh.patchList_[patchI].nFaces());  
    coefficients_[patchI].gradientBoundaryCoeffs.resize(mesh.patchList_[patchI].nFaces());
    
    // Retreiving the number of the faces that the current patchI has to use in the following For-loops
    int sizeOfPatch(coefficients_[patchI].gradientInternalCoeffs.size());

    // Retreiving the name and the type, respectively, for this boundary patch.
    std::string patchBCName(boundaryPatches.patchIName(patchI));
    std::string patchBCType(boundaryPatches.patchITypeOfBCondition(patchI));
    
    // Retrieving the index of the inital face for this patch
    int startPatchFaceID = mesh.patchList_[patchI].startFace();
    
    if(patchBCType == "fixedValue")
    {
      for (int faceI = 0; faceI < sizeOfPatch; faceI++)
      {
        // The inverse distance between the face Center and cell Center [ delta =  1 / || d || ]
        double delta( 1.0 / mag( mesh.faceList_[startPatchFaceID+faceI].getCentoidsDist()) );
        // Load the field value defined by the User for this patch and face. 
        typename vectorType::value_type value(boundaryPatches.patchIFaceJValue(patchI, faceI));
        // coefficients_[patchI].valueInternalCoeffs[faceI] = 0;
        // coefficients_[patchI].valueBoundaryCoeffs[faceI] = value;
        coefficients_[patchI].gradientInternalCoeffs[faceI] = -delta;
        coefficients_[patchI].gradientBoundaryCoeffs[faceI] = value*delta;
      }
    }
    else if (patchBCType == "fixedGradient")
    {
      for (int faceI = 0; faceI < sizeOfPatch; faceI++)
      {
        // Load the gradient value defined by the User for the patch and face. 
        typename vectorType::value_type value(boundaryPatches.patchIFaceJValue(patchI, faceI));
        
        // coefficients_[patchI].valueInternalCoeffs[faceI]= 1;
        // coefficients_[patchI].valueBoundaryCoeffs[faceI]= -value;
        coefficients_[patchI].gradientInternalCoeffs[faceI]= 0;
        coefficients_[patchI].gradientBoundaryCoeffs[faceI]= value;
      }
    }
    else if (patchBCType == "symmetry")
    {
      for (int faceI = 0; faceI < sizeOfPatch; faceI++)
      {
        // coefficients_[patchI].valueInternalCoeffs[faceI] = 1;
        // coefficients_[patchI].valueBoundaryCoeffs[faceI] = 0;
        coefficients_[patchI].gradientInternalCoeffs[faceI] = 0;
        coefficients_[patchI].gradientBoundaryCoeffs[faceI] = 0;
      }
    }
    else if (patchBCType == "empty")
    {
        /* Do nothing */
    }
    else
    {
        std::cerr << "\n\nThe boundary condition for the patch named as \'" << patchBCName << "\' for the field \'" << field.fieldFileName() << "\' in the file \'" << field.fieldFilePath() << field.fieldFileName() << "\' set as \'" << patchBCType << "\' is not available!" << "\n\n\tPlease choose one of the options: fixedValue, fixedGradient, symmetry or empty." << std::endl << std::endl << std::endl;
        throw std::runtime_error(" ");
    }
  }     
}