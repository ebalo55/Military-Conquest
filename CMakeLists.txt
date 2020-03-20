cmake_minimum_required(VERSION 3.15)
project(TD_TowerDefense_SFML)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES main.cpp Classes/Maps/Map.h Classes/Maps/AssetsMap.h Classes/Maps/AssetsMap.cpp Classes/Maps/MapEasy.h Classes/EventHandler.cpp Classes/EventHandler.h Classes/RenderHandler.cpp Classes/RenderHandler.h Classes/Maps/MapHard.h)

add_executable(TD_TowerDefense_SFML ${SOURCES})

find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)

target_link_libraries(TD_TowerDefense_SFML sfml-graphics sfml-window sfml-system)