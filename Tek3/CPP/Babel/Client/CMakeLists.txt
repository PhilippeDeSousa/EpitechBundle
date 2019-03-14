project(client)
cmake_minimum_required(VERSION 3.1.0)
#add_definitions("-fPIC")
set(CMAKE_CXX_STANDARD 17)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
# Auto link Ressources (.qrc)
#set(CMAKE_AUTORCC ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/bin/qt.conf "[Paths]\nPrefix = ")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/bin/qt.conf ${CONAN_QT_ROOT})

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})

FILE(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
#FILE(GLOB RCC_FILES ${PROJECT_SOURCE_DIR}/*.qrc)

add_executable(     ${PROJECT_NAME}
                    ${SRC_FILES}
#                    ${RCC_FILES}
                    )

target_link_libraries(  ${PROJECT_NAME}
                        ${CONAN_LIBS}
                        Qt5::Core
                        Qt5::Widgets
                        Qt5::Network
                        )
