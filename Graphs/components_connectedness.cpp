#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <stack>
#include <map>

struct Comp {
    bool operator()(const size_t &fir, const size_t &sec) const {
        return fir > sec;
    }
};

std::vector<size_t> GeneralDFS(const std::vector<std::unordered_set<size_t>> &graph) {
    size_t index = 0;
    std::vector<bool> visited(graph.size());
    std::vector<size_t> dfs_numb(graph.size());
    for (size_t counter = 0; counter < graph.size(); ++counter) {
        if (!visited[counter]) {
            std::stack<size_t> stack;
            stack.push(counter);
            visited[counter] = true;
            while (!stack.empty()) {
                size_t top = stack.top();
                bool has_not_visited = false;
                for (size_t c: graph[top]) {
                    if (!visited[c]) {
                        has_not_visited = true;
                        stack.push(c);
                        visited[c] = true;
                        break;
                    }
                }
                if (!has_not_visited) {
                    dfs_numb[top] = index;
                    ++index;
                    stack.pop();
                }
            }
        }
    }
    return dfs_numb;
}

std::vector<std::unordered_set<size_t>> Reverse(const std::vector<std::unordered_set<size_t>> &graph) {
    std::vector<std::unordered_set<size_t>> rev_graph(graph.size());
    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t c: graph[i]) {
            rev_graph[c].insert(i);
        }
    }
    return rev_graph;
}

std::vector<size_t>
ComputeComponents(const std::vector<std::unordered_set<size_t>> &graph, const std::vector<size_t> &targets) {
    std::vector<size_t> num_comp(graph.size());
    std::vector<bool> visited(graph.size());
    size_t index = 0;
    std::map<size_t, size_t, Comp> seq_vers;
    for (size_t i = 0; i < targets.size(); ++i) {
        seq_vers[targets[i]] = i;
    }
    for (auto [key, vertex]: seq_vers) {
        if (!visited[vertex]) {
            std::stack<size_t> stack;
            stack.push(vertex);
            visited[vertex] = true;
            num_comp[vertex] = index;
            while (!stack.empty()) {
                size_t top = stack.top();
                bool has_not_visited = false;
                for (size_t c: graph[top]) {
                    if (!visited[c]) {
                        has_not_visited = true;
                        stack.push(c);
                        visited[c] = true;
                        num_comp[c] = index;
                        break;
                    }
                }
                if (!has_not_visited) {
                    stack.pop();
                }
            }
            ++index;
        }
    }
    return num_comp;
}

std::vector<uint64_t> Compute(const std::vector<std::unordered_set<size_t>> &graph) {
    auto exits = GeneralDFS(graph);
    auto rev_graph = Reverse(graph);
    auto vers_components = ComputeComponents(rev_graph, exits);
    return vers_components;
}
