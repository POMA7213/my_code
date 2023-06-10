cmake_minimum_required(VERSION 3.25)
project(my_code)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_code main.cpp
        Strings/prefix_function.cpp Strings/zet_function.cpp Strings/prefix_to_zet.cpp Strings/zet_to_prefix.cpp Strings/suff_arr_slow.cpp Strings/lcp.cpp DataStructures/rmq.cpp)
