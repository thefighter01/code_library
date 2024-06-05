#include<iostream>
#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
//using L = __int128;
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define nd "\n"
#define all(x) (x).begin(), (x).end()
#define lol cout <<"i am here"<<nd;
#define py cout <<"YES"<<nd;
#define pp  cout <<"ppppppppppppppppp"<<nd;
#define pn cout <<"NO"<<nd;
#define popcount(x)  __builtin_popcount(x)
#define clz(n) __builtin_clz(n)//31 -x
const  double PI = acos(-1.0);
double EPS = 1e-9;
#define print2(x , y) cout <<x<<' '<<y<<nd;
#define print3(x , y , z) cout <<x<<' '<<y<<' '<<z<<nd;
#define watch(x) cout << (#x) << " = " << x << nd;
const ll N = 1e5+5, LOG = 20 , inf = 2e9, SQ= 350 , mod=1e9+7 , mod2 = 998244353 , P1 = 31 , P2 = 29;
template<class container> void print(container v) { for (auto& it : v) cout << it << ' ' ;cout <<endl;}
//template <class Type1 , class Type2>
ll fp(ll a , ll p){ if(!p) return 1; ll v = fp(a , p/2); v*=v;return p & 1 ? v*a : v;  }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll l , ll r) { return uniform_int_distribution<ll>(l, r)(rng); }
template <typename T> using ordered_set =  tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update>;
template< typename  T > using min_heap = priority_queue <T , vector <T >  , greater < T > >;
const ll B1 = 200117 , B2 = 200201;
 
ll mul (ll a, ll b , ll m){
    return ((a % m) *  (b % m)) % m;
}
ll add (ll a , ll b , ll m){
    return (a + b + m ) % m;
} // x ^ phi(m) is congruent to 1 mod m
// x ^ (phi -1) is congruent to  x^ -1 mod m
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
 
int dx[] {0 ,1 , 0 , -1};
int dy[] {1 , 0 , -1 ,0};
//  m , c
 
 
 
 
struct seq{
    int L , R , root , tp;
    bool operator < (const seq & rhs) const{
        return (L ^ rhs.L ? L < rhs.L : R < rhs.R);
    }
};
set<seq> st;
 
const int mn = 1e7; int nodes , tot;
int lc[mn] , rc[mn] , val[mn];
void push(int x){
    val[x] = val[lc[x]] + val[rc[x]];
}
 
void upd(int & x , int nl , int nr , int p){
    if (!x) x = ++nodes;
    if (nl+1 == nr){ val[x] = 1;return; }
    int mid = nl + nr >> 1;
    if(p < mid) upd(lc[x], nl , mid , p);
    else upd(rc[x], mid , nr , p);
    push(x);
}
 
int merge(int u , int v , int nl , int nr){
    if (!u || !v) return u | v;
    if (nl+1 == nr){
        val[u]+=val[v];
        return u;
    }
    int mid = nl + nr >> 1;
    lc[u] = merge(lc[u] , lc[v] , nl , mid);
    rc[u] = merge(rc[u] , rc[v] , mid , nr);
    push(u);
    return u;
}
int n;
void split(int u , int &v , int k){
    if (!u) return v = 0 , void();
    if (!v) v = ++nodes;
    if (k < val[lc[u]]) swap(rc[u] , rc[v]) , split(lc[u] , lc[v] , k);
    else if (k == val[lc[u]]) swap(rc[u] , rc[v]);
    else split(rc[u] , rc[v] , k - val[lc[u]]);
    val[v] = val[u] - k ,val[u] = k;
}
void split(int p){
    if (p == 0 || p == n) return;
 
    auto it = --st.upper_bound({p ,n, 0 , 0});
    if (it->R == p) return;
    int nuR = 0; int old = it->root;
    if (it->tp == 0) split(old , nuR , p - it->L +1);
    else split(old, nuR , it->R - p) , swap(old , nuR);
 
    st.insert({it->L , p , old , it->tp});
    st.insert({p+1 , it->R , nuR , it->tp});
    st.erase(it);
}
 
int query(int node , int nl , int nr , int k){
    int L = val[lc[node]];
    if (nl +1 == nr) return nl;
    int mid = nl + nr >> 1;
    int ans = -1;
    if (L < k) ans = query(rc[node] , mid , nr , k - L);
    else ans = query(lc[node] , nl , mid , k);
    return ans;
}
int nl = 0 , nr = 28;
void main_(int tc) {
    int qs; cin >> n >> qs;
    for (int i = 1; i <= n; ++i){
        char c; cin >> c;
        int p = 0; upd(p ,nl , nr, c-'a'+1);
        st.insert({i , i ,p , 0});
    }
    for (int l , r , tp , i = 1; i <= qs; ++i){ // 0 inc , 1 dec
        cin >> l >> r >> tp; tp^= 1;
        split(l-1); split(r);
        int nuR = 0;
        while (!st.empty()){
            auto it = st.lower_bound({l , 0 , 0 , 0});
            if (it == st.end() || it->L > r) break;
            nuR = merge(nuR , it->root ,nl , nr);
            st.erase(it);
        }
        st.insert({l , r , nuR , tp});
    }
    // for (auto &x : st) cout << x.L <<" "<<x.R <<" "<<x.tp << endl;
    //pp;
    for (int i = 1; i <= n; ++i){
        auto it = --st.upper_bound({i , n , 0 , 0});
        //  cout << it->L <<" "<<it->R << endl;
        int p = !it->tp ? i - it->L+1 : it->R - i +1 ;
        //  cout << p <<" ";
        p = query(it->root , nl , nr , p);
        //  cout << i <<" "<<p << endl;
        cout << char('a'+p-1);
    }
 
}
 
int main() {
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    //  freopen("library.in", "r", stdin); // freopen("bridges.out", "w", stdout);
    int tt = 1, tc = 0;//cin >> tt;
    while (tt--) main_(++tc);
    return 0;
}
