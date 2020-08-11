#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,tune=native")
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

const ll MOD = 1e16L+61;
const ll MLT = 101;

int n, m, shit, length;

const int N = 51;
int remap[N];

set<int> idx;
vector<pii> cmp;
gp_hash_table<ll, null_type> vis;
vector<pair<vector<char>,ll>> cur;
vector<char> init;

ll hashs(const vector<char>& v) {
	ll ha = 0;
	for (int j=0; j<length; j++) {
		ha = ha*MLT%MOD + v[j];
	}
	return ha;
}

ll hashv(const pair<vector<char>,ll>& v) {
	return hashs(v.first) ^ v.second<<20;
}

ll hashi(const vector<char>& in) {
	vector<char> v;
	for (int i=0; i<n; i++) {
		if (remap[i] == -1) {
			v.push_back(in[i]);
		}
	}
	ll ha = 0;
	for (int j=0; j<v.size(); j++) {
		ha = ha*MLT%MOD + v[j];
	}
	return ha;
}

pair<vector<char>,ll> convert(const vector<char>& v) {
	vector<char> out;
	for (int i=0; i<n; i++) {
		if (remap[i] != -1) {
			out.push_back(v[i]);
		}
	}
	return make_pair(out, hashi(v));
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	while (T--) {
		memset(remap, -1, sizeof remap);
		cin >> n >> m >> shit;

		idx.clear();
		cmp.clear();
		vis.clear();
		cur.clear();
		init.clear();

		for (int i=0; i<m; i++) {
			int a, b;
			cin >> a >> b;
			--a; --b;
			cmp.emplace_back(a,b);
			idx.insert(a);
			idx.insert(b);
		}

		length = idx.size();
		{
			int inum = 0;
			for (int it : idx) {
				remap[it] = inum++;
			}
			for (pii& it : cmp) {
				it.first = remap[it.first];
				it.second = remap[it.second];
			}
		}

		for (int i=1; i<=n; i++) {
			init.push_back(i);
		}
		vis.insert(hashv(convert(init)));
		cur.push_back(convert(init));

		for (int i=0; i<n; i++) {
			for (int j=0; j<i; j++) {
				{
					vector<char> it = init;
					for (int k=j; k<i; k++) {
						swap(it[k], it[k+1]);
					}
					ll ha = hashv(convert(it));
					if (vis.find(ha) == vis.end()) {
						vis.insert(ha);
						cur.push_back(convert(it));
					}
				}
				{
					vector<char> it = init;
					for (int k=i; k>j; k--) {
						swap(it[k], it[k-1]);
					}
					ll ha = hashv(convert(it));
					if (vis.find(ha) == vis.end()) {
						vis.insert(ha);
						cur.push_back(convert(it));
					}
				}
			}
		}

		//cerr << "init: " << cur.size() << nl; for (int i=0; i<cur.size(); i++) {
			//cerr << i << ": "; for (int j : cur[i]) {
				//cerr << j << ' '; }
			//cerr << nl; }

		for (const pii& it : cmp) {
			int len = cur.size();
			for (int j=0; j<len; j++) {
				swap(cur[j].first[it.first], cur[j].first[it.second]);
				ll ha = hashv(cur[j]);
				if (vis.find(ha) == vis.end()) {
					vis.insert(ha);
					cur.push_back(cur[j]);
				}
				swap(cur[j].first[it.first], cur[j].first[it.second]);
			}
		}

		cout << cur.size() << nl;
	}

	return 0;
}
