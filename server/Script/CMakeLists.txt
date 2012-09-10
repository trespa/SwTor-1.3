cmake_minimum_required(VERSION 2.6)
include(FindBoost)


#name
project(Script)
set(LIBRARY_OUTPUT_PATH ../Bin/${CMAKE_BUILD_TYPE})


#files

find_package(
	Boost 
	1.48.0
	COMPONENTS serialization signals system thread filesystem date_time REQUIRED
)

message(
	STATUS
	${Boost_LIBRARIES}
)

SET(CMAKE_BUILD_TYPE "Release")

link_directories(${Boost_LIBRARY_DIRS} /usr/lib)
include_directories(${Boost_INCLUDE_DIRS} ./Src /usr/include/ ../Script/Src /usr/lib/jvm/java-6-openjdk/include)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O2 -std=c++0x")        ## Optimize
    set(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
endif()

file(
	GLOB_RECURSE
	source_files
	Src/*
)

# binary
add_library(
	Script
	SHARED
	${source_files}
)

target_link_libraries(
	Script
	${Boost_LIBRARIES} 
)
