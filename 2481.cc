#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define lowbit(x) ((x) & (-(x)))

const int N = 100005;

int n;
int bit[N];
int ans[N];

struct Cow {
    int left;
    int right;
    int index;
} cows[N];

void add(int x, int y) {
    for (int i = x; i <= N; i += lowbit(i)) {
        bit[i] += y;
    }
}

int sum(int x) {
    int ret = 0;
    for (int i = x; i >= 1; i -= lowbit(i)) {
        ret += bit[i];
    }
    return ret;
}

bool cmp(Cow a, Cow b) {
    if (a.right == b.right) {
        return a.left < b.left;
    }
    return a.right > b.right;
}

int main() {
    while (scanf("%d", &n) == 1 && n != 0) {
        memset(bit, 0, sizeof(bit));
        memset(ans, 0, sizeof(ans));
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &cows[i].left, &cows[i].right);
            ++cows[i].left;
            cows[i].index = i;
        }
        sort(cows, cows + n, cmp);
        int cnt = 0;
        int pre_left = -1;
        int pre_right = -1;

        for (int i = 0; i < n; ++i) {
            if (pre_left == cows[i].left && pre_right == cows[i].right) {
                ++cnt;
            } else {
                cnt = 0;
                pre_left = cows[i].left;
                pre_right = cows[i].right;
            }
            ans[cows[i].index] = sum(cows[i].left) - cnt;
            add(cows[i].left, 1);
        }

        for (int i = 0; i < n; ++i) {
            printf("%d ", ans[i]);
        }
        puts("");
    }
}
