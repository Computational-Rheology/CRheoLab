// BoundaryField constructor by reading Input file  
template <typename vectorType>
BoundaryField<vectorType>::BoundaryField(std::string fileName, const Mesh& mesh, const RunTime& time, fileAction action)
:     nPatches_(mesh.nPatches_)
{
    for (int i = 0; i < nPatches_; i++)
    {
        boundaryData_.push_back(Boundary<vectorType>(fileName, mesh.patchList_[i], time, action));
    }
}

// BoundaryField constructor by setting a default value for the field  
template <typename vectorType>
BoundaryField<vectorType>::BoundaryField(std::string fileName, const Mesh& mesh, const RunTime& time, fileAction action,  const typename vectorType::value_type& defaultValue)
:     nPatches_(mesh.nPatches_)
{
    for (int i = 0; i < nPatches_; i++)
    {
        boundaryData_.push_back(Boundary<vectorType>(fileName, mesh.patchList_[i], time, action, defaultValue));
    }
}

// Returns the size of the boundary patch
template <typename vectorType>
const int& BoundaryField<vectorType>::nPatches() const
{
    return nPatches_;
}

// Returns the size of the boundary patch
template <typename vectorType>
const int BoundaryField<vectorType>::patchINumberOfFaces(int i) const
{
    return boundaryData_[i].numberOfFaces();
}

// Returns the size of the boundary patch
template <typename vectorType>
const std::string& BoundaryField<vectorType>::patchITypeOfBCondition(int i) const
{
    return boundaryData_[i].type();
}

// Returns the size of the boundary patch
template <typename vectorType>
const std::string& BoundaryField<vectorType>::patchIName(int i) 
{
    return boundaryData_[i].name();
}

// Returns for a patch I, the face J defined value
template <typename vectorType>
typename vectorType::value_type BoundaryField<vectorType>::patchIFaceJValue(int patchI, int faceJ)
{
    return boundaryData_[patchI].definedValues(faceJ);
}

// Member function to access the boundary data
template <typename vectorType>
vector<Boundary<vectorType>>& BoundaryField<vectorType>::boundaryData()
{
    return boundaryData_;
}

// Returns the name in the boundaryField patch list for the give patch index 
template <typename vectorType>
const int& BoundaryField<vectorType>::patchID(const std::string& patchName) const
{
    int pId=-1;
    for (unsigned int i = 0; i < nPatches_; i++)
    {
        if (boundaryData_[i].name()==patchName)
        {
            pId=boundaryData_[i].index();
        } 
    }
    return pId;
}

