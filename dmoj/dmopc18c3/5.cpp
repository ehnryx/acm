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

bool cmp(int a, int b) {
	if (a==0) a=INF;
	if (b==0) b=INF;
	return a < b;
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

	int n, k;
	cin >> n >> k;

	int m = 32-__builtin_clz(n-1);
	int a[1<<m];
	memset(a, 0, sizeof a);
	for (int i=1; i<=n; i++) {
		int v;
		cin >> v;
		a[v-1] = i;
	}

	vector<vector<int>> res;
	res.push_back({});
	for (int i=0; i<1<<m; i++) {
		res.back().push_back(a[i]);
	}

	for (int l=0; l<m; l++) {
		int len = 1<<l;
		int cnt = 1<<(m-1-l);

		vector<int> nxt;
		for (int i=0; i<cnt; i++) {
			for (int j=i*len; j<(i+1)*len; j++) {
				nxt.push_back(res.back()[len*cnt-1-j]);
				nxt.push_back(res.back()[len*cnt+j]);
			}
			if (i%2==1) sort(nxt.begin()+2*i*len, nxt.end());
			else sort(nxt.begin()+2*i*len, nxt.end(), greater<int>());
		}

		if (l == m-1) sort(nxt.begin(), nxt.end(), cmp);
		res.push_back(nxt);
	}

	cout << m << nl;
	for (int i=m; i>0; i--) {
		set<int> s;
		for (int j=1<<(m-1); j<1<<m; j++) {
			s.insert(res[i-1][j]);
		}
		for (int j=1; j<1<<m; j++) {
			if (res[i][j] != 0) {
				if (s.count(res[i][j])) cout << 'B';
				else cout << 'T';
			}
		}
		cout << nl;
	}

	return 0;
}
