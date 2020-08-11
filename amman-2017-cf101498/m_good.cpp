#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 18;

int length;
int zero, last;
bool solve(int n, const multiset<int>& dist, vector<int>& cur) {
	if (n == 0) return true;
	if (n < 0) return false;

	bool good;
	multiset<int> nxt;
	int d = *dist.rbegin();
	int cnt = dist.count(d);

	if (d == length/2) {

		if (cnt % (zero+last) != 0) return false;
		cnt /= (zero+last);

		good = true;
		nxt = dist;

		if (nxt.count(0) != cnt*(cnt-1)/2) {
			return false;
		} else {
			for (int i = 0; i < cnt*(cnt-1)/2; i++) {
				nxt.erase(nxt.find(0));
			}
		}

		for (int p : cur) {
			if (nxt.count(abs(d-p)) < cnt) {
				good = false;
				break;
			}
			for (int i = 0; i < cnt; i++) nxt.erase(nxt.find(abs(d-p)));
		}

		if (good) {
			for (int i = 0; i < cnt; i++) cur.push_back(d);
			if (solve(n-cnt, nxt, cur)) return true;
			for (int i = 0; i < cnt; i++) cur.pop_back();
		}
	}

	else {
		for (int left = 0; left*zero <= cnt; left++) {
			if ((cnt-left*zero) % last != 0) continue;
			int other = (cnt-left*zero) / last;

			good = true;
			nxt = dist;

			if (nxt.count(0) < left*(left-1)/2 + other*(other-1)/2) {
				continue;
			} else {
				for (int i = 0; i < left*(left-1)/2 + other*(other-1)/2; i++) {
					nxt.erase(nxt.find(0));
				}
			}

			if (nxt.count(abs(length-d-d)) < left*other) {
				continue;
			} else {
				for (int i = 0; i < left*other; i++) {
					nxt.erase(nxt.find(abs(length-d-d)));
				}
			}

			for (int p : cur) {
				if (nxt.count(abs(d-p)) < left || nxt.count(abs(length-d-p)) < other) {
					good = false;
					break;
				}
				for (int i = 0; i < left; i++) nxt.erase(nxt.find(abs(d-p)));
				for (int i = 0; i < other; i++) nxt.erase(nxt.find(abs(length-d-p)));
			}

			if (good) {
				for (int i = 0; i < left; i++) cur.push_back(d);
				for (int i = 0; i < other; i++) cur.push_back(length-d);
				if (solve(n-left-other, nxt, cur)) return true;
				for (int i = 0; i < left+other; i++) cur.pop_back();
			}
		}
	}

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		int m = n*(n-1)/2;

		int a;
		multiset<int> dist;
		for (int i = 0; i < m; i++) {
			cin >> a;
			dist.insert(a);
		}

		length = *dist.rbegin();
		if (length == 0) {
			for (int i = 0; i < n; i++) {
				cout << 0 << " ";
			}
			cout << nl;
			continue;
		}

		vector<int> cur;
		int cnt = dist.count(length);
		for (int left = 1; left <= cnt; left++) {
			if (cnt % left == 0) {
				int other = cnt/left;
				if (dist.count(0) < left*(left-1)/2 + other*(other-1)/2) {
					continue;
				}

				multiset<int> start = dist;
				for (int i = 0; i < left*(left-1)/2 + other*(other-1)/2; i++) {
					start.erase(start.find(0));
				}
				start.erase(length);

				cur.clear();
				for (int i = 0; i < left; i++) cur.push_back(0);
				for (int i = 0; i < other; i++) cur.push_back(length);
				zero = left;
				last = other;
				if (solve(n-left-other, start, cur)) {
					break;
				}
			}
		}

		assert(cur.size() == n);
		sort(cur.begin(), cur.end());
		for (int it : cur) {
			cout << it << " ";
		}
		cout << nl;
	}

	return 0;
}
