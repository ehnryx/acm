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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 250000 + 1;
const int L = 18;

struct Stack {
	vector<int> v;
	Stack(): v(vector<int>(1, INF)) {}
	bool operator < (int x) const { return v.back() < x; }
	friend bool operator < (int x, const Stack& v) { return x < v.v.back(); }
	void add(int x) { v.push_back(x); }
	int search(int x) { return *prev(lower_bound(v.rbegin(), v.rend(), x)); }
};

struct Tree {
	int depth[N], anc[N][L];
	vector<Stack> lis;
	int get(int i) const {
		return depth[i] - 1;
	}
	Tree(const vector<int>& a) {
		depth[0] = 0;
		lis.resize(N, Stack());
		memset(anc, 0, sizeof anc);
		int n = a.size();
		for(int i=0; i<n; i++) {
			auto it = lower_bound(lis.begin(), lis.end(), a[i]);
			if(it == lis.begin()) {
				anc[a[i]][0] = 0;
			} else {
				auto pre = prev(it);
				int u = pre->v.back();
				int v = pre->search(a[i]);
				anc[a[i]][0] = lca(u, v);
			}
			depth[a[i]] = depth[anc[a[i]][0]] + 1;
			for(int j=1; j<L; j++) {
				anc[a[i]][j] = anc[anc[a[i]][j-1]][j-1];
			}
			it->add(a[i]);
		}
	}
	int lca(int a, int b) {
		if(depth[a] < depth[b]) swap(a,b);
		for(int j=L-1; j>=0; j--) {
			if(depth[anc[a][j]] >= depth[b]) {
				a = anc[a][j];
			}
		}
		if(a == b) return a;
		for(int j=L-1; j>=0; j--) {
			if(anc[a][j] != anc[b][j]) {
				a = anc[a][j];
				b = anc[b][j];
			}
		}
		return anc[a][0];
	}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	vector<int> a(n);
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}

	Tree forward(a);
	reverse(a.begin(), a.end());
	for(int i=0; i<n; i++) {
		a[i] = n+1-a[i];
	}
	Tree backward(a);

	for(int i=0; i<n; i++) {
		cout << forward.get(n+1-a[n-1-i]) + backward.get(a[n-1-i]) << " ";
	}
	cout << nl;

	return 0;
}
