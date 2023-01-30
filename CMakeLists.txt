cmake_minimum_required(VERSION 3.10)

# set the project name
project(igbenchmark VERSION 1.0.0.1 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

#configure_file(igbenchmark.h.in igbenchmark.h)

set(sources	
    igbenchmark.cpp)

set(headers  
    igbenchmark.h)

add_library(igbenchmark SHARED ${sources} ${headers})

add_compile_definitions(IGBENCHMARK_EXPORTS)

target_link_libraries(igbenchmark PRIVATE Qt${QT_VERSION_MAJOR}::Core)

#SET_TARGET_PROPERTIES(igbenchmark PROPERTIES LINK_FLAGS "/versionflags")

install(TARGETS igbenchmark DESTINATION bin)


