#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
int main() {
    ll mn, mx;
    scanf("%lld%lld", &mn, &mx);
    vector<bool> is_square_no_no(mx - mn + 1, true);
    for (ll i = 2; i * i <= mx; i++) {
        ll sq = i * i;
        int count = 0;
        ll start = mn - mn % sq;
        if (start < mn) {
            start += sq;
        }
        for (ll j = start; j <= mx; j++) {
            if (!(j % sq)) {
                is_square_no_no[j-mn] = false;
                j += (sq - 1);
            }
        }
    }
    int count = 0;
    for (int i = 0; i < is_square_no_no.size(); i++) {
        count += is_square_no_no[i];
    }
    printf("%lld", count);
}