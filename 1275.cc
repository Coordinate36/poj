#include <iostream>

using namespace std;

const int maxn = 1005;

int m;
int R[24];
int applicants[maxn];

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        for (int i = 0; i < 24; ++i) {
            scanf("%d", &R[i]);
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            scanf("%d", &applicants[i]);
        }
        
    }
}