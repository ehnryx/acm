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

int get_number(const string& s, int& i) {
  int res = 0;
  for(;isdigit(s[i]);i++) {
    res = res*10 + s[i]-'0';
  }
  --i;
  return res;
}

vector<int> get_block(const string& s, int& i) {
  //cerr<<"get_block"<<nl;
  int cnt = 1;
  vector<int> res;
  for(i++;cnt>0;i++) {
    //cerr<<s[i]<<" w/ "<<cnt<<nl;
    if(s[i]=='('||s[i]=='[') {
      cnt++;
    } else if(s[i]==')'||s[i]==']') {
      cnt--;
    } else if(isdigit(s[i])) {
      int v = get_number(s, i);
      res.push_back(v);
    }
  }
  //cerr<<"done getting block"<<nl;
  return res;
}

vector<vector<int>> convert(const string& s) {
  int n = s.size();
  vector<vector<int>> res;
  bool last = false;
  for(int i=0;i<n;i++) {
    if(s[i]=='c') {
      while(s[i]!='(') {
        i++;
      }
    } else if(s[i]=='s') {
      if(s[i+1]=='o') {
        while(s[i]!='(') {
          i++;
        }
        vector<int> cur = get_block(s,i);
        sort(cur.begin(),cur.end());
        if(last) {
          for(int it:cur) {
            res.back().push_back(it);
          }
        } else {
          res.push_back(cur);
        }
        last = true;
      } else {
        while(s[i]!='(') {
          i++;
        }
        vector<int> cur = get_block(s,i);
        sort(cur.begin(),cur.end());
        if(cur.front()==cur.back()) {
          if(last) {
            for(int it:cur) {
              res.back().push_back(it);
            }
          } else {
            res.push_back(cur);
          }
          last = true;
        } else {
          cur.push_back(INF);
          res.push_back(cur);
          last = false;
        }
      }
    } else if(s[i]=='[') {
      vector<int> cur = get_block(s,i);
      if(last) {
        for(int it:cur) {
          res.back().push_back(it);
        }
      } else {
        res.push_back(cur);
      }
      last = true;
    }
  }
  return res;
}

void print(const vector<vector<int>>& v) {
  for(const auto& it:v) {
    for(const auto& jt: it) {
      cout<<jt<<" ";
    }
    cout<<nl;
  }
  cout<<nl;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  string s,t;
  cin>>s>>t;
  vector<vector<int>> a = convert(s);
  vector<vector<int>> b = convert(t);
  //cerr<<s<<": "<<nl; print(a);
  //cerr<<t<<": "<<nl; print(b);
  if(a==b) {
    cout<<"equal"<<nl;
  } else {
    cout<<"not equal"<<nl;
  }

  return 0;
}
