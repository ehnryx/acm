#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct AhoCorasick {
  struct Node {
    Node *end, *p;
    unordered_map<char,Node*> ch;
    int id, d, cnt, val;
    Node(int _d=0): id(-1), d(_d), cnt(0), val(0) {}
  };

  static bool cmp(Node* a, Node* b) {
    return a->d > b->d;
  }

  Node* root;
  int wcnt;
  AhoCorasick(): root(new Node), wcnt(0) {}
  void insert(const string& s, const vector<int>& v) {
    //cerr<<"insert "<<s<<nl;
    Node* u = root;
    int sz = s.size();
    for(int i=0;i<sz;i++) {
      char c = s[i];
      if(!u->ch.count(c)) u->ch[c] = new Node(u->d+1);
      u = u->ch[c];
      u->cnt++;
      u->val = max(u->val, v[i]);
      //cerr<<u<<nl;
    }
    u->id = wcnt++;
    //cerr<<nl;
  }

  ull build() {
    //cerr<<"root: "<<root<<nl;
    root->end = root; root->p = 0;
    stack<Node*> rev;
    queue<Node*> bfs; bfs.push(root);
    while(!bfs.empty()) {
      Node* u = bfs.front(); bfs.pop();
      rev.push(u);
      for(const auto& it : u->ch) {
        char c; Node* v; tie(c,v) = it;
        Node* j = u->p;
        while(j && !j->ch.count(c)) j=j->p;
        v->p = (j ? j->ch[c] : root);
        v->end = (v->id == -1 ? v->p->end : v);
        bfs.push(v);
      }
    }
    ull res = 0;
    while(!rev.empty()) {
      Node* u = rev.top(); rev.pop();
      if(u==root) break;
      //cerr<<"@ "<<u<<" w/ "<<u->d<<" * "<<u->cnt<<" * "<<u->val<<nl;
      Node* v = u->p;
      v->val = max(v->val, u->val);
      assert(v->d < u->d);
      //cerr<<" -> "<<v<<nl;
      res = max(res, (ull)u->d * u->cnt * u->val);
    }
    return res;
  }
};

const int N = 1e5;
string s[N];
vector<int> a[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  freopen("exciting.in", "r", stdin);

  int T;
  cin>>T;
  while(T--) {
    AhoCorasick ac;
    int n;
    cin>>n;
    for(int i=0;i<n;i++) {
      cin>>s[i];
    }
    for(int i=0;i<n;i++) {
      a[i].resize(s[i].size());
      for(int j=0;j<s[i].size();j++) {
        cin>>a[i][j];
      }
      ac.insert(s[i],a[i]);
    }
    cout<<ac.build()<<nl;
    //cerr<<endl;
  }

  return 0;
}
