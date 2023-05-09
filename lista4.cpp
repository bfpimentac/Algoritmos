#include <iostream>
#define HOR 0
#define VER 1
using namespace std;

const int maxN = 200005;
int parent[maxN], sizes[maxN];

void makeSet(int n){
    for(int i = 0; i <= n; i++){
        parent[i] = i;
        sizes[i] = 1;
    }
}

int findSet(int x){
    if(x==parent[x]) return x;
    return (parent[x] = findSet(parent[x]));
}

bool isSameSet(int a, int b){
    return findSet(a) == findSet(b);
}

void uniteSet(int a, int b){
    int x = findSet(a), y = findSet(b);
    if(x != y){
        if(sizes[x] > sizes[y]) parent[y] = x;
        else{
            parent[x] = y;
            if(sizes[x] == sizes[y]) sizes[y]++;
        }
    }
}

int main(){
    int k;
    cin >> k;

    for(int i = 0; i < k; i++){
        int n, m, q, w;
        bool type_wall;
        cin >> n >> m >> q;
        makeSet(n*n + 1);
        while(m--){
            cin >> w;
            int row = w/(n+n-1);
            int a, b;
            if(w%(n+n-1) < n-1) type_wall = HOR;
            else type_wall = VER;
            if(type_wall == HOR){
                a = w - row*(n-1);
                b = a+1;
            }
            else{
                a = w - (row+1)*(n-1);
                b = a+n;
            }
            uniteSet(a, b);
        }
        for(int j = 0; j < q; j++){
            int a, b;
            cin >> a >> b;
            if(isSameSet(a, b))
                cout << i << "." << j << " " << 1 << endl;
            else cout << i << "." << j << " " << 0 << endl;
        }
        cout << endl;
    }
}