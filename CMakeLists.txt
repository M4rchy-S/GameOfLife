cmake_minimum_required(VERSION 3.13)
set(CXX_STANDARD 17)

set(PROJECT_NAME GameOfLife)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} WIN32 src/main.cpp src/GameLife.cpp extern/rlImGui/rlImGui.cpp)

include_directories(include)
include_directories(extern/rlImGui)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)


find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)


message("Operating System: ${CMAKE_SYSTEM_NAME}")
message("Archittecture: ${CMAKE_SYSTEM_PROCESSOR}")
message("Compiler: ${CMAKE_CXX_COMPILER}")
message("Project Name: ${PROJECT_NAME}")
message("Compilation Flags DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message("Compilation Flags RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")

# cmake ../. -DCMAKE_TOOLCHAIN_FILE=C:/Programs/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_MANIFEST_MODE=ON
