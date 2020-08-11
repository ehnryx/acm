#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using pii = pair<int,int>;
using ll = long long;
using ld = long double;
using pt = complex<ld>;
const int INF = 0x3f3f3f3f;
const char nl = '\n';


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	while(T--) {
		int n, a, b;
		cin >> n >> a >> b;
		bool rev = (a > b);
		if(rev) swap(a, b);

		vector<pair<int,int>> ranges;
		ranges.push_back(make_pair(a, a));
		if(a>1) ranges.push_back(make_pair(1, 1));
		if(a>2) ranges.push_back(make_pair(2, a-1));
		if(b<n) ranges.push_back(make_pair(b+1, n));
		if(a+1<b) ranges.push_back(make_pair(a+1, b-1));
		ranges.push_back(make_pair(b, b));

		int best = INF;
		vector<pair<int,int>> perm;

		int m = ranges.size();
		sort(next(ranges.begin()), prev(ranges.end()));
		do {
			for(int bm=0; bm<1<<m; bm++) {
				bool skip = false;
				for(int i=0; i<m; i++) {
					if((bm & 1<<i) && ranges[i].first == ranges[i].second) {
						skip = true;
						break;
					}
				}
				if(skip) continue;
				int jmp = 0;
				vector<pair<int,int>> cur;
				int pre = 0;
				for(int i=0; i<m; i++) {
					int l, r;
					tie(l,r) = ranges[i];
					if(bm & 1<<i) swap(l,r);
					cur.push_back(make_pair(l, r));
					if(abs(l-pre) == 1 || pre == 0) {
					} else if(__gcd(l, pre) == 1) {
						jmp++;
					} else {
						jmp = INF;
						break;
					}
					pre = r;
				}
				if(jmp < best) {
					best = jmp;
					perm = move(cur);
				}
			}
		} while(next_permutation(next(ranges.begin()), prev(ranges.end())));

		vector<int> ans;
		for(const auto& it : perm) {
			int l, r;
			tie(l,r) = it;
			int dir = (l<r ? 1 : -1);
			for(int i=l; i!=r; i+=dir) {
				ans.push_back(i);
			}
			ans.push_back(r);
		}
		if(rev) {
			reverse(ans.begin(), ans.end());
		}

		if(best >= INF) {
			cout << -1 << nl;
		} else {
			assert(ans.size() == n);
			cout << best << nl;
			for(int it : ans) {
				cout << it << " ";
			}
			cout << nl;
		}

	}

	return 0;
}
