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

static void swap(matrix & m, size_t i, size_t j, tAxis ax=AX_ROW) {
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

static void transpose(matrix &m) {
    const size_t rc = m.size();
    const size_t cc = m[0].size();

    for (size_t r = 0; rc > r; r++) {
        for (size_t c = r; cc > c; c++) {
            swap(m[r][c], m[c][r]);
        }
    }
}

static vector<matrix> generate_magic_squares() {
    vector<matrix> ms;

    matrix m0 = {
        {8, 1, 6},
        {3, 5, 7},
        {4, 9, 2}
    };

    ms.push_back(m0);

    matrix m01(m0);
    swap(m01, 0, 2, AX_ROW);
    ms.push_back(m01);

    matrix m02(m01);
    swap(m02, 0, 2, AX_COL);
    ms.push_back(m02);

    matrix m03(m02);
    swap(m03, 0, 2, AX_ROW);
    ms.push_back(m03);

    matrix m1(m0);
    transpose(m1);
    ms.push_back(m1);

    matrix m11(m1);
    swap(m11, 0, 2, AX_ROW);
    ms.push_back(m11);

    matrix m12(m11);
    swap(m12, 0, 2, AX_COL);
    ms.push_back(m12);

    matrix m13(m12);
    swap(m13, 0, 2, AX_ROW);
    ms.push_back(m13);

    return ms;
}

static int cost(const matrix &m0, const matrix &m1) {
    const size_t n = m0.size();
    int cost = 0;
    for (size_t r = 0; n > r; r++) {
        for (size_t c = 0; n > c; c++) {
            if (m0[r][c] > m1[r][c]) {
                cost += m0[r][c] - m1[r][c];
            } else {
                cost += m1[r][c] - m0[r][c];
            }
        }
    }

    return cost;
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

/*
 * Complete the 'formingMagicSquare' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY s as parameter.
 */

int formingMagicSquare(vector<vector<int>> s) {
    const size_t n = s.size();
    const size_t nn = n * n;
    int minCost = nn * (nn + 1) / 2;
    int c;

    vector<matrix> magic_squares = generate_magic_squares();

    for (matrix &m : magic_squares) {
        cout << toString(m) << endl;
        c = cost(m, s);
        cout << "-> Cost: " << c << endl;
        minCost = (c < minCost) ? c : minCost;
    }

    return minCost;
}

int main(void) {
    matrix m = {
        {7, 2, 9},
        {6, 6, 2},
        {5, 1, 2}
    };

    formingMagicSquare(m);
}
