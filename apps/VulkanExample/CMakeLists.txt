cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "VulkanExample")
set(OUTEXE_NAME "VulkanExample")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_HOST_WIN32)
    if (CMAKE_CL_64)
        set(lib_dir "${CMAKE_SOURCE_DIR}/3rd/windows/amd64")
    else()
        set(lib_dir "${CMAKE_SOURCE_DIR}/3rd/windows/x86")
    endif()
else()
    message("unsupported architecture")
endif()

#message(" >> ${lib_dir}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/apps/${PROJECT_NAME})
include_directories(${lib_dir}/glad/include)
include_directories(${lib_dir}/glfw/include)
# include_directories(${lib_dir}/spdlog/include)


link_directories(${lib_dir}/glad/lib)
link_directories(${lib_dir}/glfw/lib)
# link_directories(${lib_dir}/spdlog/lib)

file(GLOB_RECURSE header_files 
    ${CMAKE_CURRENT_LIST_DIR}/*/*.h)
#message(" >>> ${header_files}")

file(GLOB_RECURSE source_files 
    ${CMAKE_CURRENT_LIST_DIR}/*/*.cc
    ${CMAKE_CURRENT_LIST_DIR}/*/*.cpp)


file(GLOB_RECURSE entry_file
    ${CMAKE_CURRENT_LIST_DIR}/main.cc)
#message(" >>> ${entry_file}")

# foreach(main_file ${source_files})
#     string(REGEX MATCH ".*/${entry_file}" needed_remove_file ${main_file})
#     if(needed_remove_file)
#         list(REMOVE_ITEM source_files ${needed_remove_file})
#     endif()
# endforeach()

foreach(sfile ${source_files})
    get_filename_component(PARENT_DIR "${sfile}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" PARENT_DIR "${PARENT_DIR}")
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" sfile "${sfile}")
    string(REPLACE "/" "" PARENT_DIR "${PARENT_DIR}")
    source_group("${PARENT_DIR}" FILES "${sfile}")
    message("<<<${sfile}>>>")
endforeach()


foreach(hfile ${header_files})
    get_filename_component(PARENT_DIR "${hfile}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" PARENT_DIR "${PARENT_DIR}")
    string(REPLACE "/" "" PARENT_DIR "${PARENT_DIR}")
    message("<<<${PARENT_DIR}>>>")
    source_group("${PARENT_DIR}" FILES "${hfile}")
endforeach()

find_package(OpenGL)
find_package(Vulkan)

#include_directories(${Vulkan_INCLUDE_DIR})
include_directories(${header_files})

#link_directories(${Vulkan_LIBRARY})

add_executable(${OUTEXE_NAME} ${entry_file} ${source_files} ${header_files})
set_target_properties(${OUTEXT_NAME} PROPERTIES FOLDER "ImguiExample")

target_include_directories(${OUTEXE_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

target_link_libraries(${OUTEXE_NAME} PRIVATE OpenGL::GL OpenGL::GLU imgui::imgui spdlog::spdlog glm::glm Vulkan::Vulkan glad.lib glfw3.lib)


# if (MSVC)
#     set(libs 
#         glad glfw3 spdlog)
#    foreach(lib ${libs})
#        target_link_libraries(triangle_drawer debug "${lib}d.lib" optimized "${lib}.lib")
#    endforeach()
#    
# endif()

#target_link_libraries(triangle_drawer glad.lib glfw3.lib spdlogd.lib)
