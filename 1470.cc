#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 905;

int n;
int parent[maxn];
int visit[maxn];
int ans[maxn]; // ans[i]是i作为LCA的次数
int is_root[maxn];
vector<vector<int>> son(maxn);
vector<vector<int>> query(maxn);

void Init() {
    int size = (n + 1) * sizeof(int);
    memset(parent, -1, size);
    memset(visit, 0, size);
    memset(ans, 0, size);
    memset(is_root, 1, size);
    for (int i = 1; i <= n; ++i) {
        son[i].clear();
        query[i].clear();
    }
}

int find(int x) {
    if (parent[x] == x) {
        return x;
    }
    parent[x] = find(parent[x]);
    return parent[x];
}

void tarjan(int x) {
    parent[x] = x;
    for (int i = 0; i < son[x].size(); ++i) {
        tarjan(son[x][i]);
        parent[son[x][i]] = x;
    }
    visit[x] = 1;
    for (int i = 0; i < query[x].size(); ++i) {
        if (visit[query[x][i]]) {
            ++ans[find(query[x][i])];
        }
    }
}

int main() {
    char tmp[3];
    while (scanf("%d", &n) == 1) {
        Init();
        int x, y, m;
        for (int i = 0; i < n; ++i) {
            scanf("%d%2s%d%1s", &x, tmp, &m, tmp);
            while (m--) {
                scanf("%d", &y);
                is_root[y] = 0;
                son[x].push_back(y);
            }
        }

        scanf("%d", &m);
        while (m--) {
            scanf("%1s%d%d%1s", tmp, &x, &y, tmp);
            query[x].push_back(y);
            query[y].push_back(x);
        }
        for (int i = 1; i <= n; ++i) {
            if (is_root[i]) {
                tarjan(i);
                break;
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (ans[i]) {
                printf("%d:%d\n", i, ans[i]);
            }
        }
    }
    return 0;
}