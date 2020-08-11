#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// get_sarray()[i] = idx of suffix s[i..L-1] in list of sorted suffixes
struct suff_array {
	const int L; string s; int i, skip, lvl;
	vector<vi> P; vector<pair<pii,int>> M;
	suff_array(const string &s) : L(s.size()), s(s), P(1, vi(L, 0)), M(L) {
		for (i = 0; i < L-(L==1); i++) P[0][i] = int(s[i]);
		for (skip = 1, lvl = 1; skip < L; skip *= 2, lvl++) {
			P.push_back(vi(L, 0));
			for (int i = 0; i < L; i++)
				M[i] = {{P[lvl-1][i], i+skip<L ? P[lvl-1][i + skip] : -1000}, i};
			sort(M.begin(), M.end());
			for (int i = 0; i < L; i++)
				P[lvl][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ?
					P[lvl][M[i-1].second] : i; } }
	const vi& get_sarray() { return P.back(); }
	//returns len of longest common prefix of s[i...L-1] and s[j...L-1], O(lg L)
	int lcp(int i, int j) {
		int len = 0; if (i == j) return L - i;
		for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--)
			if (P[k][i] == P[k][j]) { i += 1 << k; j += 1 << k; len += 1 << k; }
		return len; }
};

const int N = 2e5+2;
struct BIT {
	int f[N];
	BIT() { memset(f, 0, sizeof f); }
	void insert(int x, int v) {
		for ( ; x<N; x+=x&-x) {
			f[x] += v;
		}
	}
	void insert_range(int l, int r) {
		l++; r++;
		insert(l, 1);
		insert(r+1, -1);
	}
	int query(int x) {
		x++;
		int res = 0;
		for ( ; x>0; x-=x&-x) {
			res += f[x];
		}
		return res;
	}
};

BIT sum, rev;
int sid[N], rid[N];

bool equal(const string& t, const string& s, int i) {
	for (int j=0; j<t.size(); j++) {
		if (i+j==s.size() || t[j]!=s[i+j]) return false;
	}
	return true;
}

bool matchl(const string& t, const string& s, int i) {
	for (int j=0; j<t.size(); j++) {
		if (i+j==s.size()) return false;
		if (t[j]>s[i+j]) return false;
		if (t[j]<s[i+j]) return true;
	}
	return true;
}

bool matchr(const string& t, const string& s, int i) {
	for (int j=0; j<t.size(); j++) {
		if (i+j==s.size()) return true;
		if (t[j]<s[i+j]) return false;
		if (t[j]>s[i+j]) return true;
	}
	return true;
}

pii search(const string& t, int l, int r, int id[], const string& s) {
	int lend, rend;
	{
		int left = l;
		int right = r;
		while (left < right) {
			int mid = (left+right)/2;
			if (matchl(t, s, id[mid])) {
				right = mid;
			} else {
				left = mid+1;
			}
		}
		if (!equal(t, s, id[left])) {
			return pii(1, 0);
		}
		lend = left;
	}
	{
		int left = l;
		int right = r;
		while (left < right) {
			int mid = (left+right+1)/2;
			if (matchr(t, s, id[mid])) {
				left = mid;
			} else {
				right = mid-1;
			}
		}
		rend = left;
	}
	return pii(lend, rend);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	string s;
	cin >> s;
	int n = s.size();

	suff_array sa(s);
	For(i,n) {
		sid[sa.get_sarray()[i]] = i;
	}

	string r = s;
	reverse(r.begin(), r.end());
	suff_array ra(r);
	For(i,n) {
		rid[ra.get_sarray()[i]] = i;
	}

	int m;
	cin >> m;
	For(i,m) {
		string t;
		cin >> t;
		int left, right;
		tie(left,right) = search(t, 0, n-1, sid, s);
		if (left <= right) sum.insert_range(left, right);
		reverse(t.begin(), t.end());
		tie(left,right) = search(t, 0, n-1, rid, r);
		if (left <= right) rev.insert_range(left, right);
	}

	ll ans = 0;
	For(i,n-1) {
		int a = sa.get_sarray()[i+1];
		int b = ra.get_sarray()[n-1-i];
		ans += (ll)sum.query(a) * rev.query(b);
	}
	cout << ans << nl;

	return 0;
}
