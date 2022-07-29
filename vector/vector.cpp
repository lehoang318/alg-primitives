#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "util/misc.hpp"
#include "util/profiling.hpp"

using namespace std;

static void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int max(vector<int> &v) {
    const size_t n = v.size();
    int max = v[0];

    for (size_t i = 1; n > i; i++) {
        max = (v[i] > max) ? v[i] : max;
    }

    return max;
}

int min(vector<int> &v) {
    const size_t n = v.size();
    int min = v[0];

    for (size_t i = 1; n > i; i++) {
        min = (v[i] < min) ? v[i] : min;
    }

    return min;
}

void bubbleSort(vector<int> &v) {
    const size_t n = v.size();
    bool swap_flag = false;

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                swap_flag = true;
            }
        }

        if (!swap_flag) {
            break;
        }
    }
}

void insertionSort(vector<int> &v) {
    const size_t n = v.size();
    size_t j;
    int val;

    for (size_t i = 1; i < n; i++) {
        val = v[i];

        for (j = i; j > 0; j--) {
            if (v[j - 1] > val) {
                v[j] = v[j - 1];
            } else {
                break;
            }
        }

        v[j] = val;
    }
}

void selectionSort(vector<int> &v) {
    const size_t n = v.size();
    size_t j, k;

    for (size_t i = 0; (n - 1) > i; i++) {
        j = i + 1;
        k = i;

        while (n > j) {
            if (v[k] > v[j]) {
                k = j;
            }

            j++;
        }

        if (i != k) {
            swap(v[i], v[k]);
        }
    }
}

static void partition(std::vector<int> &v, size_t first, size_t last) {
    if (first < last) {
        size_t i = first;
        size_t j;

        for (j = first + 1; j <= last; j++) {
            if (v[first] > v[j]) {
                i++;
                swap(v[i], v[j]);
            }
        }

        swap(v[first], v[i]);

        if (0 < i) {
            partition(v, first, i - 1);
        }

        partition(v, i + 1, last);
    }
}

void quickSort(vector<int> &v) {
    const size_t n = v.size();
    partition(v, 0, n - 1);
}

// 0 <= v[i] <= max
void indexSort(vector<int> &v, int max) {
    const size_t n = v.size();
    vector<int> bins(max + 1, 0);

    for (auto val : v) {
        bins[val] += 1;
    }

    size_t i = 0;
    for (size_t j = 0; max >= j; j++) {
        for (size_t k = 0; bins[j] > k; k++) {
            v[i++] = j;
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

static string toString(vector<int> &v) {
    const size_t n = v.size();

    string text = "[";

    for (size_t i = 0; (n - 1) > i; i++) {
        text += itos(v[i], 2, '0') + " ";
    }
    text += itos(v[n - 1], 2, '0') + "]\n";

    return text;
}

#define NO_OF_TESTS         3
#define NO_OF_ELEMENTS      32
#define MIN_ELEMENT_VALUE   0
#define MAX_ELEMENT_VALUE   255

void test(size_t ecnt) {
    util::Profiler profiler;
    const int timer_id = 0;
    vector<int> v = util::rng_integers(ecnt, MIN_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
    const int vmin = min(v);
    const int vmax = max(v);

    {
        cout << "Bubble\t" << ecnt << "\t" << vmin << "\t" << vmax << "\t";
        vector<int> vcopy(v);
        profiler.start(timer_id);
        bubbleSort(vcopy);
        auto duration = profiler.stop(timer_id, util::TIME_UNIT_NANOSECOND);
        cout << std::to_string(duration) << endl;
    }

    {
        cout << "Insertion\t" << ecnt << "\t" << vmin << "\t" << vmax << "\t";
        vector<int> vcopy(v);
        profiler.start(timer_id);
        insertionSort(vcopy);
        auto duration = profiler.stop(timer_id, util::TIME_UNIT_NANOSECOND);
        cout << std::to_string(duration) << endl;
    }

    {
        cout << "Selection\t" << ecnt << "\t" << vmin << "\t" << vmax << "\t";
        vector<int> vcopy(v);
        profiler.start(timer_id);
        selectionSort(vcopy);
        auto duration = profiler.stop(timer_id, util::TIME_UNIT_NANOSECOND);
        cout << std::to_string(duration) << endl;
    }

    {
        cout << "Quick\t" << ecnt << "\t" << vmin << "\t" << vmax << "\t";
        vector<int> vcopy(v);
        profiler.start(timer_id);
        quickSort(vcopy);
        auto duration = profiler.stop(timer_id, util::TIME_UNIT_NANOSECOND);
        cout << std::to_string(duration) << endl;
    }

    {
        cout << "Index\t" << ecnt << "\t" << vmin << "\t" << vmax << "\t";
        vector<int> vcopy(v);
        profiler.start(timer_id);
        indexSort(vcopy, max(vcopy));
        auto duration = profiler.stop(timer_id, util::TIME_UNIT_NANOSECOND);
        cout << std::to_string(duration) << endl;
    }
}

int main(void) {
    srand(time(NULL));
    const vector<size_t> ecounts = {16UL, 63UL, 256UL, 1025UL, 4096UL, 16383UL};

    cout << "Type\tSize\tMin\tMax\tDuration(ns)"<< endl;

    for (auto val : ecounts) {
        test(val);
    }

    return 0;
}
