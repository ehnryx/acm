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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 3e5+1;
int dp[N], pre[N];
int cnt[N], val[N];

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
  struct Node {
    Node *end, *p;
    unordered_map<char,Node*> ch;
    int id, d;
    Node(int d=0): id(-1), d(d) {}
  };

  Node* root;
  AhoCorasick(): root(new Node) {}

  void insert(const string& s, int id) {
    Node* u = root;
    for (char c : s) {
      if (!u->ch.count(c)) u->ch[c] = new Node(u->d+1);
      u = u->ch[c];
    }
    assert(u->id == -1); u->id = id;
  }

  void build() {
    root->end = root; root->p = 0;
    queue<Node*> bfs; bfs.push(root);
    while (!bfs.empty()) {
      Node* u = bfs.front(); bfs.pop();
      for (const auto& it : u->ch) {
        char c; Node* v; tie(c,v) = it;
        Node* j = u->p;
        while (j && !j->ch.count(c)) j = j->p;
        v->p = (j ? j->ch[c] : root);
        v->end = (v->id == -1 ? v->p->end : v);
        bfs.push(v);
      }
    }
  }

  void match(const string& s) {
    Node* u = root;
    for (int i=0; i<s.size(); i++) {
      while (u!=root && !u->ch.count(s[i])) u = u->p;
      if (u->ch.count(s[i])) u = u->ch[s[i]];
      for (Node* v=u; v->end!=root; v=v->p) {
        v = v->end; // get matches
        int j = i-v->d+1;
        if(dp[j]) {
          if(dp[i+1]) {
            if(val[j] + cnt[v->id] > val[i+1]) {
              pre[i+1] = v->id;
              val[i+1] = val[j] + cnt[v->id];
            }
          } else {
            dp[i+1] = true;
            pre[i+1] = v->id;
            val[i+1] = val[j] + cnt[v->id];
          }
        }
      }
    }
  }
};
//*/

AhoCorasick ac;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  string s[n], t[n];
  unordered_map<string,int> idx;
  for(int i=0;i<n;i++) {
    cin>>t[i];
    for(char c:t[i]) {
      if(c=='A'||c=='E'||c=='I'||c=='O'||c=='U') cnt[i]++;
      else s[i].push_back(c);
    }
    if(idx.count(s[i])) {
      if(cnt[i] > cnt[idx[s[i]]]) {
        idx[s[i]] = i;
      }
    } else {
      idx[s[i]] = i;
    }
  }

  for(const auto& it:idx) {
    ac.insert(it.first,it.second);
  }
  ac.build();

  string w;
  cin>>w;
  dp[0] = true;
  ac.match(w);
  assert(dp[w.size()]);

  vector<int> ans;
  for(int i=w.size();i>0;i-=s[pre[i]].size()) {
    ans.push_back(pre[i]);
  }
  for(int i=ans.size()-1;i>=0;i--) {
    cout<<t[ans[i]]<<" ";
  }
  cout<<nl;

  return 0;
}
