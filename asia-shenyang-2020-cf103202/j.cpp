#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct node {
  int value;
  node *left, *right, *parent;
  node(int v, node* l = nullptr, node* r = nullptr, node* p = nullptr):
    value(v), left(l), right(r), parent(p) {}
};

const int N = 1 << 19;
node* init[2 * N];
node* root[N];

int get_value(node* x) {
  while(x->parent) {
    x = x->parent;
  }
  return x->value;
}

void set_link(node* x, node* to) {
  if(x->parent) {
    if(x->parent->left == x) {
      x->parent->left = to;
    } else {
      x->parent->right = to;
    }
  }
}

node* extract(node* x, int l, int r, int i=1, int s=0, int e=N-1) {
  if(r < s || e < l || !x) return nullptr;
  if(l <= s && e <= r) {
    set_link(x, nullptr); // sever the link
    return x;
  }
  int m = (s + e) / 2;
  node* left = extract(x->left, l, r, 2*i, s, m);
  node* right = extract(x->right, l, r, 2*i+1, m+1, e);
  if(!left && !right) return nullptr;
  node* ret = new node(x->value + 1, left, right);
  if(left) left->parent = ret;
  if(right) right->parent = ret;
  // update master
  if(init[i] == x) init[i] = ret;
  // remove ghosts
  if(!x->left && !x->right) {
    set_link(x, nullptr);
    if(i == 1) root[x->value] = nullptr;
    delete x;
  }
  return ret;
}

node* merge(node* x, node* to) {
  if(!x) return to;
  if(!to) return x;
  to->left = merge(x->left, to->left);
  to->right = merge(x->right, to->right);
  if(to->left) to->left->parent = to;
  if(to->right) to->right->parent = to;
  delete x;
  return to;
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

  fill(begin(init), end(init), nullptr);
  fill(begin(root), end(root), nullptr);

  int n, m;
  cin >> n >> m;

  for(int i=1; i<=n; i++) {
    init[i + N] = new node(0);
  }
  for(int i=N-1; i>0; i--) {
    if(init[2*i] || init[2*i + 1]) {
      init[i] = new node(0, init[2*i], init[2*i + 1]);
      if(init[2*i]) init[2*i]->parent = init[i];
      if(init[2*i + 1]) init[2*i + 1]->parent = init[i];
    }
  }
  root[0] = init[1];

  for(int i=0; i<m; i++) {
    int t;
    cin >> t;
    if(t == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      node* subtree = extract(root[x], l, r);
      root[x + 1] = merge(subtree, root[x + 1]);
      if(root[x + 1]) root[x + 1]->value = x + 1;
    } else {
      int l, r;
      cin >> l >> r;
      int ans = 0;
      for(l+=N, r+=N+1; l < r; l/=2, r/=2) {
        //cerr << "AT " << l << " " << r << nl;
        if(l&1) ans = max(ans, get_value(init[l++]));
        if(r&1) ans = max(ans, get_value(init[--r]));
      }
      cout << ans << nl;
    }
  }

  return 0;
}
