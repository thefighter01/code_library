struct Line {
    ll m , c;
    Line(): m(0), c(INF) {}

    Line(ll _m , ll _c) : m(_m) , c(_c) {}

    ll f(ll x){
        return m * x + c;
    }
};

const int mm = 30 * 2e5; // this lichao computes the mn value for a given point 
Line val[mm]; 
int lc[mm] , rc[mm] , nodes , root , L , R;
void init0(int a , int b){
    root = nodes = 0;
    L = a , R = b;
}
int extend(){
    int cur = ++nodes;
    assert(cur < mm);
    val[cur] = Line(); lc[cur] = rc[cur] = 0;
    return cur;
}

void modify(int nl , int nr ,int &x , Line nw){
    if (!x) x = extend();
    int md = (nl + nr) >> 1;
    int c1 = nw.f(nl) < val[x].f(nl);
    int c2 = nw.f(md) < val[x].f(md);
    if (c2) swap(nw , val[x]);
    if (nl +1 == nr) return;
    if (c1 != c2) modify(nl , md , lc[x] , nw);
    else modify(md , nr , rc[x] , nw);
}

void ins(Line nw){
    modify(L , R , root , nw);
}

ll query(int nl , int nr , int &x , ll p){
    if (nl+1 == nr){
        return val[x].f(p);
    }
    int md = (nl + nr) >> 1;
    ll ans = val[x].f(p);
    if (p < md) ans = min(ans , query(nl , md , lc[x] , p));
    else ans = min(ans , query(md, nr , rc[x] , p));
    return ans;
}
ll query(ll p){
    return query(L , R , root , p);
}
 
}
