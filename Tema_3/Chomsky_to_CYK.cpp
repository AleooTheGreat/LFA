//
// Created by Alex Pascaru on 24.05.2024.
//
#include<bits/stdc++.h>
#include<fstream>

/*
Formatul este:
S -> AC | BD
A -> BB | a
B -> CC | b
C -> AB | a
D -> BA | c
baacab
 se introce o gramatica CNF si pe ultimul rand cuvantul pe care dorim sa il analizam
 sursa de inspiratie pentru algorithm:
 https://www.cs.ucdavis.edu/~rogaway/classes/120/winter12/CYK.pdf
 */

void solve(std::string& word, std::unordered_map<std::string,std::vector<char>>& tab) {

    std::ofstream fout("output.txt");

    std::vector<std::vector<std::deque<char>>> dp;

    for (int i = 0; i < word.size(); i++) {
        std::vector<std::deque<char>> auxl;
        for (int j = 0; j < word.size(); j++) {
            std::deque<char> daux;
            daux.push_back('#');
            auxl.push_back(daux);
        }
        dp.push_back(auxl);
    }

    for (int i = 0; i < word.size(); i++) {
        for (int j = 0; j < word.size() - i; j++) {
            std::string aux;
            if (i == 0) {
                aux = word[j];
                for (auto k: tab[aux]) {
                    if (dp[i][j].back() == '#') {
                        dp[i][j].clear();
                    }
                    dp[i][j].push_back(k);
                }
            } else {
                for (int k = j; k < j + i; k++) {
                    std::deque<char> deq1;
                    std::deque<char> deq2;

                    for (auto t: dp[k - j][j]) {
                        deq1.push_back(t);
                    }
                    for (auto t: dp[j + i - k - 1][k + 1]) {
                        deq2.push_back(t);
                    }


                    for (auto t: deq1) {
                        for (auto t2: deq2) {
                            aux = t;
                            aux += t2;
                            if (tab.count(aux) != 0) {
                                for (auto t3: tab[aux]) {
                                    if (dp[i][j].back() == '#') {
                                        dp[i][j].clear();
                                    }
                                    ///verificam duplicatele
                                    std::deque<char>::iterator itr;
                                    itr = std::find(dp[i][j].begin(),dp[i][j].end(),t3);
                                    if(itr == dp[i][j].end()) {
                                        dp[i][j].push_back(t3);
                                    }
                                }
                            }
                        }
                    }

                }
            }

        }
    }

    ///afisarea dp ului
   /* for (auto it: dp) {
        for (auto it2: it) {
            for (auto it3: it2) {
                fout << it3 << " ";
            }
            fout << " ; ";
        }
        fout << '\n';
    }*/

    if (dp[word.size() - 1][0].front() != '#') {
        fout << "DA!";
    } else {
        fout << "NU!";
    }

    fout.close();

}

int main(){
    ///citire
    std::ifstream fin("Tema_3/Chomsky_to_CYK.txt");
    std::ofstream fout("output.txt");

    ///variabile
    std::unordered_map<std::string,std::vector<char>> table;
    std::string cuvant;

    ///aici rezolvam inputul (l-as putea numi parsat dar e cam bruteforce sincer)
    if(fin.is_open()) {
        std::string s;
        while(std::getline(fin, s)){
            int i = 0;
            char a;
            std::string b;
            while(s.size() != i){
                if(i == 0 && s[i] >= 'A' && s[i] <= 'Z'){
                    a = s[0];
                }else if(i == 0){
                    cuvant = s;
                    break;
                }else {

                    if (s[i] >= 'A' && s[i] <= 'Z') {
                        b = char(s[i]);
                        b += char(s[i + 1]);
                        table[b].push_back(a);
                        b.clear();
                        i++;
                    }

                    if (s[i] >= 'a' && s[i] <= 'z') {
                        b = s[i];
                        table[b].push_back(a);
                    }
                }

                i++;
            }
        }
        fin.close();
    }

    solve(cuvant, table);
}