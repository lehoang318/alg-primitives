#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DjSet {
public:
    DjSet(int n) {
        mIState = vector<int>(n + 1, -1);
    }

    int findAncestor(int i) {
        int ti = i;
        while (0 < mIState[ti]) {
            ti = mIState[ti];
        }

        return ti;
    }

    void join(int s0, int s1) {
        int ti[] = {s0, s1};

        while (0 < mIState[ti[0]]) {
            ti[0] = mIState[ti[0]];
        }

        while (0 < mIState[ti[1]]) {
            ti[1] = mIState[ti[1]];
        }

        if (ti[0] < ti[1]) {
            mIState[ti[1]] += mIState[ti[0]];
            mIState[ti[0]] = ti[1];
        } else {
            mIState[ti[0]] += mIState[ti[1]];
            mIState[ti[1]] = ti[0];
        }
    }

    string toString(void) {
        string txt("[");

        for (int i = 0; mIState.size() > i; i++) {
            txt += to_string(mIState[i]) + " ";
        }

        txt = txt.substr(0, txt.length() - 1);
        return txt + "]";
    }

private:
    vector<int> mIState;

};  // class DjSet

int main(void) {
    DjSet s(10);
    cout << s.toString() << endl;

    s.join(3, 9);
    s.join(5, 9);

    cout << s.toString() << endl;

    s.join(4, 10);
    s.join(7, 10);
    s.join(8, 10);
    cout << s.toString() << endl;

    s.join(3, 4);
    cout << s.toString() << endl;

    return 0;
}
