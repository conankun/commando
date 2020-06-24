#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
bool decide(int size, const vector<ll> &X, const ll &B) {
    int mid = size >> 1;
    ll cost = 0;
    for (int i = 0; i < mid; i++) cost += X[mid] - X[i];
    for (int i = mid + 1; i < size; i++) cost += X[i] - X[mid];
    if (cost <= B) return true;
    int l = 0, r = size - 1;
    while (r + 1 < X.size()) {
        cost -= X[mid] - X[l];
        l++, r++, mid++;
        cost += X[r] - X[mid];
        if (!(size & 1)) cost += X[mid] - X[mid-1];
        if (cost <= B) return true;
    }
    return false;
}
ll bs(int low, int high, const vector<ll> &X, const ll &B) {
    if (low > high) return -1;
    int size = (low + high) >> 1;
    if (decide(size, X, B)) {
        return max<ll>(bs(size + 1, high, X, B), size);
    } else {
        return bs(low, size - 1, X, B);
    }
}
ll besthub(int R, ll L, const vector<ll> &X, ll B) {
    return bs(1, R, X, B);
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll R, L, B;
    cin>>R>>L>>B;
    vector<ll> X(R);
    for (int i = 0; i < R; i++) cin>>X[i];
    cout << besthub(R, L, X, B);
}
