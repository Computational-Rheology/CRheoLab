#include <iostream>
#include "Mesh.h"
#include "IODictionary.h"
#include "IODictionaryw.h"
#include "VolField.h"
#include "fvBoundaryConditionsField.h"


//  void write_csv(std::string filename, std::string , std::vector<double> );

/*template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[ \n";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << std::endl;
    }
    os << "]\n";
    return os;
}*/

using namespace std;

int main()
{
      
    std::cout << "Current path is : " << getExecutablePath() << std::endl;

    checkCaseStructure();
    
    RunTime time;
    std::cout << "Current path from time object is : " << time.Path() << std::endl;

    Mesh polyMesh;
    
    // ----------------------------------------------------------------------- |
    // Testing Boundary Field and Condition classes implementations

        // Testing constructor from the constructor initialization in the VolField class
        VolField<scalarField> p ("p", polyMesh, time, MUST_READ);
        // Testing constructor from the constructor initialization in the VolField class with default value
        VolField<scalarField> pDefVal ("p", polyMesh, time, MUST_READ, 1348.84);
        VolField<scalarField> pDefVal1 ("p", polyMesh, time, NO_READ );
        // Testing constructor from the BoundaryField  class with Input file
        BoundaryField<scalarField> pBoundary("p", polyMesh, time, MUST_READ);
        // fvBoundaryConditionsField<scalarField> pBoundaryCondition(pBoundary);
        fvBoundaryConditionsField<scalarField> pBoundaryCondition(p);

        // for (int i = 0; i < polyMesh.patchList_.size(); i++)
        // {
        //     std::cout << "The startFace ID is: " << polyMesh.patchList_[i].startFace() << std::endl;
        //     std::cout << "The number of Faces is: " << polyMesh.patchList_[i].nFaces() << std::endl;
        //     int startFace = polyMesh.patchList_[i].startFace();
        //     int totalPatchFaces = polyMesh.patchList_[i].nFaces();
        //     for (int faceI = 0; faceI < totalPatchFaces; faceI++)
        //     {
        //         std::cout << "The Faces with ID: " << startFace+faceI << " has the cell ID " <<
        //         polyMesh.faceList_[startFace+faceI].getOwnerID() << " as Owner cell." << std::endl;
        //     }
        // }
        
        // Testing constructor from the constructor initialization in the VolField class
        VolField<vectorField> U ("U", polyMesh, time, MUST_READ);
        // Testing constructor from the constructor initialization in the VolField class with default value
        VolField<vectorField> UDefVal ("U", polyMesh, time, NO_READ,  vector3{1,2,3} );
        VolField<vectorField> UDefVal1 ("U", polyMesh, time, NO_READ );
        // Testing constructor from the BoundaryField  class with Input file
        BoundaryField<vectorField> UBoundary ("U", polyMesh, time, MUST_READ);
        // Testing constructor from the BoundaryField  class with Default Value
        BoundaryField<vectorField> UBoundaryNoRead ("U", polyMesh, time, NO_READ, vector3{2,1,3} );
        // Testing the c-like initialization for the BoundaryField object with the VolField Class boundary data access member function
        BoundaryField<vectorField> UBAddress = U.boundaryField();    

        // VolField<tensorField> tau ("tau", polyMesh, time);

        // std::cout << pBoundary[0].patchName() << std::endl;
        // std::cout << pBoundary[1].patchName() << std::endl;
        // std::cout << pBoundary[2].patchName() << std::endl;

        // std::cout<<"Patch ID: "<<p.patchID("banana")<<std::endl;
        // std::cout<<"Patch ID: "<<p.patchID("top")<<std::endl;
        // std::cout<<"Patch ID: "<<p.patchID("bottom")<<std::endl;
        // std::cout<<"Patch Name: "<<pBoundary[p.patchID("top")].patchName()<<std::endl;
        // std::cout<<"Patch Name: "<<pBoundary[p.patchID("banana")].patchName()<<std::endl;
        // std::cout<<"Patch ID: "<<p.patchID(pBoundary[p.patchID("banana")].patchName())<<std::endl;

    // --- End - of --- Testing Boundary Class implementation
    // ----------------------------------------------------------------------- |

    // ----------------------------------------------------------------------- |
    // Testing IODictionaryw.h implementation

        // symmTensorField symmfield =  {{5e+06, -0.000144797, -0.000460091, 0.0545079, -0.00401398, 0.102309},{5e+06, -0.000115814 ,-0.000726005, 0.00996289 ,0.0168723, 0.0300389},{5e+06, -0.000115814 ,-0.000726005, 0.00996289 ,0.0168723, 0.0300389}  } ;
        // patchBoundaryConditions<symmTensorField> pBCRIght = { "calculated", symmfield , {} };
        // patchBoundaryConditions<symmTensorField> pBCLeft = { "empty", {} , {} };
        // patchBoundaryConditions<symmTensorField> pBCTop = { "empty", symmfield , {} };

        // std::cout<<"\n\n"<<std::endl;
        // //std::cout << '\n'<< pBCRight << std::endl;
        // boundaryField<symmTensorField> bField = {{"Right","Left","Top"},{pBCRIght,pBCLeft,pBCTop}};
        
        // internalField<symmTensorField> iField =  {symmfield.size(),symmfield};
        // // VolField<vectorField> U ("U", polyMesh);

        // std::cout<<iField<<std::endl;

        // std::cout<< bField << std::endl;

        // std::cout<<"OK"<<std::endl;

    // --- End - of --- Testing IODictionaryw.h implementation
    // ----------------------------------------------------------------------- |

    return 0;

}


