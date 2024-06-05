#include<iostream>
#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
//using LL = __int128;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define clz(n) __builtin_clz(n)//31 -x
#define nd "\n"
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll l , ll r) { return uniform_int_distribution<ll>(l, r)(rng); }
const  double PI = acos(-1.0);  double EPS = 1e-9; const int M = 5000 + 5; ll INF = 1e16+5;  const ll B1 = 200117 , B2 = 200201; const ll N = 4e5+10, LOG = 20 , inf = 1e9, SQ= 200 , mod=1e9+7, mod2 = 998244353 , P1 = 31 , P2 = 29;
template<class container> void print(container v) { for (auto& it : v) cout << it << ' ' ;cout <<endl;}
template <typename T> using ordered_set =  tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update>;
ll fp(ll a , ll p){ if(!p) return 1; ll v = fp(a , p/2); v*=v;return p & 1 ? v*a : v;  }
template< typename  T > using min_heap = priority_queue <T , vector <T >  , greater < T > >;
//# define int long long
#define all(x) x.begin() , x.end()
#define makeUnique(v)  sort(all(v)) , v.resize(unique(all(v))-v.begin());
#define popcount(x)  __builtin_popcount(x)
 
ll mul (ll a, ll b , ll m){
    return ((a % m) *  (b % m)) % m;
}
ll add (ll a , ll b , ll m){
    return ((a+b) % m + m) % m;
}
ll Fp (ll b , ll p , ll m){
    if (!p) return 1;
    ll v = Fp(b , p >> 1 , m);
    v = mul(v , v , m);
    if (p & 1) v = mul(v , b , m);
    return v;
}
ll modInv(ll n , ll m){
    return Fp(n , m-2 , m);
}
int dx[] {0 , 0 , -1 , 1 ,-1 , 1 , 1 , -1};
int dy[] {-1 , 1 , 0 , 0 , -1 , 1 , -1 , 1};
 
int nodes;
const int mm = 90 * 2e5;
 
int val[mm] , ls[mm] ,rs[mm];
void modify(int l, int r, int p, int &x, int v) {
    if(!x) {
        assert(nodes+1 < mm);
        x = ++nodes;
    }
    val[x] += v;
    if(l == r) return;
    int m = l + r >> 1;
    if(p <= m) modify(l, m, p, ls[x], v);
    else modify(m + 1, r, p, rs[x], v);
}
int query(int l, int r, int ql, int qr, int x) {
    if(ql <= l && r <= qr || !x) return val[x];
    int m = l + r >> 1, ans = 0;
    if(ql <= m) ans += query(l, m, ql, qr, ls[x]);
    if(m < qr) ans += query(m + 1, r, ql, qr, rs[x]);
    return ans;
}
int root;
int mx = 1e9;
struct ds{
    int L , R;
    ds(int _L , int _R){ L = _L , R = _R; }
    bool operator < (const ds & rhs) const{
        return L < rhs.L;
    }
};
 
set<ds> has;
int ans;
int solve(int L , int R){
    return query(1 , mx , L , R , root);
}
void main_(int tc){
    ans = 0;
    int n; cin >> n;
    vector <int > a(n);
    for (auto &i : a) {
        cin >> i;
        modify(1  , mx , i , root ,  1);
    }
    vector< array<int , 3 > > q;
    int qs; cin >> qs;
 
 
    for (int i = 1; i <= qs; ++i){
        int tp , L , R; L = R = 0;
        cin >> tp;
        if (tp == 1) cin >> L >> R;
        q.push_back({tp , L , R });
 
    }
 
    auto add =[&](int L , int R){
        auto it = has.lower_bound({L , -1 });
        if (it != has.begin()) --it;
        
        auto temp = * it;
        if (!has.empty() && temp.R >= L && temp.L < L ){
            ans-= solve(temp.L , temp.R);
            has.erase(it);
            has.insert({temp.L , L-1});
            ans+= solve(temp.L , L-1);
            if (temp.R > R){
                has.insert({R+1 , temp.R});
                ans+= solve(R+1 , temp.R);
            }
        }
 
 
        while (!has.empty()){
            it = has.lower_bound({L , -1});
 
            if (it == has.end() || it->L > R) break;
 
            temp = *it;
            ans-= solve(temp.L , temp.R);
          //  cout << "ii " << temp.L << " " << temp.R<< endl;
            if (R >= it->R) it = has.erase(it);
            else{
                has.insert({R+1 , temp.R });
                ans+= solve(R+1 , temp.R);
                has.erase(it);
            }
        }
        ans+= solve(L , R);
     //   cout << L << " " << R << " " << solve(L , R)  << " "  << ans  << endl;
        has.insert({L , R});
    };
 
 
    for (int i = 0; i < qs; ++i){
        auto &[tp , L , R] = q[i];
        if (tp == 2) {
            has.clear();
            ans = 0;
        }
        else {
            add(L , R);
            cout << n - ans << nd;
        }
    }
 
 
 
 
 
 
 
}
 
 
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    int tt = 1, tc = 0;//cin >> tt;
    while (tt--) main_(++tc);
    return 0;
}
// look at my code
// my code is amazing
