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
const ll N = 3e5, LOG = 20 , inf = 1e8 , SQ= 200 , mod=998244353;//1e9+7;//
template<class container> void print(container v) { for (auto& it : v) cout << it << ' ' ;cout <<endl;}
//template <class Type1 , class Type2>
ll fp(ll a , ll p){ if(!p) return 1; ll v = fp(a , p/2); v*=v;return p & 1 ? v*a : v;  }
 
template <typename T> using ordered_set =  tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update>;
template< typename  T > using min_heap = priority_queue <T , vector <T >  , greater < T > >;
ll mul (ll a, ll b){
    return ( ( a % mod ) * ( b % mod ) ) % mod;
}
ll add (ll a , ll b){
    return (a + b + mod) % mod;
}
 
 
vector < vector <ll > > g , dist , my , myp;
vector < int > del , par , sz , u , v  , w , dep;
int n , qs , root , nodes ;
void init(){
    del = dep = sz =par = u = v = w = vector <int > (n+10);
    root = n+5;
    dist = vector < vector <ll > > (LOG+1 , vector <ll > (n+10));
    my = myp = g = vector < vector <ll > > (n+10);
    nodes = 0;
}
void dfs_sz(int node , int p){
    sz[node] = 1; nodes+=1;
    for (auto &e : g[node]){
        int nu = u[e] ^ v[e] ^ node;
        if (del[e] || nu == p) continue;
        dfs_sz(nu , node) ,sz[node]+=sz[nu];
    }
}
int find_c (int node , int p){
    for (auto &e : g[node]){
        int nu = u[e] ^ v[e] ^ node;
        if (del[e] || nu == p) continue;
        if (sz[nu] > nodes / 2) return find_c(nu , node);
    }
    return node;
}
void add_edge(int p , int ch){
    par[ch] = p;
    dep[ch] = 1 + dep[p];
}
 
void dfs(int node , int p , int d){
    for (auto &e : g[node]){
        int nu = u[e] ^ v[e] ^ node;
        if (nu == p || del[e]) continue;
        dist[d][nu] = w[e] + dist[d][node];
        dfs(nu , node , d);
    }
}
void decompose (int node , int rt){
    nodes = 0;
    dfs_sz(node , node);
    int cent = find_c(node , node);
    add_edge(rt , cent);
    dfs(cent , cent , dep[cent]);
    for (auto &e : g[cent]){
        int nu = u[e] ^ v[e] ^ cent;
        if (del[e]) continue;
        del[e] = 1;
        decompose(nu , cent);
    }
}
void main_(int tc) {
    cin >> n >> qs; init();
    for (int i = 1; i < n; ++i){
        cin >> u[i] >> v[i] >> w[i];
       g[u[i]].emplace_back(i);
        g[v[i]].emplace_back(i);
    }
    decompose(1 , root);
 
    for (int node = 1; node <= n; ++ node){
        for (int p = node ; p != root ; p = par[p]){
            my[p].emplace_back(dist[dep[p]][node]);
            myp[p].emplace_back(dist[dep[par[p]]][node]);
        }
    }
    for (int node = 1; node <= n; ++node){
        sort(all(my[node]));
        sort(all(myp[node]));
    }
 
    auto get = [&]( vector <ll > & a , ll val){
        return upper_bound(all(a) , val)-a.begin();
    };
 
 
    auto solve = [&](ll node , ll d)->ll{
        ll ans = get(my[node] , d);
        int lf = node; int ch = node;
        int p = par[node];
        while (p != root){
            ans+= get(my[p] , d -dist[dep[p]][lf]);
            ans-=get(myp[ch] , d - dist[dep[p]][lf]);
            ch = p;
            p = par[p];
        }
        return ans;
    };
 
    for (ll node , l , i = 1; i <= qs; ++i){
        cin >> node >> l;
        cout << solve(node , l) << nd;
    }
 
 
 
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);cout.tie(0);
    int tt = 1 , tc = 0;// cin >> tt;
    while(tt--) main_(++tc);
    return 0;
}
