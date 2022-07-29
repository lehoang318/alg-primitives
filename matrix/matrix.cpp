#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix;

typedef enum {
    AX_ROW,
    AX_COL
} tAxis;

static void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

static void swap(int &a, int &b, int &c, int &d) {
    int tmp = d;
    d = c;
    c = b;
    b = a;
    a = tmp;
}

void swap(matrix & m, size_t i, size_t j, tAxis ax=AX_ROW) {
    const size_t rc = m.size();
    const size_t cc = m[0].size();

    if (AX_ROW == ax) {
        for (size_t k = 0; cc > k; k++) {
            swap(m[i][k], m[j][k]);
        }
    } else {
        for (size_t k = 0; rc > k; k++) {
            swap(m[k][i], m[k][j]);
        }
    }
}

void lrotate(matrix &m) {
    const size_t rc = m.size();
    const size_t cc = m[0].size();

    for (size_t r = 0; (rc/2) > r; r++) {
        for (size_t c = r; (cc - r -1) > c; c++) {
            swap(
                m[cc - 1 - c][cc - 1 - (cc - 1 - r)],
                m[cc - 1 - r][cc - 1 - c],
                m[c][cc - 1 - r],
                m[r][c]
            );
        }
    }
}

void rrotate(matrix &m) {
    const size_t rc = m.size();
    const size_t cc = m[0].size();

    for (size_t r = 0; (rc/2) > r; r++) {
        for (size_t c = r; (cc - r -1) > c; c++) {
            swap(
                m[r][c],
                m[c][cc - 1 - r],
                m[cc - 1 - r][cc - 1 - c],
                m[cc - 1 - c][cc - 1 - (cc - 1 - r)]
            );
        }
    }
}

void transpose(matrix &m) {
    const size_t rc = m.size();
    const size_t cc = m[0].size();

    for (size_t r = 0; rc > r; r++) {
        for (size_t c = r; cc > c; c++) {
            swap(m[r][c], m[c][r]);
        }
    }
}

static string itos(int i, int width=0, char fill=' ') {
    string text = "";
    while(0 < i) {
        text = (char)((i % 10) + '0') + text;
        i = i / 10;
    }

    width -= text.length();

    while (0 < width--) {
        text = fill + text;
    }

    return text;
}

static string toString(matrix &m) {
    const size_t rc = m.size();
    const size_t cc = m[0].size();

    string text = "";

    for (size_t r = 0; cc > r; r++) {
        text += "[";
        for (size_t c = 0; (cc - 1) > c; c++) {
            text += itos(m[r][c], 2, '0') + " ";
        }

        text += itos(m[r][cc - 1], 2, '0') + "]\n";
    }

    return text;
}

int main(void) {
    matrix m = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    cout << "Original:" << endl;
    cout << toString(m) << endl;
    cout << endl;

    cout << "Swap (r1, r2):" << endl;
    swap(m, 1, 2, AX_ROW);
    cout << toString(m) << endl;
    cout << endl;

    cout << "Swap (c1, c2):" << endl;
    swap(m, 1, 2, AX_COL);
    cout << toString(m) << endl;
    cout << endl;

    cout << "Transpose:" << endl;
    transpose(m);
    cout << toString(m) << endl;
    cout << endl;

    cout << "Left rotatation:" << endl;
    lrotate(m);
    cout << toString(m) << endl;
    cout << endl;

    cout << "Right rotation:" << endl;
    rrotate(m);
    cout << toString(m) << endl;
    cout << endl;

    return 0;
}
