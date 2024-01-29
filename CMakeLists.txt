cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

# add_subdirectory(Application)
add_subdirectory(external)
add_subdirectory(Tests)
add_subdirectory(Common)
# add_subdirectory(Map)
add_subdirectory(TestApp)
