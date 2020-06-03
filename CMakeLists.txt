cmake_minimum_required(VERSION 2.8.11)

project(QtVtkViewer)

set(VTK_DIR "/Volumes/Data/Software/VTK")
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# List source files & resources
file (GLOB_RECURSE Sources *.cpp *.cxx)
file (GLOB_RECURSE Headers *.h)
file (GLOB_RECURSE Resources *.qrc)
file (GLOB_RECURSE UIs *.ui)

# Find package Qt
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# Use Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
qt5_add_resources(Resources ${Resources})

include_directories(${Qt5Widgets_INCLUDES})
include_directories(${Qt5OpenGL_INCLUDES})
include_directories(${Qt5Core_INCLUDES})
include_directories(${Qt5Gui_INCLUDES})

add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5OpenGL_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})
add_definitions(${Qt5Core_DEFINITIONS})

# Find package VTK
find_package(VTK REQUIRED)

# Use VTK
include(${VTK_USE_FILE})
include_directories(${VTK_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

# Build executable
add_executable(QtVtkViewer WIN32 ${Sources} ${Headers} ${Resources} ${UIs})

# Link libraries
target_link_libraries(QtVtkViewer Qt5::Widgets Qt5::OpenGL ${VTK_LIBRARIES})
