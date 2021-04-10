#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

struct Seg {
	int l, r;
};

const int N = 1010;
vector<int> pegs;
vector<int> npegs;
int have[N];
int after[N];
int take[N];

vector<Seg> segs;
int n, p;

int next_in(int i) {
	int cur = segs[i].l+1;
	while (true) {
		bool found = false;
		for (auto& x : pegs) {
			if (x == cur) {
				found = true;
			}
		}
		for (auto& x : npegs) {
			if (x == cur) {
				found = true;
			}
		}
		if (!found) {
			//cerr << " :: " << cur << endl;
			return cur;
		}
		++cur;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n;
	for (int i=0; i<n; ++i) {
		Seg s;
		cin >> s.l >> s.r;
		segs.push_back(s);
	}
	cin >> p;
	for (int i=0; i<p; ++i) {
		int x;
		cin >> x;
		pegs.push_back(x);
		for (int j=0; j<n; ++j) {
			if (segs[j].r == x) {
				++after[j];
			}
			if (segs[j].l <= x && segs[j].r >= x) {
				++have[j];
			}
		}
	}
	for (int i=0; i<n; ++i) {
		if (have[i] > 2) {
			cout << "impossible\n";
			return 0;
		}
	}
	for (int i=0; i<n; ++i) {
		if (have[i] < 2 && have[i+1] < 2 && i+1<n && !after[i] && segs[i].r == segs[i+1].l) {
			++have[i];
			++have[i+1];
			npegs.push_back(segs[i].r);
		}
		while (have[i] < 2) {
			npegs.push_back(next_in(i));
			++have[i];
		}
	}
	sort(npegs.begin(), npegs.end());
	cout << npegs.size() << "\n";
	for (auto& x : npegs) {
		cout << x << " ";
	}
	cout << "\n";

	return 0;
}
