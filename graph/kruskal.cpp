#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct _EdgeType{
    _EdgeType(int n0, int n1, int cost) {
        this->n0 = n0;
        this->n1 = n1;
        this->cost = cost;
    }

    _EdgeType(const _EdgeType & other) {
        this->n0 = other.n0;
        this->n1 = other.n1;
        this->cost = other.cost;
    }

    _EdgeType& operator= (const _EdgeType & other) {
        this->n0 = other.n0;
        this->n1 = other.n1;
        this->cost = other.cost;

        return *this;
    }

    int n0;
    int n1;
    int cost;
} EdgeType;

class DjSet {
public:
    DjSet(int n) {
        mIState = vector<int>(n, -1);
    }

    int findAncestor(int i) {
        int ti = i;
        while ((0 < ti) && ((int)(mIState.size()) > ti) && (0 < mIState[ti])) {
            ti = mIState[ti];
        }

        return ti;
    }

    int join(int s0, int s1) {
        int ti[] = {s0, s1};

        while ((0 < ti[0]) && ((int)(mIState.size()) > ti[0]) && (0 < mIState[ti[0]])) {
            ti[0] = mIState[ti[0]];
        }

        while ((0 < ti[1]) && ((int)(mIState.size()) > ti[1]) && (0 < mIState[ti[1]])) {
            ti[1] = mIState[ti[1]];
        }

        if (ti[0] < ti[1]) {
            mIState[ti[1]] += mIState[ti[0]];
            mIState[ti[0]] = ti[1];

            return ti[1];
        } else {
            mIState[ti[0]] += mIState[ti[1]];
            mIState[ti[1]] = ti[0];

            return ti[0];
        }
    }

    string toString(void) {
        string txt("[");

        for (int i = 0; (int)(mIState.size()) > i; i++) {
            txt += to_string(mIState[i]) + " ";
        }

        txt = txt.substr(0, txt.length() - 1);
        return txt + "]";
    }

private:
    vector<int> mIState;
};  // class DjSet

vector<EdgeType> edges = {
    {0, 1, 25},
    {0, 5, 5},
    {1, 2, 12},
    {1, 6, 10},
    {2, 3, 8},
    {3, 4, 16},
    {3, 6, 14},
    {4, 5, 20},
    {4, 6, 18}
};

int main(void) {
    const int NodeCount = 7;
    const int EdgeCount = edges.size();
    vector<int> added(EdgeCount, 0);
    vector<int> sortedEdges(EdgeCount, -1);

    for (int i = 1; EdgeCount > i; i++) {
        int j = i - 1;
        EdgeType te(edges[i]);

        while (0 <= j) {
            if (edges[j].cost > te.cost) {
                edges[j + 1] = edges[j];
            } else {
                break;
            }

            j--;
        }

        if ((j + 1) != i) {
            edges[j + 1] = te;
        }
    }

    DjSet ns(NodeCount);

    int ei = 0;
    ns.join(edges[ei].n0, edges[ei].n1);
    int cost = edges[ei].cost;
    cout << "Added: " << edges[ei].n0 << "-" << edges[ei].n1 << " => +" << edges[ei].cost << endl;

    int a[2];
    ei++;

    for (int i = 1; (((NodeCount - 1) > i) && (EdgeCount > ei));) {
        a[0] = ns.findAncestor(edges[ei].n0);
        a[1] = ns.findAncestor(edges[ei].n1);

        if ((0 > a[0]) || (0 > a[1]) || (a[0] != a[1])) {
            ns.join(a[0], a[1]);
            cost += edges[ei].cost;

            cout << "Added: " << edges[ei].n0 << "-" << edges[ei].n1 << " => +" << edges[ei].cost << endl;
            i++;
        } else {
            cout << "Ignored: " << edges[ei].n0 << "-" << edges[ei].n1 << endl;
            cout << "a0/a1: " << a[0] << "/" << a[1] << endl;
        }

        cout << "Set: " << ns.toString() << endl;

        ei++;
    }

    cout << "Total cost: " << cost << endl;

    return 0;
}
