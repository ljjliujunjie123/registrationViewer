cmake_minimum_required(VERSION 3.20)
project(registrationViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/zzy/Qt/5.15.2/clang_64")
#set(CMAKE_PREFIX_PATH "E:/QT/5.15.2/mingw81_64")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
aux_source_directory(. TOP_LEVEL)
aux_source_directory(./Utils UTILS_SRC)
add_subdirectory(Controls)
add_subdirectory(Nodes)
#message(NOTICE "Included Files:" ${NODES_SRC})
add_executable(registrationViewer main.cpp ${TOP_LEVEL} ${UTILS_SRC})
target_link_libraries(registrationViewer nodes)
target_link_libraries(registrationViewer controls)
target_link_libraries(registrationViewer
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )