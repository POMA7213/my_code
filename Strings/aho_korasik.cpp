#include <memory>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <queue>

struct Node : public std::enable_shared_from_this<Node> {
    std::shared_ptr<Node> terminal_link = nullptr;
    std::shared_ptr<Node> suffix_link = nullptr;
    std::vector<size_t> terminated_ids;
    std::map<char, std::shared_ptr<Node>> trie_transitions;
    std::map<char, std::shared_ptr<Node>> automaton_transitions;

    std::shared_ptr<Node> GetAutomatonTransition(char item, const std::shared_ptr<Node> &root) {
        if (automaton_transitions.contains(item)) {
            return automaton_transitions[item];
        }
        auto p = shared_from_this();
        while (!p->trie_transitions.contains(item)) {
            if (p == root) {
                automaton_transitions[item] = p;
                return p;
            }
            if (!p->automaton_transitions.contains(item)) {
                p = p->suffix_link;
            } else {
                automaton_transitions[item] = p->automaton_transitions[item];
                return automaton_transitions[item];
            }
        }
        automaton_transitions[item] = p->trie_transitions[item];
        return automaton_transitions[item];
    }
};

class Trie {
public:
    explicit Trie(const std::vector<std::pair<std::string, size_t>> &strings_with_ids) {
        BuildTrie(strings_with_ids);
        BuildSuffix();
        BuildTerminal();
    }

    std::vector<std::vector<size_t>> Scan(const std::string &text) {
        state_ = root_;
        std::vector<std::vector<size_t>> res(text.size());
        for (size_t i = 0; i < text.size(); ++i) {
            auto matches = Next(text[i]);
            for (size_t c: matches) {
                if (strings_[c].empty()) {
                    res[i].push_back(c);
                } else {
                    res[i + 1 - strings_[c].size()].push_back(c);
                }
            }
        }
        return res;
    }

private:
    std::shared_ptr<Node> root_ = std::make_shared<Node>();
    std::shared_ptr<Node> state_ = root_;
    std::map<size_t, std::string> strings_;

    void BuildTrie(const std::vector<std::pair<std::string, size_t>> &strings_with_ids) {
        for (const auto &str: strings_with_ids) {
            strings_[str.second] = str.first;
            auto current = root_;
            for (char item: str.first) {
                if (!current->trie_transitions.contains(item)) {
                    current->trie_transitions[item] = std::make_shared<Node>();
                }
                current = current->trie_transitions[item];
            }
            current->terminated_ids.push_back(str.second);
        }
    }

    void BuildSuffix() {
        std::queue<std::shared_ptr<Node>> queue;
        root_->suffix_link = root_;
        queue.push(root_);
        while (!queue.empty()) {
            auto front = queue.front();
            queue.pop();
            for (auto &[symbol, node]: front->trie_transitions) {
                if (front == root_) {
                    node->suffix_link = root_;
                    queue.push(node);
                    continue;
                }
                auto p = front->suffix_link;
                while (!p->trie_transitions.contains(symbol)) {
                    if (p == root_) {
                        break;
                    }
                    p = p->suffix_link;
                }
                if (p->trie_transitions.contains(symbol)) {
                    node->suffix_link = p->trie_transitions[symbol];
                } else {
                    node->suffix_link = root_;
                }
                queue.push(node);
            }
        }
    }

    void BuildTerminal() {
        std::queue<std::shared_ptr<Node>> queue;
        queue.push(root_);
        while (!queue.empty()) {
            auto front = queue.front();
            queue.pop();
            if (front == root_) {
                front->terminal_link = nullptr;
            } else if (!front->suffix_link->terminated_ids.empty()) {
                front->terminal_link = front->suffix_link;
            } else {
                front->terminal_link = front->suffix_link->terminal_link;
            }
            for (auto &[key, value]: front->trie_transitions) {
                queue.push(value);
            }
        }
    }

    std::vector<size_t> Next(char symbol) {
        state_ = state_->GetAutomatonTransition(symbol, root_);
        std::vector<size_t> matches;
        auto node = state_;
        while (node != nullptr) {
            for (size_t c: node->terminated_ids) {
                matches.push_back(c);
            }
            node = node->terminal_link;
        }
        return matches;
    }
};
