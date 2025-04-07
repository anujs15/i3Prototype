cmake_minimum_required(VERSION 3.14)

project(i3KeyboardInterceptor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Network Widgets REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/i3connector.h
        src/i3connector.cpp
        src/keyboardinterceptor.h
        src/keyboardinterceptor.cpp
        resources/qml.qrc
)

add_executable(i3KeyboardInterceptor ${PROJECT_SOURCES})

target_compile_definitions(i3KeyboardInterceptor
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(i3KeyboardInterceptor
  PRIVATE Qt5::Core Qt5::Quick Qt5::Network Qt5::Widgets)
