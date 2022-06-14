# CMakeList.txt : CMake project for imGuiEx, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("imGuiEx")
find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (imGuiEx "imGuiEx.cpp" "imGuiEx.h" "UseImGui.cpp" "UseImGui.h")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET imGuiEx PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(imGuiEx PRIVATE imgui::imgui)

target_link_libraries(imGuiEx PRIVATE glad::glad)

target_link_libraries(imGuiEx PRIVATE glfw)
