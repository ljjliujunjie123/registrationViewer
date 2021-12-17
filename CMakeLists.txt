cmake_minimum_required(VERSION 3.20)
project(registrationViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/zzy/Qt/5.15.2/clang_64")
#set(CMAKE_PREFIX_PATH "E:/QT/5.15.2/mingw81_64")
#include_directories([SYSTEM] "/Library/Developer/CommandLineTools/SDKs/MacOSX12.1.sdk/usr/include")
set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_subdirectory(Controls)
add_subdirectory(Nodes)

aux_source_directory(. TOP_LEVEL)
aux_source_directory(./Utils UTILS_SRC)
aux_source_directory(./Controls CONTROLS_SRC)

#message(NOTICE "Included Files:" ${NODES_SRC})

#vtk:
link_directories("/Users/zzy/Documents/GitHub/VTK-9.1.0/cmake-build-debug/lib")
include_directories(
        /Users/zzy/Documents/GitHub/VTK-9.1.0/Interaction/Widgets
        /Users/zzy/Documents/GitHub/VTK-9.1.0/Rendering/Core
        /Users/zzy/Documents/GitHub/VTK-9.1.0/cmake-build-debug/Interaction/Widgets/
        /Users/zzy/Documents/GitHub/VTK-9.1.0/Common/Core
        /Users/zzy/Documents/GitHub/VTK-9.1.0/cmake-build-debug/Common/Core
        /Users/zzy/Documents/GitHub/VTK-9.1.0/Utilities/KWIML
        /Users/zzy/Documents/GitHub/VTK-9.1.0/cmake-build-debug/Rendering/Core
        /Users/zzy/Documents/GitHub/VTK-9.1.0/cmake-build-debug/Filters/Core
)


list(REMOVE_ITEM CONTROLS_SRC ./Controls/test.cpp)
message("MAIN: removing test.cpp from controls...")
message(${CONTROLS_SRC})
add_executable(registrationViewer main.cpp ${TOP_LEVEL} ${UTILS_SRC} ${CONTROLS_SRC})
target_link_libraries(registrationViewer nodes)
#target_link_libraries(registrationViewer controls)
target_link_libraries(registrationViewer libvtkInteractionWidgets-9.1.1.dylib)
target_link_libraries(registrationViewer
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )