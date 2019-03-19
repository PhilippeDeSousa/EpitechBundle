cmake_minimum_required(VERSION 2.8.12)
project(server C CXX)
#add_definitions("-std=c++1z")

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W0" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Werror")
endif()

if(WIN32)
	set(SYSTEM windows)
	set(EXECUTABLE_OUTPUT_PATH ../)
#	add_definitions(-D_WIN32_WINNT=0x0501)
else(WIN32)
	set(SYSTEM linux)
endif(WIN32)

## --- CONAN SETUP ---

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

## --- !CONAN SETUP ---

## --- ADD EXECUTABLE ---

set(PROJECT_SOURCE_DIR .)
set(SHARED_DIR ../Shared)

include_directories(    ${SHARED_DIR}/Inc 
                        ${SHARED_DIR}/${SYSTEM}
                        ${PROJECT_DIR}/Inc
                        ${PROJECT_DIR}/Inc/${SYSTEM} 
                        )

FILE(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/Src/*.cpp)
FILE(GLOB SHARED_SRC_FILES ./Shared/Src/*.cpp)
add_executable( ${PROJECT_NAME}
                ${SRC_FILES}
                ${SHARED_SRC_FILES}
                )

## --- !ADD EXECUTABLE ---

## --- LINK ---

target_link_libraries(  ${PROJECT_NAME}
                        ${CONAN_LIBS}
                        )
## --- !LINK ---
