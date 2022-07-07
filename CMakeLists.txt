# CMakeList.txt : CMake project for imGuiEx, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("imGuiEx")

# Add source to this project's executable.
add_executable (imGuiEx "imGuiEx.cpp" "imGuiEx.h" "UseImGui.cpp" "UseImGui.h")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET imGuiEx PROPERTY CXX_STANDARD 20)
endif()

find_package(glad CONFIG REQUIRED)
target_link_libraries(imGuiEx PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(imGuiEx PRIVATE glfw)

find_package(gl3w CONFIG REQUIRED)
target_link_libraries(imGuiEx PRIVATE unofficial::gl3w::gl3w)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(imGuiEx PRIVATE imgui::imgui)

find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
target_include_directories(imGuiEx PRIVATE ${STB_INCLUDE_DIRS})


