#include <vector>
#include <string>

using namespace std;
typedef long long ll;

vector<ll> ComputePrefix(const string &pattern) {
    vector<ll> res(pattern.size());
    for (ll counter = 1; counter < res.size(); ++counter) {
        ll cur_pos = counter;
        while (cur_pos != 0) {
            cur_pos = res[cur_pos - 1];
            if (pattern[cur_pos] == pattern[counter]) {
                if (cur_pos == 0) {
                    res[counter] = 1;
                } else {
                    res[counter] = cur_pos + 1;
                }
                break;
            }
        }
    }
    return res;
}
