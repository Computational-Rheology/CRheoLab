#include "IODictionary.h"
#include<typeinfo>
#include "mathOperations.h"

#include <map>


template<typename vectorType>
struct patchBoundaryConditions
{
            std::string type;
            vectorType fieldValue;
            std::map<std::string, std::string> otherInfo;  
};


template<typename vectorType>
inline std::ostream& operator<<(std::ostream& out_data, patchBoundaryConditions<vectorType>& pBC)
{
    out_data<<"\t\ttype\t\t\t"<<pBC.type<<';'<< std::endl;
    if(pBC.type != "empty") // if the pach is non-empty  then write the otherInfo and the field value 
    {

        std::map<std::string, std::string>::iterator it;
        for (it = pBC.otherInfo.begin(); it != pBC.otherInfo.end();it++)
        {
           out_data << "\t\t" << it->first << "\t\t\t" << it->second << ";" << std::endl;
        }

        int aux = -1; // auxilliary variable
        // Assingning a given value to aux according to the type of the InternalField.
        // Acting almost as a precondition of a two-step verification of data type.
        // In contrary of using if constexp(....), this aprroach doesn't give erro while checking the type of the vectorTYpe
        if (typeid(pBC.fieldValue).name() == typeid(scalarField).name()) aux = 0;
        if (typeid(pBC.fieldValue).name() == typeid(vectorField).name()) aux = 1;
        if (typeid(pBC.fieldValue).name() == typeid(tensorField).name()) aux = 2;
        if (typeid(pBC.fieldValue).name() == typeid(symmTensorField).name()) aux = 3;   


        
        switch (aux)
        {
            case 0:  //scalarField 
                if (pBC.fieldValue.size()>1)// Nonuniform scalarFields
                {
                     out_data<<"\t\tvalue\t\t\tnonuniform List<scalar>"<<std::endl;
                     out_data<<pBC.fieldValue.size() <<std::endl;
                     out_data<<pBC.fieldValue<<std::endl;
                     out_data<<";"<<std::endl;
                }
                else
                {
                    if (pBC.fieldValue.size()==1) //Uniform scalarFields
                    {
                        out_data<<"\t\tuniform\t\t\t"<<pBC.fieldValue[0]<<";"<<std::endl;
                    }
                    else //empty scalarFields
                    {
                        out_data<<"\t\tuniform\t\t\t 0;"<<std::endl;
                    }
            
               } 
            break;

            //For vectorFields, tensorFields, symmTensorFields 
            case 1: //vectorField
            case 2: //or a tensorField
            case 3: //or symmTensorField
                if(pBC.fieldValue.size()>1) 
                {
                    switch (aux)
                    {
                        case 1: // vectorField case
                            out_data<<"\t\tvalue\t\t\tnonuniform List<vector>"<<std::endl;
                        break;
                        case 2: //tensorField case
                             out_data<<"\t\tvalue\t\t\tnonuniform List<tensor>"<<std::endl;           
                        break;
                        case 3: //symmTensorField case
                            out_data<<"\t\tvalue\t\t\tnonuniform List<symmTensor>"<<std::endl;  
                        break;           
                        default:
                            std::cerr<<"An error ocurred will writing the field values for nonuniform fields!!!"<<std::endl;
                        break;
                    }  

                    out_data<<pBC.fieldValue.size() <<std::endl;
                    out_data<<pBC.fieldValue <<std::endl;
                    out_data<<";"<<std::endl;

                }
               else
                {
                    if(pBC.fieldValue.size() == 1) // fields with only 1 element
                    {
                       out_data<<"\t\tuniform\t\t\t"<<pBC.fieldValue[0]<<";"<<std::endl;
                    }
                    else
                     {
                        switch (aux)
                        {
                            case 1:
                              out_data<<"\t uniform (0 0 0);\n"<<std::endl;
                            break;
                            case 2:
                              out_data<<"\t uniform (0 0 0 0 0 0 0 0 0);\n"<<std::endl;
                            break;
                            case 3:
                            out_data<<"\t uniform (0 0 0 0 0 0);\n"<<std::endl;
                            break;
               
                            default:
                            std::cerr<<"An error ocurred will writing an empty field!!!"<<std::endl;
                             break;
                        }
                    }
               }
                

            break;
        
            default:

                std::cerr<<"An error ocurred while writing the field values!!!"<<std::endl;
            break;
          }
          
    } 
    
    return out_data;

}

typedef std::vector<std::string>     patchList;


template<typename vectorType>
struct boundaryField
{
    patchList  patchs;
    std::vector<patchBoundaryConditions<vectorType>> patchBCs;
};

template<typename vectorType>
inline std::ostream& operator<<(std::ostream& out_data, boundaryField<vectorType>& bField)
{
    out_data<<"boundaryField"<<std::endl;
    out_data<<"{"<<std::endl;
    for(unsigned int i = 0; i < bField.patchs.size();i++)
    {
        out_data<<"\t" << bField.patchs[i] << std::endl;
        out_data<<"\t{"<<std::endl;
        out_data<< bField.patchBCs[i]<<std::endl;
        out_data<<"\t}\n"<<std::endl;
    }
    out_data<<"}"<<std::endl;
    return out_data;

}

template<typename vectorType>
struct internalField
{
    int size ;
    vectorType fieldValue; 
};


template<typename vectorType>
inline std::ostream& operator<<(std::ostream& out_data, internalField<vectorType>& intField)
{
        int aux = -1; // auxilliary variable
        // Assingning a given value to aux according to the type of the InternalField.
        // Acting almost as a precondition of a two-step verification of data type.
        // In contrary of using if constexp(....), this aprroach doesn't give erro while checking the type of the vectorTYpe
        if (typeid(intField.fieldValue).name() == typeid(scalarField).name()) aux = 0;
        if (typeid(intField.fieldValue).name() == typeid(vectorField).name()) aux = 1;
        if (typeid(intField.fieldValue).name() == typeid(tensorField).name()) aux = 2;
        if (typeid(intField.fieldValue).name() == typeid(symmTensorField).name()) aux = 3;   


        
        switch (aux)
        {
            case 0:  //scalarField 
                if (intField.fieldValue.size()>1)// Nonuniform scalarFields
                {
                     out_data<<"\tinternalField\tnonuniform List<scalar>"<<std::endl;
                     out_data<<intField.fieldValue.size() <<std::endl;
                     out_data<<intField.fieldValue<<std::endl;
                     out_data<<";"<<std::endl;
                }
                else
                {
                    if (intField.fieldValue.size()==1) //Uniform scalarFields
                    {
                        out_data<<"\t\tuniform\t\t\t"<<intField.fieldValue[0]<<";"<<std::endl;
                    }
                    else //empty scalarFields
                    {
                        out_data<<"\t\tuniform\t\t\t 0;"<<std::endl;
                    }
            
               } 
            break;

            //For vectorFields, tensorFields, symmTensorFields 
            case 1: //vectorField
            case 2: //or a tensorField
            case 3: //or symmTensorField
                if(intField.fieldValue.size()>1) 
                {
                    switch (aux)
                    {
                        case 1: // vectorField case
                            out_data<<"\tinternalField\tnonuniform List<vector>"<<std::endl;
                        break;
                        case 2: //tensorField case
                             out_data<<"\tinternalField\tnonuniform List<tensor>"<<std::endl;           
                        break;
                        case 3: //symmTensorField case
                            out_data<<"\tinternalField\tnonuniform List<symmTensor>"<<std::endl;  
                        break;           
                        default:
                            std::cerr<<"An error ocurred will writing the field values for nonuniform fields!!!"<<std::endl;
                        break;
                    }  

                    out_data<<intField.fieldValue.size() <<std::endl;
                    out_data<<intField.fieldValue <<std::endl;
                    out_data<<";"<<std::endl;

                }
               else
                {
                    if(intField.fieldValue.size() == 1) // fields with only 1 element
                    {
                       out_data<<"\tinternalField\tuniform"<<intField.fieldValue[0]<<";"<<std::endl;
                    }
                    else
                     {
                        switch (aux)
                        {
                            case 1:
                              out_data<<"\tinternalField\tuniform (0 0 0);\n"<<std::endl;
                            break;
                            case 2:
                              out_data<<"\tinternalField\tuniform (0 0 0 0 0 0 0 0 0);\n"<<std::endl;
                            break;
                            case 3:
                            out_data<<"\tinternalField\t uniform  (0 0 0 0 0 0);\n"<<std::endl;
                            break;
               
                            default:
                            std::cerr<<"An error ocurred will writing an empty field!!!"<<std::endl;
                             break;
                        }
                    }
               }
                

            break;
        
            default:

                std::cerr<<"An error ocurred while writing the field values!!!"<<std::endl;
            break;
          }
          
    
    return out_data;

}