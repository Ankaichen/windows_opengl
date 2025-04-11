file(GLOB_RECURSE APPLICATION_SRCS ./ *.cpp)

add_library(application ${APPLICATION_SRCS})

target_link_libraries(application glfw3dll)