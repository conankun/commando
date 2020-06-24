/*
#include <iostream>
#define MAXN 1000000
#define SQ(x) ((x) * (x))
typedef long long ll;
using namespace std;
ll N, A, B, C, S[MAXN + 1], D[MAXN + 1];
// j + 1번째 병사부터 n 번째 병사까지를 하나의 그룹으로 묶었을때의 비용함수를 리턴한다.
inline ll evaluate(int n, int j) {
    return A * (SQ(S[n] - S[j])) + B * (S[n] - S[j]) + C;
}
ll solve() {
    for (int i = 1; i <= N; i++) {
        // 최댓값이 음수가 될 수 있으므로 j = 0 일 때의 함수값을 D[i] 의 기본 값으로 설정하고 시작한다.
        // 즉 D[i] 의 초기값은 evaluate(i, j=0) + D[j=0] 인데 D[0] = 0 이므로 생략한다.
        D[i] = evaluate(i, 0);
        for (int j = 1; j < i; j++) {
            D[i] = max(D[i], D[j] + evaluate(i, j));
        }
    }
    return D[N];
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin>> N >> A >> B >> C;
    // 입력 받음과 동시에 누적합을 구한다.
    for (int i = 1; i <= N; i++) cin>>S[i], S[i] += S[i-1];
    cout << solve();
}
*/
#include <deque>
#include <iostream>
#define MAXN 1000000
#define SQ(x) ((x) * (x))
#define END(diff) (candid[candid.size() - 1 - diff])
typedef long long ll;
using namespace std;
ll N, A, B, C, S[MAXN + 1], D[MAXN + 1];
// i 번째 선분과 j 번째 선분 (j < i)의 교점을 찾는다.
inline double intersect(int i, int j) {
    return (A * (SQ(S[j]) - SQ(S[i])) - B * (S[j] - S[i]) + D[j] - D[i]) / (2.0*A*(S[j]- S[i]));
}
// 비용함수 A * (S_n)^2 + B(S_n) + C 를 리턴한다.
inline ll evaluate(int n) {
    return A * SQ(S[n]) + B * S[n] + C;
}
ll solve() {
    // 선분 후보들을 저장하는 덱 (deque).
    deque<int> candid;
    candid.push_back(0);
    for (int n = 1; n <= N; n++) {
        // 현재 선분 후보에 있는 선분중 맨 처음 두 선분의 번호를 candid[0], candid[1] 이라고 하자.
        // candid[1]번째 선분의 기울기가 candid[0]번째 선분의 기울기보다 크므로, 만약 두 선분의 교점이 S[n] 보다 작다면
        // x = S[n] 일 때 candid[1]번째 선분을 쓰는것이 candid[0]번째 선분을 쓰는것보다 더 좋다.
        while(candid.size() > 1 && intersect(candid[0], candid[1]) < S[n]) candid.pop_front();
        int i = candid.front();
        D[n] = -2*A*S[i]*S[n] + A * SQ(S[i]) - B * S[i] + D[i] + evaluate(n);
        // 현재 선분 후보에 들어 있는 선분중 맨 끝 두 선분의 번호를 END(1), END(0) 라고 하고, 새로 추가된 선분의 번호를 n 이라 할 때
        // n 번 선분과 END(1) 번 선분의 교점이 END(0) 선분과 END(1) 번 선분의 교점보다 앞에 있다면 n 번째 선분이 END(0) 번째 선분보다 항상 기울기가
        // 크기 때문에 END(0) 번째 선분을 이용할 일이 절대 없다. 따라서 그냥 없앤다.
        while (candid.size() > 1 && intersect(n, END(1)) < intersect(END(0), END(1)))
            candid.pop_back();
        candid.push_back(n);
    }
    return D[N];
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin>> N >> A >> B >> C;
    // 입력 받음과 동시에 누적합을 구한다.
    for (int i = 1; i <= N; i++) cin>>S[i], S[i] += S[i-1];
    cout << solve();
}