int nodes;
const int mm = 30 * 1e5;
 
int extend(){
    int cur = ++ nodes;
    assert(cur < mm);
    return cur;
}
 
 
int val[mm] , ls[mm] ,rs[mm];
void modify(int l, int r, int p, int &x, int v) {
    if(!x)  x = extend();
    
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
    int L, R;
    mutable int v;
    bool operator<(const ds &rhs) const{
        return L < rhs.L;
    }
};
 
set<ds> has;
auto split(int pos){
    if (pos > mx || has.empty()) return has.end();
    ds t = {pos, -1, 0};
    auto it = has.lower_bound(t);
    if (it != has.end() && it->L == pos) return it;
    if (it == has.begin()) return has.end();
    it--;
    
    int l = it->L, r = it->R;
    int v = it->v;
    if (r < pos) return has.end();
    has.erase(it);
    has.insert({l, pos - 1, v});
    return has.insert({pos, r, v}).first;
}
int ans;
int solve(int L , int R){
    return query(1 , mx , L , R , root);
}
void work(int L , int R , int v = 0){
     auto it = has.lower_bound({L , -1 , -1});
      while (it != has.end() &&it->L <=R){
            auto temp = *it;
            ans-= solve(temp.L , temp.R);
            it = has.erase(it);
        }
        ans+= solve(L , R);
        has.insert({L , R  , v});
}
 
void main_(int tc){
    ans = 0;
    int n; cin >> n;
    vector <int > a(n);
    for (auto &i : a) {
        cin >> i;
        modify(1  , mx , i , root ,  1);
    }
  
    int qs; cin >> qs;
 
 
 
    auto upd = [&](int l, int r, int v = 0){
        auto itr = split(r + 1);
        auto itl = split(l);
        work(l ,  r , v);
    };
 
 
 
    for (int i = 0; i < qs; ++i){
         int tp , L , R; L = R = 0;
        cin >> tp;
        if (tp == 2) {
            has.clear();
            ans = 0;
        }
        else {
              cin >> L >> R;
            upd(L , R);
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
