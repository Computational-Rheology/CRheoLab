cmake_minimum_required(VERSION 3.16.3)

project(CRheo)

add_subdirectory(core)

add_subdirectory(app)
add_subdirectory(matFormats)

option(USE_OPTIONAL_LIB "An option to select or de-select a library." ON)
if(USE_OPTIONAL_LIB)
    add_subdirectory(solvers)
endif()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS filesystem) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})  
    target_link_libraries(${PROJECT_NAME}  ${Boost_LIBRARIES})
endif()
include(InstallRequiredSystemLibraries)
# set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")


# install(TARGETS ${PROJECT_NAME} DESTINATION bin)
# include(CPack)