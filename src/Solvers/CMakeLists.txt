file(GLOB SRC_SOL src/*.cpp)
add_library(Solvers SHARED ${SRC_SOL})

# add_library(solvers src/SGaussSiedel.cpp
#                     src/SJacobi.cpp       
#                     src/SSOR.cpp                 
#                     src/FVMatrixSolver.cpp
#             )

target_include_directories(Solvers PUBLIC ../Matrix/include  
                                   PUBLIC ../Mesh/include  
                                   PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
                          )                    