cmake_minimum_required(VERSION 2.8.11)

project(morse_translator)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED Qml Quick Gui)

qt5_add_resources(qml_QRC src/qml.qrc)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Morse.cpp
    src/Morse.h
    ${qml_QRC})

target_link_libraries(${PROJECT_NAME} Qt5::Qml Qt5::Quick)
