#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define dump cout << "[" << __LINE__ << "/" << __func__ << "]"

static int length;
static vector<char> flags;
static vector<char> result;

static void _permute(const string &s, int k) {
    if (length == k) {
        dump << " `" << string(result.begin(), result.end()) << "`" << endl;
        return;
    }

    for (int i = 0; i < s.length(); i++) {
        if (0 == flags[i]) {
            flags[i] = 1;
            result[k] = s[i];
            _permute(s, k + 1);
            flags[i] = 0;
        }
    }
}

void permute(const string &s, int slen) {
    length = slen;
    flags = vector<char>(s.length(), 0);
    result = vector<char>(length, 0);
    _permute(s, 0);
}

int main(void) {
    string s("abcde");
    permute(s, 3);
    return 0;
}
