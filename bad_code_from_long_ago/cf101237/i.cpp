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
	pair<ld,int> lis[n];
	int pred[n];
	for (int i = 0; i < n; i++) {
		memset(pred, -1, sizeof pred);
		for (int j = 0; j < n; j++) {
			lis[j] = pair<ld,int>(420, 0);
		}

		for (int j = 0; j < n; j++) {
			if (segs[j].first > segs[i].first)
				break;
			if (segs[j].second < segs[i].first)
				continue;
			if (segs[j].second > segs[i].second)
				continue;
			pair<ld,int>* it = lower_bound(lis, lis+n, pair<ld,int>(segs[j].second, j));
			*it = pair<ld,int>(segs[j].second, j);
			if (it != lis) 
				pred[j] = (it-1)->second;
		}
		cur = lower_bound(lis, lis+n, pair<ld,int>(420, 0)) - lis;

		if (cur > ans.size()) {
			ans.clear();
			for (int j = lis[cur-1].second; j != -1; j = pred[j]) {
				ans.push_back(index[segs[j].second]);
			}
			reverse(ans.begin(), ans.end());
		}
	}

	cout << ans.size() << nl;
	for (int it : ans) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
