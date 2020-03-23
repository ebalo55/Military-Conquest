cmake_minimum_required(VERSION 3.15)
project(TD_TowerDefense_SFML)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES main.cpp Classes/Maps/Map.h Classes/Maps/AssetsMap.h Classes/Maps/AssetsMap.cpp Classes/Maps/MapEasy.h Classes/EventHandler.cpp Classes/EventHandler.h Classes/RenderHandler.cpp
        Classes/RenderHandler.h Classes/Maps/MapHard.h Classes/States/GameState.h Classes/States/windowSize.h Classes/Elements/ButtonRect.h Classes/Elements/ButtonRect.cpp
        Classes/Interface/Notifier.h Classes/States/DifficultState.h Classes/States/EnemyState.h Classes/States/MouseStates.h Classes/States/ObserversTypeId.h
        Classes/States/TurretState.h Classes/Observers/MouseClickObserver.h Classes/Observers/MouseHoverObserver.h Classes/Observers/MouseOutObserver.h Classes/Interface/Observer.h
        Classes/Interface/MouseObserver.h Classes/Interface/Button.h Classes/Interface/Event.h Classes/Events/StartButtonHover.h Classes/Events/StartButtonClick.h Classes/Events/DifficultButtonHover.h
        Classes/Events/DifficultEasyButtonClick.h Classes/Elements/Enemy.h Classes/Elements/Enemy.cpp Classes/Elements/EnemyGenerator.h Classes/Elements/EnemyGenerator.cpp Classes/Interface/Movement.h)

add_executable(TD_TowerDefense_SFML ${SOURCES})

find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)

target_link_libraries(TD_TowerDefense_SFML sfml-graphics sfml-window sfml-system)