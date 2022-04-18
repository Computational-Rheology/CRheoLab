file(GLOB SRC_CORE src/*.cpp)
add_library(core ${SRC_CORE})

# add_library(core       src/Cell.cpp 
#                        src/Face.cpp 
#                        src/IODictionary.cpp 
#                        src/Mesh.cpp 
#                        src/Patch.cpp 
#                        src/Point.cpp 
#                        src/RunTime.cpp                          
# )       
        
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)