template <typename vectorType>
template <typename primitiveType>
primitiveType Boundary<vectorType>::readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter)
{
    throw std::runtime_error("Not implemented");
}

template <>
template <>
double Boundary<scalarField>::readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter)
{
    return this->readScalarData(in_file,iss,line, lineCounter);
}


template <>
template <>
vector3 Boundary<vectorField>::readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter)
{
    return this->readVectorTensorData<vector3>(in_file, iss, line, lineCounter);
}

template <>
template <>
symmTensor Boundary<symmTensorField>::readData(std::ifstream &in_file, std::istringstream &iss, std::string &line, int &lineCounter)
{
    return this->readVectorTensorData<symmTensor>(in_file, iss, line, lineCounter);
}

template <>
template <>
tensor Boundary<tensorField>::readData(std::ifstream &in_file, std::istringstream &iss, std::string &line, int &lineCounter)
{
    return this->readVectorTensorData<tensor>(in_file, iss, line, lineCounter);
}






template <typename vectorType>
void Boundary<vectorType>::readBoundaryPatch(const std::string& patchName)
{
 
    // Create structure to store information
    // patchBoundaryDefinitions store;
    this->uniformField_=true;
  
    // File location path
    std::string fileLocation = this->path();

    // Passes the file location path into a ifsteam
    std::ifstream in_file(fileLocation.c_str());

    // Checks if file is to be open correctly
    if(!in_file.is_open())
    {
        std::cerr << "The input file was not open correctly!" << std::endl;
        //return 1;
    }

    // Line to store input from file
    std::string line;

    // Line counter for error reporting
    int lineCounter=0;

    // Sets a stringstream to get information from string
    std::istringstream iss (line);

    bool findBoundaryField = false;
    bool findPatch = false;
    bool endCycle = false; 

    // Read file
    while (!endCycle && !in_file.eof())
    { 
        // Updates lines 
        newLineAndUpdateSStream(in_file, iss, line, lineCounter);

        if (checkExactMatch(line, std::string("boundaryField")))
        {
            findBoundaryField = true;
            // Updates lines
            newLineAndUpdateSStream(in_file, iss, line, lineCounter);

            readCharacter(in_file, iss, '{', lineCounter);    

            while(!findPatch && !in_file.eof())
            {
                // Updates lines 
                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                // Found patch 
                if ( checkExactMatch(line, patchName) )
                {
                    findPatch=true;

                    // Get next line
                    newLineAndUpdateSStream(in_file, iss, line, lineCounter);
                    
                    // Check if '{' exists 
                    readCharacter(in_file, iss, '{', lineCounter);   

                    bool endInnerCycle = false;

                    while (!endInnerCycle)
                    {
                        // Get new line
                        newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                        // Get type
                        if (checkExactMatch(line, "type"))
                        {
                            // trip type
                            line = line.substr(line.find("type") + 4); 

                            // Check semicoln
                            checkSemiColon(in_file, line, lineCounter);

                            // Remove ';' at the end and white spaces
                            line.erase(std::remove(line.begin(), line.end(), ';'), line.end());
                            line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

                            // Store information into structure
                            this->type_ = line;

                            // Get new line
                            newLineAndUpdateSStream(in_file, iss, line, lineCounter);
                        }

                        // Get other patch input that is not the entry 'value' or 'type' or singleLined characters (e.g, }, ) , ...
                        if( !checkExactMatch(line, "value") && !checkExactMatch(line, "type") && (countCharactersInString(line) > 1) ) // need to add here the name of the other patches in the mesh..
                        {
                            // Check if ; it at the end of the sentance
                            checkSemiColon(in_file, line, lineCounter);

                            // Remove ';' at the end
                            line.erase(std::remove(line.begin(), line.end(), ';'), line.end());

                            // Split string by spaces
                            std::vector<std::string> tmp =  splitString(line, ' ');

                            // If there are more than 2 splits, warn the user (here for the time being... might change in the future)
                            if(tmp.size() > 2)
                            {
                                errorMessage(in_file, "More than two string ", lineCounter);
                            }

                            // store information in structure
                            this->otherInfo_.insert ( std::pair<std::string, std::string>(tmp[0] ,tmp[1] ) );
                            
                            // Get new line
                            //newLineAndUpdateSStream(in_file, iss, line, lineCounter);
                        }

                        // Get value
                        if( checkExactMatch(line, "value"))
                        {
                            if (checkExactMatch(line, "uniform"))
                            {
                                checkSemiColon(in_file, line, lineCounter);

                                // Strips the string from uniform onwards
                                line = line.substr(line.find("uniform") + 7); 

                                // update string stream
                                iss.clear();
                                iss.str(line);

                                // Create a primitiveType to store the data
                                typename vectorType::value_type dataToVector;

                                dataToVector = readData<typename vectorType::value_type>(in_file,iss, line, lineCounter);

                                // Push data to vector
                                this->definedValues_.push_back(dataToVector);

                                // Get new line
                                //newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                            } // If the internalField is non-uniform
                            else if (checkExactMatch(line, "nonuniform")) 
                            {
                                this->uniformField_=false;

                                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                                // Variable to store the number of points in the field
                                int nPointsInNonUniformField;

                                // Gets integer from string
                                iss >> nPointsInNonUniformField;

                                // If something is wrong, warn the user and shutdown the program
                                if (iss.fail())
                                {
                                    errorMessage(in_file, "Something is wrong with number of points in non-uniform field ", lineCounter);
                                }

                                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                                // check if parenthesis exists '('
                                readCharacter(in_file, iss, '(', lineCounter);   

                                // Resize the vector to accomudade the incoming data
                                this->definedValues_.resize(nPointsInNonUniformField);

                                // Loop to get the vector data
                                // Loop counter integer 
                                int i=0;

                                while (i < nPointsInNonUniformField)
                                {
                                    newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                                    this->definedValues_[i] = readData<typename vectorType::value_type>(in_file, iss, line, lineCounter);

                                    i++;
                                }

                                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                                // Check if ')' exists
                                readCharacter(in_file, iss, ')', lineCounter);   

                                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                                // Check if ';' exists
                                readCharacter(in_file, iss, ';', lineCounter);

                                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                            }
                        }

                        // If another curly brace is found it will shutdown the program
                        char c1;
                        iss >> c1;
                        if (!iss.fail() && c1 == '{')
                        {
                            std::string message = "There is no closing parenthesis, '}', in patch " + patchName + " ";
                            errorMessage(in_file, message, lineCounter);
                        }

                        if (!iss.fail() && c1 == '}')
                        {
                            // Exits inner while
                            endInnerCycle=true;
                        }
                    }
                }
            }


            if (!findPatch)
            {
                std::string message = "Patch " + patchName + " not found";
                errorMessage(in_file, message, 0, true);
            }

            if (this->type_.empty() || (this->definedValues_.size()==0 && ( (this->type_ != "empty") && (this->type_ != "symmetry")) ))
            {
                std::string message = "Problem in patch " + patchName ;
                errorMessage(in_file, message, 0, true);
            }

            // Catch closing of boundaryField

            bool endBoundaryField = false;
            while (!endBoundaryField && !in_file.eof())
            {
                // Updates lines 
                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                char c1;
                iss >> c1;
                if ( c1 == '}')
                {

                   endBoundaryField= true;
                    // Exits outer while
                    endCycle=true;
                }
                else
                {
                   // Loop until finding two consecutive } } 
                   bool findFirstClosingCurly =false;
                   bool findSecondClosingCurly =false;

                   while (!findSecondClosingCurly && !in_file.eof())
                   {
                        newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                        iss >> c1;

                        if ( !findFirstClosingCurly && c1 == '}')
                        {
                            findFirstClosingCurly = true;
                            newLineAndUpdateSStream(in_file, iss, line, lineCounter);
                            c1=' '; // reset char
                            
                        }

                        iss >> c1;
                        if ( findFirstClosingCurly &&  c1 == '}')
                        {
                            findSecondClosingCurly = true;
                            endBoundaryField = true;
                            endCycle=true;
                        }
                        else
                        {
                            findFirstClosingCurly =false;
                        }

                   }
                }

            }

            if (!endBoundaryField)
            {
                errorMessage(in_file, "Missing '}' at the end of boundaryField", lineCounter, true);
            }
       
        }

        if ( !findBoundaryField && in_file.eof() )
        {
            std::string message = "Keyword 'boundaryField is not defined";
            errorMessage(in_file, message, 0, true);
        }

    }

    // Close the file
    in_file.close();

}
