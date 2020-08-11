#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct LinkedList {
	struct Node {
		int left;
		int right;
		int value;
		Node(int l, int r, int v) {
			left = l;
			right = r;
			value = v;
		}
	};
	int curr;
	int start;
	int end;
	vector<Node> arr;
	LinkedList() {
		start = end = -1;
	}
	void move_to(int p) {
		curr = start;
		for (int i = 1; i < p; i++)
			curr = arr[curr].right;
	}
	void append(int v) {
		if (start == -1) {
			start = 0;
			end = 0;
			arr.push_back(Node(-1, -1, v));
		}
		else {
			arr.push_back(Node(end, -1, v));
			arr[end].right = arr.size()-1;
			end = arr.size()-1;
		}
	}
	void add_left(int v) {
		if (curr == start) {
			arr.push_back(Node(-1, curr, v));
			arr[curr].left = arr.size()-1;
			start = arr.size()-1;
		}
		else {
			arr.push_back(Node(arr[curr].left, curr, v));
			arr[arr[curr].left].right = arr.size()-1;
			arr[curr].left = arr.size()-1;
		}
	}
	void add_right(int v) {
		if (curr == end) {
			arr.push_back(Node(curr, -1, v));
			arr[curr].right = arr.size()-1;
			end = arr.size()-1;
		}
		else {
			arr.push_back(Node(curr, arr[curr].right, v));
			arr[arr[curr].right].left = arr.size()-1;
			arr[curr].right = arr.size()-1;
		}
	}
	int get() {
		return arr[curr].value;
	}
	void move_left() {
		if (arr[curr].left != -1) 
			curr = arr[curr].left;
	}
	void move_right() {
		if (arr[curr].right != -1) 
			curr = arr[curr].right;
	}
};

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	LinkedList stilldumb;
	int n, p, a;
	cin >> n >> p;
	for (int i = 0; i < n; i++) {
		cin >> a;
		stilldumb.append(a);
	}
	stilldumb.move_to(p);

	string s;
	int q;
	cin >> q;
	while (q--) {
		//cerr << "current: " << stilldumb.curr << nl;
		cin >> s;
		if (s == "moveLeft") {
			stilldumb.move_left();
		}
		else if (s == "moveRight") {
			stilldumb.move_right();
		}
		else if (s == "insertLeft") {
			cin >> a;
			stilldumb.add_left(a);
		}
		else if (s == "insertRight") {
			cin >> a;
			stilldumb.add_right(a);
		}
		else if (s == "print") {
			cout << stilldumb.get() << nl;
		}
	}

	return 0;
}
