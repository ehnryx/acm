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

const int N = 1<<20;
int cov[2*N];
int segt[2*N];
bool lazy[2*N];

void build(int n) {
	memset(lazy, 0, sizeof lazy);
	memset(segt, 0, sizeof segt);
	memset(cov, 0, sizeof cov);
	for (int i=1; i<=n; i++) {
		segt[i+N] = 1;
	}
	for (int i=N-1; i>=0; i--) {
		segt[i] = segt[2*i] + segt[2*i+1];
	}
}

void update(int l, int r, int v) {
	for (l+=N,r+=N+1; l<r; l/=2,r/=2) {
		if (l&1) { cov[l] = max(cov[l],v); l++; }
		if (r&1) { --r; cov[r] = max(cov[r],v); }
	}
}

int cover(int x) {
	int res = 0;
	for (x+=N; x>0; x/=2) {
		res = max(res, cov[x]);
	}
	return res;
}

void push(int i) {
	if (lazy[i]) {
		segt[2*i] = segt[2*i+1] = 0;
		lazy[2*i] = lazy[2*i+1] = true;
		lazy[i] = false;
	}
}

void pull(int i) {
	segt[i] = segt[2*i] + segt[2*i+1];
}

void insert(int l, int r, int i=1, int s=0, int e=N-1) {
	if (r<s || e<l) return;
	if (l<=s && e<=r) {
		segt[i] = 0;
		lazy[i] = true;
		return;
	}
	push(i);
	int m = (s+e)/2;
	insert(l,r,2*i,s,m);
	insert(l,r,2*i+1,m+1,e);
	pull(i);
}

int query(int l, int r, int i=1, int s=0, int e=N-1) {
	if (r<s || e<l) return 0;
	if (l<=s && e<=r) {
		return segt[i];
	}
	push(i);
	int m = (s+e)/2;
	return query(l,r,2*i,s,m) + query(l,r,2*i+1,m+1,e);
}

int findr(int l, int k, int& res, int i=1, int s=0, int e=N-1) {
	if (l==s && segt[i] <= k) {
		if (segt[i] == k) res = e;
		return segt[i];
	}
	push(i);
	int m = (s+e)/2;
	int sum = 0;
	if (l <= m) sum += findr(l, k, res, 2*i, s, m);
	if (sum < k) sum += findr(max(l,m+1), k-sum, res, 2*i+1, m+1, e);
	return sum;
}

int find(int l, int k) {
	int res = INF;
	findr(l, k, res);
	assert(res != INF);
	return res;
}

struct Point {
	int x, i, t;
	bool operator < (const Point& o) const {
		if (x != o.x) return x < o.x;
		else return t > o.t;
	}
};

const int Q = 30000+1;
int seen[Q];

bool valid(int k, int n, int m, const vector<Point>& p) {
	if (k == 0) return true;
	build(n);
	memset(seen, 0, m*sizeof(int));

	//cerr << nl << " CHECK " << k << endl;

	multiset<int> active;
	for (const Point& it : p) {
		if (!seen[it.i]) {
			//cerr << "INSERT " << it.x << " (" << it.i << ")" << endl;
			assert(it.t == 1);
			seen[it.i] = it.x;
			active.insert(it.x);
		} else {
			//cerr << "CLOSE " << it.x << " (" << it.i << ")" << "  match " << seen[it.i] << endl;
			assert(it.t == -1);
			int lb = max(cover(seen[it.i]), seen[it.i]);
			//cerr << "upd w/ " << seen[it.i] << " -> " << lb << endl;
			if (query(lb, it.x) < k) {
				//cerr << "can't get enough " << lb << " " << it.x << " -> " << query(lb,it.x) << endl;
				return false;
			}
			int rb = find(lb,k);
			insert(lb, rb);
			update(seen[it.i], rb, it.x+1);
			//cerr << "find " << lb << " -> " << rb << " insert " << it.x+1 << endl;
			active.erase(active.find(seen[it.i]));
		}
	}
	return true;
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

	int T;
	cin >> T;
	for (int tt=1; tt<=T; tt++) {
		cout << "Case #" << tt << ": ";

		int n, m;
		cin >> n >> m;

		vector<Point> p;
		for (int i=0; i<m; i++) {
			int l, r;
			cin >> l >> r;
			p.push_back({l,i,1});
			p.push_back({r,i,-1});
		}
		sort(p.begin(), p.end());

		int left = 0;
		int right = n;
		while (left < right) {
			int mid = (left+right+1)/2;
			if (valid(mid,n,m,p)) {
				left = mid;
			} else {
				right = mid-1;
			}
		}
		cout << left << nl;
		//cerr << nl << " ------------ " << nl;

	}

	return 0;
}
