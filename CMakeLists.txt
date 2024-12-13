cmake_minimum_required(VERSION 3.10.2)
project(proxyBot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)

SET(HEADERS ./src/ProxyBot.hpp ./src/ProxyBot.hpp)
SET(SOURCES ./src/ProxyBot.cpp ./src/main.cpp)

set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/3rdparty")

include(FetchContent)
FetchContent_Declare(
  tgbot-cpp
  GIT_REPOSITORY https://github.com/reo7sp/tgbot-cpp.git
  GIT_TAG        v1.8
)

FetchContent_MakeAvailable(tgbot-cpp)

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
                                
target_link_libraries(proxyBot ${CMAKE_BINARY_DIR}/3rdparty/tgbot-cpp-build/TgBot.lib
                 ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${CURL_LIBRARIES}  Boost::system)