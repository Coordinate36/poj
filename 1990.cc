#include <cstdio>
#include <algorithm>
using namespace std;

#define lowbit(x) ((x) & (-(x)))

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 20005;

pii cows[maxn];

int bit_num[maxn];
int bit_pos[maxn];

int sum(int *bit, int x) {
    int ret = 0;
    for (int i = x; i >= 1; i -= lowbit(i)) {
        ret += bit[i];
    }
    return ret;
}

void add(int *bit, int x, int y) {
    for (int i = x; i <= maxn; i += lowbit(i)) {
        bit[i] += y;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &cows[i].first, &cows[i].second);
    }

    sort(cows, cows + n);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int v = cows[i].first;
        int pos = cows[i].second;

        int nleft = sum(bit_num, pos - 1);
        int nright = i - nleft;

        ll sleft = nleft * pos - sum(bit_pos, pos - 1);
        ll sright = sum(bit_pos, maxn) - sum(bit_pos, pos) - nright * pos;

        ans += (sleft + sright) * v;

        add(bit_num, pos, 1);
        add(bit_pos, pos, pos);
    }

    printf("%lld\n", ans);

    return 0;
}