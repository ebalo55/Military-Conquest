cmake_minimum_required(VERSION 3.15)
project(MilitaryConquest)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(Tests)

set(SOURCES main.cpp Classes/Maps/Map.h Classes/Maps/AssetsMap.h Classes/Maps/AssetsMap.cpp Classes/Maps/MapEasy.h Classes/EventHandler.cpp Classes/EventHandler.h Classes/RenderHandler.cpp
        Classes/RenderHandler.h Classes/Maps/MapHard.h Classes/States/GameState.h Classes/States/windowSize.h Classes/Elements/ButtonRect.h Classes/Elements/ButtonRect.cpp
        Classes/Interface/Notifier.h Classes/States/DifficultState.h Classes/States/EnemyState.h Classes/States/MouseStates.h Classes/States/ObserversTypeId.h
        Classes/States/TurretState.h Classes/Observers/MouseClickObserver.h Classes/Observers/MouseHoverObserver.h Classes/Observers/MouseOutObserver.h Classes/Interface/Observer.h
        Classes/Interface/MouseObserver.h Classes/Interface/Button.h Classes/Interface/Event.h Classes/Events/StartButtonHover.h Classes/Events/StartButtonClick.h Classes/Events/DifficultButtonHover.h
        Classes/Events/DifficultEasyButtonClick.h Classes/Elements/Enemy.h Classes/Elements/Enemy.cpp Classes/Elements/EnemyGenerator.h Classes/Elements/EnemyGenerator.cpp Classes/Interface/Movement.h
        Classes/Observers/EnemyLPObserver.h Classes/Observers/TowerLPObserver.h Classes/Elements/Tower.h Classes/Elements/Tower.cpp Classes/Elements/Turret.h Classes/Elements/Turret.cpp Classes/Elements/TurretGenerator.h
        Classes/Elements/TurretGenerator.cpp Classes/Elements/ButtonIcon.cpp Classes/Elements/ButtonIcon.h Classes/Events/IconButtonHover.h Classes/Events/TurretMenuButtonClick.h Classes/Events/CraftTurretButtonClick.h
        Classes/Observers/MouseMotionObserver.h Classes/Interface/FakeButton.h Classes/Events/TurretPositioning.h Classes/Events/BuildTurret.h Classes/Events/PlacedTurretHover.h Classes/Events/PlacedTurretOut.h
        Classes/Maps/RenderableMap.cpp Classes/Maps/RenderableMap.h Classes/Elements/DrawableFactory.cpp Classes/Elements/DrawableFactory.h Classes/Events/PlacedTurretClick.h Classes/Events/TurretUpgrade.h
        Classes/Elements/Bullet.cpp Classes/Elements/Bullet.h Classes/Elements/WaveController.cpp Classes/Elements/WaveController.h Classes/Interface/Wave.h Classes/Interface/Random.h
        Classes/Interface/Achievement.h Classes/Observers/AchievementObserver.h Classes/Achievements/KilledEnemies.h Classes/Interface/AchievementNotifier.h Classes/Adapters/EnemyGeneratorAdapter.h
        Classes/Achievements/SurvivedWaves.h Classes/Adapters/TurretAdapter.h Classes/Parser/MapParser.h Classes/Parser/Config.h Classes/Parser/Config.cpp Classes/States/TurretStats.h Classes/States/EnemyStats.h Classes/States/AchievementInfos.h)

add_executable(MilitaryConquest ${SOURCES})
add_library(MilitaryConquest_Tests ${SOURCES})

find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)

target_link_libraries(MilitaryConquest sfml-graphics sfml-window sfml-system nlohmann_json::nlohmann_json)