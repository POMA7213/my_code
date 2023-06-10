#include <fstream>
#include <memory>

template<class T>
struct Node {
    Node(const T &val, const std::shared_ptr<Node<T>> &p) : key(val), right(nullptr), left(nullptr), parent(p) {
    }

    std::shared_ptr<Node<T>> right;
    std::shared_ptr<Node<T>> left;
    std::shared_ptr<Node<T>> parent;
    T key;
};

template<class T>
class Tree {
    std::shared_ptr<Node<T>> first;
public:
    Tree() : first(nullptr) {}

    std::shared_ptr<Node<T>> GetFirst() { return first; }

    bool IsEmpty() { return first == nullptr; }

    void Insert(const T &k) {
        if (IsEmpty())
            first = std::make_shared<Node<T>>(k, nullptr);
        else {
            auto cur = first;
            while (true) {
                if (k == cur->key) {
                    break;
                }
                if (k < cur->key) {
                    if (cur->left != nullptr) {
                        cur = cur->left;
                    } else {
                        cur->left = std::make_shared<Node<T>>(k, cur);
                        break;
                    }
                } else {
                    if (cur->right != nullptr) {
                        cur = cur->right;
                    } else {
                        cur->right = std::make_shared<Node<T>>(k, cur);
                        break;
                    }
                }
            }
        }
    }

    std::shared_ptr<Node<T>> Find(const T &k) {
        if (IsEmpty())
            return nullptr;
        else {
            auto cur = first;
            while (true) {
                if (k == cur->key) {
                    return cur;
                }
                if (k < cur->key) {
                    if (cur->left)
                        cur = cur->left;
                    else {
                        return nullptr;
                    }
                } else {
                    if (cur->right)
                        cur = cur->right;
                    else {
                        return nullptr;
                    }
                }
            }
        }
    }

    void DelOneOrZero(const std::shared_ptr<Node<T>> &p) {
        if (p->left == nullptr && p->right == nullptr) {
            if (p != first) {
                if (p->parent->left == p) {
                    p->parent->left = nullptr;
                } else {
                    p->parent->right = nullptr;
                }
            } else {
                first = nullptr;
            }
        } else {
            if (p == first) {
                if (p->left == nullptr) {
                    first = p->right;
                    first->parent = nullptr;
                } else {
                    first = p->left;
                    first->parent = nullptr;
                }
            } else {
                if (p->left == nullptr) {
                    if (p->parent->right == p) {
                        p->parent->right = p->right;
                    } else {
                        p->parent->left = p->right;
                    }
                    p->right->parent = p->parent;
                } else {
                    if (p->parent->right == p) {
                        p->parent->right = p->left;
                    } else {
                        p->parent->left = p->left;
                    }
                    p->left->parent = p->parent;
                }
            }
        }
    }

    void DelTwo(const std::shared_ptr<Node<T>> &p) {
        auto c = p->right;
        while (c->left) {
            c = c->left;
        }
        if (p == first) {
            auto cp = c->parent;
            auto cr = c->right;
            if (p != cp) {
                c->left = p->left;
                c->right = p->right;
                c->parent = nullptr;
                first = c;

                cp->left = p;
                p->parent = cp;
                p->right = cr;
                p->left = nullptr;
                DelOneOrZero(p);
            } else {
                c->left = p->left;
                p->right = c->right;
                p->left = nullptr;
                c->right = p;
                p->parent = c;
                c->parent = nullptr;
                first = c;
                DelOneOrZero(p);
            }
        } else {
            auto cp = c->parent;
            auto cr = c->right;
            if (p != cp) {
                c->left = p->left;
                c->right = p->right;
                c->parent = p->parent;
                if (p->parent->right == p) {
                    p->parent->right = c;
                } else {
                    p->parent->left = c;
                }

                cp->left = p;
                p->parent = cp;
                p->right = cr;
                p->left = nullptr;
                DelOneOrZero(p);
            } else {
                c->left = p->left;
                p->right = c->right;
                p->left = nullptr;
                c->right = p;

                if (p->parent->right == p) {
                    p->parent->right = c;
                } else {
                    p->parent->left = c;
                }
                p->parent = c;

                DelOneOrZero(p);
            }
        }
    }

    void DelNode(const T &k) {
        auto p = Find(k);
        if (p == nullptr) {
            return;
        }
        if (p->right == nullptr || p->left == nullptr) {
            DelOneOrZero(p);
        } else {
            DelTwo(p);
        }
    }
};
