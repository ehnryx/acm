#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

////////////////////////////////////////////////////////////////////////
// Extended Euclidean Algorithm (UBC)
// egcd(a,b,x,y) calculates x,y such that ax+by=gcd(a,b)
// To find a^{-1} mod m, use egcd(a,m,x,y), then x = a^{-1}
// Returns gcd(a,b)
//*!
ll egcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    } else {
        ll d = egcd(b, a%b, y, x);
        y -= x * (a/b);
        return d;
    }
}
//*/

////////////////////////////////////////////////////////////////////////
// Int struct for operations on a prime field (TESTED)
// WARNING: slow
//*!
struct Int {
    ll x;
    Int (ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
    Int operator + (const Int& n) const { return Int(x + n.x); }
    Int operator - (const Int& n) const { return Int(x - n.x); }
    Int operator * (const Int& n) const { return Int(x * n.x); }
    Int operator / (const Int& n) const { return Int(x * n.inv()); }
    void operator += (const Int& n) { x = (x + n.x) % MOD; }
    void operator -= (const Int& n) { x = (x + MOD - n.x) % MOD; }
    void operator *= (const Int& n) { x = (x * n.x) % MOD; }
    void operator /= (const Int& n) { x = (x * n.inv()) % MOD; }
    ll inv() const {
        if (x == 0) throw runtime_error("divide by zero");
        ll c, d;
        egcd(x, MOD, c, d);
        return (c < 0) ? c+MOD : c;
    }
};
//*/

template <class T> struct Matrix {
    int rows, cols;
    vector<vector<T>> a;

    // diagonal constructor
    Matrix(int r, int c, int v=0) {
        rows = r; cols = c;
        a.resize(r, vector<T>(c));
        if (v) for (int i = 0; i < min(r,c); i++)
            a[i][i] = v;
    }
    // 2d vector constructor
    Matrix(const vector<vector<T>>& v) {
        rows = v.size(); cols = v[0].size();
        a = v;
    }
    // access elements
    vector<T>& operator [] (unsigned int i) {
        return a[i];
    }

    // operations
    Matrix<T>& operator *= (const Matrix<T>& other) {
        return *this = *this * other;
    }
    Matrix<T> operator * (const Matrix<T>& other) {
        Matrix<T> res(rows,cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res[i][j] = 0;
                for (int k = 0; k < cols; k++)
                    res[i][j] += a[i][k] * other.a[k][j];
            }
        }
        return res;
    }
    vector<T> operator * (const vector<T>& v) {
        vector<T> res(rows);
        for (int i = 0; i < rows; i++) {
            res[i] = 0;
            for (int j = 0; j < cols; j++)
                res[i] += a[i][j] * v[j];
        }
        return res;
    }
    Matrix<T> operator + (const Matrix<T>& other) {
        Matrix<T> res(rows,cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                res[i][j] = a[i][j] + other.a[i][j];
        return res;
    }
    Matrix<T>& operator += (const Matrix<T>& other) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                a[i][j] += other.a[i][j];
        return *this;
    }
};
//*/

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	ll n;
	cin >> n;

	Matrix<Int> ans(1<<6,1<<6,1);
	Matrix<Int> mat(1<<6,1<<6,0);
	for (int i=0; i<1<<6; i++) {
		if (!(i&3)||!(i&3<<2)||!(i&3<<4)) continue;
		if ((i&3)==(i>>2&3)||(i>>2&3)==(i>>4&3)) continue;
		for (int j=0; j<1<<6; j++) {
			if (!(j&3)||!(j&3<<2)||!(j&3<<4)) continue;
			if ((j&3)==(j>>2&3)||(j>>2&3)==(j>>4&3)) continue;
			if ((i&3)!=(j&3)&&(i>>2&3)!=(j>>2&3)&&(i>>4&3)!=(j>>4&3)) {
				mat[i][j] = 1;
			}
		}
	}

	n--;
	while (n>0) {
		if (n&1) ans *= mat;
		mat *= mat;
		n /= 2;
	}

	Int res = 0;
	for (int i=0; i<1<<6; i++) {
		if ((i&3)&&(i&3<<2)&&(i&3<<4)&&(i&3)!=(i>>2&3)&&(i>>2&3)!=(i>>4&3)) {
			for (int j=0; j<1<<6; j++) {
				res += ans[j][i];
			}
		}
	}
	cout << res.x << nl;

	return 0;
}
