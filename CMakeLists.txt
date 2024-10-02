cmake_minimum_required(VERSION 3.10.2)
project(proxyBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)

SET(HEADERS ./src/ProxyBot.hpp ./src/ProxyBot.hpp)
SET(SOURCES ./src/ProxyBot.cpp ./src/main.cpp)

include(GNUInstallDirs)

find_package(Threads REQUIRED)
find_package(CURL)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_executable(proxyBot ${HEADERS} ${SOURCES})
install(TARGETS proxyBot DESTINATION ../../${CMAKE_BINARY_DIR})

target_link_libraries(proxyBot C:/Work/libs/vcpkg/installed/x64-windows/lib/TgBot.lib #[[Change this path to local TgBot.lib]] ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})