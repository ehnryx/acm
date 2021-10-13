#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/splay_tree.h"

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
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
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

using node = splay_node<void, int>;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  //rope<int> v;
  splay_tree<node> v;
  for(int i=0;i<n;i++) {
    string s; int x;
    cin>>s>>x;
    if(s=="get") {
      //cout<<v[x]<<nl;
      cout << v.at(x)->value << nl;
    } else if(s=="push_back") {
      v.push_back(x);
    } else if(s=="push_front") {
      v.push_front(x);
    } else {
      int id = (v.size()+1)/2;
      //v.insert(v.mutable_begin()+id, x);
      v.insert_before(id, x);
    }
    //v.__debug_print();
    //cout << nl;
  }

  return 0;
}
