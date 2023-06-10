#include <vector>
#include <string>
#include <algorithm>

std::vector<size_t> ComputeSuffArr(std::string string) {
    string.push_back('$');
    size_t real_size = string.size();

    std::vector<size_t> counter(*std::max_element(string.begin(), string.end()) + 1);
    std::vector<size_t> position(real_size);
    for (size_t i = 0; i < real_size; i++) {
        counter[string[i]]++;
    }
    for (size_t i = 1; i < counter.size(); i++) {
        counter[i] += counter[i - 1];
    }
    for (size_t i = 0; i < real_size; i++) {
        position[counter[string[i]] - 1] = i;
        counter[string[i]]--;
    }
    size_t cur_class = 1;
    std::vector<size_t> classes(real_size);
    for (size_t i = 1; i < real_size; i++) {
        if (string[position[i]] != string[position[i - 1]]) {
            cur_class++;
        }
        classes[position[i]] = cur_class - 1;
    }

    std::vector<size_t> posn(real_size);
    std::vector<size_t> cln(real_size);
    size_t deg = 1;
    while (deg < string.size()) {
        for (size_t i = 0; i < real_size; i++) {
            if (deg > position[i]) {
                posn[i] = position[i] + real_size - deg;
            } else {
                posn[i] = position[i] - deg;
            }
        }
        counter = std::vector<size_t>(cur_class);
        for (size_t i = 0; i < real_size; i++) {
            counter[classes[posn[i]]]++;
        }
        for (size_t i = 1; i < counter.size(); i++) {
            counter[i] += counter[i - 1];
        }
        for (size_t i = real_size - 1;; i--) {
            position[counter[classes[posn[i]]] - 1] = posn[i];
            counter[classes[posn[i]]]--;
            if (i == 0) {
                break;
            }
        }
        cur_class = 1;
        for (size_t i = 1; i < real_size; i++) {
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
