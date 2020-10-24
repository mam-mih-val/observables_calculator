cmake_minimum_required(VERSION 3.15)
project(ObservablesCalculator)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
list(APPEND CMAKE_PREFIX_PATH $ENV{QnTools_HOME})
list(APPEND CMAKE_PREFIX_PATH ${QnTools_HOME})

find_package(ROOT REQUIRED COMPONENTS RIO Tree)
find_package(QnTools REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall")
include(${ROOT_USE_FILE})

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${ROOT_INCLUDE_DIRS}
        ${QnTools_INCLUDE_DIR}/QnTools
)
link_directories(
        ${CMAKE_SOURCE_DIR}
        ${QnTools_LIBRARY_DIR}
)

set(SOURCES
        src/file_manager.cc
        src/method_of_3se.cc
        )

add_executable(flow src/calculate.cc ${SOURCES})
target_link_libraries(flow QnTools::Base ${ROOT_LIBRARIES})