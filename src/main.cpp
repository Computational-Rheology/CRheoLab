
#include "Mesh.h"
#include "RunTime.h"
#include "IODictionary.h"
#include "VolField.h"
#include "IOObject.h"
#include "Dictionary.h"

void foo(VolField<std::vector<double>>& field)
{
    Dictionary& banana2 = field.mesh().lookup<Dictionary>( "transportProperties");
    double d1 = banana2.lookup<double>("abc");

    VolField<std::vector<double>> banana
    (
        IOObject
        (
            "p",
            field.mesh().time().constant(),
            field.mesh(),
            fileAction::NO_READ,
            fileAction::NO_WRITE,
            false
        ),
         d1
    );

    field = field+banana;

    
}

int main()
{
    RunTime time;
    Mesh mesh(time);
    

    Dictionary myDict
    (
        IOObject
        (
            "transportProperties",
            time.constant(),
            mesh,
            fileAction::MUST_READ,
            fileAction::NO_WRITE
        )
    );
    


   Dictionary& banana1 = mesh.lookup<Dictionary>("transportProperties");
  

    VolField<std::vector<double>> p
    (
        IOObject
        (
            "p",
            time.constant(),
            mesh,
            fileAction::MUST_READ,
            fileAction::NO_WRITE
        )
    
    );

        foo(p);


   // double DT = tst2.lookup<double>("dt");
    // double a = tst3.lookup<double>("dt");
    // tensor b  = tst.lookup<tensor>("tensor1");
    // std::string c = tst2.lookup<std::string>("someString");
    // vector3 d = tst3.lookup<vector3>("vector2");

    // scalarField sf(10, DT);
    // vectorField vf(10, a);
    // tensorField tf(10, b);

    // std::cout << DT << std::endl;
    // std::cout << a << std::endl;
    // std::cout << b << std::endl;

    // std::cout << sf << std::endl;
    // std::cout << vf << std::endl;
    // std::cout << tf << std::endl;

    // std::cout << time.constant() << std::endl;
    // std::cout << time.system() << std::endl;
    // std::cout << time.runTime() << std::endl;

    std::cout << "I am here" << std::endl;

    return 0;
}
