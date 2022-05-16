
#include "Mesh.h"
#include "RunTime.h"
#include "IODictionary.h"
#include "VolField.h"
#include "IOObject.h"
#include "dictionary.h"



int main()
{
    


 // const dictionary& tst = myDict.subDict("subDict");
   // const dictionary& tst2 = myDict.subDict("subDict").subDict("three");


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

    RunTime time;
    Mesh mesh(time);


       dictionary myDict1
    (
        IOObject
        (
            "transportProperties",
            time.constant(),  // "/home/ricardo/CRheoLab_dev_v8/run/constant/",
            mesh,
            fileAction::MUST_READ,
            fileAction::NO_WRITE
        )
    );

        dictionary myDict2
    (
        IOObject
        (
            "transportProperties 2",
            time.constant(),  // "/home/ricardo/CRheoLab_dev_v8/run/constant/",
            mesh,
            fileAction::MUST_READ,
            fileAction::NO_WRITE
        )
    );

    VolField<std::vector<double>> p 
    (
        IOObject
        (
            "p",
            time.timeName(),
            mesh,
            fileAction::MUST_READ,
            fileAction::NO_WRITE
        )

    );




    std::cout << "I am here" << std::endl;


    return 0;
}
