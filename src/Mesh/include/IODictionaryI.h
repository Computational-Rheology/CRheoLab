
template <typename primitiveType>
primitiveType IODictionary::readVectorTensorData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int lineCounter)
{
    char c1; // Variable to catch "(" in vectors and tensors
    char c2; // Variable to catch ")" in vectors and tensors

    // Store data
    primitiveType vectorData {0};

    line = stripComments(in_file, line, lineCounter);

    // update string stream
    iss.clear();
    iss.str(line);

    // Catch first parenthesis
    iss >> c1;
    if (iss.fail() || c1 != '(')
    {
        vectorFormatError(in_file, lineCounter);
    }

    // Catch vector/tensor data
    for (unsigned int i=0; i<vectorData.size(); i++)
    {
        iss >> vectorData[i];
        // If something is wrong with string stream warn the user
        if (iss.fail())
        {
            vectorFormatError(in_file, lineCounter);
        }
    }

    // Catch second parenthesis
    iss >> c2;
    if (iss.fail() || c2 != ')')
    {
        vectorFormatError(in_file, lineCounter);
    }

    return vectorData;
}
