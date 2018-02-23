#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 505;
const int maxm = 2005;

int parent[maxn];
int relationship[maxn];
int depth[maxn];
int left[maxm];
int right[maxm];
int d[maxm];
int judge[maxn];
int pos[maxn];

void makeSet() {
    memset(parent, -1, sizeof(parent));
    memset(relationship, 0, sizeof(relationship));
    memset(depth, 0, sizeof(depth));
}

int find(int x) {
    if (parent[x] == -1) {
        return x;
    }
    int px = parent[x];
    parent[x] = find(px);
    relationship[x] = (relationship[x] + relationship[px]) % 3;
    return parent[x];
}

void Union(int x, int y, int d)  
{  
    int fx = find(x);  
    int fy = find(y);

    if (depth[fx] > depth[fy]) {
        parent[fy] = fx;
        relationship[fy] = (relationship[x] - relationship[y] - d + 6) % 3; 
    } else {
        parent[fx] = fy;
        relationship[fx] = (relationship[y] - relationship[x] + d + 3) % 3;
        if (depth[fx] == depth[fy]) {
            ++depth[fy];
        }
    }  
}  

void input(int m) {
    char c;
    for (int i = 0; i < m; ++i) {
        scanf("%d%c%d", &left[i], &c, &right[i]);
        switch (c) {
            case '=': d[i] = 0; break;
            case '<': d[i] = 1; break;
            case '>': d[i] = 2;
        }
    }
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        input(m);
        memset(judge, 1, sizeof(judge));
        memset(pos, -1, sizeof(pos));

        for (int i = 0; i < n; ++i) {
            makeSet();
            for (int j = 0; j < m; ++j) {
                if (left[j] == i || right[j] == i) {
                    continue;
                }
                int fx = find(left[j]);
                int fy = find(right[j]);
            
                if (fx == fy) {
                    if ((relationship[right[j]] + d[j]) % 3 != relationship[left[j]]) {
                        judge[i] = 0;
                        pos[i] = j + 1;
                        break;
                    }
                } else {
                    Union(left[j], right[j], d[j]);
                }
            }
        }
        int judge_num = 0;
        int judger = 0;
        int max_err = 0;
        for (int i = 0; i < n; ++i) {
            if (judge[i]) {
                judge_num++;
                judger = i;
            } else {
                max_err = max_err > pos[i] ? max_err: pos[i];
            }
        }
        switch(judge_num) {
            case 0: printf("Impossible\n"); break;
            case 1: printf("Player %d can be determined to be the judge after %d lines\n", judger, max_err); break;
            default: printf("Can not determine\n");
        }
    }

    return 0;
}
