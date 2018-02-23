#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 605;

int parent[maxn];
int relationship[maxn];

int num[maxn][2];
vector<int> members[maxn][2];
int visit[maxn];
int dp[maxn][maxn];

void reset() {
    memset(parent, -1, sizeof(parent));
    memset(relationship, 0, sizeof(relationship));
    memset(visit, 0, sizeof(visit));
    memset(num, 0, sizeof(num));
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < maxn; ++i) {
        members[i][0].clear();
        members[i][1].clear();
    }
}

int find(int x) {
    if (parent[x] == -1) {
        return x;
    }
    int px = parent[x];
    parent[x] = find(px);
    relationship[x] = relationship[x] ^ relationship[px];
    return parent[x];
}

int main() {
    int n, p1, p2;
    int x, y, d;
    char str[4];
    while (scanf("%d%d%d", &n, &p1, &p2) == 3 && (n || p1 || p2)) {
        reset();
        while (n--) {
            scanf("%d%d%s", &x, &y, str);
            d = str[0] == 'y' ? 0: 1;
            int fx = find(x);
            int fy = find(y);
            if (fx != fy) {
                parent[fx] = fy;
                relationship[fx] = relationship[x] ^ relationship[y] ^ d;
            }
        }

        int cnt = 1;
        for (int i = 1; i <= p1 + p2; ++i) {
            if (visit[i]) {
                continue;
            }
            int fi = find(i);
            for (int j = i; j <= p1 + p2; ++j) {
                int fj = find(j);
                if (fi == fj) {
                    visit[j] = 1;
                    ++num[cnt][relationship[j]];
                    members[cnt][relationship[j]].push_back(j);
                }
            }
            ++cnt;
        }
        // for (int i = 0; i < cnt; ++i) {
        //     printf("%d, %d\n", num[i][0], num[i][1]);
        // }
        dp[0][0] = 1;

        for (int i = 1; i < cnt; ++i) {
            for (int j = p1; j >= 0; --j) {
                if (j >= num[i][0]) {
                    dp[i][j] += dp[i - 1][j - num[i][0]];
                }
                if (j >= num[i][1]) {
                    dp[i][j] += dp[i - 1][j - num[i][1]];
                }
            }
        }
        if (dp[cnt - 1][p1] != 1) {
            printf("no\n");
            continue;
        }
        vector<int> ans;
        for (int i = cnt - 1; i >= 1; --i) {
            if (p1 >= num[i][0] && p2 >= num[i][1] && dp[i - 1][p1 - num[i][0]] == 1) {
                ans.insert(ans.end(), members[i][0].begin(), members[i][0].end());
                p1 -= num[i][0];
                p2 -= num[i][1];
            } else if (p1 >= num[i][1] && p2 >= num[i][0] && dp[i - 1][p1 - num[i][1]] == 1) {
                ans.insert(ans.end(), members[i][1].begin(), members[i][1].end());
                p1 -= num[i][1];
                p2 -= num[i][0];
            }
        }
        sort(ans.begin(), ans.end());
        for(int i = 0; i < ans.size(); ++i) {
            printf("%d\n", ans[i]); 
        }
        printf("end\n");
    }
}

