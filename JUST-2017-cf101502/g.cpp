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

struct Trie {
	struct Node {
		int cnt;
		unordered_map<char,Node*> nxt;
		Node(): cnt(0) {}
	};

	Node* root;
	unordered_map<int,int> ans;

	Trie() {
		root = new Node;
	}

	void add(const string& s) {
		Node* cur = root;
		for (char c : s) {
			if (!cur->nxt.count(c)) {
				cur->nxt[c] = new Node;
			}
			cur = cur->nxt[c];
			cur->cnt++;
		}
	}

	void solve(Node* cur, int d) {
		ans[d] = max(ans[d], cur->cnt);
		for (const pair<char,Node*> it : cur->nxt) {
			solve(it.second, d+1);
		}
	}

	int query(int d) {
		return ans[d];
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n, q;
		cin >> n >> q;

		Trie cactus;
		string s;
		for (int i=0; i<n; i++) {
			cin >> s;
			reverse(s.begin(), s.end());
			cactus.add(s);
		}
		cactus.solve(cactus.root, 0);

		while (q--) {
			int a;
			cin >> a;
			cout << cactus.query(a) << nl;
		}
	}

	return 0;
}
