#include <iostream>
#include <climits>

using namespace std;

const int MAXN = 105;
const int MAXM = 105;

int C[MAXN][MAXM];

void preCal() {
    for (int i = 1; i < MAXN; ++i) {
        C[i][0] = 1;
        C[i][1] = i;
    }
    for (int i = 2; i < MAXN; ++i) {
        for (int j = 2; j <= i; ++j) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
}

int main() {
    preCal();
    int n, m;
    cout << LONG_MAX << endl;
    while ((cin >> n >> m) && n != 0) {
        cout << n << " things taken " << m << " at a time is " << C[n][m] << " exactly." << endl;
    }
    return 0;
}