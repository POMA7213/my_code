cmake_minimum_required(VERSION 3.25)
project(my_code)

set(CMAKE_CXX_STANDARD 20)

add_executable(my_code
        Strings/prefix_function.cpp Strings/zet_function.cpp Strings/prefix_to_zet.cpp Strings/zet_to_prefix.cpp Strings/suff_arr_slow.cpp Strings/lcp.cpp DataStructures/rmq.cpp Graphs/push_relabel.cpp Graphs/edmonds_karp.cpp Graphs/components_connectedness.cpp Graphs/dijkstra.cpp Graphs/topology_sort.cpp Trees/bin_tree.cpp main.cpp Other/sieve_of_eratosthenes.cpp Strings/aho_korasik.cpp DataStructures/segment_tree.cpp Other/sudoku_solver.cpp
        Trees/lca.cpp
        DataStructures/segment_tree_simple.cpp
        DataStructures/merge_sort_tree.cpp)
