set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "../${PROJECT_SOURCE_DIR}/CMake")

add_subdirectory(googletest)

set(gtest_DIR, googletest/)
include_directories(${gtest_DIR}/include ${gtest_DIR})

set(SOURCES_TESTS mainTests.cpp MapTests.h DrawableFactoryTest.h EnemyTests.h TurretTests.h parserTests.h battleTest.h ConfigParserTests.h)

add_executable(test ${SOURCES_TESTS})
find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)

target_link_libraries(test gtest gtest_main MilitaryConquest_Tests sfml-graphics sfml-window sfml-system)