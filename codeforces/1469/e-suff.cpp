//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

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
  const int ALPHA = 2;
	int toi(char c) { return c - '0'; }
	string a; // v = cur node, q = cur position
  int v=0, q=0, m=2;
  vector<vector<int>> t;
  vector<int> l, r, p, s;

	void ukkadd(int i, int c) { suff:
		if (r[v]<=q) {
			if (t[v][c]==-1) { t[v][c]=m;  l[m]=i;
				p[m++]=v; v=s[v]; q=r[v];  goto suff; }
			v=t[v][c]; q=l[v];
		}
		if (q==-1 || c==toi(a[q])) q++; else {
			l[m+1]=i;  p[m+1]=m;  l[m]=l[v];  r[m]=q;
			p[m]=p[v];  t[m][c]=m+1;  t[m][toi(a[q])]=v;
			l[v]=q;  p[v]=m;  t[p[m]][toi(a[l[m]])]=m;
			v=s[p[m]];  q=l[m];
			while (q<r[m]) { v=t[v][toi(a[q])];  q+=r[v]-l[v]; }
			if (q==r[m])  s[m]=v;  else s[m]=m+2;
			q=r[v]-(q-r[m]);  m+=2;  goto suff;
		}
	}

	SuffixTree(string _a) : a(_a) {
    int N = 2*a.size() + 10;
    r.resize(N, a.size());
    l.resize(N);
    p.resize(N);
    s.resize(N);
    t.resize(N, vector<int>(ALPHA, -1));
    fill(t[1].begin(), t[1].end(), 0);
		s[0] = 1; l[0] = l[1] = -1; r[0] = r[1] = p[0] = p[1] = 0;
		for (int i=0; i<a.size(); i++) ukkadd(i, toi(a[i]));
	}
};

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    transform(s.begin(), s.end(), s.begin(), [](char c) {
      return c == '0' ? '1' : '0';
    });
    const int m = 20;

    SuffixTree st(s);
    int len = min(m, k);
    int u = 0, ui = 0;
    for(int i=0; i<k-len; i++) {
      ui++;
      if(ui == st.r[u] - st.l[u]) {
        ui = 0;
        u = st.t[u][0];
      }
      if(u != -1 && st.a[st.l[u] + ui] != '0') {
        u = -1;
      }
      if(u == -1) break;
    }
    if(u == -1) {
      cout << "YES" << nl;
      cout << string(k, '0') << nl;
      continue;
    }

    bool done = false;
    for(int bm=0; bm<1<<len; bm++) {
      int v = u;
      int vi = ui;
      for(int i=0; i<len; i++) {
        char c = '0' + (bm >> (len-1-i) & 1);
        vi++;
        if(vi == st.r[v] - st.l[v]) {
          vi = 0;
          v = st.t[v][st.toi(c)];
        }
        if(v != -1 && st.a[st.l[v] + vi] != c) {
          v = -1;
        }
        if(v == -1) break;
      }
      if(v == -1) {
        done = true;
        cout << "YES" << nl;
        cout << string(k-len, '0');
        for(int i=0; i<len; i++) {
          cout << (bm >> (len-1-i) & 1);
        }
        cout << nl;
        break;
      }
    }

    if(!done) {
      cout << "NO" << nl;
    }
  }

  return 0;
}
