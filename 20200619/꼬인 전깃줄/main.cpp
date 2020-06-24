#include <iostream>
#include <vector>
#define LEFT (node<<1)
#define RIGHT (LEFT + 1)
using namespace std;
struct SegTree {
    vector<int> tree;
    int n;
    void add(int pos, int val, int node, int ns, int ne) {
        if (pos < ns || pos > ne) return;
        if (ns == ne) {
            tree[node]=val;
            return;
        }
        int m = (ns + ne) >> 1;
        add(pos, val, LEFT, ns, m);
        add(pos, val, RIGHT, m + 1, ne);
        tree[node] = max(tree[LEFT], tree[RIGHT]);
    }
    int query(int s, int e, int node, int ns, int ne) {
        if (e < ns || s > ne) return 0;
        if (s <= ns && ne <= e) return tree[node];
        int m = (ns + ne) >> 1;
        return max(query(s, e, LEFT, ns, m), query(s, e, RIGHT, m + 1, ne));
    }
public:
    SegTree(int n) : n(n), tree(4*n) {}
    void add(int pos, int val) {
        return add(pos, val, 1, 1, n);
    }
    int query(int s, int e) {
        return query(s, e, 1, 1, n);
    }
};
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N;
    cin>>N;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) cin>>arr[i];
    int ans = 0;
    SegTree seg(N);
    for (int i = 0; i < N; i++) {
        int ret = seg.query(1, arr[i] - 1) + 1;
        ans = max(ans, ret);
        seg.add(arr[i], ret);
    }
    cout << N - ans;
}
