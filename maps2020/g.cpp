//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

enum {
  PUSH,
  COPY,
  SWAP,
  REMOVE,
  ADD,
  SUB,
  MUL,
  DIV,
  PRINT,
};

int get_instruction(const string& s, int& i) {
  if(s[i] == 'S' && s[i+1] == 'S') { i+=2; return PUSH; }
  else if(s[i] == 'S' && s[i+1] == 'N' && s[i+2] == 'S') { i+=3; return COPY; }
  else if(s[i] == 'S' && s[i+1] == 'N' && s[i+2] == 'T') { i+=3; return SWAP; }
  else if(s[i] == 'S' && s[i+1] == 'N' && s[i+2] == 'N') { i+=3; return REMOVE; }
  else if(s[i] == 'T' && s[i+1] == 'S' && s[i+2] == 'S' && s[i+3] == 'S') { i+=4; return ADD; }
  else if(s[i] == 'T' && s[i+1] == 'S' && s[i+2] == 'S' && s[i+3] == 'T') { i+=4; return SUB; }
  else if(s[i] == 'T' && s[i+1] == 'S' && s[i+2] == 'S' && s[i+3] == 'N') { i+=4; return MUL; }
  else if(s[i] == 'T' && s[i+1] == 'S' && s[i+2] == 'T' && s[i+3] == 'S') { i+=4; return DIV; }
  else if(s[i] == 'T' && s[i+1] == 'N' && s[i+2] == 'S' && s[i+3] == 'T') { i+=4; return PRINT; }
  else assert(false);
}

int get_number(const string& s, int& i) {
  int sgn = (s[i] == 'T' ? -1 : 1);
  int v = 0;
  for(++i; s[i] != 'N'; i++) {
    v = v*2 + (s[i] == 'T' ? 1 : 0);
  }
  i++;
  return v*sgn;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;
  stack<int> stk;
  for(int i=0; i<s.size(); ) {
    int t = get_instruction(s, i);
    if(t == PUSH) {
      int v = get_number(s, i);
      stk.push(v);
    } else if(t == COPY) {
      if(stk.empty()) {
        cout << "Invalid copy operation" << nl;
      } else {
        int v = stk.top();
        stk.push(v);
      }
    } else if(t == SWAP) {
      if(stk.size() < 2) {
        cout << "Invalid swap operation" << nl;
      } else {
        int u = stk.top(); stk.pop();
        int v = stk.top(); stk.pop();
        stk.push(u);
        stk.push(v);
      }
    } else if(t == REMOVE) {
      if(stk.empty()) {
        cout << "Invalid remove operation" << nl;
      } else {
        stk.pop();
      }
    } else if(t == ADD) {
      if(stk.size() < 2) {
        cout << "Invalid addition operation" << nl;
      } else {
        int u = stk.top(); stk.pop();
        int v = stk.top(); stk.pop();
        stk.push(u+v);
      }
    } else if(t == SUB) {
      if(stk.size() < 2) {
        cout << "Invalid subtraction operation" << nl;
      } else {
        int u = stk.top(); stk.pop();
        int v = stk.top(); stk.pop();
        stk.push(v-u);
      }
    } else if(t == MUL) {
      if(stk.size() < 2) {
        cout << "Invalid multiplication operation" << nl;
      } else {
        int u = stk.top(); stk.pop();
        int v = stk.top(); stk.pop();
        stk.push(v*u);
      }
    } else if(t == DIV) {
      if(stk.size() < 2) {
        cout << "Invalid division operation" << nl;
      } else {
        int u = stk.top(); stk.pop();
        int v = stk.top(); stk.pop();
        if(u == 0) {
          cout << "Division by zero" << nl;
          stk.push(v);
          stk.push(u);
        } else {
          stk.push(v/u);
        }
      }
    } else if(t == PRINT) {
      if(stk.empty()) {
        cout << "Invalid print operation" << nl;
      } else {
        cout << stk.top() << nl;
        stk.pop();
      }
    } else {
      assert(false);
    }
  }

  return 0;
}
