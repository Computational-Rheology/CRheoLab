

template <typename T>
T Dictionary::lookup(const std::string& keyWord) const
{
    for(unsigned int i = 0; i<localData_.size(); i++) 
    {
        std::string line = localData_[i];

        if (checkExactMatch(line, keyWord))
        {
            // Strip keyword
            stripString(line, keyWord);

            // Check for semicolon
            if ((line.find( ';' ) == std::string::npos))
            {
                throw std::runtime_error("Missing ';' in " + localData_[i]);
            }

            // Strip semicolon
            stripString(line, ";");

            // Collect data
            T data;

            std::istringstream iss(line);
            
            iss >> data;

            // If operation failed or there are more data types in the same string. 
            // Shutdown the program
            if (iss.fail() || iss >> data)
            {
                throw std::runtime_error("Could not retrieve data type from "  + localData_[i]);
            }

            return data;
        }
    } 

    throw std::runtime_error("Could not retrieve data type");
}
