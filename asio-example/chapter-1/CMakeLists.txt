
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
set(APP Creating_endpoint_Client)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

set(APP Creating_endpoint_Server)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

set(APP Creating_an_active_socket_TCP_IPv4)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

set(APP Creating_an_active_socket_TCP_IPv4_open_in_constructor)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

set(APP Creating_a_passive_socket)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

set(APP Resolving_a_DNS_name_TCP)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

set(APP Resolving_a_DNS_name_UDP)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

set(APP Binding_a_socket_TCP_passive)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

set(APP Binding_a_socket_UDP_active)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

set(APP Connecting_a_socket)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

set(APP Connecting_a_socket_DNS_name)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

set(APP Accepting_a_connection)
add_executable(${APP} ${APP}.cpp)
target_include_directories(${APP} PRIVATE ${INC})
target_link_libraries(${APP} PRIVATE ${LIB})
unset(APP)

