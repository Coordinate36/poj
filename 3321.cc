#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define lowbit(x) ((x) & (-(x)))

const int N = 100000;

int n;
int cur;
int c[N];
int left[N];
int right[N];
int state[N];
vector<vector<int>> son(N);

void add(int x, int y) {
    for (int i = x; i <= n; i += lowbit(i)) {
        c[i] += y;
    }
}

int sum(int x) {
    int ret = 0;
    for (int i = x; i >= 1; i -= lowbit(i)) {
        ret += c[i];
    }
    return ret;
}

void dfs(int x) {
    left[x] = cur;
    for (int i = 0; i < son[x].size(); ++i) {
        ++cur;
        dfs(son[x][i]);
    }
    right[x] = cur;
}

int main() {
    scanf("%d", &n);
    int u, v;
    for (int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        son[u].push_back(v);
    }
    cur = 1;
    dfs(1);
    for (int i = 1; i <= n; ++i) {
        add(i, 1);
    }

    int m;
    int x;
    char command[2];
    scanf("%d", &m);
    while (m--) {
        scanf("%s%d", command, &x);
        if (command[0] == 'Q') {
            int ret = sum(right[x]) - sum(left[x] - 1);
            printf("%d\n", ret);
        } else {
            if (state[x] == 0) {
                add(left[x], -1);
            } else {
                add(left[x], 1);
            }
            state[x] = state[x] ^ 1;
        }
    }
}
