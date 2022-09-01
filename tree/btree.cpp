#include <memory>
#include <mutex>
#include <queue>
#include <string>

#include "util/misc.hpp"

using namespace std;

class BTree;

class Node {
public:
    Node(int val) : val(val) {}
    virtual ~Node() {}

private:
    int val;
    shared_ptr<Node> plc;
    shared_ptr<Node> prc;

    friend class BTree;
};  // class Node

class BTree {
public:
    BTree() {}
    virtual ~BTree() {}

    int addChild(int val) {
        if (!pRoot) {
            pRoot = make_shared<Node>(val);
            return 0;
        }

        int childIdx = -1;
        int nodeIdx = 0;

        shared_ptr<Node> pn;
        queue<shared_ptr<Node>> q;
        q.push(pRoot);

        while (!q.empty()) {
            pn = q.front();
            q.pop();

            if (pn) {
                nodeIdx++;
                if (nullptr == pn->plc) {
                    pn->plc = make_shared<Node>(val);
                    childIdx = nodeIdx;
                    break;
                }
                q.push(pn->plc);

                nodeIdx++;
                if (nullptr == pn->prc) {
                    pn->prc = make_shared<Node>(val);
                    childIdx = nodeIdx;
                    break;
                }
                q.push(pn->prc);
            }
        }

        return childIdx;
    }

    int find(int val) {
        int childIdx = -1;
        int nodeIdx = 0;

        shared_ptr<Node> pn;
        queue<shared_ptr<Node>> q;
        q.push(pRoot);

        while ((!q.empty()) && (-1 == childIdx)) {
            pn = q.front();
            q.pop();

            if (pn) {
                if (val == pn->val) {
                    childIdx = nodeIdx;
                } else {
                    nodeIdx++;
                    q.push(pn->plc);
                    q.push(pn->prc);
                }
            }
        }

        return childIdx;
    }

    bool getNodeValue(int childIdx, int &val) {
        bool found = false;
        int nodeIdx = 0;

        shared_ptr<Node> pn;
        queue<shared_ptr<Node>> q;
        q.push(pRoot);

        while ((!q.empty()) && (nodeIdx != childIdx)) {
            pn = q.front();
            q.pop();

            if (childIdx == nodeIdx) {
                if (pn) {
                    val = pn->val;
                }
                break;
            }

            nodeIdx++;

            if (pn) {
                q.push(pn->plc);
                q.push(pn->prc);
            }
        }

        return (childIdx == nodeIdx);
    }

    void traverse() {
        int nodeIdx = 0;

        shared_ptr<Node> pn;
        queue<shared_ptr<Node>> q;
        q.push(pRoot);

        string text;

        while (!q.empty()) {
            pn = q.front();
            q.pop();

            text = "Node " + to_string(nodeIdx) + ": ";
            nodeIdx++;

            if (pn) {
                text += to_string(pn->val);
                q.push(pn->plc);
                q.push(pn->prc);
            } else {
                text += "N/A";
            }

            LOG(text.c_str());
        }
    }

private:
    shared_ptr<Node> pRoot;
    mutex m;
};  // class BTree

int main(void) {
    vector<int> values = {
         0,  1,  2,  3,
        10, 11, 12, 13,
        20, 21, 22, 23
    };

    BTree tree;
    int childIdx;
    string text;

    for (auto val : values) {
        childIdx = tree.addChild(val);
        text = "Added " + to_string(val) + " at " + to_string(childIdx);
        LOG(text.c_str());
    }

    tree.traverse();

    return 0;
}
