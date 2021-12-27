cmake_minimum_required(VERSION 3.20)
project(registrationViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#set(CMAKE_PREFIX_PATH "/Users/zzy/Qt/5.15.2/clang_64")
#set(CMAKE_PREFIX_PATH "E:/QT/5.15.2/mingw81_64")
#include_directories([SYSTEM] "/Library/Developer/CommandLineTools/SDKs/MacOSX12.1.sdk/usr/include")
#set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        OpenGL
        REQUIRED)

add_subdirectory(Controls)
add_subdirectory(Nodes)
add_subdirectory(AntsProcessBridge)

aux_source_directory(. TOP_LEVEL)
aux_source_directory(./Utils UTILS_SRC)
aux_source_directory(./UI UI_SRCS)
aux_source_directory(./Controls CONTROLS_SRC)

#message(NOTICE "Included Files:" ${NODES_SRC})

#vtk:
#set( VTK_DIR "/Users/zzy/Documents/GitHub/VTK-9.1.0")
set( VTK_DIR "D:/respository/vtk-9.1.0")
#link_directories(${VTK_DIR}/cmake-build-debug/lib)
link_directories(${VTK_DIR}/Build/lib/Debug)
include_directories(
        ${VTK_DIR}/Interaction/Widgets
        ${VTK_DIR}/GUISupport/Qt
        ${VTK_DIR}/Build/GUISupport/Qt
        ${VTK_DIR}/IO/Image
        ${VTK_DIR}/Build/IO/Image
        ${VTK_DIR}/Filters/Core
        ${VTK_DIR}/Imaging/Core
        ${VTK_DIR}/Build/Imaging/Core
        ${VTK_DIR}/Rendering/Volume
        ${VTK_DIR}/Build/Rendering/Volume
        ${VTK_DIR}/Rendering/Core
        ${VTK_DIR}/Build/Interaction/Widgets/
        ${VTK_DIR}/Common/Core
        ${VTK_DIR}/Build/Common/Core
        ${VTK_DIR}/Common/Color
        ${VTK_DIR}/Common/ComputationalGeometry
        ${VTK_DIR}/Common/DataModel
        ${VTK_DIR}/Build/Common/DataModel
        ${VTK_DIR}/Common/ExecutionModel
        ${VTK_DIR}/Common/Math
        ${VTK_DIR}/Common/Misc
        ${VTK_DIR}/Build/Common/Misc
        ${VTK_DIR}/Common/System
        ${VTK_DIR}/Common/Transforms
        ${VTK_DIR}/Build/Common/Core
        ${VTK_DIR}/Build/Common/ExecutionModel
        ${VTK_DIR}/Utilities/KWIML
        ${VTK_DIR}/Build/Rendering/Core
        ${VTK_DIR}/Build/Filters/Core
)


list(REMOVE_ITEM CONTROLS_SRC ./Controls/test.cpp)
message("MAIN: removing test.cpp from controls...")
message(${CONTROLS_SRC})
add_executable(registrationViewer main.cpp ${TOP_LEVEL} ${UTILS_SRC} ${CONTROLS_SRC} ${UI_SRCS})
target_link_libraries(registrationViewer nodes)
#target_link_libraries(registrationViewer controls)
#target_link_libraries(registrationViewer libvtkInteractionWidgets-9.1.1.dylib)
target_link_libraries(registrationViewer
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

target_link_libraries(registrationViewer
        vtkGUISupportQt-9.1d
        vtkIOLegacy-9.1d
        vtkCommonCore-9.1d
        vtkRenderingCore-9.1d
        )