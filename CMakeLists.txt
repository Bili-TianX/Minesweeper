cmake_minimum_required(VERSION 3.25)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia Sql REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h" "assets/assets.qrc" "assets/exe.rc")
if (${CMAKE_BUILD_TYPE} MATCHES Release)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
elseif (${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_executable(${PROJECT_NAME} ${SOURCES})
endif ()
target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia Qt5::Sql)