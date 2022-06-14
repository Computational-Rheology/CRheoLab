file(GLOB SRC_MESH src/*.cpp)
add_library(Mesh SHARED ${SRC_MESH})

# add_library(core       src/Cell.cpp 
#                        src/Face.cpp 
#                        src/IODictionary.cpp 
#                        src/Mesh.cpp 
#                        src/Patch.cpp 
#                        src/Point.cpp 
#                        src/RunTime.cpp                          
# )       
        
target_include_directories(Mesh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)