#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef mt19937 RNG;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

ostream& operator << (ostream& os, const unordered_set<int> v) {
	for (int it : v) os << it << " "; return os;
}

struct Node {
	Node* par;
	unordered_set<int> vals;
	unordered_set<Node*> child;
	bool isleaf;
	Node(Node* p = NULL, unordered_set<int> v = {}, bool l = false): 
		par(p), vals(v), isleaf(l) {}
	int get_val() { return *vals.begin(); }
};
ostream& operator << (ostream& os, Node v) {
	return os << v.vals;
}

int queries = 0;

struct Tree {
	Node* root;
	int root_id;
	unordered_set<int> unknown;

	Tree(int rt, const unordered_set<int>& mid) {
		unknown = mid;
		root_id = rt;
		root = new Node(NULL, {rt});
	}

	void query(int leaf) {
		int in;
		unordered_set<int> path;
		stack<Node*> todo;
		for (Node* it : root->child) {
			todo.push(it);
		}

		unordered_set<Node*> vis;
		bool split = false;
		Node* last = root;

		while (!todo.empty()) {
			Node* cur = todo.top();
			if (vis.count(cur)) {
				break;
			}
			vis.insert(cur);

			int seen = 0;
			for (int v : cur->vals) {
				queries++; assert(queries <= 2550);
				cout << "? 3 " << root_id << " " << leaf << " " << v << endl;
				cin >> in;
				if (in == 3) {
					path.insert(v);
					seen |= 2;
				}
				else {
					seen |= 1;
				}
			}
			if (seen & 2) {
				last = cur;
			}

			if (seen == 3) {
				split = true;
				break;
			}
			if (seen == 2) {
				for (Node* it : cur->child) {
					if (!it->isleaf) {
						todo.push(it);
					}
				}
			}
			else {
				todo.pop();
			}
		}

		//cerr << "connecting to " << *last << endl;

		if (split) {
			//cerr << "split" << endl;
			unordered_set<int> overlap;
			for (int v : last->vals) {
				if (path.count(v)) {
					overlap.insert(v);
				}
			}
			//cerr << "overlap: " << overlap.size() << "  vals: " << last->vals.size() << endl;
			//assert(overlap.size() < last->vals.size());
			for (int v : overlap) {
				last->vals.erase(v);
			}

			//cerr << "overlap: " << overlap << endl;
			//cerr << "other: " << *last << endl;
			//cerr << endl;

			Node* to_add = new Node(last->par, overlap);
			to_add->child.insert(last);
			last->par->child.erase(last);
			last->par->child.insert(to_add);
			last->par = to_add;
			last = to_add;
		}

		//cerr << "now connecting to " << *last << endl;

		path.clear();
		for (int mid : unknown) {
			queries++; assert(queries <= 2550);
			cout << "? 3 " << root_id << " " << leaf << " " << mid << endl;
			cin >> in;
			if (in == 3) {
				path.insert(mid);
			}
		}
		for (int it : path) {
			unknown.erase(it);
		}

		//cerr << "path: " << path << endl;
		if (path.empty()) {
			last->child.insert(new Node(last, {leaf}, true));
		}
		else {
			Node* to_add = new Node(last, path);
			last->child.insert(to_add);
			to_add->child.insert(new Node(to_add, {leaf}, true));
		}
	}

	void dfs(int cur, int par, vector<int>& ans, const vector<vector<int>>& adj) {
		ans[cur] = par;
		for (int x : adj[cur]) {
			if (x != par) {
				dfs(x, cur, ans, adj);
			}
		}
	}

	void reroot(int rt, int n, vector<int>& ans) {
		assert(unknown.empty());
		//cerr << "REROOT" << endl;
		vector<vector<int>> adj(n+1);

		stack<Node*> stk;
		stk.push(root);
		while (!stk.empty()) {
			Node* cur = stk.top();
			stk.pop();
			//cerr << "cur: " << cur->get_val() << endl;
			int id = cur->get_val();
			for (Node* it : cur->child) {
				//cerr << "it values size: " << it->vals.size() << " --> " << it->get_val() << endl;
				assert(it->vals.size() == 1);
				int other = it->get_val();
				adj[id].push_back(other);
				adj[other].push_back(id);
				stk.push(it);
			}
		}

		//cerr << "DFS" << endl;
		dfs(rt, -1, ans, adj);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, in;
	cin >> n;

	vector<int> leaf;
	unordered_set<int> nonleaf;
	for (int i = 1; i <= n; i++) {
		queries++; assert(queries <= 2550);
		cout << "? " << n-1;
		for (int j = 1; j <= n; j++) {
			if (j != i) cout << " " << j;
		}
		cout << endl;
		cin >> in;
		if (in == n)
			nonleaf.insert(i);
		else
			leaf.push_back(i);
	}

	const int root = leaf.back();
	leaf.pop_back();
	Tree tree(root, nonleaf);

	for (int v : leaf) {
		tree.query(v);
	}

	vector<int> ans(n+1);
	tree.reroot(1, n, ans);
	cout << "!";
	for (int i = 2; i <= n; i++) {
		cout << " " << ans[i];
	}
	cout << endl;

	return 0;
}
