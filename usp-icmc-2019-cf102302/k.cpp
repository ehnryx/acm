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

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
inline void readll(ll &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

// get_sarray()[i] = idx of suffix s[i..L-1] in list of sorted suffixes
struct suff_array {
	const int L; vi s; int i, skip, lvl;
	vector<vi> P; vector<pair<pii,int>> M;
	suff_array(const vi &s) : L(s.size()), s(s), P(1, vi(L, 0)), M(L) {
		for (i = 0; i < L-(L==1); i++) P[0][i] = s[i];
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

const int N = 1<<19;
vector<ll> st[2*N];
void insert(int x, ll v) {
	for(x+=N;x;x/=2) {
		st[x].push_back(v);
	}
}
void build() {
	for(int i=1;i<2*N;i++) {
		sort(st[i].begin(),st[i].end());
	}
}
int query_node(int i, ll lb, ll ub) {
	return upper_bound(st[i].begin(),st[i].end(),ub) - lower_bound(st[i].begin(),st[i].end(),lb);
}
int query(int l, int r, ll lb, ll ub) {
	int res = 0;
	for(l+=N,r+=N;l<r;l/=2,r/=2) {
		if(l&1) res += query_node(l++,lb,ub);
		if(r&1) res += query_node(--r,lb,ub);
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n; ll left,right;
	//cin>>n>>left>>right;
	read(n);readll(left);readll(right);
	vector<int> a(n);
	ll cur = 0;
	for(int i=0;i<n;i++) {
		//cin>>a[i];
		read(a[i]);
		insert(i,cur+=a[i]);
	}
	build();

	suff_array sa(a);
	auto& id = sa.get_sarray();
	int rev[n];
	for(int i=0;i<n;i++) {
		rev[id[i]]=i;
	}

	ll ans = 0;
	set<int> idx;
	for(int i=cur=0;i<n;i++) {
		int pre = 0;
		auto it = idx.lower_bound(id[i]);
		if(it!=idx.end()) pre = max(pre,sa.lcp(i,rev[*it]));
		if(it!=idx.begin()) pre = max(pre,sa.lcp(i,rev[*prev(it)]));
		idx.insert(id[i]);
		ans += query(i+pre,n,left+cur,right+cur);
		cur += a[i];
	}
	cout<<ans<<nl;

	return 0;
}
