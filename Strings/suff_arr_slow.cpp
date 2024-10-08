#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<ll> ComputeSuffArr(string string) {
    string.push_back('$');
    ll real_size = string.size();

    vector<ll> counter(*max_element(string.begin(), string.end()) + 1);
    vector<ll> position(real_size);
    for (ll i = 0; i < real_size; i++) {
        counter[string[i]]++;
    }
    for (ll i = 1; i < counter.size(); i++) {
        counter[i] += counter[i - 1];
    }
    for (ll i = 0; i < real_size; i++) {
        position[counter[string[i]] - 1] = i;
        counter[string[i]]--;
    }
    ll cur_class = 1;
    vector<ll> classes(real_size);
    for (ll i = 1; i < real_size; i++) {
        if (string[position[i]] != string[position[i - 1]]) {
            cur_class++;
        }
        classes[position[i]] = cur_class - 1;
    }

    vector<ll> posn(real_size);
    vector<ll> cln(real_size);
    ll deg = 1;
    while (deg < string.size()) {
        for (ll i = 0; i < real_size; i++) {
            if (deg > position[i]) {
                posn[i] = position[i] + real_size - deg;
            } else {
                posn[i] = position[i] - deg;
            }
        }
        counter = vector<ll>(cur_class);
        for (ll i = 0; i < real_size; i++) {
            counter[classes[posn[i]]]++;
        }
        for (ll i = 1; i < counter.size(); i++) {
            counter[i] += counter[i - 1];
        }
        for (ll i = real_size - 1;; i--) {
            position[counter[classes[posn[i]]] - 1] = posn[i];
            counter[classes[posn[i]]]--;
            if (i == 0) {
                break;
            }
        }
        cur_class = 1;
        for (ll i = 1; i < real_size; i++) {
            if (classes[position[i]] != classes[position[i - 1]] ||
                classes[(position[i] + deg) % real_size] != classes[(position[i - 1] + deg) % real_size]) {
                cur_class++;
            }
            cln[position[i]] = cur_class - 1;
        }
        classes = cln;
        deg *= 2;
    }
    position.erase(position.begin());
    return position;
}
