#include <bits/stdc++.h>
using namespace std;

%:include "utility/defines.h"
%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "ds/segment_tree.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct node {
  using out_t = vector<int>;
  node() = default;
  vector<pair<int, int>> v;
  // void put(int y, int h) {
  //   v.emplace_back(y, h);
  // }
  vector<int> get(int l, int r, int& take) const {
    if(!take) return {};
    auto it = lower_bound(begin(v), end(v), pair(l, -1));
    auto jt = lower_bound(begin(v), end(v), pair(r+1, -1));
    vector<int> res;
    while(it != jt && take) {
      res.push_back(it++->second);
      take--;
    }
    return res;
  }
  static vector<int> merge(vector<int> a, vector<int> b) {
    if(size(a) < size(b)) swap(a, b);
    a.insert(end(a), begin(b), end(b));
    return a;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

	int n, m;
	cin >> n >> m;
	vector<tuple<int, int, int>> all(n);
	map<int, int> remap;
	for(int i=0; i<n; i++) {
		cin >> all[i];
		remap[get<0>(all[i])];
	}

	int rid = 0;
	for(auto& it : remap) {
		it.second = rid++;
	}

	segment_tree<node> st(rid);
	// for(auto [x, y, h] : all) {
	//   st.update_up(remap[x], y, h);
	// }
	// for(int i=1; i<2*st.length; i++) {
	//   sort(begin(st[i].v), end(st[i].v));
	// }
	// manually do merge sort instead
	for(auto [x, y, h] : all) {
		st[st.length + remap[x]].v.emplace_back(y, h);
	}
	for(int i=0; i<rid; i++) {
		sort(begin(st[st.length + i].v), end(st[st.length + i].v));
	}
	for(int i=st.length-1; i>0; i--) {
		auto l = st[2*i].v.begin();
		auto r = st[2*i+1].v.begin();
		while(l != st[2*i].v.end() && r != st[2*i+1].v.end()) {
			if(*l < *r) st[i].v.push_back(*l++);
			else st[i].v.push_back(*r++);
		}
		while(l != st[2*i].v.end()) {
			st[i].v.push_back(*l++);
		}
		while(r != st[2*i+1].v.end()) {
			st[i].v.push_back(*r++);
		}
	}

	while(m--) {
		int a, b, x, y;
		cin >> a >> b >> x >> y;
		auto it = remap.lower_bound(a);
		auto jt = remap.upper_bound(x);
		if(it == jt) {
			cout << 0 << nl;
			continue;
		}
		vector<int> res = st.query_copy(it->second, prev(jt)->second, b, y, 45);
		sort(begin(res), end(res));
		bool ok = false;
		for(int i=2; !ok && i<size(res); i++) {
			ok |= (res[i-1] + res[i-2] > res[i]);
		}
		cout << ok << nl;
	}

  return 0;
}
