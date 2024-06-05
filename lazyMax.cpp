
 
struct sss{
    int n;
    vector <ll > t , lazy;
    void init(int _n , vector <ll > & v){
        n = _n+5;
        while (popcount(n) != 1) ++n;
        t = vector <ll > (2 * n);
        lazy = vector <ll > (2 * n);
        build(0 , 0 , n , v);
    }
    void drop (int node , int nl , int nr){
        if (!lazy[node]) return;
        t[node]+= lazy[node];
        if (nr-nl-1){
            lazy[2 * node +1]+= lazy[node];
            lazy[2 * node +2]+= lazy[node];
        }
        lazy[node] = 0;
    }
    void build (int node , int nl , int nr , vector <ll > & v){
        if (nl+1 == nr){
            if (nl < (int)v.size() && nl) t[node] = v[nl-1];
            else if (!nl) t[node] = 0;
            return;
        }
        int md = nl + nr >> 1;
        build(2 * node +1 , nl , md , v);
        build(2* node +2 , md , nr , v);
        t[node] = max(t[2* node +1] , t[2 * node +2]);
    }
    void upd (int node , int nl , int nr , int ql , int qr , int v){
        drop(node , nl , nr);
        if (nl >= qr || ql >= nr) return;
        if (nl >= ql && qr >= nr){
            lazy[node] = v;
            return drop(node , nl , nr);
        }
        int md = nl + nr >> 1;
        upd(2* node +1 , nl , md , ql , qr , v);
        upd(2* node +2 , md , nr , ql , qr , v);
        t[node] = max(t[2 * node +1] , t[2 * node +2] );
    }
 
    void upd (int L ,int R , int v) {
        return upd(0, 0, n, L, R + 1, v);
 
    }
    ll query (int node , int nl , int nr , int ql , int qr){
        drop(node , nl , nr);
        if (nl >= qr || ql >= nr) return 0;
        if (nl >= ql && qr >= nr) return t[node];
        int md = nl + nr >> 1;
        ll L = query(2 * node +1 , nl , md , ql , qr);
        ll R = query(2 * node +2 , md , nr , ql , qr);
        return max(L , R);
    }
    ll query (int L , int R){
        return query(0 , 0 , n , L , R+1);
    }
};
