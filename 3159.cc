#include <cstdio>
#include <cstring>
#include <stack>
#include <climits>

using namespace std;

const int maxn = 30005;
const int maxm = 150005;

struct Node {
    int to;
    int weight;
    int next;
} edges[maxm];

int tot;
int Head[maxn];
int dist[maxn];
int visit[maxn];
int queue[maxm];

void addEdge(int u, int v, int weight) {
    edges[tot].to = v;
    edges[tot].weight = weight;
    edges[tot].next = Head[u];
    Head[u] = tot++;
}

void spfa() {    
    stack<int> q;
    q.push(1); 
    dist[1] = 0;
    while(!q.empty()) {  
        int cur = q.top(); 
        q.pop();
        visit[cur] = 0;
        for(int i = Head[cur]; i != -1; i = edges[i].next) {  
            int id = edges[i].to;  
            if(dist[id] > dist[cur] + edges[i].weight) {
                printf("%d\n", id);
                dist[id] = dist[cur] + edges[i].weight; 
                if(!visit[id]) {
                    q.push(id);
                    visit[id] = true;
                }
            }
        }  
    }  
}  

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    tot = 0;
    memset(Head, -1, sizeof(Head));
    for (int i = 0; i <= n; ++i) {
        dist[i] = INT_MAX;
    }

    int u, v, w;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
    }
    
    spfa();
    // for (int i = 0; i < n; ++i) {
    //     printf("%d ", dist[i]);
    // }
    // printf("%d\n", dist[n]);
    return 0;
}
