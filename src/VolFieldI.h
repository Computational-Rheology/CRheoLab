#include "readVolField.h"

template <typename vectorType>
VolField<vectorType>::VolField(const IOObject& IO)
    : IODictionary(IO),
      mesh_(IO.mesh()),
      runTime_(IO.mesh().time()),
      boundaryField_(IO)
{
  // Check action
  if (read_  == MUST_READ)
  {
      internalField_=readInternalField();
  }
  else if (read_ == NO_READ)
  {
      internalField_.resize(this->mesh().nCells_);
  }
  else
  {
      std::cerr << "Unrecognized action for internalField!" << std::endl;
  }
}

template <typename vectorType>
VolField<vectorType>::VolField(const IOObject& IO, const typename vectorType::value_type& defaultValue)
    : IODictionary(IO),
      mesh_(mesh),
      runTime_(time),
      boundaryField_(this.name(), this.mesh(), this.mesh().time(), defaultValue)
{
      internalField_.resize(this.mesh().nCells_, defaultValue);
}

// Give access to the boundary entities
template <typename vectorType>
BoundaryField<vectorType>& VolField<vectorType>::boundaryField()
{
  return boundaryField_;
}
