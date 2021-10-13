//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2")

#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/data_structure/splay_tree.h"

/*
inline char get(void) {
  static char buf[300000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 300000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
template <typename T> inline void read(T &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
void readchar(char& c) {
  while (isspace(c = get()));
}
void read(string& s) {
  s.resize(3);
  readchar(s[0]);
  s[1] = get();
  s[2] = get();
  while(!isspace(get()));
}
*/

constexpr char nl = '\n';

const int INF = 0x3f3f3f3f;

struct S {
  int val, ans, pref, suff, sum; char lazy; // [push val, reverse]
  S(): val(-INF), ans(-INF), pref(-INF), suff(-INF), sum(0), lazy(0) {}
  S(int v): val(v), ans(v), pref(v), suff(v), sum(v), lazy(0) {}
};

struct node final : splay_node_range<node, void, S, int> {
  using base_node = splay_node_range<node, void, S, int>;
  node(): base_node() {}
  node(int v): base_node(S(v)) {}
  void put(void* _v) {
    int v = *(int*)_v;
    if(v == INF) {
      // reverse
      value.lazy ^= 1;
      swap(left, right);
      swap(value.pref, value.suff);
    } else {
      value.val = v;
      value.sum = v * size;
      value.ans = value.pref = value.suff = max(v, value.sum);
      value.lazy |= 2;
    }
  }
  int get(void* _v) {
    int v = *(int*)_v;
    if(v == 0) {
      return value.sum; // GET-SUM
    } else {
      return value.ans; // MAX-SUM
    }
  }
  void push() {
    if(value.lazy & 1) {
      int v = INF;
      if(left != nil) left->put(&v);
      if(right != nil) right->put(&v);
      value.lazy &= ~1;
    }
    if(value.lazy & 2) {
      int v = value.val;
      if(left != nil) left->put(&v);
      if(right != nil) right->put(&v);
      value.lazy &= ~2;
    }
  }
  void pull() {
    value.ans = value.val;
    value.ans = max(value.ans, max(left->value.ans, left->value.suff + value.val));
    value.ans = max(value.ans, max(right->value.ans, right->value.pref + value.val));
    value.ans = max(value.ans, left->value.suff + value.val + right->value.pref);
    value.sum = value.val + left->value.sum + right->value.sum;
    value.pref = max(left->value.sum + value.val, left->value.sum + value.val + right->value.pref);
    value.pref = max(value.pref, left->value.pref);
    value.suff = max(right->value.sum + value.val, right->value.sum + value.val + left->value.suff);
    value.suff = max(value.suff, right->value.suff);
  }
};

using scary_tree = splay_tree<node, 500'000>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  //cerr << "sizeof node: " << sizeof(node) << nl;

  scary_tree st;

  int n, q;
  cin >> n >> q;
  //read(n); read(q);
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    //read(a);
    st.push_back(a);
  }

  for (int qqq = 0; qqq < q; qqq++) {
    string qtype;
    cin >> qtype;
    //read(qtype);
    //cerr << "qtype: " << qtype << " AT :: "; for(const auto& it : st) {
    //cerr << it.val << "  "; } cerr << nl;

    if (qtype == "MAKE-SAME") {
      int i, t, c;
      cin >> i >> t >> c;
      //read(i); read(t); read(c);
      if(t == 0) continue;
      i -= 1;
      st.update_range(i, i+t-1, &c);

    } else if (qtype == "INSERT") {
      int i, t;
      cin >> i >> t;
      //read(i); read(t);
      if (t == 0) continue;
      i -= 1;
      /*
      for (int j = 0; j < t; j++) {
        int s;
        //cin >> s;
        read(s);
        //st.insert_before(i + j, s);
        st.insert_after(i + j, s);
      }
      */
      scary_tree add;
      for (int j = 0; j < t; j++) {
        int s;
        cin >> s;
        //read(s);
        add.push_back(s);
      }
      auto tail = st.split_after(i);
      st.append(add);
      st.append(tail);

    } else if (qtype == "DELETE") {
      int i, t;
      cin >> i >> t;
      //read(i); read(t);
      if (t == 0) continue;
      i -= 1;
      /*
      for (int j = 0; j < t; j++) {
        st.erase_at(i);
      }
      */
      auto tail = st.split_after(i - 1);
      tail.split_before(t).clear(); // clear is necessary here if the desructor is skipped
      st.append(tail);
      /*
      auto rem = st.range(i, i+t-1);
      if (rem->parent == node::nil) {
        st.clear(); // sad
      } else {
        if (rem == rem->parent->left) rem->parent->left = node::nil;
        else rem->parent->right = node::nil;
        st.splay(rem->parent);
        st.erase_tree(rem);
      }
      */

    } else if (qtype == "REVERSE") {
      int i, t;
      cin >> i >> t;
      //read(i); read(t);
      if (t == 0) continue;
      i -= 1;
      if (t > 0) {
        static int c = INF;
        st.update_range(i, i+t-1, &c);
      }

    } else if (qtype == "GET-SUM") {
      int i, t;
      cin >> i >> t;
      //read(i); read(t);
      i -= 1;
      if (t > 0) {
        static int c = 0;
        cout << st.query_range(i, i+t-1, &c) << nl;
      } else {
        cout << 0 << nl;
      }

    } else if (qtype == "MAX-SUM") {
      static int c = 1;
      cout << st.root->get(&c) << nl;
    }
  }

  return 0;
}

