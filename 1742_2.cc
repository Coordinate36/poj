#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
bool dp[100010];
int a[110], c[110];
bool q[100010];
int main(int argc, char const* argv[]) {
    int n, m;
    while (~scanf("%d%d", &n, &m) && (n + m)) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &c[i]);
        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        int ret = 0;
        for (int i = 0; i < n; i++) {
            if (c[i] == 1) {
                for (int j = m; j >= a[i]; j--) {
                    if (!dp[j] && dp[j - a[i]]) {
                        ret++;
                        dp[j] = 1;
                    }
                }
            } else if (c[i] * a[i] >= m) {
                for (int j = a[i]; j <= m; ++j) {
                    if (!dp[j] && dp[j - a[i]]) {
                        dp[j] = 1;
                        ret++;
                    }
                }
            } else {
                for (int mod = 0; mod < a[i]; mod++) {
                    int l = 0, r = 0;
                    int sum = 0;
                    for (int j = mod; j <= m; j += a[i]) {
                        if (r > l && r - l > c[i]) {
                            sum -= q[l++];
                        }
                        sum += dp[j];
                        q[r++] = dp[j];
                        if (!dp[j] && sum) {
                            dp[j] = 1;
                            ret++;
                        }
                    }
                }
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
