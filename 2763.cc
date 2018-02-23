#include<iostream>
#include<cstring>

using namespace std;

#define lowbit(x) ((x) & (-(x)))
#define min(x, y) (dep[x] <= dep[y] ? (x): (y))
#define mem(x, y) memset(x, y, sizeof(x))

const int maxn = 100005 << 1;

struct Edge {
    int to;
    int id;
    int weight;
    int next;
} edges[maxn];


int tot;
int s;
int bitn;
int w[maxn];
int id[maxn];
int es[maxn];
int dep[maxn];
int vs[maxn];
int bit[maxn];
int dp[maxn][20];
int head[maxn];

void add(int x, int y) {
    for (int i = x; i < bitn; i += lowbit(i)) {
        bit[i] += y;
    }
}

int sum(int x) {
    int ret = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        ret += bit[i];
    }
    return ret;
}

void addEdge(int u, int v, int id, int w) {
    edges[tot].to = v;
    edges[tot].id = id;
    edges[tot].weight = w;
    edges[tot].next = head[u];
    head[u] = tot++;
}

void dfs(int u, int p, int sum, int &k) {
    id[u] = k;
    vs[k] = u;
    dep[k++] = sum;
    for (int i = head[u]; ~i; i = edges[i].next) {
        Edge &e = edges[i];
        if (e.to != p) {
            add(k, e.weight);
            es[e.id * 2] = k;
            dfs(e.to, u, sum + e.weight, k);
            vs[k] = u;
            dep[k++] = sum;
            add(k, -e.weight);
            es[e.id * 2 + 1] = k;
        }
    }
}

void initRmq(int n) {
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = i;
    }
    for (int j = 1; j < 20; ++j) {
        for (int i = 0; i + (1 << j) - 1 <= n; ++i) {
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }
}

void init(int n) {
    tot = 0;
    bitn = n * 2 - 1;
    memset(head, -1, sizeof(head));
    memset(bit, 0, sizeof bit);
}

int query(int l, int r) {
    int k;
    for (k = 1; (1 << k) < (r - l + 1); ++k);
    --k;
    return min(dp[l][k], dp[r - (1 << k) + 1][k]);
}

int lca(int a, int b) {
    if (id[a] > id[b]) {
        swap(a, b);
    }
    return vs[query(id[a], id[b])];
}

int main() {
    int n, q, u, v;
    scanf("%d%d%d", &n, &q, &s);
    init(n);

    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d%d", &u, &v, &w[i]);
        --u, --v;
        addEdge(u, v, i, w[i]);
        addEdge(v, u, i, w[i]);
    }

    int k = 0;
    dfs(0, -1, 0, k);
    initRmq(2 * n - 1);

    int op, a, b;
    --s;
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &op, &a);
        --a;
        if (op == 0) {
            int p = lca(s, a);
            printf("%d\n", sum(id[s]) + sum(id[a]) - 2 * sum(id[p]));
            s = a;
        } else {
            scanf("%d", &b);
            add(es[2 * a], b - w[a]);
            add(es[2 * a + 1], w[a] - b);
            w[a] = b;
        }
    }
    return 0;
}