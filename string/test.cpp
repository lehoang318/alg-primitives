#include <atomic>
#include <iostream>
#include <string>
#include <vector>

#include "Trie.hpp"

atomic_int Node::Count(0);

using namespace std;

int main(void) {
    Trie tree;
    string s;
    int nodeCount = 0;

    cout << "Size of a Trie: " << sizeof(tree) << "bytes" << endl;
    cout << "Size of a Trie.Node: " << sizeof(*tree.getRootPtr()) << "bytes" << endl;
    nodeCount = Node::Count;

    cout << "Number of nodes: " << nodeCount << endl;

    s = "abcde";
    tree.add(s);
    cout << "Added `" << s << "`" << endl;
    cout << Node::Count - nodeCount << " nodes have been created!" << endl;
    nodeCount = Node::Count;

    s = "abba";
    tree.add(s);
    cout << "Added `" << s << "`" << endl;
    cout << Node::Count - nodeCount << " nodes have been created!" << endl;
    nodeCount = Node::Count;

    s = "abbadef";
    tree.add(s);
    cout << "Added `" << s << "`" << endl;
    cout << Node::Count - nodeCount << " nodes have been created!" << endl;
    nodeCount = Node::Count;

    s = "ac";
    tree.add(s);
    cout << "Added `" << s << "`" << endl;
    cout << Node::Count - nodeCount << " nodes have been created!" << endl;
    nodeCount = Node::Count;

    s = "abc";
    tree.add(s);
    cout << "Added `" << s << "`" << endl;
    cout << Node::Count - nodeCount << " nodes have been created!" << endl;
    nodeCount = Node::Count;

    vector<string> l = tree.list();

    for (string s : l) {
        cout << s << endl;
    }

    return 0;
}
