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

ll modpow(ll n, ll e, ll mod) {
	ll r = 1;
	for(;e;e/=2) {
		if(e&1) r = r*n % mod;
		n = n*n % mod;
	}
	return r;
}

const ll mod = (119<<23) + 1, root = 62;
typedef vector<ll> vl;
void ntt(vl& a, vl& rt, vl& rev, int n) {
	for(int i=0; i<n; i++) if(i<rev[i]) swap(a[i], a[rev[i]]);
	for(int k=1; k<n; k*=2)
		for(int i=0; i<n; i+=2*k) for(int j=0; j<k; j++) {
			ll z = rt[j+k] * a[i+j+k] % mod, &ai = a[i+j];
			a[i+j+k] = (z > ai ? ai-z+mod : ai-z);
			ai += (ai + z >= mod ? z-mod : z);
		}
}
vl conv(const vl& a, const vl& b) {
	if(a.empty() || b.empty()) return {};
	int s = a.size()+b.size()-1, B = 32-__builtin_clz(s), n=1<<B;
	vl L(a), R(b), out(n), rt(n, 1), rev(n);
	L.resize(n), R.resize(n);
	for(int i=0; i<n; i++) rev[i] = (rev[i/2]|(i&1)<<B)/2;
	ll curL = mod/2, inv = modpow(n, mod-2, mod);
	for(int k=2; k<n; k*=2) {
		ll z[] = {1, modpow(root, curL/=2, mod)};
		for(int i=k; i<2*k; i++) rt[i] = rt[i/2] * z[i&1] % mod;
	}
	ntt(L, rt, rev, n); ntt(R, rt, rev, n);
	for(int i=0; i<n; i++) out[-i&(n-1)] = L[i]*R[i] % mod * inv % mod;
	ntt(out, rt, rev, n);
	return {out.begin(), out.begin()+s};
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
	vl a(n), b(m), c;
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
		res[i] += -2 * c[i];
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
		res[i] += c[i];
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
		res[i] += -2 * c[i];
	}

	// 1 * t^4
	vector<ll> pref(m+1);
	for(int i=0; i<m; i++) {
		pref[i+1] = pref[i] + t[i]*t[i]*t[i]*t[i];
	}

	// output
	for(int i=n-1; i<m; i++) {
		ll val = (res[i] + sum + pref[i+1] - pref[i-n+1]) % mod;
		cout << !val;
	}
	cout << nl;

	return 0;
}
