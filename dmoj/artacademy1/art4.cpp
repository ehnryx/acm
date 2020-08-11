//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct SegTree {
	static const int N = 1<<19;
	struct Node {
		int pre, suf, ans;
		bool all, lazy;
		Node(): pre(0), suf(0), ans(0), all(0), lazy(0) {}
		Node(int v): pre(v), suf(v), ans(v), all(true), lazy(true) {}
	};
	unordered_map<int,Node> st;

	void push(int i) {
		if(st[i].lazy) {
			st[2*i].pre = st[2*i].suf = st[2*i].ans = st[i].ans/2;
			st[2*i+1].pre = st[2*i+1].suf = st[2*i+1].ans = st[i].ans/2;
			st[2*i].all = st[2*i+1].all = true;
			st[2*i].lazy = st[2*i+1].lazy = true;
			st[i].lazy = false;
		}
	}

	void pull(int i) {
		st[i].ans = max(st[2*i].ans, st[2*i+1].ans);
		st[i].pre = (st[2*i].all ? st[2*i].pre + st[2*i+1].pre : st[2*i].pre);
		st[i].suf = (st[2*i+1].all ? st[2*i].suf + st[2*i+1].pre : st[2*i+1].suf);
		st[i].all = (st[2*i].all && st[2*i+1].all);
	}

	void insert(int l, int r, int i=1, int s=0, int e=N-1) {
		if(r<s || e<l) return;
		if(l<=s && e<=r) {
			st[i] = Node(e-s+1);
			return;
		}
		push(i);
		int m = (s+e) / 2;
		insert(l, r, 2*i, s, m);
		insert(l, r, 2*i+1, m+1, e);
		pull(i);
	}

	void remove(int l, int r, int i=1, int s=0, int e=N-1) {
		if(r<s || e<l) return;
		if(l<=s && e<=r) {
			st[i] = Node(0);
			return;
		}
		push(i);
		int m = (s+e) / 2;
		insert(l, r, 2*i, s, m);
		insert(l, r, 2*i+1, m+1, e);
		pull(i);
	}

	int query_in(int l, int r, int i=1, int s=0, int e=N-1) {
		if(r<s || e<l || !st.count(i)) return 0;
		if(l<=s && e<=r) {
			return st[i].ans;
		}
		push(i);
		int m = (s+e) / 2;
		return max(query_in(l, r, 2*i, s, m), query_in(l, r, 2*i+1, m+1, e));
	}

	bool query_all(int l, int r, int i=1, int s=0, int e=N-1) {
		if(r<s || e<l) return true;
		if(!st.count(i)) return false;
		if(l<=s && e<=r) {
			return st[i].all;
		}
		push(i);
		int m = (s+e) / 2;
		return query_all(l, r, 2*i, s, m) && query_all(l, r, 2*i+1, m+1, e);
	}

	int query_left(int x) {
		int l = 0;
		int r = x;
		while(l < r) {
			int m = (l+r) / 2;
			if(query_all(m, x)) {
				r = m;
			} else {
				l = m+1;
			}
		}
		return r;
	}

	int query_right(int x) {
		int l = x;
		int r = N-1;
		while(l < r) {
			int m = (l+r+1) / 2;
			if(query_all(x, m)) {
				l = m;
			} else {
				r = m-1;
			}
		}
		return r;
	}

	int query(int l, int r) {
		int ans = query_in(l, r);
		ans = max(ans, query_right(l) - query_left(l) + 1);
		ans = max(ans, query_right(r) - query_left(r) + 1);
		return ans;
	}
};

const int N = 1e5 + 1;
SegTree segx[N], segy[N];
int T[N], X[N], Y[N], Z[N];

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m, q;
	cin >> n >> m >> q;
	map<int,int> rex, rey;
	for(int i=0; i<q; i++) {
		cin >> T[i] >> X[i] >> Y[i] >> Z[i];
		rex[X[i]]; rex[X[i]+Z[i]];
		rey[Y[i]]; rey[Y[i]+Z[i]];
	}

	int xid = 0;
	for(auto& it : rex) {
		it.second = xid++;
	}
	int yid = 0;
	for(auto& it : rey) {
		it.second = yid++;
	}

	for(int i=0; i<q; i++) {
		if(T[i] == 1) {
			for(auto it=rex.lower_bound(X[i]); it->first<X[i]+Z[i]; it++) {
				segx[it->second].insert(Y[i], Y[i]+Z[i]-1, 1);
			}
			for(auto it=rey.lower_bound(Y[i]); it->first<Y[i]+Z[i]; it++) {
				segy[it->second].insert(X[i], X[i]+Z[i]-1, 1);
			}
		} else if(T[i] == 2) {
			for(auto it=rex.lower_bound(X[i]); it->first<X[i]+Z[i]; it++) {
				segx[it->second].remove(Y[i], Y[i]+Z[i]-1, -1);
			}
			for(auto it=rey.lower_bound(Y[i]); it->first<Y[i]+Z[i]; it++) {
				segy[it->second].remove(X[i], X[i]+Z[i]-1, -1);
			}
		} else {
			int ans = 0;
			for(auto it=rex.lower_bound(X[i]); it->first<X[i]+Z[i]; it++) {
				ans = max(ans, segx[it->second].query(Y[i], Y[i]+Z[i]-1));
			}
			for(auto it=rey.lower_bound(Y[i]); it->first<Y[i]+Z[i]; it++) {
				ans = max(ans, segy[it->second].query(X[i], X[i]+Z[i]-1));
			}
			cout << ans << nl;
		}
	}

	return 0;
}

// this is wrong
