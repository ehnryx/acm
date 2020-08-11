#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
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

const int N = 1e5+1;
struct BIT {
	int f[N];
	BIT() { memset(f, 0, sizeof f); }
	void insert(int x) {
		for ( ; x<N; x+=x&-x) {
			f[x]++;
		}
	}
	int query(int x) {
		int res = 0;
		for ( ; x>0; x-=x&-x) {
			res += f[x];
		}
		return res;
	}
	int query(int l, int r) {
		if (l>r) return query(l,N-1) + query(1,r);
		return query(r) - query(l-1);
	}
};

BIT bit[3];
int cnt[3];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n;
	cin >> n;

	string s;
	cin >> s;

	For(i,n) {
		bit[s[i]-'A'].insert(i+1);
		cnt[s[i]-'A']++;
	}

	int ans = INF;

	For(i,n) {
		int j = (i+cnt[0])%n;
		int k = (j+cnt[1])%n;
		int cur = 0;
		if (cnt[0] > 0) {
			cur += cnt[0] - bit[0].query(i+1,(j+n-1)%n+1);
		}
		if (cnt[1] > 0) {
			cur += cnt[1] - bit[1].query(j+1,(k+n-1)%n+1);
		}
		if (cnt[2] > 0) {
			cur += cnt[2] - bit[2].query(k+1,(i+n-1)%n+1);
		}
		ans = min(ans, cur);
	}

	swap(cnt[0], cnt[1]);
	swap(bit[0], bit[1]);

	For(i,n) {
		int j = (i+cnt[0])%n;
		int k = (j+cnt[1])%n;
		int cur = 0;
		if (cnt[0] > 0) {
			cur += cnt[0] - bit[0].query(i+1,(j+n-1)%n+1);
		}
		if (cnt[1] > 0) {
			cur += cnt[1] - bit[1].query(j+1,(k+n-1)%n+1);
		}
		if (cnt[2] > 0) {
			cur += cnt[2] - bit[2].query(k+1,(i+n-1)%n+1);
		}
		ans = min(ans, cur);
	}

	cout << ans << nl;

	return 0;
}
