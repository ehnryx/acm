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

const ll MOD = 1e6+3;
const ld EPS = 1e-9;

const int N = 1024;

bool operator < (bitset<N>& l, bitset<N>& r) {
  typedef array<unsigned long long, (N/64)> AsArray;
  //cerr; auto a = *reinterpret_cast<AsArray*>(&l);
  //cerr; auto b = *reinterpret_cast<AsArray*>(&r);
  //cerr << "A: "; for (auto it : a) //cerr << it << " "; //cerr << nl;
  //cerr << "B: "; for (auto it : b) //cerr << it << " "; //cerr << nl;
  return *reinterpret_cast<AsArray*>(&l)
       < *reinterpret_cast<AsArray*>(&r);
}

inline int get(int i) {
	return N - (1 + (i-1)/64) * 64 + ((i-1) % 64);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;

	int k, temp;
	bitset<N> a;
	vector<bitset<N>> vals;
	for (int i = 0; i < m; i++) {
		cin >> k;
		a.reset();
		for (int j = 0; j < k; j++) {
			cin >> temp;
			a.set(get(temp));
		}
		vals.push_back(a);
	}
	a.reset();
	for (int i = 1; i <= n; i++)
		a.set(get(i));
	vals.push_back(a);

	bitset<N> ans;
	unordered_set<bitset<N>> res;
	for (int bit = 1; bit <= n; bit++) {
		ans = a;
		for (bitset<N>& it : vals) {
			if (it[get(bit)] && it < ans)
				ans = it;
		}
		res.insert(ans);
	}

	n = res.size();
	int andrew_stanfordkevitch = 1;
	for (int i = 0; i < n; i++) {
		andrew_stanfordkevitch = andrew_stanfordkevitch * 2 % MOD;
	}
	cout << andrew_stanfordkevitch << nl;

	return 0;
}
