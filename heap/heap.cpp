#include <algorithm>
#include <string>
#include <vector>

#include "util/misc.hpp"

using namespace std;

class Heap {
public:
    Heap() {}
    Heap(vector<int> _data) : data(_data) {
        const int n = data.size();
        for (int i = (n - 1); 0 <= i; i--) {
            int val = data[i];

            int j = i;
            int fchild_idx = ((j + 1) << 1) - 1;
            while (n > fchild_idx) {
                // Find biggest child
                if ((n > (fchild_idx + 1)) && (data[fchild_idx + 1] > data[fchild_idx])) {
                    fchild_idx++;
                }

                if (data[fchild_idx] > val) {
                    data[j] = data[fchild_idx];
                    data[fchild_idx] = val;
                    j = fchild_idx;
                    fchild_idx = ((j + 1) << 1) - 1;
                } else {
                    break;
                }
            }
        }
    }

    bool add(int val) {
        int i = data.size();
        data.push_back(val);

        while ((0 < i) && (data[i >> 1] < data[i])) {
            int tmp = data[i];
            data[i] = data[i >> 1];

            i = i >> 1;
            data[i] = tmp;
        }

        return true;
    }

    bool remove(const int val) {
        return remove_idx(find_sub_tree(val, 0));
    }

    bool remove_idx(int idx) {
        if ((0 > idx) || (data.size() <= idx)) {
            return false;
        }

        data[idx] = data[data.size() - 1];
        data.pop_back();

        int val = data[idx];

        while (data.size() > idx) {
            int fchild_idx = ((idx + 1) << 1) - 1;

            if (data[fchild_idx] > val) {
                data[idx] = data[fchild_idx];
                data[fchild_idx] = val;
            }

            idx = ((idx + 1) << 1) - 1;
        }

        return true;
    }

    int find(const int val) {
        if (data.empty()) {
            return -1;
        }

        return find_sub_tree(val, 0);
    }

    string traverse(void) {
        string txt("");
        int i = 0;
        int level = 0;

        while (data.size() > i) {
            const int start = util::exp(2, level) - 1;
            const int end = util::exp(2, (level + 1)) - 1;

            txt += "\n" + to_string(level) + "/\t";
            for (i = start; ((end > i) && (data.size() > i)); i++) {
                txt += to_string(data[i])  + " ";
            }

            level++;
        }

        return (txt + "\n");
    }

    string toString(void) {
        return util::arr2str(data);
    }

private:
    int find_sub_tree(const int val, int parent_idx) {
        if ((0 > parent_idx) || (data.size() <= parent_idx) || (data[parent_idx] < val)) {
            return -1;
        }

        if (data[parent_idx] == val) {
            return parent_idx;
        }

        parent_idx = (parent_idx + 1) << 1;
        int i = find_sub_tree(val, parent_idx);
        if (0 > i) {
            i = find_sub_tree(val, (parent_idx - 1));
        }

        return i;
    }

    vector<int> data;
};  // class Heap

int main(void) {
    RAND_INIT();

    vector<int> data = util::rng_integers(10, 0, 255);
    LOG(("Input: " + util::arr2str(data)).c_str());

    Heap h;
    for (auto val : data) {
        LOG(("Adding " + to_string(val)).c_str());
        h.add(val);
    }

    LOG(("=> " + h.toString()).c_str());
    LOG(h.traverse().c_str());

    LOG(("Removing " + to_string(data[3])).c_str());
    h.remove(data[3]);

    LOG(h.traverse().c_str());

    LOG("Removing element at index 0");
    h.remove_idx(0);

    LOG(h.traverse().c_str());

    LOG("Removing element at index 5");
    h.remove_idx(5);

    LOG(h.traverse().c_str());

    Heap h1(data);
    LOG(("Heapify: " + h1.toString()).c_str());
    LOG(h1.traverse().c_str());

    return 0;
}
