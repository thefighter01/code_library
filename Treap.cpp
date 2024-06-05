#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include<iostream>
#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
//using LL = __int128;
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
const ll N = 1e5+10, LOG = 20 , inf = 1e9,/* SQ= 200 ,*/ mod=1e9+7 , mod2 = 998244353 , P1 = 31 , P2 = 29;
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

int dx[] {0 , 0 , 1 , -1};
int dy[] {1 , -1 , 0 ,0};




//int dx[] {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1};
//int dy[] {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};


// E gym - D div1
//  div1 E , div1 E

// C , F , H // demask

//  k , j , h , b // lol

struct node;
extern node *Empty;
enum DIR{L , R};

struct node{
    node *ch[2], * par;
    ll data , B , sz , lazy;
    node(){
        data = sz = lazy = 0;B= INT_MIN;
        ch[L] = ch[R] = par =  this;
    }
    node(ll val , node * lc = Empty , node * rc = Empty){
        data = val; B = rand(1 , 1e13); lazy = 0;
        ch[L] = lc , ch[R] = rc; par = Empty;
        push_up();
    }
    void push_up(){
        for (auto i : {0 , 1}) if (ch[i] != Empty) ch[i]->par = this;
        sz = ch[L]->sz +ch[R]->sz + 1;
    }

    void push_down(){
        if (!lazy) return;
        for (auto i : {0 , 1}) ch[i]->drop();
        lazy = 0;
    }
    void drop(){
        if (this == Empty) return;
        swap(ch[L] , ch[R]);
        lazy^=1;
    }

};

node *Empty = new node();

node * merge (node * lc , node * rc){
    if (lc == Empty) return rc;
    if (rc == Empty) return lc;
    lc->push_down();
    rc->push_down();
    if (lc->B > rc->B) {
        lc->ch[R] = merge(lc->ch[R], rc);
        lc->push_up();
        return lc;
    }
    rc->ch[L] = merge(lc , rc->ch[L]);
    rc->push_up();
    return rc;
}

void split(node * root , int lsz ,  node * & lc , node * & rc){
    if (root == Empty){
        lc = rc = Empty;return;
    }
    root->push_down();
    int Lsz = root->ch[L]->sz;
    if (lsz <= Lsz){
        split(root->ch[L] , lsz , lc , root->ch[L]);
        rc = root;
    }
    else{
        split(root->ch[R] , lsz-Lsz-1 , root->ch[R] , rc);
        lc = root;
    }
    root->push_up();
    root->par = Empty;
}

int get_value(node * root , int pos){
    node * after , * before;
    split(root , pos+1 , root , after);
    split(root , pos , before , root);
    int v = root->data;
    root = merge(merge(before , root) , after);
    return v;
}

void solve (node *& root , int L , int R){
    node * before , * after;
    split(root , R+1 , root , after);
    node *cur;
    split(root , R , root , cur);
    split(root , L , before , root);
    root = merge(merge(before , cur) , merge(root , after));
}

void work (node * & root , int L , int R){
    node * before , * after;
    split(root , R+1 , root , after);
    split(root , L , before , root);
    root->drop();
    root = merge(merge(before , root) , after);
}

void main_(int tc){
  int n , qs , m; cin >> n >> qs >> m;
  vector <int > a(n);
  node * root = Empty;
  for (int i = 0; i < n; ++i){
      cin >> a[i];
      root = merge(root , new node(a[i]));
  }
  for (int _ = 1 ; _ <= qs; ++_){
      int tp , L , R; cin >> tp >> L >> R; L-=1 , R-=1;
      if (tp == 1) solve(root , L , R);
       else work(root , L , R);
  }

  for (int _ = 1; _ <= m; ++_){
      int idx; cin >> idx;
      cout << get_value(root , idx-1) << " \n"[_ == m];
  }



}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    //  freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int tt = 1, tc = 0;//cin >> tt;
    while (tt--) main_(++tc);
    return 0;
}

 
