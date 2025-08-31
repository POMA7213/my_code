#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll Rec(ll ver, ll parent, ll cur_depth, const vector<set<ll>> &graph, vector<ll> &depth, vector<ll> &dp, vector<set<ll>> &bridges)
{
    if (dp[ver] != -1)
    {
        return dp[ver];
    }
    depth[ver] = cur_depth;
    dp[ver] = cur_depth;
    for (auto c : graph[ver])
    {
        if (c == parent)
        {
            continue;
        }
        dp[ver] = min(dp[ver], Rec(c, ver, cur_depth + 1, graph, depth, dp, bridges));
    }
    if (dp[ver] == cur_depth && parent != -1)
    {
        bridges[ver].insert(parent);
        bridges[parent].insert(ver);
    }
    return dp[ver];
}

vector<set<ll>> FindBridges(const vector<set<ll>> &graph)
{
    vector<ll> depth(graph.size());
    vector<ll> dp(graph.size(), -1);
    vector<set<ll>> bridges(graph.size());
    Rec(0, -1, 0, graph, depth, dp, bridges);
    return bridges;
}
