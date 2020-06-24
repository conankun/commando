#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int N;
vector<int> arr;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>N;
    arr = vector<int>(N);
    for (int i = 0; i < N; i++) cin>>arr[i];
    sort(arr.begin(), arr.end());
    int left = 0, right = N - 1;
    int ans1 = 0, ans2 = N - 1;
    while (left < right) {
        while (left < right-1 && abs(arr[left] + arr[right]) > abs(arr[left] + arr[right-1])) right--;
        if (abs(arr[ans1] + arr[ans2]) > abs(arr[left] + arr[right])) ans1 = left, ans2 = right;
        left++;
    }
    cout << arr[ans1] << ' ' << arr[ans2];
}
