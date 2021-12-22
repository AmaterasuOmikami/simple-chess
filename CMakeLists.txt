cmake_minimum_required(VERSION 3.21)
project(GUI)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -s -O3")
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/icon.rc")

# SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics window audio system REQUIRED)

add_executable(${PROJECT_NAME}
        WIN32
        ${APP_ICON_RESOURCE_WINDOWS}
        src/main.cpp
        src/menu.cpp
        src/menu.hpp
        src/button.cpp
        src/button.hpp
        src/game.cpp
        src/game.hpp
        src/settings.cpp
        src/settings.hpp
        src/promotion.cpp
        src/promotion.hpp
        src/message.cpp
        src/message.hpp
        src/engine.hpp
        src/engine.cpp)

# SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-audio sfml-system)

# Chsmv
include_directories(C:/programming/chess/chsmv/include)
target_link_libraries(${PROJECT_NAME} C:/programming/chess/chsmv/build/libchsmv-lib.a)