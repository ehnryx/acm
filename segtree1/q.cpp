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

struct Pair {
	int a, b;
	Pair(int a=0, int b=0): a(a), b(b) {}
	Pair fix() {
		a -= a*b;
		return *this;
	}
	int val(int x) const {
		return a + b*x;
	}
};

const int N = 1<<17;
Pair rmq[2*N];
int lazy[2*N];
bool setv[2*N];

void push(int i) {
	if (setv[i]) {
		rmq[2*i] = rmq[2*i+1] = rmq[i];
		lazy[i] = lazy[2*i] = lazy[2*i+1] = 0;
		setv[2*i] = setv[2*i+1] = true;
		setv[i] = false;
	} else if (lazy[i]) {
		rmq[2*i].a += lazy[i];
		rmq[2*i+1].a += lazy[i];
		lazy[2*i] += lazy[i];
		lazy[2*i+1] += lazy[i];
		lazy[i] = 0;
	}
}

void increment(int l, int r, int v, int i=1, int s=0, int e=N-1) {
	if (r<s || e<l) return;
	if (l<=s && e<=r) {
		rmq[i].a += v;
		lazy[i] += v;
		return;
	}
	push(i);
	int m = (s+e)/2;
	increment(l,r,v,2*i,s,m);
	increment(l,r,v,2*i+1,m+1,e);
}

void update(int l, int r, Pair v, int i=1, int s=0, int e=N-1) {
	if (r<s || e<l) return;
	if (l<=s && e<=r) {
		rmq[i] = v;
		lazy[i] = 0;
		setv[i] = true;
		return;
	}
	push(i);
	int m = (s+e)/2;
	update(l,r,v,2*i,s,m);
	update(l,r,v,2*i+1,m+1,e);
}

int query(int x, int i=1, int s=0, int e=N-1) {
	if (s==e) return rmq[i].val(x);
	push(i);
	int m = (s+e)/2;
	if (x<=m) return query(x,2*i,s,m);
	else return query(x,2*i+1,m+1,e);
}

int find(int l, int r, int s) {
	while (l < r) {
		int m = (l+r+1)/2;
		if (query(m) < s*(m-l)) {
			r = m-1;
		} else {
			l = m;
		}
	}
	return l;
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

	int n;
	cin >> n;

	int a[n+1];
	for (int i=1; i<=n; i++) {
		cin >> a[i];
	}

	int m;
	cin >> m;
	int ans[m];
	map<int,vector<pii>> p;
	for (int i=0; i<m; i++) {
		int x, y;
		cin >> x >> y;
		p[y].push_back({x,i});
	}

	update(0, n, Pair(0,0));
	update(n+1, n+1, Pair(-INF,0));
	for (int i=1; i<=n; i++) {
		increment(n-i+1, n, a[i]);
		int last = find(n-i, n+1, a[i]);
		//cerr << "last: " << last << nl;
		update(n-i, last-1, Pair(a[i]*(i-n),a[i]));
		//cerr << "SEGTREE: " << i << nl;
		//for (int i=0; i<N; i++) cerr << rmq[i].a << "," << rmq[i].b << "  ";
		//cerr << nl;
		//for (int i=N; i<N+N; i++) cerr << rmq[i].a << "," << rmq[i].b << "  ";
		//cerr << nl;
		//for (int i=0; i<N; i++) cerr << query(i) << "   ";
		//cerr << nl;
		for (pii it : p[i]) {
			ans[it.second] = query(n-i+it.first);
		}
	}

	for (int i=0; i<m; i++) {
		cout << ans[i] << nl;
	}

	return 0;
}

/*
0  0  0  0  0  0  0 : 0
   2  2  3  4  3  4 : 1
      4  5  7  6  7 : 2
         7  9  9 10 : 3
           11 12 13 : 4
					    14 16 : 5
							   18 : 6

0  0  0  0  0  0  0  0
   1  3  2  3  4  0  2
      4  4  5  7  0  2
         6  7  9  0  2
            9 11  0  2
					    13  0  2
							    0  2
									   2


0  0  0  0  0
   4  2  3  1
	    4  5  2
			   7  3
				    4

*/
