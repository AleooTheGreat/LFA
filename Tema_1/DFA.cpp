#include<fstream>
#include <vector>

using namespace std;

bool solve(const vector<int>& nod,const vector<int>& final, vector<vector<int>> v, int st, string cuv){

    int c = 0;

    while(c != (cuv.length())){
        int a = cuv[c] - 97;

        if(v[st][a] == -1){
            return false;
        }else{
            st = v[st][a];
            c++;
        }
    }

    for(auto i : final){
        if(st == i){
            return true;
        }
    }

    return false;
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m, st, f, nr_cuv;

    vector<int> nod;
    vector<int> final;
    vector<vector<int>> v;

    in>>n;
    for(int i = 0 ; i < n ; i++){
        int x;
        in >> x;
        nod.push_back(x);
    }

    in >> m;

    for(int i = 0 ; i < m; i++){
        vector<int> aux;
        for(int j = 0 ; j < 26; j++){
            aux.push_back(-1);
        }
        v.push_back(aux);
    }

    for(int i = 0 ; i < m ; i++){
        int x,y, xx, yy;
        char l;
        in >> x >> y >> l;

        for(int j = 0 ; j < n; j++){
            if(x == nod[j]){
                xx = j;
            }
            if(y == nod[j]){
                yy = j;
            }
        }

        v[xx][l-97] = yy;
    }

    in >> st;
    for(int j = 0 ; j < n; j++) {
        if (st == nod[j]) {
            st = j;
        }
    }

    in >> f;

    for(int i = 0 ; i < f ;i++){
        int x;
        in >> x;
        for(int j = 0 ; j < n; j++) {
            if (x == nod[j]) {
                x = j;
            }
        }
        final.push_back(x);
    }

    in >> nr_cuv;

    for(int i = 0 ; i < nr_cuv; i++){

        string cuv;

        in >> cuv;

        if(solve(nod, final, v, st, cuv)){
            out<<"DA"<<'\n';
        }else{
            out<<"NU"<<'\n';
        }
    }

}