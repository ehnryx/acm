#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ ";
	for (const T& it : v) os << it << " ";
	os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ ";
	for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
	os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Range {
	int first;
	vector<int> index;
	set<int> larger;

	Range() {}
	Range(int f, const vector<int>& id): first(f), index(id) {}
	Range(int n) {
		first = 0;
		for (int i = 1; i <= n; i++)
			index.push_back(i);
	}

	int find(int id) {
		larger.clear();
		char c;
		for (int it : index) {
			cout << "? " << id << " " << it << endl;
			cin >> c;
			if (c == '>') {
				larger.insert(it);
			}
		}

		if (larger.empty())
			return -1;
		else if (larger.size() == index.size())
			return INF;
		else
			return first + larger.size();
	}

	Range split() {
		vector<int> left, right;
		for (int it : index) {
			if (larger.count(it)) {
				left.push_back(it);
			} else {
				right.push_back(it);
			}
		}
		int prev = first;
		index = right;
		first += left.size();
		return Range(prev, left);
	}
};

ostream& operator << (ostream& os, const Range& r) {
	os << r.first << ": " << r.index << ";"; return os;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	int eans[n+1], oans[n+1];
	vector<int> even;
	vector<Range> odd;
	odd.push_back(Range((n+1)/2));
	for (int i = 1; i <= n/2; i++) {
		even.push_back(i);
	}
	srand(clock() + time(nullptr));
	random_shuffle(even.begin(), even.end());

	for (int x : even) {
		int left, mid, right, val;
		left = 0;
		right = odd.size()-1;
		while (left <= right) {
			mid = (left + right) / 2;
			val = odd[mid].find(x);
			if (val == -1)
				right = mid-1;
			else if (val == INF)
				left = mid+1;
			else {
				break;
			}
		}
		if (val == INF) {
			eans[x] = n;
		} else {
			eans[x] = 2*val;
			Range temp = odd[mid].split();
			odd.insert(odd.begin() + mid, temp);
		}
		//cerr << odd << nl << nl;
		//cerr << "upd " << x << " to " << eans[x] << nl;
	}

	for (const Range& rng : odd) {
		oans[rng.index[0]] = 2 * rng.first + 1;
	}

	cout << "! ";
	for (int i = 1; i <= n/2; i++) {
		cout << eans[i] << " ";
	}
	for (int i = 1; i <= (n+1)/2; i++) {
		cout << oans[i] << " ";
	}
	cout << endl;

	return 0;
}
