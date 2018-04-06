#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

const int MAX_CASH = 100001;

int cash;
int n;
bool dp[MAX_CASH];

inline void completePack(int w) {
    for (int i = w; i <= cash; ++i) {
        dp[i] = dp[i] | dp[i - w];
    }
}

inline void zeroOnePack(int w) {
    for (int i = cash; i >= w; --i) {
        dp[i] = dp[i] | dp[i - w];
    }
}

inline void multiPack(int w, int n) {
    if (w * n >= cash) {
        completePack(w);
    } else {
        int shift = 0;
        while ((1 << shift) <= n) {
            n -= 1 << shift;
            zeroOnePack(w << shift);
            ++shift;
        }
        if (n) {
            zeroOnePack(w * n);
        }
    }
}

int main() {
    while (cin >> cash >> n) {
        memset(dp, 0, sizeof(dp));
        dp[0] = true;
        int money, num;
        while (n--) {
            cin >> num >> money;
            multiPack(money, num);
        }
        for (int i = cash; i >= 0; --i) {
            if (dp[i]) {
                cout << i << endl;
                break;
            }
        }
    }
    return 0;
}