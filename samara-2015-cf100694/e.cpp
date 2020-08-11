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

struct Q {
	int id;
	int cur;
	int prev;
	int cnt;
	Q(){}
	Q(int i, int nxt, int pre = 0, int cnt = 0):
		id(i), cur(nxt), prev(pre), cnt(cnt) {}
	bool operator < (const Q& v) const {
		if (value() == v.value()) return id > v.id;
		else return value() > v.value();
	}
	ll value() const {
		if (prev) return cnt*(cur+prev);
		else return cnt*(2*cur);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, k;
	cin >> n >> k;

	int arr[n];
	for (int i=0; i<n; i++) {
		cin >> arr[i];
	}

	priority_queue<Q> q;
	for (int i=1; i<=k; i++) {
		q.push(Q(i,0));
	}

	int ans[n];
	for (int i=0; i<n; i++) {
		Q cur = q.top(); q.pop();
		ans[i] = cur.id;
		cur.prev = cur.cur;
		cur.cur = arr[i];
		cur.cnt++;
		q.push(cur);
	}

	for (int i=0; i<n; i++) {
		cout << ans[i] << " ";
	}
	cout << nl;

	return 0;
}
