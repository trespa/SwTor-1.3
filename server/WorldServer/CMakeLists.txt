cmake_minimum_required(VERSION 2.6)
include(FindBoost)


#name
project(WorldServer)
set(EXECUTABLE_OUTPUT_PATH ../Bin/${CMAKE_BUILD_TYPE})


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

SET(CMAKE_BUILD_TYPE "DEBUG")

link_directories(${Boost_LIBRARY_DIRS} /usr/lib ../Bin/  /usr/local/lib/)
include_directories(${Boost_INCLUDE_DIRS} ./Src /usr/include/ /usr/include/crypto++/ ../Framework/Src  /usr/local/include /usr/local/include/bullet)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O2 -std=c++0x")        ## Optimize
   # set(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
endif()

file(
	GLOB_RECURSE
	source_files
	Src/*
)

# binary
add_executable(
	WorldServer
	${source_files}
)

target_link_libraries(
	WorldServer
	${Boost_LIBRARIES} odbc Framework BulletDynamics BulletCollision LinearMath
)
