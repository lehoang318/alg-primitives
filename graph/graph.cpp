#include <iostream>
#include <array>
#include <deque>
#include <vector>

using namespace std;

const vector<vector<int>> GRAPH = {
  //        1   2   3   4   5   6   7
  /* 1 */ { 0, 25,  0,  0,  0,  5,  0},
  /* 2 */ {25,  0, 12,  0,  0,  0, 10},
  /* 3 */ { 0, 12,  0,  8,  0,  0,  0},
  /* 4 */ { 0,  0,  8,  0, 16,  0, 14},
  /* 5 */ { 0,  0,  0, 16,  0, 20, 18},
  /* 6 */ { 5,  0,  0,  0, 20,  0,  0},
  /* 7 */ { 0, 10,  0, 14, 18,  0,  0}
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

int prim(void) {
    const int n = GRAPH.size();
    vector<int> list;
    vector<int> v(n, 0);
    int cost = 0;
    int min = -1;

    for (int i = 0; n > i; i++) {
        for (int j = i + 1; n > j; j++) {
            if (
                (0 < GRAPH[i][j]) &&
                (
                    (0 > min) || (GRAPH[i][j] < min)
                )
            ) {
                min = GRAPH[i][j];
                list.clear();
                list.push_back(i);
                list.push_back(j);
            }
        }
    }

    cost += min;

    for (int i = 0; list.size() > i; i++) {
        v[list[i]] = 1;
        cout << (list[i] + 1) << " ";
    }

    while (n > list.size()) {
        int nnode = -1;
        min = -1;

        for (int i = 0; n > i; i++) {
            for (int j = 0; list.size() > j; j++) {
                int ti = list[j];
                if ((0 < GRAPH[ti][i]) && (0 == v[i])) {
                    if (0 > min) {
                        min = GRAPH[ti][i];
                        nnode = i;

                    } else if (GRAPH[ti][i] < min) {
                        min = GRAPH[ti][i];
                        nnode = i;
                    }
                }
            }
        }

        v[nnode] = 1;
        list.push_back(nnode);
        cost += min;
        cout << (nnode + 1) << " ";
    }

    cout << endl;

    return cost;
}

int main(void) {
    // bfs();
    // dfs();

    cout << "Spanning Tree - Prim" << endl;
    int cost = prim();
    cout << "=> Cost: " << cost << endl;

    return 0;
}
