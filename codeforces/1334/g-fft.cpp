//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<int> vi;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = acos((ld)-1);

template <class T> struct cplx {
	T x, y;
	cplx(const T& a=0, const T& b=0): x(a), y(b) {}
	cplx operator + (const cplx& o) const { return {x+o.x, y+o.y}; }
	cplx operator - (const cplx& o) const { return {x-o.x, y-o.y}; }
	cplx operator * (const cplx& o) const { return {x*o.x-y*o.y, x*o.y+y*o.x}; }
	cplx operator * (const complex<T>& o) const { return {x*o.real()-y*o.imag(), x*o.imag()+y*o.real()}; }
	void operator += (const cplx& o) { *this = *this + o; }
	void operator *= (const cplx& o) { *this = *this * o; }
	void imag(const T& v) { y = v; }
};

template <class T> T imag(const cplx<T>& v) { return v.y; }
template <class T> cplx<T> conj(const cplx<T>& v) { return {v.x, -v.y}; }

typedef cplx<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	static vector<cplx<ld>> R(2, 1);
	static vector<C> rt(2, 1);
	for(static int k=2; k<n; k*=2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.L, PI / k);
		for(int i=k; i<2*k; i++) {
			R[i] = i&1 ? R[i/2] * x : R[i/2];
			rt[i] = { R[i].x, R[i].y };
		}
	}
	vi rev(n);
	for(int i=0; i<n; i++) rev[i] = (rev[i/2] | (i&1)<<L) / 2;
	for(int i=0; i<n; i++) if(i<rev[i]) swap(a[i], a[rev[i]]);
	for(int k=1; k<n; k*=2)
		for(int i=0; i<n; i+=2*k) for(int j=0; j<k; j++) {
			C z = rt[j+k] * a[i+j+k];
			a[i+j+k] = a[i+j]-z;
			a[i+j] += z;
		}
}
vd conv(const vd& a, const vd& b) {
	if(a.empty() || b.empty()) return {};
	vd res(a.size() + b.size() - 1);
	int L = 32 - __builtin_clz(res.size()), n = 1<<L;
	vector<C> in(n), out(n);
	copy(a.begin(), a.end(), in.begin());
	for(int i=0; i<b.size(); i++) in[i].imag(b[i]);
	fft(in);
	for(auto& x : in) x *= x;
	for(int i=0; i<n; i++) out[i] = in[-i & (n-1)] - conj(in[i]);
	fft(out);
	for(int i=0; i<res.size(); i++) res[i] = imag(out[i]) / (4*n);
	return res;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	const int M = 26;
	int p[M];
	for(int i=0; i<M; i++) {
		cin >> p[i];
		p[i]--;
	}

	string S, T;
	cin >> S >> T;
	int n = S.size();
	int m = T.size();
	vector<int> s(n), t(m);
	for(int i=0; i<n; i++) s[i] = S[i] - 'a';
	for(int i=0; i<m; i++) t[i] = T[i] - 'a';
	reverse(s.begin(), s.end());

/* brute force
	for(int j=0; j+n<=m; j++) {
		ll res = 0;
		for(int i=0; i<n; i++) {
			res += llround(pow(s[i]-t[n-1-i+j], 2) * pow(p[s[i]]-t[n-1-i+j], 2));
		}
		cout << !res;
	}
	cout << nl;
*/

	vector<ll> res(n+m-1);
	vd a(n), b(m), c;
	ll sum = 0;

	// (s^2 * p^2) * t^0
	for(int i=0; i<n; i++) {
		sum += s[i]*s[i] * p[s[i]]*p[s[i]];
	}

	// -2 * (s^2 * p + s * p^2) * t^1
	for(int i=0; i<n; i++) {
		a[i] = s[i]*s[i] * p[s[i]] + s[i] * p[s[i]]*p[s[i]];
	}
	for(int i=0; i<m; i++) {
		b[i] = t[i];
	}
	c = conv(a, b);
	for(int i=0; i<n+m-1; i++) {
		res[i] += -2 * llround(c[i]);
	}

	// (4*s*p + s^2 + p^2) * t^2
	for(int i=0; i<n; i++) {
		a[i] = 4*s[i]*p[s[i]] + s[i]*s[i] + p[s[i]]*p[s[i]];
	}
	for(int i=0; i<m; i++) {
		b[i] = t[i]*t[i];
	}
	c = conv(a, b);
	for(int i=0; i<n+m-1; i++) {
		res[i] += llround(c[i]);
	}

	// -2 * (s + p) * t^3
	for(int i=0; i<n; i++) {
		a[i] = s[i] + p[s[i]];
	}
	for(int i=0; i<m; i++) {
		b[i] = t[i]*t[i]*t[i];
	}
	c = conv(a, b);
	for(int i=0; i<n+m-1; i++) {
		res[i] += -2 * llround(c[i]);
	}

	// 1 * t^4
	vector<ll> pref(m+1);
	for(int i=0; i<m; i++) {
		pref[i+1] = pref[i] + t[i]*t[i]*t[i]*t[i];
	}

	// output
	for(int i=n-1; i<m; i++) {
		ll val = res[i] + sum + pref[i+1] - pref[i-n+1];
		cout << !val;
	}
	cout << nl;

	return 0;
}
