#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int N = 1 << 17;

vector<ll> s;
ll query(int x) {
	ll ans = 0;
	for (x += N; x; x /= 2) {
		ans += s[x];
	}
	return ans;
}
void update(int l, int r, ll x) {
	for (l += N, r += N+1; l < r; l /= 2, r /= 2) {
		if (l%2) s[l++] += x;
		if (r%2) s[--r] += x;
	}
}

int n, m, asol;
int a[N], b[N];
int ans[N];

vector<pair<int, int>> v;
map<ll, int> bal;
bool check(int x) {
	vector<ll> ss = s;
	memset(ans, 0, sizeof ans);
	auto balloon = bal;
	for (const auto& p : v) {
		if (ss[N+p.second] > x) continue;
		ll t = query(p.second);
		while (t + p.first <= m) {
			auto it = balloon.upper_bound(t + p.first);
			if (it == balloon.begin()) break;
			--it;
			ans[it->second] = p.second;
			balloon.erase(it);
			t += p.first;
			update(p.second, n, p.first);
		}
	}
	vector<int> pops;
	for (int i = 1; i <= n; i++) {
		if (ans[i]) {
			pops.push_back(ans[i]);
		}
	}
	sort(pops.begin(), pops.end());
	pops.push_back(n+1);
	vector<int> sol;
	int bsol = 0;
	ll curt = 0;
	int prev = 0;
	for (int i : pops) {
		while (prev < i) {
			curt += b[prev];
			if (curt > m) {
				prev--;
				break;
			}
			prev++;
		}
		curt += b[i];
		if (curt > m) break;
		sol.push_back(curt);
	}
	bsol = prev;
	bool ret = 1;
	curt = 0;
	prev = 0;
	pops.pop_back();
	for (int i : pops) {
		while (prev < i) {
			curt += b[prev];
			prev++;
		}
		curt += b[i];
		if (curt > m) {
			ret = 0;
			break;
		}
	}
	//cerr << asol << " " << bsol << nl;
	if (asol <= bsol) {
		s = ss;
		return ret;
	}
	cout << sol.size() << nl;
	for (int i : sol) {
		cout << i << " ";
	}
	cout << nl;
	exit(0);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	s.resize(2*N);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	ll curt = 0;
	for (int i = 1; i <= n; i++) {
		s[N+i] = curt;
		curt += b[i];
	}
	for (int i = 1; i <= n; i++) {
		v.emplace_back(b[i], i);
	}
	sort(v.rbegin(), v.rend());
	curt = 0;
	for (int i = 1; i <= n; i++) {
		curt += a[i];
		if (curt <= m) asol++;
		bal[curt] = i;
	}

	int l = 0, r = m;
	while (l <= r) {
		//cerr << l << " " << r << nl;
		int mid = (l+r)/2;
		if (check(mid)) {
			l = mid+1;
		} else r = mid-1;
	}
	for (int i = -5; i <= 5; i++) {
		check(l+i);
	}
	puts("-1");

	return 0;
}
