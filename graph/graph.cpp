#include <iostream>
#include <array>
#include <deque>
#include <vector>

using namespace std;

const vector<vector<int>> GRAPH = {
  //       1  2  3  4  5  6  7
  /* 1 */ {0, 1, 1, 1, 0, 0, 0},
  /* 2 */ {1, 0, 1, 0, 0, 0, 0},
  /* 3 */ {1, 1, 0, 1, 1, 0, 0},
  /* 4 */ {1, 0, 1, 0, 1, 0, 0},
  /* 5 */ {0, 0, 1, 1, 0, 1, 1},
  /* 6 */ {0, 0, 0, 0, 1, 0, 0},
  /* 7 */ {0, 0, 0, 0, 1, 0, 0}
};

string vtos(vector<int> v) {
    string text("[");
    for (auto e : v) {
        text += to_string(e) + " ";
    }

    return (text.substr(0, (v.size() << 1) - 1) + "]");
}

void bfs(void) {
    const int n = GRAPH.size();
    deque<int> q;
    vector<int> v(n, 0);
    int i = 0;

    cout << "Breath First Search:" << endl;

    q.push_back(i);
    v[i] = 1;

    while (!q.empty()) {
        i = q.front();
        q.pop_front();
        cout << (i + 1) << " ";
        

        for (int j = 0; n > j; j++) {
            if ((0 != GRAPH[i][j]) && (0 == v[j])) {
                q.push_back(j);
                v[j] = 1;
            }
        }
    }

    cout << endl;
    
    return;
}

void dfs(void) {
    const int n = GRAPH.size();
    vector<int> v(n, 0);
    deque<int> stack;
    int i = 0;

    cout << "Depth First Search:" << endl;

    stack.push_back(i);
    v[i] = 1;

    while (!stack.empty()) {
        i = stack.back();
        for (int j = 0; n > j; j++) {
            if ((0 != GRAPH[i][j]) && (0 == v[j])) {
                stack.push_back(j);
                v[j] = 1;
                break;
            }
        }

        if (stack.back() == i) {
            cout << (stack.back() + 1) << " ";
            stack.pop_back();
        }
    }

    cout << endl;
}

int main(void) {
    bfs();
    dfs();
    return 0;
}
