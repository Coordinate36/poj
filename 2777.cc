#include <iostream>

using namespace std;

#define lchild(i) (i << 1)
#define rchild(i) ((i << 1) + 1)

const int maxn = 100005;

struct Node {
    int left;
    int right;
    int color;
    bool cover;
} nodes[maxn << 2];

int ans;

void build(int left, int right, int t) {
    nodes[t].left = left;
    nodes[t].right = right;
    nodes[t].color = 1;
    nodes[t].cover = true;
    if (left == right) {
        return;
    }
    int mid = (left + right) >> 1;
    build(left, mid, lchild(t));
    build(mid + 1, right, rchild(t));
}

void pushUp(int t) {
    nodes[t].color = nodes[lchild(t)].color | nodes[rchild(t)].color;
}

void pushDown(int t) {
    nodes[lchild(t)].color = nodes[t].color;
    nodes[rchild(t)].color = nodes[t].color;
    nodes[lchild(t)].cover = true;
    nodes[rchild(t)].cover = true;
    nodes[t].cover = false;
}

void update(int left, int right, int color, int t) {
    if (nodes[t].left == left && nodes[t].right == right) {
        nodes[t].color = color;
        nodes[t].cover = true;
        return;
    }
    if (nodes[t].color == color) {
        return;
    }
    if (nodes[t].cover) {
        pushDown(t);
    }
    int mid = (nodes[t].left + nodes[t].right) >> 1;
    if (right <= mid) {
        update(left, right, color, lchild(t));
    } else if (left > mid) {
        update(left, right, color, rchild(t));
    } else {
        update(left, mid, color, lchild(t));
        update(mid + 1, right, color, rchild(t));
    }
    pushUp(t);
}

void query(int left, int right, int t) {
    if ((nodes[t].left == left && nodes[t].right == right) || nodes[t].cover) {
        ans |= nodes[t].color;
        return;
    }
    int mid = (nodes[t].left + nodes[t].right) >> 1;
    if (right <= mid) {
        query(left, right, lchild(t));
    } else if (left > mid) {
        query(left, right, rchild(t));
    } else {
        query(left, mid, lchild(t));
        query(mid + 1, right, rchild(t));
    }
}

int main() {
    int n, t, q;
    scanf("%d%d%d", &n, &t, &q);
    build(1, n, 1);
    int a, b, c;
    char op[2];
    while (q--) {
        scanf("%s%d%d", op, &a, &b);
        if (a > b) {
            swap(a, b);
        }
        if (op[0] == 'C') {
            scanf("%d", &c);
            update(a, b, 1 << (c - 1), 1);
        } else {
            ans = 0;
            int res = 0;
            query(a, b, 1);
            while (ans) {
                res += ans & 1;
                ans >>= 1;
            }
            printf("%d\n", res);
        }
    }
    return 0;
}