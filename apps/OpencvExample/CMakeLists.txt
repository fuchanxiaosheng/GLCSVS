cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "OpencvExample")
set(OUTEXE_NAME "opencv_example")

project(${PROJECT_NAME})



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
message(" CMAKE_CURRENT_SOURCE_DIR >>>> ${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(${CMAKE_CURRENT_LIST_DIR})
# include_directories(${lib_dir}/glad/include)
# include_directories(${lib_dir}/glfw/include)
# # include_directories(${lib_dir}/spdlog/include)


# link_directories(${lib_dir}/glad/lib)
# link_directories(${lib_dir}/glfw/lib)
# # link_directories(${lib_dir}/spdlog/lib)

file(GLOB header_files 
    ${CMAKE_CURRENT_LIST_DIR}/include/*.h)
message(" >>> ${header_files}")

file(GLOB source_files 
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
message(" >>> ${source_files}")

file(GLOB entry_file
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cc)

foreach(main_file ${source_files})
    string(REGEX MATCH ".*/${entry_file}" needed_remove_file ${main_file})
    if(needed_remove_file)
        list(REMOVE_ITEM source_files ${needed_remove_file})
    endif()
endforeach()

# find_package(OpenGL)
# find_package(Vulkan)

# include_directories(${Vulkan_INCLUDE_DIR})
# include_directories(${header_files})

# link_directories(${Vulkan_LIBRARY})
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) # Not needed for CMake >= 2.8.11
#    target_link_libraries(MY_TARGET_NAME ${OpenCV_LIBS})

add_executable(${OUTEXE_NAME} ${entry_file} ${source_files} ${header_files})

target_include_directories(${OUTEXE_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")
message("=========================")
message("${CMAKE_SOURCE_DIR}/extern/opencv/include/opencv")
message("============================")

# target_link_libraries(${OUTEXE_NAME} PRIVATE OpenGL::GL OpenGL::GLU imgui::imgui spdlog::spdlog glm::glm glad.lib glfw3.lib)
target_link_libraries(${OUTEXE_NAME} PRIVATE imgui::imgui spdlog::spdlog glm::glm ${OpenCV_LIBS})
# if (MSVC)
#     set(libs 
#         glad glfw3 spdlog)
#    foreach(lib ${libs})
#        target_link_libraries(triangle_drawer debug "${lib}d.lib" optimized "${lib}.lib")
#    endforeach()
#    
# endif()

#target_link_libraries(triangle_drawer glad.lib glfw3.lib spdlogd.lib)
