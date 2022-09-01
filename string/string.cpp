#include <string>
#include <vector>

#include "util/misc.hpp"

using namespace std;

#define METHOD_0

static int _len;
static int _clen;
static vector<string> _results;
#if defined METHOD_0
static vector<char> _flags;
#else
#endif
static vector<char> _combination;

#if defined METHOD_0
static void _permute(const string &s, const int k) {
    if (_clen == k) {
        _results.push_back(string(_combination.begin(), _combination.end()));
        return;
    }

    for (int i = 0; _len > i; i++) {
        if (0 == _flags[i]) {
            _flags[i] = 1;
            _combination[k] = s[i];
            _permute(s, k + 1);
            _flags[i] = 0;
        }
    }
}
#else
static void _permute(string s, const int l, const int r) {
    if (l == r) {
        _results.push_back(s.substr(0, _clen));
        return;
    }

    for (int i = l; r >= i; i++) {
        swap(s[l], s[i]);
        _permute(s, l + 1, r);
        swap(s[l], s[i]);
    }
}
#endif  // METHOD_0

vector<string> permute(const string &s, int clen) {
    _len = s.length();

#if defined METHOD_0
    _flags = vector<char>(_len, 0);
#endif  // METHOD_0

    _clen = clen;
    _combination = vector<char>(_clen, 0);

    _results.clear();

#if defined METHOD_0
    _permute(s, 0);
#else
    _permute(s, 0, _len - 1);
#endif  // METHOD_0

    return vector<string>(_results);
}

int main(void) {
    string s("a1b2c");
    string msg;

    for (int i = 1; i < 4; i++) {
        msg = "Permutation: " + to_string(i) + "/" + to_string(s.length());
        LOG(msg.c_str());

        vector<string> results = permute(s, i);
        for (auto result : results) {
            LOG((" + `" + result + "`").c_str());
        }
    }

    return 0;
}
