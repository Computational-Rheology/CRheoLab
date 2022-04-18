file(GLOB SRC_MAT src/*.cpp)
add_library(matFormats ${SRC_MAT})

# add_library(matFormats src/csrSpmat.cpp 
#                        src/FVMatrix.cpp 
#                        src/lilSpmat.cpp 
#                        src/spmat.cpp    
#                        src/Reader.cpp 
#             )

target_include_directories(matFormats PUBLIC ../core/include 
                                      PUBLIC ../solvers/include 
                                      PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                          )                      