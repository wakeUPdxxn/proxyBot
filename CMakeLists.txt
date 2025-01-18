cmake_minimum_required(VERSION 3.10.2)
project(proxyBot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)

SET(HEADERS ./src/ProxyBot.hpp ./src/ProxyBot.hpp ./src/IPC.hpp)
SET(SOURCES ./src/ProxyBot.cpp ./src/main.cpp ./src/IPC.cpp)

find_package(Threads REQUIRED)
find_package(CURL)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tgbot-cpp/include)
include_directories(${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    add_definitions(-DHAVE_CURL)
endif()

add_subdirectory(tgbot-cpp)

add_executable(proxyBot ${HEADERS} ${SOURCES})

target_link_libraries(proxyBot ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${CURL_LIBRARIES} ${BOOST_LIBRARIES}
    ${CMAKE_CURRENT_BINARY_DIR}/tgbot-cpp/TgBot.lib)

include(GNUInstallDirs)
install(TARGETS proxyBot DESTINATION ${CMAKE_INSTALL_BINDIR})
                                