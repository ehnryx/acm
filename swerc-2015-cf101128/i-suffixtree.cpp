//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct SuffixTree {
	enum { N = (int)2e5 + 7, ALPHA = 26 }; // N ~ 2*maxlen+10
	int toi(char c) { return c - 'a'; }
	string a; // v = cur node, q = cur position
	int t[N][ALPHA],l[N],r[N],p[N],s[N],v=0,q=0,m=2;

	int leaves = 0;
	ll answer = 0;
	queue<int> order;

	int get_child(int u) {
		int child = -1;
		for(int c=0; c<ALPHA; c++) {
			if(t[u][c] != -1) {
				if(child != -1) return -1;
				child = t[u][c];
			}
		}
		return child;
	}

	void ukkadd(int i, int c) { suff:
		if (r[v]<=q) {
			if (t[v][c]==-1) {
				t[v][c]=m;  l[m]=i;
				// add leaf
				leaves++;
				order.push(m);
				// end add
				p[m++]=v; v=s[v]; q=r[v];  goto suff;
			}
			v=t[v][c]; q=l[v];
		}
		if (q==-1 || c==toi(a[q])) q++; else {
			l[m+1]=i;  p[m+1]=m;  l[m]=l[v];  r[m]=q;
			p[m]=p[v];  t[m][c]=m+1;  t[m][toi(a[q])]=v;
			l[v]=q;  p[v]=m;  t[p[m]][toi(a[l[m]])]=m;
			// split leaf
			leaves++;
			order.push(m+1);
			// end split
			v=s[p[m]];  q=l[m];
			while (q<r[m]) { v=t[v][toi(a[q])];  q+=r[v]-l[v]; }
			if (q==r[m])  s[m]=v;  else s[m]=m+2;
			q=r[v]-(q-r[m]);  m+=2;  goto suff;
		}
		answer += leaves;
	}

	void remove(int start, int pos) {
		int u = order.front();
		order.pop();
		if(u == v) {
			// truncate leaf
			int len = pos - q;
			answer -= len;
			// follow suffix link
			v = s[p[u]];
			q = pos - (q - l[u]);
			v = t[v][toi(a[q])];
			// walk to next suffix
			while(q + r[v]-l[v] < pos) {
				q += r[v]-l[v];
				v = t[v][toi(a[q])];
			}
			// update left ep of u
			l[u] += len;
			// update active position
			q = l[v] + pos-q;
			assert(q <= r[u]);
			// requeue
			order.push(u);
		} else {
			// remove leaf
			leaves--;
			int len = pos - l[u];
			answer -= len;
			// get parent and detach u
			int b = p[u];
			t[b][toi(a[l[u]])] = -1;
			// get child
			int c = get_child(b);
			if(b != 0 && c != -1) {
				// attach p[b] to c
				t[p[b]][toi(a[l[b]])] = c;
				p[c] = p[b];
				// shift left endpoint
				l[c] -= r[b]-l[b];
				// update active vertex and position
				if(v == b) {
					v = c;
					q = l[c] + q-l[b];
				}
			}
		}
	}

	SuffixTree(string _a) : a(_a) {
		fill(r,r+N,a.size());
		memset(s, 0, sizeof s);
		memset(t, -1, sizeof t);
		fill(t[1],t[1]+ALPHA,0);
		s[0] = 1; l[0] = l[1] = -1; r[0] = r[1] = p[0] = p[1] = 0;
		//for (int i=0; i<a.size(); i++) ukkadd(i, toi(a[i]));
	}
};

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	string s;
	cin >> s;
	int n = s.size();
	SuffixTree st(s);
	vector<ll> ans(n);

	int m, k;
	cin >> m >> k;

	for(int i=0; i<k; i++) {
		st.ukkadd(i, st.toi(s[i]));
	}
	ans[1] = st.answer;

	for(int i=k; i<n; i++) {
		st.remove(i-k, i);
		st.ukkadd(i, st.toi(s[i]));
		ans[i-k+2] = st.answer;
	}

	for(int i=0; i<m; i++) {
		int v;
		cin >> v;
		cout << ans[v] << nl;
	}

	return 0;
}
