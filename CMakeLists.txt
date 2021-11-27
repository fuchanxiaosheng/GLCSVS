cmake_minimum_required(VERSION 3.5)

project(GLCSVS)

#set(CMAKE_EXE_LINKER_FLAGS "-static")
#添加自定义cmake库
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

message(">>>env $ENV{VULKAN_SDK}")
#add_subdirectory(./3rd)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakePredefinedTargets")


#set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/cmake)

#add_subdirectory(./libs)
add_subdirectory(extern)
set_property(TARGET gmock PROPERTY FOLDER "ExternLib")
set_property(TARGET gmock_main PROPERTY FOLDER "ExternLib")
set_property(TARGET gtest PROPERTY FOLDER "ExternLib")
set_property(TARGET gtest_main PROPERTY FOLDER "ExternLib")
set_property(TARGET imgui PROPERTY FOLDER "ExternLib")
set_property(TARGET spdlog PROPERTY FOLDER "ExternLib")

add_subdirectory(apps)

