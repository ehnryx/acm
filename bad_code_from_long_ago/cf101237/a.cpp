#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const int N = 1e6;

struct SegTree {
	static const int length = 1<<20;
	int nodes[2*length];
	SegTree() {
		memset(nodes, -1, sizeof(nodes));
	}

	void insert(int id, int x) {
		insert(id, x, 1, length);
	}
	void insert(int id, int x, int start, int end) {
		int i = (length+id-1)/(end-start+1);
		if (start == end) {
			nodes[i] = x;
			return;
		}

		int mid = (start+end)/2;
		if (id <= mid) {
			insert(id, x, start, mid);
		} else {
			insert(id, x, mid+1, end);
		}
		nodes[i] = min(nodes[2*i], nodes[2*i+1]);
	}

	int query(int ub) {
		int i;
		for (i = 1; i < length; ) {
			if (nodes[2*i] < ub)
				i = 2*i;
			else
				i = 2*i + 1;
		}
		return i - length;
	}
};

struct Range {
	int id;
	int left, right;
	Range(int i, int a, int b): id(i), left(a), right(b) {}
	bool operator < (const Range& other) const {
		if (right == other.right) return left < other.left;
		else return right < other.right;
	}
};

int a[N+1];
int ans[N+1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	vector<Range> queries;
	int l, r;
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		cin >> l >> r;
		queries.push_back(Range(i, l, r));
	}
	sort(queries.begin(), queries.end());

	SegTree segtree;
	int j = 0;
	for (int i = 1; i <= n; i++) {
		segtree.insert(a[i]+1, i);
		while (j < q && queries[j].right == i) {
			ans[queries[j].id] = segtree.query(queries[j].left);
			j++;
		}
	}

	for (int i = 0; i < q; i++) {
		cout << ans[i] << nl;
	}

	return 0;
}
