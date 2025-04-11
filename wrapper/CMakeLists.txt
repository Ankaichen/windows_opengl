file(GLOB_RECURSE WRAPPER_SRCS ./ *.cpp)

add_library(wrapper ${WRAPPER_SRCS})