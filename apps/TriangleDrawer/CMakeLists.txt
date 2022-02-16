cmake_minimum_required(VERSION 3.5)

project(TriangleDrawer)

if(CMAKE_HOST_WIN32)
    if (CMAKE_CL_64)
        set(lib_dir "${CMAKE_SOURCE_DIR}/3rd/windows/amd64")
    else()
        set(lib_dir "${CMAKE_SOURCE_DIR}/3rd/windows/x86")
    endif()
else()
    message("unsupported architecture")
endif()

message(" >> ${lib_dir}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/apps/TriangleDrawer)
include_directories(${lib_dir}/glad/include)
include_directories(${lib_dir}/glfw/include)
# include_directories(${lib_dir}/spdlog/include)


link_directories(${lib_dir}/glad/lib)
link_directories(${lib_dir}/glfw/lib)
# link_directories(${lib_dir}/spdlog/lib)

file(GLOB header_files 
    ${CAMKE_SOURCE_DIR}/apps/TriangleDrawer/*.h)
message(" >>> ${header_files}")

file(GLOB source_files 
    ${CMAKE_SOURCE_DIR}/apps/TriangleDrawer/*.cc
    ${CMAKE_SOURCE_DIR}/apps/TriangleDrawer/*.cpp)
message(" >>> ${source_files}")

file(GLOB entry_file
    ${CMAKE_SOURCE_DIR}/apps/TriangleDrawer/main.cc)

foreach(main_file ${source_files})
    string(REGEX MATCH ".*/${entry_file}" needed_remove_file ${main_file})
    if(needed_remove_file)
        list(REMOVE_ITEM source_files ${needed_remove_file})
    endif()
endforeach()

find_package(OpenGL)
find_package(Vulkan)


include_directories(${Vulkan_INCLUDE_DIR})

link_directories(${Vulkan_LIBRARY})

add_executable(triangle_drawer ${entry_file} ${source_files} ${header_files})

target_link_libraries(triangle_drawer PRIVATE OpenGL::GL OpenGL::GLU imgui::imgui spdlog::spdlog gtest gtest_main gmock gmock_main glm::glm Vulkan::Vulkan glad.lib glfw3.lib)


# if (MSVC)
#     set(libs 
#         glad glfw3 spdlog)
#    foreach(lib ${libs})
#        target_link_libraries(triangle_drawer debug "${lib}d.lib" optimized "${lib}.lib")
#    endforeach()
#    
# endif()

#target_link_libraries(triangle_drawer glad.lib glfw3.lib spdlogd.lib)
