#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

string s;
int N;
vector<int> solve() {


	vector<int> p(N);
	vector<int> ans(N);
	iota(p.begin(), p.end(), 0);
	do {
		bool good = 1;
		for (int i = 0; i < N-1; i++) {
			if (s[p[i]] == '<' && p[i+1] > p[i]) {
				good = 0;
			} else if (s[p[i]] == '>' && p[i+1] < p[i]) {
				good = 0;
			}
		}
		ans[p.back()] += good;
	} while (next_permutation(p.begin(), p.end()));
	return ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> N;

	for (int i = 0; i < (1 << N); i++) {
		s.clear();
		for (int j = 0; j < N; j++) {
			if (i & (1 << j)) s.push_back('<');
			else s.push_back('>');
		}
		cout << s << " -> ";
		vector<int> v = solve();
		for (int i : v) cout << i << " "; cout << nl;
	}

	return 0;
}
