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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

namespace SuffixTree {
  static const int N = 4e5 + 10;
  static const int ALPHA = 27;
	int toi(char c) { return c - 'a'; }
	string a; // v = cur node, q = cur position
	int t[N][ALPHA],l[N],r[N],p[N],s[N],v=0,q=0,m=2;

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

	void build(const string& _a) {
    a = _a;
		fill(r,r+N,a.size());
		memset(s, 0, sizeof s);
		memset(t, -1, sizeof t);
		fill(t[1],t[1]+ALPHA,0);
		s[0] = 1; l[0] = l[1] = -1; r[0] = r[1] = p[0] = p[1] = 0;
		for (int i=0; i<a.size(); i++) ukkadd(i, toi(a[i]));
	}

  vector<pair<int,int>> put[N];
  void put_query(int id, const string& b, int k) {
    int u = 0, j = r[0];
    for(int i=0; i<size(b) && u!=-1; ) {
      if(j == r[u]) {
        u = t[u][toi(b[i])];
        if(u != -1) {
          j = l[u];
        }
      } else if(a[j] == b[i]) {
        i++;
        j++;
      } else {
        u = -1;
      }
    }
    if(u != -1) {
      put[u].emplace_back(id, k);
    }
  }

  ordered_set<int> dfs(int u, int depth, vector<int>& ans) {
    depth += r[u] - l[u];
    bool leaf = true;
    ordered_set<int> cur;
    for(int c=0; c<ALPHA; c++) {
      if(t[u][c] == -1) continue;
      leaf = false;
      ordered_set<int> child = dfs(t[u][c], depth, ans);
      if(size(cur) < size(child)) {
        cur.swap(child);
        //swap(cur, child);
      }
      for(int it : child) {
        cur.insert(it);
      }
    }
    if(leaf) {
      cur.insert((int)size(a) + 2 - depth);
    }
    for(auto [i, it] : put[u]) {
      if(it <= size(cur)) {
        ans[i] = *cur.find_by_order(it-1);
      }
    }
    return cur;
  }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  string s;
  cin >> s;
  SuffixTree::build(s + (char)('z'+1));

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    int k;
    cin >> s >> k;
    SuffixTree::put_query(i, s, k);
  }

  vector<int> ans(m, -1);
  SuffixTree::dfs(0, 0, ans);
  for(int i=0; i<m; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
