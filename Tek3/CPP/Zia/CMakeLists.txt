cmake_minimum_required (VERSION 3.1.0)

project (zia_project CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SRCS "src/*.cpp")
if (UNIX)
set(CMAKE_CXX_FLAGS_DEBUG "-Wno-parentheses -Wall -Wextra -O3 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -O3")
endif (UNIX)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

find_package(Boost 1.67)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
add_executable(zia ${SRCS} ${APIHDRS} ${HDRS})
target_include_directories(zia PRIVATE "./include" ${Boost_INCLUDE_DIRS})
target_include_directories(zia PRIVATE "./zia-api" ${Boost_INCLUDE_DIRS})
target_include_directories(zia PRIVATE "./discord-rpc/include" ${Boost_INCLUDE_DIRS})
if (UNIX)
target_link_libraries(zia ${CONAN_LIBS} ${Boost_LIBRARIES} discord-rpc stdc++fs dl)
elseif (WIN32)
target_link_libraries(zia ${CONAN_LIBS} ${Boost_LIBRARIES} discord-rpc)
endif (UNIX)

add_custom_command(TARGET zia
                   POST_BUILD
                   COMMAND cp -r "bin/zia*" "..")
