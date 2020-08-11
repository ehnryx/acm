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
// To find a^{-1} mod m, use egcd(a,m,x,y) and x = a^{-1}
// Returns gcd(a,b)
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
struct Int {
	ll x;
	Int (ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
	operator ll() { return x; }
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

/**
 * USAGE:
 *  to declare an nxn diagonal matrix: Matrix<T> mat(n,n,d);
 *  to declare a rxc matrix: Matrix<T> mat(r,c);
 *  can convert vector<vector<T>> to Matrix<T> implicitly;
 *
 *  to solve a system of equations: Ax = b
 *  define Matrix<T> A;
 *  then x = A.solve(b) where x and b are vectors
 *  free variables are all arbitrarily set to 0
 *  returns an empty vector if no solution
 */
template <class T> struct Matrix {
	int rows, cols;
	vector<vector<T>> a;
	Matrix(int r, int c, int v=0) {
		rows = r; cols = c;
		a.resize(r, vector<T>(c));
		if (v) for (int i = 0; i < min(r,c); i++)
			a[i][i] = v;
	}
	Matrix(const vector<vector<T>>& v) {
		rows = v.size(); cols = v[0].size();
		a = v;
	}

	vector<T>& operator [] (unsigned int i) {
		return a[i];
	}
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
	Matrix<T>& operator += (const Matrix<T>& other) {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				a[i][j] += other.a[i][j];
		return *this;
	}

	vector<T> solve(vector<T> goal, int& x) {
		vector<T> res;
		Matrix<T> rdu(a);
		vector<int> order(rows);
		vector<bool> pivot(cols);
		for (int i=0; i<rows; i++) order[i] = i;

		int rank = 0;
		for (int i=0; i<cols; i++) {
			for (int j=0; j<rows; j++) {
				if (!pivot[j] && abs(rdu[j][i]) > EPS) {
					pivot[j] = true;
					swap(order[j], order[rank++]);
					for (int r=0; r<rows; r++) {
						if (!pivot[r]) {
							T factor = rdu[r][i] / rdu[j][i];
							goal[r] -= factor * goal[j];
							for (int k=i; k<cols; k++) {
								rdu[r][k] -= factor * rdu[j][k];
							}
						}
					}
					break;
				}
			}
		}
		x = rank;
		return {};
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int h, w;
	cin >> h >> w;

	vector<Int> goal(h,0);
	Matrix<Int> mat(h,w);
	for (int i=0; i<h; i++) {
		for (int j=0; j<w; j++) {
			int a;
			cin >> a;
			mat[i][j] = Int(a);
		}
	}

	int x = 0;
	mat.solve(goal, x);
	cout << x << nl;

	return 0;
}
