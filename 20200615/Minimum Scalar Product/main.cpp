#include <algorithm>
#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    for (int t = 1; t<= T; t++) {
        int n;
        cin >> n;
        vector<ll> arr1(n);
        vector<ll> arr2(n);
        for (int i = 0; i < n; i++) {
            cin >> arr1[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> arr2[i];
        }
        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end(), [](auto a, auto b) { return a > b; });
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr1[i] * arr2[i];
        }
        printf("Case #%lld: %lld\n", t, sum);
    }
}