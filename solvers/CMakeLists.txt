file(GLOB SRC_SOL src/*.cpp)
add_library(solvers ${SRC_SOL})

# add_library(solvers src/SGaussSiedel.cpp
#                     src/SJacobi.cpp       
#                     src/SSOR.cpp                 
#                     src/FVMatrixSolver.cpp
#             )

target_include_directories(solvers PUBLIC ../matFormats/include  
                                   PUBLIC ../core/include  
                                   PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
                          )                    