#include<fstream>
#include <vector>
#include<list>
#include<queue>
#include <set>

using namespace std;

queue<int> lambda_goes(int n, queue<int> q1,vector<vector<list<int>>> v) {

    set<int> aux;

    while (!q1.empty()) {
        int st = q1.front();

        vector<bool> f;

        for (int i = 0; i < n; i++) {
            f.push_back(false);
        }

        queue<int> q;
        f[st] = true;
        q.push(st);
 
        while (!q.empty()) {
            int currentNode = q.front();
            aux.insert(currentNode);
            q.pop();

            for (int neighbor: v[currentNode][26]) {
                if (!f[neighbor] && neighbor != -1) {
                    f[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        q1.pop();
    }

    queue<int> q_aux;
    for (auto it: aux) {
        q_aux.push(it);
    }

    return q_aux;
}

bool solve(int n,const vector<int>& final,vector<vector<list<int>>> v, int st, string cuv){

    int c = 0;
    queue<int> q1,q3;
    q1.push(st);

    while(c != (cuv.length())){
        int a = cuv[c] - 97;

        q3 = lambda_goes(n,q1,v);

        while(!q1.empty()){
            q1.pop();
        }

        set<int> my_set;

        while(!q3.empty()){
            st = q3.front();
            if(v[st][a].front() != -1){
                for(auto it:v[st][a]){
                    my_set.insert(it);
                }
            }
            q3.pop();
        }

        if(!my_set.empty()){
            for(auto it:my_set){
                q1.push(it);
            }
            my_set.clear();
            c++;
        }else{
            return false;
        }
    }

    queue<int>q2;
    q2 = lambda_goes(n,q1,v);

    vector<int> sol;

    while(!q2.empty()){
        sol.push_back(q2.front());
        q2.pop();
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
        for(int j = 0 ; j < 27; j++){
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

        if(l == '#'){
            if (v[xx][26].front() == -1) {
                v[xx][26].pop_front();
            }

            v[xx][26].push_back(yy);
        }else{
            if (v[xx][l - 97].front() == -1) {
                v[xx][l - 97].pop_front();
            }

            v[xx][l - 97].push_back(yy);
        }
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

        if(solve(n, final, v, st, cuv)){
            out<<"DA"<<'\n';
        }else{
            out<<"NU"<<'\n';
        }
    }

}