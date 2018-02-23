#include <cstdio>
#include <vector>
#include <set>

using namespace std;

set<int> destroyed;
vector<int> st;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    char op[2];
    int x;
    while (m--) {
        scanf("%s%d", op, &x);
        switch (op[0]) {
            case 'D': {
                destroyed.insert(x);
                st.push_back(x);
                break;
            }
            case 'Q': {
                if (destroyed.find(x) != destroyed.end()) {
                    printf("0\n");
                } else {
                    int left = 1;
                    int right = n;
                    set<int>::iterator iter;
                    iter = destroyed.upper_bound(x);
                    if (iter != destroyed.end()) {
                        right = *iter - 1;
                    }
                    if (iter != destroyed.begin()) {
                        --iter;
                        left = *iter + 1;
                    }
                    printf("%d\n", right - left + 1);
                }
                break;
            }
            case 'R': {
                int recovered = st.back();
                st.pop_back();
                destroyed.erase(recovered);
            }
        }
    }
    return 0;
}

