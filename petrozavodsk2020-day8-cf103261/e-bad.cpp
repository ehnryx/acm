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

  int n;
  cin >> n;
  vector<int> arr;
  vector<tuple<int, int, int>> temp;
  int total = 0;

  for(int round = 0; round < 2*n; round++) {
    //assert(size(arr) + size(temp) == total);
    //cerr << "cur:"; for(auto it:arr){cerr<<" "<<it;}cerr<<endl;

    string op;
    int x;
    cin >> op >> x;

    if(op == "add") {
      total += 1;
      if(empty(arr)) {
        //assert(empty(temp));
        arr.push_back(x);
        cout << 0 << endl;
        goto gulag;
      }
      temp.emplace_back(x, 1, size(arr));
    }

    else {
      total -= 1;
      int found = -1;
      for(int i=0; i<size(temp); i++) {
        if(get<0>(temp[i]) == x) {
          found = i;
          break;
        }
      }
      if(found != -1) {
        temp.erase(begin(temp) + found);
        cout << 0 << endl;
        goto gulag;
      }
      int rem = find(begin(arr), end(arr), x) - begin(arr);
      for (auto& [v, l, r] : temp) {
        l = max(1, l - (rem < l));
        r = max(1, r - (rem < r));
      }
      arr.erase(begin(arr) + rem);
    }

    if(empty(arr)) {
      assert(size(temp) <= 30);
      //assert(size(temp) <= total);
      cout << size(temp);
      for(auto [v, l, r] : temp) {
        cout << " " << v;
      }
      cout << endl;
      arr.resize(size(temp));
      for(int i=0; i<size(temp); i++) {
        cin >> arr[i];
      }
      temp.clear();
    }

    else {
      vector<int> query;
      query.push_back(arr.front());
      for (auto [v, l, r] : temp) {
        if(l != r) query.push_back(arr[(l+r)/2]);
        query.push_back(v);
      }
      sort(begin(query), end(query));
      query.resize(unique(begin(query), end(query)) - begin(query));
      int k = size(query);
      assert(k <= 30);
      //assert(k <= total);
      cout << k;
      for(int it : query) {
        cout << " " << it;
      }
      cout << endl;

      map<int, int> idx;
      vector<int> order(k);
      vector<int> head;
      int seen = 0;
      for(int i=0; i<k; i++) {
        cin >> order[i];
        idx[order[i]] = i;
        seen |= (order[i] == arr.front());
        if(!seen) {
          head.push_back(order[i]);
        }
      }
      //assert(seen);

      map<int, vector<int>> insert_after;
      for(int i=0; i<size(temp); ) {
        auto [v, l, r] = temp[i];
        int pos = idx[v];
        //assert(pos < size(order));
        if (l != r) {
          int mid = idx[arr[(l+r)/2]];
          //assert(mid < size(order));
          if(mid < pos) l = (l+r)/2 + 1;
          else r = (l+r)/2;
        }
        //assert(l <= r);
        if(pos < size(head)) {
          temp.erase(begin(temp) + i);
        } else if(l == r) {
          insert_after[-r].push_back(v);
          temp.erase(begin(temp) + i);
        } else {
          i++;
        }
      }

      for (auto& [neg_pos, vec] : insert_after) {
        int pos = -neg_pos;
        sort(begin(vec), end(vec), [&](int a, int b) { return idx[a] < idx[b]; });
        arr.insert(begin(arr) + pos, begin(vec), end(vec));
        for(auto& [v, l, r] : temp) {
          l += (l > pos) * (int)size(vec);
          r += (r >= pos) * (int)size(vec);
        }
      }

      arr.insert(begin(arr), begin(head), end(head));
      for (auto& [v, l, r] : temp) {
        l += size(head);
        r += size(head);
      }

      map<int, int> arr_pos;
      for(int i=0; i<size(arr); i++) {
        if(idx.count(arr[i])) {
          arr_pos[arr[i]] = i;
        }
      }
      for(auto& [v, l, r] : temp) {
        if(arr_pos.count(v)) continue;
        for(int i=idx[v]; i>=0; i--) {
          if(arr_pos.count(order[i])) {
            l = max(l, arr_pos[order[i]] + 1);
          }
        }
        for(int i=idx[v]; i<size(order); i++) {
          if(arr_pos.count(order[i])) {
            r = min(r, arr_pos[order[i]]);
          }
        }
      }
    }

gulag:
    //assert(size(arr) + size(temp) == total);
    //if(empty(arr)) assert(empty(temp));
    cout << (empty(arr) ? -1 : arr.front()) << endl;
  }

  return 0;
}
