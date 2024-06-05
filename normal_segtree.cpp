template <typename T >
struct sss{
    // take care of data types and neutral elements and merge function
    int n;
    vector < T > t;
    void init(int _n){
        n = _n + 5;
        while (popcount(n) != 1) ++n;
        t = vector < T > (2 * n , INF);
    }
     T merge (T u, T v){
        return min(u , v);
    }
    void upd (int node , int nl , int nr , int idx , T v ){
        if (nl + 1 == nr){
            t[node] = v;
            return;
        }
        int md = (nl + nr) >> 1;
        if (idx < md) upd(2 * node + 1 , nl , md , idx, v);
        else upd(2* node + 2 , md, nr, idx, v);
        t[node] = merge (t[2* node + 1] , t[2* node + 2]);
    }
    T query (int node , int nl , int nr , int ql , int qr){
        if (nl >= ql && qr >= nr) return t[node];
        int md = (nl + nr ) >> 1;
        if (qr <= md) return query(2* node + 1 , nl , md , ql ,qr);
        if (ql >= md) return query (2* node + 2, md, nr , ql ,qr);
        return merge(query (2* node + 1 , nl , md , ql ,qr), query (2 * node + 2, md, nr , ql , qr));
    }
    void upd (int idx , T v ){
        upd(0 , 0 , n , idx , v);
    }
    T query (int L , int R){
        return query (0 ,0 , n , L , R+ 1);
    }
};
