
struct Line {
    ll m , c;
    Line(): m(0), c(INF) {}

    Line(ll _m , ll _c) : m(_m) , c(_c) {}

    ll f(ll x){
        return m * x + c;
    }
};

struct cht{ // for upper hull we need all slopes in non increasing order
    deque<Line > q;
    cht(){
        q.clear();
    }
    bool bad(Line L1 , Line L2 , Line L3){
        ll a = (__int128)(L2.c-L1.c) * (L2.m-L3.m);
        ll b = (__int128)(L3.c-L2.c) * (L1.m-L2.m);
        return a >= b;
    }
    void ins(Line nw){
        while((int)q.size() > 1 && bad(q[(int)q.size()-2] , q[(int)q.size()-1] , nw)) q.pop_back();
        q.push_back(nw);
    }

    ll query(ll p){
        int L = 0 , R = (int)q.size()-1;
        ll ans = INF;
        while(L <= R){
            int md1 = L + (R - L) / 3, md2 = R - (R-L) / 3;
            if (q[md1].f(p) <= q[md2].f(p)) R = md2-1;
            else L = md1 + 1;
            ans = min({ans , q[md1].f(p) , q[md2].f(p)});
        }
        return ans;
    }
};
