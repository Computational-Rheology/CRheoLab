add_executable(CRheo CRheo.cpp)

# #ifdef USE_OPTIONAL_LIB
#     target_link_directories(${PROJECT_NAME} PRIVATE core matFormats)

#     target_link_libraries(CRheo core  matFormats)
# #else
#     target_link_libraries(CRheo core  matFormats solvers)
#     target_link_directories(${PROJECT_NAME} PRIVATE core matFormats solvers)
# #endif

target_link_directories(${PROJECT_NAME} PRIVATE Mesh Matrix Solvers)
target_link_libraries(CRheo Mesh Matrix Solvers)