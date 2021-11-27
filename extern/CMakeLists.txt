# find_package(OpenGL)
# find_package(Vulkan)



add_subdirectory(imgui EXCLUDE_FROM_ALL)
add_subdirectory(googletest EXCLUDE_FROM_ALL)
add_subdirectory(glm EXCLUDE_FROM_ALL)
#add_subdirectory(opencv EXCLUDE_FROM_ALL)

set(BUILD_SHARED_LIBS OFF)
add_subdirectory(spdlog EXCLUDE_FROM_ALL)


# add_subdirectory(imgui)
# add_subdirectory(spdlog)
# add_subdirectory(glm)
# add_subdirectory(opencv)
# add_subdirectory(googletest)