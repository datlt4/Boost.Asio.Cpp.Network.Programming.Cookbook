
cmake_minimum_required(VERSION 3.10.2)

project(network LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# Boost
find_package(Boost 1.77.0 REQUIRED filesystem program_options regex timer chrono)
set(INC ${INC} ${Boost_INCLUDE_DIR})
set(LIB ${LIB} ${Boost_LIBRARIES})
set(LIB ${LIB} -lboost_system -lboost_thread -lboost_filesystem -lpthread)

# Message
message(STATUS "Include directories: ${INC}")
message(STATUS "Source directories:  ${SRC}")
message(STATUS "Libray directories:  ${LIB}")

# Add sources
set(APP SyncTCPClient)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

# set(APP AsyncTCPClient)
# add_executable(${APP} ${APP}.cpp)
# target_include_directories(${APP} PRIVATE ${INC})
# target_link_libraries(${APP} PRIVATE ${LIB})
# unset(APP)

# set(APP AsyncTCPClientMT)
# add_executable(${APP} ${APP}.cpp)
# target_include_directories(${APP} PRIVATE ${INC})
# target_link_libraries(${APP} PRIVATE ${LIB})
# unset(APP)

# set(APP SyncUDPClient)
# add_executable(${APP} ${APP}.cpp)
# target_include_directories(${APP} PRIVATE ${INC})
# target_link_libraries(${APP} PRIVATE ${LIB})
# unset(APP)
