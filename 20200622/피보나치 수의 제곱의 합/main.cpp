#include <cstring>
#include <iostream>
#include <vector>
#define MOD 1000000007LL
typedef long long ll;
using namespace std;
struct Matrix {
    vector<vector<ll>> elem;
    Matrix(vector<vector<ll>> elem) : elem(elem) {}
    Matrix() {
        elem = vector<vector<ll>>(6, vector<ll>(6, 0));
    }
    Matrix operator*(const Matrix &mat) const {
        Matrix ret;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                for (int k = 0; k < 6; k++) {
                    ret.elem[i][j] += elem[i][k] * mat.elem[k][j];
                    ret.elem[i][j] %= MOD;
                }
            }
        }
        return ret;
    }
    static Matrix identity() {
        Matrix ret;
        for (int i = 0; i < 6; i++) ret.elem[i][i] = 1;
        return ret;
    }
    static Matrix pow(const Matrix &mat, ll k) {
        if (!k) return Matrix::identity();
        Matrix ret = pow(mat, k >> 1LL);
        if (k & 1LL) return ret * ret * mat;
        return ret * ret;
    }
    vector<ll> multiply(const vector<ll> &vec) {
        vector<ll> ret(6, 0);
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                ret[i] += elem[i][j] * vec[j];
                ret[i] %= MOD;
            }
        }
        return ret;
    }
};
int main() {
    ll n;
    cin>>n;
    Matrix mt({{1,1,0,0,0,0}, {0,1,1,2,0,0}, {0,1,0,0,0,0},{0,1,0,1,0,0}, {0,0,0,0,1,1},{0,0,0,0,1,0}});
    Matrix ans = Matrix::pow(mt, n);
    cout << ans.multiply({0, 1, 0, 0, 1, 0}).front();
}
