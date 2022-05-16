
template< typename T>
T& Mesh::lookup(const std::string& seeking) const
{
    const std::vector <IOObject*>& db  = dataBase();
    auto found = std::find_if(db.begin(),db.end(), 
                              [seeking](IOObject* item)
                              {
                                return item->name() == seeking;
                              });  
    
    // find_if requires one argument to its test function because it has to test each element in the collection in turn. 
    // To put more paramters we will use a lambda funtion:
    
    if (found != db.end())
    { // found it
        // convert to A<int>
        T* temp = dynamic_cast<T*>(*found);

        if (temp) // dynamic _cast returns nullptr on failure.
        { // successful conversion
            return *temp; // return it.
        }
        throw std::runtime_error("wrong type"); // What we found isn't the desired type
    }
    throw std::runtime_error("not found"); // Couldn't find a match
}

