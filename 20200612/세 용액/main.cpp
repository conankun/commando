#include <algorithm>
#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
int N;
vector<ll> arr;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>N;
    arr = vector<ll>(N);
    for (int i = 0; i < N; i++) cin>>arr[i];
    sort(arr.begin(), arr.end());
    int ans1 = 0, ans2 = 1, ans3 = 2;
    for (int k = 0; k < N; k++) {
        int left = k + 1, right = N - 1;
        while (left < right) {
            while (left < right - 1 && abs(arr[left]+arr[right]+arr[k]) > abs(arr[left]+arr[right-1]+arr[k])) right--;
            if (abs(arr[ans1] + arr[ans2] + arr[ans3]) > abs(arr[left] + arr[right] + arr[k]))
                ans1 = k, ans2 = left, ans3 = right;
            left++;
        }
    }
    cout << arr[ans1] << ' ' << arr[ans2] << ' ' << arr[ans3];
}
