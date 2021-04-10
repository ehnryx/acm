#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_cxx;
using namespace __gnu_pbds;

template<typename T>
using ordered_set=tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

struct Graph {
	const int N = 500500;
	int par[N], left[N], right[N], dep[N];
	int rt;
	Graph() {
		memset(par, 0, sizeof par);
		memset(left, 0, sizeof left);
		memset(right, 0, sizeof right);
		memset(dep, 0, sizeof dep);
	}
	void build_dep(int u) {
		if (u == 0) {
			return;
		}
		if (left[u]
		build_dep(left[u]);
		build_dep(right[u]);
		dep[u] = max(dep[left[u]], dep[right[u]])+1;
	}
};

Graph orig, nxt;
int n, k;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> k;
	for (int i=1; i<=n; ++i) {
		int p;
		cin >> p;
		if (p == -1) {
			orig.rt = p;
			continue;
		}
		orig.par[i] = p;
		if (p > i) {
			orig.left[p] = i;
		} else {
			orig.right[p] = i;
		}
	}

	

	return 0;
}
