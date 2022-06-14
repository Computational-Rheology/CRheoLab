file(GLOB SRC_MAT src/*.cpp)
add_library(Matrix SHARED ${SRC_MAT})

# add_library(matFormats src/csrSpmat.cpp 
#                        src/FVMatrix.cpp 
#                        src/lilSpmat.cpp 
#                        src/spmat.cpp    
#                        src/Reader.cpp 
#             )

target_include_directories(Matrix PUBLIC ../Mesh/include 
                                      PUBLIC ../Solvers/include 
                                      PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                          )                      