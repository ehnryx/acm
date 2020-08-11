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

const int N = 1<<18;
int dp[N];

int segt[2*N], rmq[2*N];

int query_set(int l, int r) {
	int res = 0;
	for (l+=N,r+=N+1; l<r; l/=2,r/=2) {
		if (l&1) res |= segt[l++];
		if (r&1) res |= segt[--r];
	}
	return __builtin_popcount(res);
}

int get_left(int x, int v) {
	int left = 0;
	int right = x;
	while (left < right) {
		int mid = (left+right)/2;
		if (query_set(mid,x) <= v) {
			right = mid;
		} else {
			left = mid+1;
		}
	}
	return left;
}

pii get_range(int x, int k) {
	if (k == 1) return pii(get_left(x,k), x);
	else return pii(get_left(x,k), get_left(x,k-1)-1);
}

int query(int l, int r) {
	int res = INF;
	for (l+=N,r+=N+1; l<r; l/=2,r/=2) {
		if (l&1) res = min(res, rmq[l++]);
		if (r&1) res = min(res, rmq[--r]);
	}
	return res;
}

void insert(int x, int v) {
	for (rmq[x+=N]=v; x>1; x/=2) {
		rmq[x/2] = min(rmq[x], rmq[x^1]);
	}
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int k;
	cin >> k;

	string s;
	cin >> s;
	int n = s.size();

	segt[N] = (1<<30)-1;
	for (int i=1; i<=n; i++) {
		segt[N+i] = 1<<(s[i-1]-'a');
	}
	for (int i=N-1; i>0; i--) {
		segt[i] = segt[2*i]|segt[2*i+1];
	}

	for (int i=1; i<=n; i++) {
		//cerr << nl << "RESOLVE " << i << endl;
		int l, r;
		tie(l,r) = get_range(i,k);
		//cerr << "range: " << l << " " << r << nl;
		if (l<=r) dp[i] = query(l-1,r-1) + 1;
		else dp[i] = INF;
		insert(i,dp[i]);
		//cerr << "set dp " << dp[i] << nl;
	}

	for (int i=1; i<=n; i++) {
		cout << (dp[i]>=INF ? -1 : dp[i]) << " ";
	}
	cout << nl;

	return 0;
}
