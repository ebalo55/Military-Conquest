set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "../${PROJECT_SOURCE_DIR}/CMake")

add_subdirectory(googletest)

set(gtest_DIR, googletest/)
include_directories(${gtest_DIR}/include ${gtest_DIR})

set(SOURCES_TESTS mainTests.cpp MapTests.h)

add_executable(runAllTests ${SOURCES_TESTS})
find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)

target_link_libraries(runAllTests gtest gtest_main TD_TowerDefense_SFML_Tests sfml-graphics sfml-window sfml-system)