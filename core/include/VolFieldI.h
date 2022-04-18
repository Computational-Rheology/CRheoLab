#include "readVolField.h"

template <typename vectorType>
VolField<vectorType>::VolField(std::string fileName, const Mesh &mesh, const RunTime &time, fileAction action)
    : IODictionary(time.Path(), fileName),
      mesh_(mesh),
      runTime_(time),
      boundaryField_(fileName, mesh, time, action),
      action_(action)
{
  // Check action
  if (action  == MUST_READ)
  {
      internalField_=readInternalField();
  }
  else if (action == NO_READ)
  {
      internalField_.resize(mesh.nCells_);
  }
  else
  {
      std::cerr << "Unrecognized action for internalField!" << std::endl;
  }
}

template <typename vectorType>
VolField<vectorType>::VolField(std::string fileName, const Mesh &mesh, const RunTime &time, fileAction action, const typename vectorType::value_type& defaultValue)
    : IODictionary(time.Path(), fileName),
      mesh_(mesh),
      runTime_(time),
      boundaryField_(fileName, mesh, time, action, defaultValue),
      action_(action)
{
      internalField_.resize(mesh.nCells_, defaultValue);
}

// Give access to the boundary entities
template <typename vectorType>
BoundaryField<vectorType>& VolField<vectorType>::boundaryField()
{
  return boundaryField_;
}
