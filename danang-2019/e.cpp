#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define nl '\n'

struct Query {
	int l, r, u, v, ind;
	static int rt;

	Query() {}
	Query(int a, int b, int c, int d, int e) :l(a), r(b), u(c), v(d), ind(e) {}
	bool operator< (const Query& o) const {
		int lrt = l/rt;
		int olrt = o.l/rt;
		if (lrt != olrt) return lrt < olrt;
		if (lrt%2 == 0) {
			return r < o.r;
		} else {
			return r > o.r;
		}
	}
};

int Query::rt;

// TODO: use a bit
struct OrSegtree {
	vector<int> t;
	int n, h;
	OrSegtree() {}
	OrSegtree(int sz) {
		h = 32 - __builtin_clz(sz);
		n = 1<<h;
		t = vector<int>(n<<1, 0);
	}
	void assign(int x, int val) {
		x+=n;
		//cerr << "! X " << x << " VS " << n << "," << t.size() << endl;
		t[x] = val;
		for (x/=2; x; x/=2) {
			t[x] = t[x<<1]|t[x<<1|1];
		}
	}
	int query(int l, int r) { // inclusive, exclusive
		int ans = 0;
		for (l+=n, r+=n; l<r; l/=2, r/=2) {
			if (l%2) ans = ans|t[l++];
			if (r%2) ans = ans|t[--r];
		}
		return ans;
	}
};

struct OrderSegtree {
	vector<int> t;
	int n, h;
	OrderSegtree() {}
	OrderSegtree(int sz) {
		h = 32 - __builtin_clz(sz);
		n = 1<<h;
		t = vector<int>(n<<1, 0);
	}
	void insert(int x) {
		for (x+=n; x; x/=2) {
			t[x]++;
		}
	}
	void remove(int x) {
		for (x+=n; x; x/=2) {
			t[x]--;
		}
	}
	int query(int k) {
		int x = 1, amt = 0;
		while (x<n) {
			x*=2;
			if (amt+t[x] < k) {
				amt += t[x];
				x++;
			}
		}
		return x-n;
	}
	int query_range(int r) {
		int amt = 0;
		int l = 0;
		for (l+=n, r+=n; l<r; l/=2, r/=2) {
			if (l%2) assert(false);
			if (r%2) amt += t[--r];
		}
		return amt;
	}
};

struct Ans {
	int x[4];
	Ans() {
		x[1] = x[2] = x[3] = 0;
	}
	int& operator[] (const int i) {
		return x[i];
	}
};

struct Solver {
	int n, q;
	OrSegtree st[4];
	map<int, int> mp;
	//ordered_set<pii> order;
	int vals;
	vector<int> z, amt, a, b;
	vector<Ans> ans;
	vector<Query> queries;
	OrderSegtree order_seg;

	void alloc() {
		z = vector<int>(n+10, 0);
		amt = vector<int>(n+10, 0);
		a = vector<int>(n+10, 0);
		b = vector<int>(n+10, 0);

		ans = vector<Ans>(q+10);

		st[1] = OrSegtree(n+10);
		st[2] = OrSegtree(n+10);
		st[3] = OrSegtree(n+10);
		order_seg = OrderSegtree(n+10);
	}

	// val is _compressed_ value
	void insert_val(int val, int ind) {
		//cerr << "  INSERT " << val << " ( z[val] = " << z[val] << ")" << endl;
		//order.insert(pii(val, ind));
		order_seg.insert(val);
		int p = ++amt[val];
		if (p < 4) {
			//cerr << "   ASSIGN " << p << endl;
			st[p].assign(val, z[val]);
		}
	}
	void remove_val(int val, int ind) {
		//cerr << "  REMOVE " << val << " ( z[val] = " << z[val] << ")" << endl;
		//order.erase(pii(val, ind));
		order_seg.remove(val);
		int p = amt[val]--;
		if (p < 4) {
			//cerr <<"    ASSIGN(REM) " << p << endl;
			st[p].assign(val, 0);
		}
	}

	int get_kth(int k) {
		//return order.find_by_order(k-1)->first;
		return order_seg.query(k);
	}

	Ans query(int u, int v) {
		////cerr << "   QUERY " << u << " TO " << v << endl;
		int x = get_kth(u)+1;
		int y = get_kth(v)-1;
		Ans out;
		if (x-1 == y+1) {
			int cnt = v-u+1;
			for (int i=1; i<=3; ++i) {
				if (cnt >= i) {
					out[i] |= z[x-1];
				}
			}
			return out;
		}
		////cerr << "   X Y " << x << " " << y << " :: KTH U V " << get_kth(u) << " " << get_kth(v) << endl;
		int lt_x = order_seg.query_range(x);//order.order_of_key(pii(x, -1));
		int leq_y = order_seg.query_range(y+1);
		//int leq_y = order.order_of_key(pii(y+1, -1));
		int of_small = lt_x - u + 1;
		int of_large = v-leq_y;
		for (int i=1; i<=3; ++i) {
			out[i] = st[i].query(x, y+1);
			if (of_small >= i) {
				out[i] |= z[x-1];
			}
			if (of_large >= i) {
				out[i] |= z[y+1];
			}
		}
		return out;
	}

	void solve() {
		cin >> n >> q;
		alloc();

		Query::rt = sqrt(n);

		for (int i=1; i<=n; ++i) {
			cin >> a[i];
			mp[a[i]] = -1;
		}
		vals = 0;
		for (auto& p : mp) {
			p.second = ++vals;
			z[vals] = p.first;
		}

		for (int i=1; i<=n; ++i) {
			b[i] = mp[a[i]];
		}

		for (int i=1; i<=q; ++i) {
			int l, r, u, v;
			cin >> l >> r >> u >> v;
			queries.emplace_back(l, r, u, v, i);
		}
		sort(queries.begin(), queries.end());

		int old_left = 1, old_right = 0;
		for (auto& p : queries) {
			////cerr << " PROCESS QUERY " << p.l << "," << p.r << "  " << p.u << "," << p.v << "  (q " << p.ind << ")" << endl;
			int l = p.l;
			int r = p.r;
			while (old_left > l) {
				--old_left;
				insert_val(b[old_left], old_left);
			}
			while (old_right < r) {
				++old_right;
				insert_val(b[old_right], old_right);
			}
			while (old_left < l) {
				remove_val(b[old_left], old_left);
				++old_left;
			}
			while (old_right > r) {
				remove_val(b[old_right], old_right);
				--old_right;
			}

			ans[p.ind] = query(p.u, p.v);
		}

		for (int i=1; i<=q; ++i) {
			////cerr << " :: " << ans[i][1] << " " << ans[i][2] << " " << ans[i][3] << endl;
			cout << (ll) ans[i][1]+ans[i][2]+ans[i][3] << "\n";
			//cout <<  ans[i][1]+ans[i][2]+ans[i][3] << "\n";
		}
	}
	Solver() {}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int TT;
	cin >> TT;
	while (TT--) {
		Solver s;
		s.solve();
	}

	return 0;
}
