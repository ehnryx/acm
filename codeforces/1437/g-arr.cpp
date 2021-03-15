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

////////////////////////////////////////////////////////////////////////
// Aho-Corasick String Matching -- O(n + m + numMatches)
// WARNING: all pattern strings must be different; patterns 0-indexed
//          change `int id` to `vector<int> id` for non-unique patterns
// USAGE:
//  0. AhoCorasick trie;
//  1. trie.insert(pattern) to insert patterns
//  2. trie.build() to build links once all words are inserted
//  3. auto matches = trie.match(string) to find words in string
//*!
struct AhoCorasick {
#define toi(c) (c - 'a')
  struct Node {
    int ch[26];
    int end, p, id, d;
    multiset<int> value;
    Node(int _d=0): id(-1), d(_d) { memset(ch, 0, sizeof ch); }
  };

  static constexpr int root = 1;
  vector<Node> data;
  int wcnt, dcnt;
  AhoCorasick(int N): wcnt(0), dcnt(1) {
    data.resize(N);
  }
  vector<Node*> ends;

  void insert(const string& s) {
    int u = root;
    for (char c : s) {
      if (!data[u].ch[toi(c)]) data[u].ch[toi(c)] = ++dcnt;
      u = data[u].ch[toi(c)];
    }
    assert(data[u].id == -1); data[u].id = wcnt++;
    ends.push_back(&data[u]);
  }

  void build() {
    data[root].end = root; data[root].p = 0;
    queue<int> bfs; bfs.push(root);
    while (!bfs.empty()) {
      int u = bfs.front(); bfs.pop();
      for(int c=0; c<26; c++) {
        if(!data[u].ch[c]) continue;
        int v = data[u].ch[c];
        int j = data[u].p;
        while (j && !data[j].ch[c]) j = data[j].p;
        data[v].p = (j ? data[j].ch[c] : root);
        data[v].end = (data[v].id == -1 ? data[data[v].p].end : v);
        bfs.push(v);
      }
    }
  }

  int match(const string& s) {
    int res = -1;
    int u = root;
    for (int i=0; i<s.size(); i++) {
      while (u!=root && !data[u].ch[toi(s[i])]) u = data[u].p;
      if (data[u].ch[toi(s[i])]) u = data[u].ch[toi(s[i])];
      for (int v=u; data[v].end!=root; v=data[v].p) {
        v = data[v].end; // get matches
        res = max(res, *data[v].value.rbegin());
      }
    }
    return res;
  }
};
//*/

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

  int n, m;
  cin >> n >> m;
  int len = 0;
  unordered_map<string,int> idx;
  vector<int> remap(n), value(n);
  vector<string> names;
  for(int i=0, sid=0; i<n; i++) {
    string s;
    cin >> s;
    if(!idx.count(s)) {
      idx[s] = sid++;
      names.push_back(s);
      len += s.size();
    }
    remap[i] = idx[s];
  }

  AhoCorasick ac(len + 7);
  for(const string& s : names) {
    ac.insert(s);
  }
  ac.build();

  for(int i=0; i<n; i++) {
    ac.ends[remap[i]]->value.insert(0);
  }

  for(int i=0; i<m; i++) {
    int t;
    cin >> t;
    if(t == 1) {
      int j, v;
      cin >> j >> v;
      int rj = remap[j-1];
      multiset<int>& all = ac.ends[rj]->value;
      all.erase(all.find(value[j-1]));
      all.insert(v);
      value[j-1] = v;
    } else {
      string s;
      cin >> s;
      cout << ac.match(s) << nl;
    }
  }

  return 0;
}

