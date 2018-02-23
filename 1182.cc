#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 50001;

int parent[maxn];
int relationship[maxn];  // relationship[i] record the relationship between i and parent[i]. 0 -> i and parent[i] is of the same kind. 1 -> parent[i] eats i. 2 -> i eats parent[i]
int depth[maxn];

void makeSet(int n) {
    memset(parent, -1, sizeof(parent));
}

int find(int x) {
    if (parent[x] == -1) {
        return x;
    }
    int px = parent[x];
    parent[x] = find(px);  // path compression
    relationship[x] = (relationship[x] + relationship[px]) % 3;
    return parent[x];
}

void Union(int x, int y, int d)  
{  
    int fx = find(x);  
    int fy = find(y);

    if (depth[fx] > depth[fy]) {
        parent[fy] = fx;
        relationship[fy] = (relationship[x] - relationship[y] + d + 2) % 3;      
    } else {
        parent[fx] = fy;
        relationship[fx] = (relationship[y] - relationship[x] - d + 4) % 3;
        if (depth[fx] == depth[fy]) {
            ++depth[fy];
        }
    }  
}  

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    makeSet(n);
    int ans = 0;
    int d, x, y;
    for (int i = 0; i < k; ++i) {
        scanf("%d%d%d", &d, &x, &y);

        if (x > n || y > n || (d == 2 && x == y)) {
            ++ans;
        } else if (find(x) == find(y)) {
            if (d == 1 && relationship[x] != relationship[y]) {
                ++ans;
            } else if (d == 2 && (relationship[y] - relationship[x] + 2) % 3 != 0) {
                ++ans;
            }
        } else {
            Union(x, y, d);
        }
    }
    printf("%d\n", ans);
    return 0;
}