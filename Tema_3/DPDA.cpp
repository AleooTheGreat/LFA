//
// Created by Alex Pascaru on 25.05.2024.
//
/*
 * Acesta este un DPDA si are urmatoarele reguli de implementare:
 * By default pe stiva o sa existe $ si consideram ca dupa ce efectuam operatii pe stiva
 * si ajungem iar la $, terminand cuvantul tesat, vom avea cuvant acceptat.
 * Aceasta este singura situatie, in care aveam cuvant acceptat.
 * Inputul este de forma de ( de unde plecam, cu ce plecam, ce stergem de pe stiva, ce punem pe stiva, si unde ajugem)
 * Numarul de stari finale si starile finale
 * cuvantul
 */

#include<bits/stdc++.h>

bool solve(std::vector<std::vector<std::tuple<std::string,std::string,int>>>& tab, std::string& word){

    std::ofstream fout("output.txt");

    std::deque<char> q;
    q.push_back('$');

    int index = 0,pos = 0;
    while(index != word.size()){
        std::string c1 = std::get<0>(tab[pos][word[index] - 'a']);

        for(auto i : c1){
            if(i != q.back()) {
                return false;
            }
            q.pop_back();
        }
        c1 = std::get<1>(tab[pos][word[index] - 'a']);
        std::reverse(c1.begin(),c1.end());
        for(char i : c1){
            if(i != '#') {
                q.push_back(i);
            }
        }
        pos = std::get<2>(tab[pos][word[index] - 'a']);
        index++;
    }
    if(q.size() == 1 and q.front() == '$'){
        return true;
    }
}

int main(){

    std::ifstream fin("Tema_3/DPDA.txt");
    std::ofstream fout("output.txt");

    std::vector<std::vector<std::tuple<std::string,std::string,int>>> table;
    int n;

    fin >> n;

    for(int i = 0 ; i < n + 1 ; i++){
        std::vector<std::tuple<std::string,std::string,int>> aux;
        for(int j = 0 ; j <= 27 ; j++){
            std::tuple<std::string,std::string,int> chr;
            chr = std::make_tuple('-','-', -1);
            aux.push_back(chr);
        }
        table.push_back(aux);
    }

    int nr_stari;
    fin >> nr_stari;

    for(int i = 0 ; i < nr_stari; i++){
        int a,b;
        char c1;
        std::string c2,c3;
        fin >> a >> c1 >> c2 >> c3 >> b;
        if(c1 != '#') {
            std::get<0>(table[a][c1-'a']) = c2;
            std::get<1>(table[a][c1-'a']) = c3;
            std::get<2>(table[a][c1-'a']) = b;
        }else{
            std::get<0>(table[a][26]) = c2;
            std::get<1>(table[a][26]) = c3;
            std::get<2>(table[a][26]) = b;
        }

    }

    int nr_finale;
    fin>>nr_finale;
    std::vector<int> finale;
    for(int i = 0 ; i < nr_finale; i++){
        int a;
        fin >> a;
        finale.push_back(a);
    }

    std::string cuvant;
    fin >> cuvant;


    if(cuvant.size() % 2 == 0){
        if(solve(table,cuvant)){
            fout<<"DA!";
        }else{
            fout<<"NU!";
        }
    }else{
        fout<<"NU!";
        return 0;
    }
}