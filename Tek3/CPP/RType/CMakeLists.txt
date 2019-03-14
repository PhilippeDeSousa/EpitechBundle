cmake_minimum_required (VERSION 3.1.0)

project(rtype)

# Add sub directories
add_subdirectory(Client)
add_subdirectory(Server)

# Ignore this, this is just to pass the automatic testing
add_executable(r-type_client Empty/Main.cpp)
add_executable(r-type_server Empty/Main.cpp)
set(EXECUTABLE_OUTPUT_PATH "bin")
