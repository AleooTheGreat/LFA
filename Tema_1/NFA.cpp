#include<fstream>
#include <vector>
#include<list>
#include<queue>

using namespace std;

bool solve(const vector<int>& nod,const vector<int>& final, vector<vector<list<int>>> v, int st, string cuv){

    int c = 0;
    queue<int> q1,q2;
    q1.push(st);

    while(c != (cuv.length())){
        int a = cuv[c] - 97;

        while(!q1.empty()){
            st = q1.front();

            if(v[st][a].front() != -1){
                for(auto it:v[st][a]){
                    q2.push(it);
                }
            }
            q1.pop();
        }

        if(!q2.empty()){
            q1.swap(q2);
            c++;
        }else{
            return false;
        }
    }

    vector<int> sol;

    while(!q1.empty()){
        sol.push_back(q1.front());
        q1.pop();
    }

    for(auto i : final){
        for(auto it : sol) {
            if (it == i) {
                return true;
            }
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
    vector<vector<list<int>>> v;

    in>>n;
    for(int i = 0 ; i < n ; i++){
        int x;
        in >> x;
        nod.push_back(x);
    }

    in >> m;

    for(int i = 0 ; i < n; i++){
        vector<list<int>> aux;
        for(int j = 0 ; j < 26; j++){
            aux.push_back({-1});
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

        if(v[xx][l-97].front() == -1){
            v[xx][l-97].pop_front();
        }

        v[xx][l-97].push_back(yy);
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