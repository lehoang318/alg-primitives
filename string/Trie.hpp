#ifndef __TRIE_HPP__
#define __TRIE_HPP__

#include <atomic>
#include <string>
#include <vector>

using namespace std;

#define MAX_CHILD_COUNT ((int)'z' - (int)'a' + 1)
#define C2I(c)  ((int)c - (int)'a')

class Node {
public:
    Node() {
        Count++;
        for (int i = 0; MAX_CHILD_COUNT > i; i++) {
            mChildren[i] = nullptr;
        }
    }

    virtual ~Node() {
        for (int i = 0; MAX_CHILD_COUNT > i; i++) {
            if (nullptr != mChildren[i]) {
                delete mChildren[i];
                mChildren[i] = nullptr;
            }
        }
    }

    bool contain(char c) {
        return (nullptr != mChildren[C2I(c)]);
    }

    void addChild(char c) {
        mChildren[C2I(c)] = new Node();
    }

    Node * getChild(char c) {
        return mChildren[C2I(c)];
    }

    atomic_bool mCompleted;

    static atomic_int Count;

private:
    Node * mChildren[MAX_CHILD_COUNT];

};  // class Node

class Trie {
public:
    Trie() {}
    virtual ~Trie() {}

    void add(string s) {
        Node * pn = &root;

        for (char c : s) {
            if (!pn->contain(c)) {
                pn->addChild(c);
            }

            pn = pn->getChild(c);
        }

        pn->mCompleted = true;
    }

    Node * getRootPtr() {
        return &root;
    }

    vector<string> list() {
        return Trie::list(&root);
    }

private:
    static vector<string> list(Node * node, string prefix="") {
        vector<string> l;

        if (nullptr == node) {
            return l;
        }

        for (char c = 'a'; 'z' >= c; c++) {
            if (nullptr != node->getChild(c)) {
                if (node->getChild(c)->mCompleted) {
                    l.push_back(prefix + c);
                }
                vector<string> l1 = list(node->getChild(c), prefix + c);
                l.insert(l.end(), l1.begin(), l1.end());
            }
        }

        return l;
    }

    Node root;
};  // class Trie

#endif // __TRIE_HPP__
