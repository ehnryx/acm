#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<int> vi;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Frac {
	ll n, d;
	Frac(ll a=0, ll b=1) {
		ll g = abs(__gcd(a,b));
		n = a/g; d = b/g;
	}
	bool operator < (const Frac& o) const {
		return n*o.d < d*o.n;
	}
	friend ostream& operator << (ostream& os, const Frac& v) {
		return os<<v.n<<"/"<<v.d;
	}
};

namespace SuffixArray {
	const int L = 18; const int N = 1<<L; const int A = 1e9+7;
	int p[L+1][N]; pair<pair<int,int>,int> m[N]; int last, n;
	void build(const string& s) { n = s.size();
		if(n <= 1) { p[0][0] = last = 0; return; }
		for (int i = 0; i < n; i++) p[0][i] = s[i];
		for (int j = 1, v = 1; j < n; j *= 2, v++) {
			for (int i = 0; i < n; i++) {
				m[i] = { make_pair(p[v-1][i] , (i+j<n ? p[v-1][i+j] : -1)), i };
			} sort(m, m+n);
			for (int i = 0; i < n; i++) {
				p[v][m[i].second] = (i > 0 && m[i].first == m[i-1].first) ?
					p[v][m[i-1].second] : i; } last = v; } }
	int* idx() { return p[last]; }
  int lcp(int i, int j) {
    int len = 0; if (i == j) return n - i;
    for (int k = last; k >= 0 && i < n && j < n; k--)
      if (p[k][i] == p[k][j]) { i += 1<<k; j += 1<<k; len += 1<<k; }
    return len; }
}

const int N = 2e5+2;
int rev[N];

Frac ans(1);
set<int> solve(int l, int r) {
	assert(l <= r);
	if(l == r) {
		set<int> out;
		out.insert(rev[l]);
		return out;
	}

	int minv = SuffixArray::lcp(rev[l], rev[r]);
	int left = l+1;
	int right = r;
	while(left<right) {
		int mid = (left+right)/2;
		if(SuffixArray::lcp(rev[l], rev[mid]) == minv) {
			right = mid;
		} else {
			left = mid+1;
		}
	}

	set<int> ls = solve(l, left-1);
	set<int> rs = solve(left, r);
	if(ls.size() > rs.size()) {
		swap(ls, rs);
	}

	for(int v : ls) {
		assert(!rs.count(v));
		auto it = rs.insert(v).first;
		assert(*it == v);
		if(it!=rs.begin()) {
			int len = v - *prev(it);
			ans = max(ans, Frac(SuffixArray::lcp(v, *prev(it)) + len, len));
		}
		if(next(it)!=rs.end()) {
			int len = *next(it) - v;
			ans = max(ans, Frac(SuffixArray::lcp(v, *next(it)) + len, len));
		}
	}
	return rs;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	string s;
	cin>>s;
	int n = s.size();
	SuffixArray::build(s);

	for(int i=0;i<n;i++) {
		rev[SuffixArray::idx()[i]] = i;
	}

	solve(0, n-1);
	cout<<ans<<nl;

	return 0;
}
