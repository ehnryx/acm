#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
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

#undef M_PI
const ld M_PI = acos(-1);

inline ld get_tangent(pt p, ld r, int dir) {
	ld angle = acos(r/abs(p));
	return arg((p / abs(p)) * exp(pt(0, dir*angle)));
}

//#define DEBUG
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	vector<pair<ld,ld>> segs;
	map<ld,int> index;

	int x, y;
	int n, r;
	cin >> n >> r;
	if (n > 200) { for(;;); }
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		pt p(x,y);
		ld a = get_tangent(p, r, 1);
		ld b = get_tangent(p, r, -1);

		segs.push_back(pair<ld,ld>(min(a,b), max(a,b)));
		index[a] = index[b] = i+1;
	}
	sort(segs.begin(), segs.end());

	int cur;
	vector<int> ans;
	ld lis[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			lis[j] = 420;
		}
		for (int j = 0; j < n; j++) {
			if (segs[j].first > segs[i].first)
				break;
			if (segs[j].second < segs[i].first)
				continue;
			if (segs[j].second > segs[i].second)
				continue;
			ld* it = lower_bound(lis, lis+n, segs[j].second);
			*it = segs[j].second;
		}
		cur = lower_bound(lis, lis+n, 420) - lis;

		if (cur > ans.size()) {
			ans.clear();
			for (int j = 0; j < cur; j++) {
				ans.push_back(index[lis[j]]);
			}
		}
	}

	cout << ans.size() << nl;
	for (int it : ans) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
