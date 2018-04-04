#include <iostream>

using namespace std;

const int MAXN = 100;
const int MAXM = 100000;

int A[MAXN];
int C[MAXM];
int dp[MAXM + 1];

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && (n != 0 || m != 0)) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &A[i]);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d", &C[i]);
        }
        for (int i = 1; i <= m; ++i) {
            dp[i] = -1;
        }
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (dp[j] >= 0) {
                    dp[j] = C[i];
                } else if (j < A[i] || dp[j - A[i]] <= 0) {
                    dp[j] = -1;
                } else {
                    dp[j] = dp[j - A[i]] - 1;
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= m; ++i) {
            ans += dp[i] >= 0;
        }
        printf("%d\n", ans);
    }
}