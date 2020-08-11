#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
#define nl '\n'


int ra() {
		return abs((rand()<<16)|rand());
}

int in_range(int u, int v) { // inclusive
	int q = v-u+1;
	if (q <= 0) {
		cerr << " U V " << u << " " <<v << endl;
	}
	assert (q > 0);
	int a = ra()%q + u;
	assert (a >= u);
	assert (a <= v);
	return a;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	const int n=50000, q=50000;
	cout << "1\n" << n << " " << q << endl;

	for (int i=0; i<n; ++i) {
		cout << in_range(1, n) << " ";
	}
	cout << endl;
	for (int i=0; i<q; ++i) {
		int l = in_range(1, n);
		int r = in_range(l, n);
		int u = in_range(0, r-l);
		int v = in_range(u, r-l);
		u++;
		v++;
		assert (l<=r);
		assert (u<=v);
		assert (v<=(r-l+1));
		cout << l << " " << r << " " << u << " " << v << endl;
	}

	return 0;
}
