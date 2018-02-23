#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

const int maxn = 10005;

map<int, int> mp;
int cur;

int parent[maxn];
int parity[maxn];

void makeSet() {
    memset(parent, -1, sizeof(parent));
}

int find(int x) {
    if (parent[x] == -1) {
        return x;
    }
    int px = parent[x];
    parent[x] = find(px);
    parity[x] ^= parity[px];
    return parent[x];
}

int Hash(int x) {
    if (mp.find(x) == mp.end()) {
        mp[x] = cur++;
    }
    return mp[x];
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int ans = m;
    int x, y, d;
    char str[5];
    makeSet();
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%s", &x, &y, str);
        d = str[0] == 'o' ? 1: 0;
        x = Hash(x - 1);
        y = Hash(y);
        // printf("%d, %d\n", x, y);

        int fx = find(x);
        int fy = find(y);

        // printf("%d, %d\n", fx, fy);

        if (fx == fy) {
            if (parity[x] ^ parity[y] != d) {
                printf("%d\n", i);
                return 0;
            }
        } else {
            parent[fy] = fx;
            parity[fy] = parity[x] ^ parity[y] ^ d;
        }
    }
    printf("%d\n", m);
    return 0;
}