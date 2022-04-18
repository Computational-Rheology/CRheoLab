
template <typename vectorType>
template <typename primitiveType>
primitiveType VolField<vectorType>::readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter)
{
    throw std::runtime_error("Not implemented");
}

template <>
template <>
double VolField<scalarField>::readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter)
{
    return this->readScalarData(in_file,iss,line, lineCounter);
}


template <>
template <>
vector3 VolField<vectorField>::readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter)
{
    return this->readVectorTensorData<vector3>(in_file, iss, line, lineCounter);
}

template <>
template <>
symmTensor VolField<symmTensorField>::readData(std::ifstream &in_file, std::istringstream &iss, std::string &line, int &lineCounter)
{
    return this->readVectorTensorData<symmTensor>(in_file, iss, line, lineCounter);
}

template <>
template <>
tensor VolField<tensorField>::readData(std::ifstream &in_file, std::istringstream &iss, std::string &line, int &lineCounter)
{
    return this->readVectorTensorData<tensor>(in_file, iss, line, lineCounter);
}

template< typename vectorType>
vectorType VolField<vectorType>::readInternalField()
{
    // File location path
    std::string fileLocation = this->Path() + this->Name();

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

    // Variable to store the information
    vectorType store;

    // stringstream to get data out of string
    std::istringstream iss (line);

    // Line counter for error reporting
    int lineCounter=0;

    // Read file
    while ( !in_file.eof() )
    { 
        // Updates lines 
        newLineAndUpdateSStream(in_file, iss, line, lineCounter);

        // Check if line has the exact match for the keyWord. 
        if ( checkExactMatch(line, std::string("internalField")) )
        {
            // Check if internalField is "uniform"
            if (checkExactMatch(line, "uniform"))
            {
                // Check if ; it at the end of the sentance
                checkSemiColon(in_file, line, lineCounter);

                // Strips the string from uniform onwards
                line = line.substr(line.find("uniform") + 7); 

                // Create a primitiveType to store the data
                typename vectorType::value_type dataToVector;

                dataToVector = readData<typename vectorType::value_type>(in_file,iss,line, lineCounter);
       
                // Push data to vector
                store.push_back(dataToVector);

                // Exits the loop (not necessary to continue looking into the file)
                break;

            } // If the internalField is non-uniform
            else if (checkExactMatch(line, "nonuniform")) 
            {
                // Updates lines 
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

                // Updates lines 
                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                readCharacter(in_file, iss, '(', lineCounter);                

                // Resize the vector to accomudade the incoming data
                store.resize(nPointsInNonUniformField);

                // Loop to get the vector data
                // Loop counter integer 
                int i = 0;
                
                while (i < nPointsInNonUniformField)
                {
                    // Updates lines 
                    newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                    store[i] = readData<typename vectorType::value_type>(in_file,iss, line, lineCounter);

                    i++;
                }

                // Updates lines 
                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                readCharacter(in_file, iss, ')', lineCounter);    

                // check if ';' exists at the end
                // Updates lines 
                newLineAndUpdateSStream(in_file, iss, line, lineCounter);

                readCharacter(in_file, iss, ';', lineCounter);    

                // Breaks the loop once it is finished
                break;
            }
        }
    }

    if (in_file.eof() )
    {
        std::string message = "Keyword 'internalField not defined in " + this->Name();
        errorMessage(in_file, message, 0, true);
    }

    // Close the file
    in_file.close();

    return store;
}












