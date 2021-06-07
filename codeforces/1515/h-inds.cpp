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

constexpr int L = 21;
constexpr int D = 1.789e7;

struct node {
  int left, right, bit, lazy, ones, zeros, res;
  node() = default;
  void apply(int v) {
    if (bit == -1) return;
    v &= (1 << (bit + 1)) - 1;
    lazy ^= v;
    int toggle = (ones ^ zeros) & v;
    ones ^= toggle;
    zeros ^= toggle;
    if (bit != -1 && v >> bit & 1) {
      swap(left, right);
    }
  }
  int diff() const { return ones & zeros; }
  void pull();
  void push();
} nds[D];

int nid = 0;
int new_node(int i) {
  nds[++nid].bit = i;
  nds[nid].res = (i == -1);
  return nid;
}

void node::pull() {
  if (bit == -1) return;
  res = nds[left].res + nds[right].res;
  ones = nds[left].ones | nds[right].ones;
  zeros = nds[left].zeros | nds[right].zeros;
  if (left) zeros |= 1 << bit;
  if (right) ones |= 1 << bit;
}

void node::push() {
  if (bit == -1 || !lazy) return;
  if (left) nds[left].apply(lazy);
  if (right) nds[right].apply(lazy);
  lazy = 0;
}

int make_trie(int v) {
  int cur = new_node(-1);
  for (int i = 0; i < L; i++) {
    int parent = new_node(i);
    if (v >> i & 1) {
      nds[parent].right = cur;
    } else {
      nds[parent].left = cur;
    }
    nds[parent].pull();
    cur = parent;
  }
  return cur;
}

int merge(int a, int b) {
  if (!a) return b;
  if (!b) return a;
  nds[a].push();
  nds[b].push();
  nds[a].left = merge(nds[a].left, nds[b].left);
  nds[a].right = merge(nds[a].right, nds[b].right);
  nds[a].pull();
  //delete b;
  return a;
}

int extract(int cur, int l, int r, int s = 0, int e = (1 << L) - 1) {
  if (!cur || r < s || e < l) return 0;
  if (l <= s && e <= r) return cur;
  nds[cur].push();
  int dup = new_node(nds[cur].bit);
  int m = (s + e) / 2;
  nds[dup].left = extract(nds[cur].left, l, r, s, m);
  nds[dup].right = extract(nds[cur].right, l, r, m + 1, e);
  if (nds[dup].left == nds[cur].left) nds[cur].left = 0;
  if (nds[dup].right == nds[cur].right) nds[cur].right = 0;
  nds[cur].pull();
  nds[dup].pull();
  if (nds[dup].res == 0) {
    //delete dup;
    return 0;
  }
  return dup;
}

void do_xor(int cur, int v) {
  if (!cur) return;
  nds[cur].apply(v);
}

void do_or(int cur, int v) {
  if (!cur) return;
  if (!(nds[cur].diff() & v)) return do_xor(cur, v & nds[cur].zeros);
  nds[cur].push();
  do_or(nds[cur].left, v);
  do_or(nds[cur].right, v);
  if (v >> nds[cur].bit & 1) {
    nds[cur].right = merge(nds[cur].left, nds[cur].right);
    nds[cur].left = 0;
  }
  nds[cur].pull();
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

  int n, m;
  cin >> n >> m;
  int root = 0;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    int leaf = make_trie(a);
    root = merge(root, leaf);
  }

  int mask = (1 << L) - 1;
  for (int i = 0; i < m; i++) {
    int t;
    cin >> t;
    if (t == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      int range = extract(root, l, r);
      if (!range) continue;
      do_xor(range, mask);
      do_or(range, x ^ mask);
      do_xor(range, mask);
      root = merge(root, range);
    } else if (t == 2) {
      int l, r, x;
      cin >> l >> r >> x;
      int range = extract(root, l, r);
      if (!range) continue;
      do_or(range, x);
      root = merge(root, range);
    } else if (t == 3) {
      int l, r, x;
      cin >> l >> r >> x;
      int range = extract(root, l, r);
      if (!range) continue;
      do_xor(range, x);
      root = merge(root, range);
    } else {
      int l, r;
      cin >> l >> r;
      int range = extract(root, l, r);
      cout << nds[range].res << nl;
      root = merge(root, range);
    }
  }

  return 0;
}
