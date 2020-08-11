#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,tune=native")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

struct seg {
	int x, i;
	bool b; // 0 = close
	bool operator<(const seg& o) const {
		return tie(x, b) < tie(o.x, o.b);
	}
};

const int N = 2e5+10;
int l[N], r[N];
int ansi[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T; cin >> T;
	while (T--) {
		int n, k; cin >> n >> k;
		vector<seg> segs(2*n);
		for (int i = 0; i < n; i++) {
			cin >> l[i] >> r[i];
			segs[2*i] = seg{l[i], i, 1};
			segs[2*i+1] = seg{r[i], i, 0};
		}
		sort(segs.begin(), segs.end());
		int ans = 0;
		int curcnt = 0;
		int prev = -1;
		vector<int> cnt(k+1);
		queue<int> need;
		for (int i = 1; i <= k; i++) need.push(i);
		set<pair<int, int>> unassigned;
		for (const seg& s : segs) {
			//cerr << "@ " << s.x << " " << s.i << " " << s.b << nl;
			//cerr << "cnt: " << curcnt << " " << prev << nl;
			//cerr << "cnt[1]: " << cnt[1] << nl;
			if (!s.b) {
				if (unassigned.count({r[s.i], s.i})) {
					ansi[s.i] = 1;
					unassigned.erase({r[s.i], s.i});
				} else {
					cnt[ansi[s.i]]--;
					if (cnt[ansi[s.i]] == 0) {
						if (!unassigned.empty()) {
							int u = unassigned.begin()->second; unassigned.erase(unassigned.begin());
							ansi[u] = ansi[s.i];
							cnt[ansi[s.i]]++;
						} else {
							need.push(ansi[s.i]);
							if (curcnt == k) {
								ans += s.x - prev;
								prev = -1;
							}
							curcnt--;
						}
					}
				}
			} else {
				if (!need.empty()) {
					int c = need.front(); need.pop();
					ansi[s.i] = c;
					cnt[c]++;
					curcnt++;
					if (curcnt == k) {
						prev = s.x;
					}
				} else {
					unassigned.emplace(r[s.i], s.i);
				}
			}
		}
		//cerr << prev << " " << curcnt << nl;
		assert(prev == -1);
		cout << ans << nl;
		for (int i = 0; i < n; i++) {
			cout << ansi[i] << " \n"[i == n-1];
		}
	}

	return 0;
}
