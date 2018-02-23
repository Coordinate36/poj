#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

const int maxn = 50005;
const int maxe = 500005;

struct Node {
    int to;
    int weight;
    int next;
} edges[maxn << 2];

int tot;
int max_num;
int Head[maxn];
int dist[maxn];
int visit[maxn];
int queue[maxe];

void addEdge(int u, int v, int weight) {
    edges[tot].to = v;
    edges[tot].weight = weight;
    edges[tot].next = Head[u];
    Head[u] = tot++;
}

void spfa() {
    int head = 0;
    int tail = 1;
    for (int i = 0; i <= max_num; ++i) {
        dist[i] = -INT_MAX;
    }
    dist[0] = 0;
    queue[0] = 0;
    while (tail > head) {
        int u = queue[head];
        visit[u] = 1;
        for (int i = Head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            // cout << u << ", " << v << endl;
            if (dist[v] < dist[u] + edges[i].weight) {
                dist[v] = dist[u] + edges[i].weight;
                if (!visit[v]) {
                    visit[v] = 1;
                    queue[tail++] = v;
                }
            }
        }
        visit[u] = 0;
        ++head;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    max_num = 0;
    tot = 0;
    memset(Head, -1, sizeof(Head));
    int u, v, w;
    while (n--) {
        scanf("%d%d%d", &u, &v, &w);
        max_num = max(max_num, v + 1);
        addEdge(u, v + 1, w);
    }
    for (int i = 0; i <= max_num; ++i) {
        addEdge(i, i + 1, 0);
        addEdge(i + 1, i, -1);
    }
    spfa();
    printf("%d\n", dist[max_num]);
    return 0;
}