#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <vector>
#define MAXN 100000
#define MAXK 200
#define K(k) ((k)&1)
#define END (candid.size() - 1)
#define SQ(x) ((x) * (x))
typedef long long ll;
using namespace std;
// 누적합 배열, 최적해를 저장하는 배열.
// long long (8바이트) 배열을 MAXK * MAXN 개 만큼 잡으면 128MB 를 넘어간다.
// 하지만 D[k][*] 를 구할 때 D[k-1][*] 만 필요하지 그 이외는 필요하지 않으므로 두개만 잡아도 된다.
ll S[MAXN + 1], D[2][MAXN + 1];
// 역추적 배열.
int OPT[MAXK + 1][MAXN + 1];
int N, K;

// intersect(k, i, j) < threshold 인지 체크.
// 만약 이 값이 true 라면 덱 (deque) 의 첫번째 선분보다 두번째 선분이 현재 위치에서 더 좋은 후보이므로 덱의 앞에서 pop 할 수 있다.
inline bool canSkip(int k, int i, int j, int threshold) {
    return (D[K(k-1)][i] - D[K(k-1)][j] + S[N] * (S[j] - S[i])) <= threshold * (S[j] - S[i]);
}

// intersect(k, i, j) <= intersect(k, j, l) 인지 체크.
inline bool canRemoveLastCandidate(int k, int i, int j, int l) {
    return (D[K(k-1)][i] - D[K(k-1)][j] + S[N] * (S[j] - S[i])) * (S[l] - S[j])
            <= (D[K(k-1)][j] - D[K(k-1)][l] + S[N] * (S[l] - S[j])) * (S[j] - S[i]);
}

// D[k][*] 를 구한다.
void dp(int k) {
    deque<int> candid;
    candid.push_back(k-1);
    // k 번째 split 이라면 자를 수 있는 처음 위치가 최소 k 이다.
    for (int i = k; i <= N; i++) {
        // 현재 S[i] 에서 사용할 수 있는 최적의 선분을 얻는다.
        while (candid.size() > 1 && canSkip(k, candid[0], candid[1], S[i])) candid.pop_front();
        int j = candid.front();
        OPT[k][i] = j;
        D[K(k)][i] = D[K(k-1)][j] + S[i] * S[j] - S[N] * S[j] + S[N] * S[i] - SQ(S[i]);
        // i 번째 선분을 집어넣으므로써 필요가 없어지는 선분들을 뒤에서 제거한다.
        while (candid.size() > 1 && canRemoveLastCandidate(k, i, candid[END], candid[END-1]))
            candid.pop_back();
        candid.push_back(i);
    }
}

// 어디서 나누면 최적의 값을 없는지 역추적한다.
vector<int> backtrace(int ind) {
    vector<int> ret;
    ret.reserve(K);
    int k = K;
    while(k > 0) {
        ret.push_back(ind);
        ind = OPT[k--][ind];
    }
    reverse(ret.begin(), ret.end());
    return ret;
}
void solve() {
    for (int k = 1; k <= K; k++) {
        memset(D[K(k)], 0, sizeof(ll) * (MAXN + 1));
        dp(k);
    }
    ll ret = 0; int ind = 1;
    for (int i = 1; i <= N; i++) if (ret < D[K(K)][i]) ret = D[K(K)][i], ind = i;

    cout << ret << '\n';
    auto opt = backtrace(ind);
    for (int x : opt) cout << x << ' ';
}
void input() {
    cin>>N>>K;
    for (int i = 1; i <= N; i++) cin>>S[i], S[i] += S[i-1];
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}
