#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int N = 1 << 21;
namespace seg {
	int is_flip[2*N];
	int no_flip[2*N];
	bitset<2*N> lazy;
	int first = N;

	void do_flip(int i) {
		swap(is_flip[i], no_flip[i]);
	}

	void push(int i) {
		if (lazy[i]) {
			lazy.flip(2*i);
			lazy.flip(2*i+1);
			do_flip(2*i);
			do_flip(2*i+1);
			lazy[i] = 0;
		}
	}
	void pull(int i) {
		no_flip[i] = no_flip[i*2] + no_flip[i*2+1];
		is_flip[i] = is_flip[i*2] + is_flip[i*2+1];
	}

	//insert to no_flip
	void insert(int x, int i=1, int s=0, int e=N) {
		int l = x, r = x+1;
		if (r <= s || e <= l) { return; }
		if (l <= s && e <= r) {
			no_flip[i] += 1;
			return;
		}
		int mid = (s+e)/2;
		push(i);
		insert(x, i*2, s, mid);
		insert(x, i*2, mid, e);
		pull(i);
	}

	// query(is_flip, l, r);
	// query(no_flip, l, r);
  int query(int arr[], int l, int r, int i=1, int s=0, int e=N) {
		if (l <= s && e <= r) { return arr[i]; }
		if (r <= s || e <= l) { return 0; }
		push(i);
		int mid = (s+e)/2;
		return
			query(arr, l, r, i*2, s, mid) +
			query(arr, l, r, i*2+1, mid, e);
	}

	void flip(int l, int r, int i=1, int s=0, int e=N) {
		if (l <= s && e <= r) {
			lazy.flip(i);
			do_flip(i);
			return;
		}
		if (r <= s || e <= l) return;
		int mid = (s+e)/2;
		flip(l, r, i*2, s, mid);
		flip(l, r, i*2, mid, e);
	}

	// left most flipped to the right of x
	int find_right(int x, int bound) {
		int lo = x;
		int hi = bound;
		while (lo < hi-1) {
			int mid = (lo+hi)/2;
			if (query(is_flip, mid, bound) > 0) {
				hi = mid;
			} else {
				lo = mid;
			}
		}
		return hi;
	}
}

ll n, c, r;
int s[N];

int should(int i) {
	if (i % 2 == 0) {
		return +1;
	}
	return -1;
}
//assume r[-1] = -1
void insert(int i) {
	cerr << "insert pos " << i << nl;
	seg::first = min(seg::first, i);
	int sgn = s[i] / abs(s[i]);
	int pre_flips = seg::query(seg::is_flip, 0, i);
	if (pre_flips % 2 == 1) {
		//odd flips before, sign is reversed
		sgn *= -1;
	}
	seg::insert(i);
	if (sgn != should(i)) {
		int rig = seg::find_right(i, n);
		seg::flip(i, rig+1); //endpoint inclusive
	}
}

int reports() {
	int cnt = seg::query(seg::is_flip, 0, n);
	cerr << "pos cnt " << cnt << nl;
	if (seg::first != N && seg::query(seg::is_flip, seg::first, seg::first+1)) {
		// first is flipped
		cerr << "first flipped" << seg::first << nl;
		cnt--;
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> c >> r;
	vector<int> ord(n);
	iota(ord.begin(), ord.end(), 0);
	for (int i = 0; i < n; ++i) {
		cin >> s[i];
	}
	sort(ord.begin(), ord.end(), [&](int i, int j) {
		return abs(s[i]) > abs(s[j]);
	});
	ll ans = r*(n-1);
	ans = min(ans, c*abs(s[ord[0]])+1);
	for (int i : ord) {
		ll accs = abs(s[i]) + 1;
		cerr << "# accounts " << accs << nl;
		ll cost = accs * c;
		if (s[i] == 0) {
			cerr << "todo\n";
			break;
		}
		ll rep = reports();
		ll tot = cost + rep * r;
		cerr << "number reports " << rep << nl;
		ans = min(ans, tot);
		insert(i);
	}
	cout << ans << nl;

	return 0;
}
