#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <stack>
#include <map>

using namespace std;

typedef long long ll;

struct Comp {
    bool operator()(const ll &fir, const ll &sec) const {
        return fir > sec;
    }
};

vector<ll> GeneralDFS(const vector<unordered_set<ll>> &graph) {
    ll index = 0;
    vector<bool> visited(graph.size());
    vector<ll> dfs_numb(graph.size());
    for (ll counter = 0; counter < graph.size(); ++counter) {
        if (!visited[counter]) {
            stack<ll> stack;
            stack.push(counter);
            visited[counter] = true;
            while (!stack.empty()) {
                ll top = stack.top();
                bool has_not_visited = false;
                for (ll c: graph[top]) {
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

vector<unordered_set<ll>> Reverse(const vector<unordered_set<ll>> &graph) {
    vector<unordered_set<ll>> rev_graph(graph.size());
    for (ll i = 0; i < graph.size(); ++i) {
        for (ll c: graph[i]) {
            rev_graph[c].insert(i);
        }
    }
    return rev_graph;
}

vector<ll>
ComputeComponents(const vector<unordered_set<ll>> &graph, const vector<ll> &targets) {
    vector<ll> num_comp(graph.size());
    vector<bool> visited(graph.size());
    ll index = 0;
    map<ll, ll, Comp> seq_vers;
    for (ll i = 0; i < targets.size(); ++i) {
        seq_vers[targets[i]] = i;
    }
    for (auto [key, vertex]: seq_vers) {
        if (!visited[vertex]) {
            stack<ll> stack;
            stack.push(vertex);
            visited[vertex] = true;
            num_comp[vertex] = index;
            while (!stack.empty()) {
                ll top = stack.top();
                bool has_not_visited = false;
                for (ll c: graph[top]) {
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

vector<ll> Compute(const vector<unordered_set<ll>> &graph) {
    auto exits = GeneralDFS(graph);
    auto rev_graph = Reverse(graph);
    auto vers_components = ComputeComponents(rev_graph, exits);
    return vers_components;
}
