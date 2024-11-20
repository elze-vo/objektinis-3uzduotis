cmake_minimum_required(VERSION 3.10)
project(studentuAppsas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(Include)
file(GLOB SOURCES "src/*.cpp")

add_executable(studentuAppsas_struct_O1 ${SOURCES})
add_executable(studentuAppsas_struct_O2 ${SOURCES})
add_executable(studentuAppsas_struct_Ox ${SOURCES})

target_compile_options(studentuAppsas_struct_O1 PRIVATE -O1)
target_compile_options(studentuAppsas_struct_O2 PRIVATE -O2)
target_compile_options(studentuAppsas_struct_Ox PRIVATE -Ox)
