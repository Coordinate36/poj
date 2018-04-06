#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 105;
const int MAXM = 100005;

int A[MAXN];
int C[MAXN];
int dp[MAXM];
int deque[MAXM];

int multiPack(int n, int m) {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (C[i] == 1) {
            for (int j = m; j >= A[i]; --j) {
                if (!dp[j] && dp[j - A[i]]) {
                    dp[j] = 1;
                    ++res;
                }
            }
        } else if (A[i] * C[i] >= m) {
            for (int j = A[i]; j <= m; ++j) {
                if (!dp[j] && dp[j - A[i]]) {
                    dp[j] = 1;
                    ++res;
                }
            }
        } else {
            for (int mod = 0; mod < A[i]; ++mod) {
                int left = 0, right = 0;
                int sum = 0;
                for (int j = mod; j <= m; j += A[i]) {
                    if (right > left && right - left > C[i]) {
                        sum -= deque[left++];
                    }
                    deque[right++] = dp[j];
                    sum += dp[j];
                    if (!dp[j] && sum) {
                        dp[j] = 1;
                        ++res;
                    }
                }
            }
        }
    }
    return res;
}

int main() {
    int n, m;
    while ((cin >> n >> m) && n != 0 && m != 0) {
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> C[i];
        }
        cout << multiPack(n, m) << endl;
    }
}