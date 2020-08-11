#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e6+1;
vector<int> adj[N];
int subsz[N];

int build(int cur, int par=0) {
	int res = 1;
	for (int x : adj[cur]) {
		if (x != par) {
			res += build(x, cur);
		}
	}
	return subsz[cur] = res;
}

int valid(int n, int x) {
	int res = 0;
	for (int i = 1; i <= n; i++) {
		if (subsz[i] % x == 0) res++;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;

	int a, b;
	for (int i = 1; i < n; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	build(1);

	int lim = sqrt(n);
	vector<int> ans;
	ans.push_back(n-1);
	for (int i = 2; i <= lim; i++) {
		if (n % i == 0) {
			if (valid(n, i) == n/i) ans.push_back(n/i-1);
			if (n/i > i && valid(n, n/i) == i) ans.push_back(i-1);
		}
	}
	sort(ans.begin(), ans.end());

	for (int it : ans) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
