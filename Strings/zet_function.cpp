#include <vector>
#include <string>
#include <utility>

using namespace std;
typedef long long ll;

vector<ll> ComputeZet(const string &pattern) {
    vector<ll> res(pattern.size());
    res[0] = pattern.size();
    if (pattern.size() == 1) {
        return res;
    }
    ll sec = 1;
    while (sec < pattern.size() && pattern[sec] == pattern[sec - 1]) {
        ++sec;
    }
    res[1] = sec - 1;
    pair<ll, ll> max_right = {1, sec};
    for (ll counter = 2; counter < res.size(); ++counter) {
        if (counter >= max_right.second) {
            auto counter_in_loop = counter;
            while (counter_in_loop < res.size() &&
                   pattern[counter_in_loop] == pattern[counter_in_loop - counter]) {
                counter_in_loop++;
            }
            res[counter] = counter_in_loop - counter;
            max_right = {counter, counter_in_loop};
            continue;
        }
        if (res[counter - max_right.first] + counter < max_right.second) {
            res[counter] = res[counter - max_right.first];
            continue;
        }
        ll counter_in_loop = max_right.second;
        while (counter_in_loop < res.size() &&
               pattern[counter_in_loop] == pattern[counter_in_loop - counter]) {
            ++counter_in_loop;
        }
        res[counter] = counter_in_loop - counter;
        max_right = {counter, counter_in_loop};
    }
    return res;
}
