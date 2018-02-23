#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 100005;

struct Node {
    int to;
    int weight;
    int next;
};

int n, m;
int cnt, qcnt;
int dis[maxn];
int parent[maxn];
int visit[maxn];
int head[maxn];
int qhead[maxn];
Node edges[maxn];
Node qedges[maxn];


void init() {
    memset(dis, 0, sizeof(dis));
    memset(parent, -1, sizeof(parent));
    memset(visit, 0, sizeof(visit));
    memset(head, -1, sizeof(head));
    memset(qhead, -1, sizeof(qhead));
    memset(edges, 0, sizeof(edges));
    memset(qedges, 0, sizeof(qedges));
    cnt = 0;
    qcnt = 0;
}

void add_edge(int x, int y, int weight) {
    edges[cnt].to = y;
    edges[cnt].weight = weight;
    edges[cnt].next = head[x];
    head[x] = cnt++;
}

void add_qedge(int x, int y) {
    qedges[qcnt].to = y;
    qedges[qcnt].next = qhead[x];
    qhead[x] = qcnt++;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void tarjan(int x) {
    parent[x] = x;
    visit[x] = 1;
    for (int i = head[x]; i != -1; i = edges[i].next) {
        if (!visit[edges[i].to]) {
            dis[edges[i].to] = dis[x] + edges[i].weight;
            tarjan(edges[i].to);
            parent[edges[i].to] = x;
        }
    }
    for (int i = qhead[x]; i != -1; i = qedges[i].next) {
        if (visit[qedges[i].to]) {
            qedges[i].weight = dis[x] + dis[qedges[i].to] - 2 * dis[find(qedges[i].to)];
            qedges[i ^ 1].weight = qedges[i].weight;
        }
    }
}

int main() {
    char tmp[3];
    while (scanf("%d%d", &n, &m) == 2) {
        init();
        int x, y, w, k;
        while (m--) {
            scanf("%d%d%d%s", &x, &y, &w, tmp);
            add_edge(x, y, w);
            add_edge(y, x, w);
        }

        scanf("%d", &k);
        while (k--) {
            scanf("%d%d", &x, &y);
            add_qedge(x, y);
            add_qedge(y, x);
        }
        tarjan(1);
        for (int i = 1; i <= qcnt; i += 2) {
            printf("%d\n", qedges[i].weight);
        }
    }
    return 0;
}