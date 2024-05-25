//
// Created by Alex Pascaru on 25.05.2024.
//
/*
 * Acest FST ruleaza accepta DFA uri si le transforma deci avem un determinist FTS
 */

#include<bits/stdc++.h>

bool solve(std::vector<std::vector<std::pair<char,int>>>& tab, std::string& word, std::vector<int>& fina){

    std::ofstream fout("output.txt");

    int index = 0, pos = 0;
    std::string cuv;

    while(index != word.size()){
        char chr = tab[pos][word[index]-'a'].first;
        pos = tab[pos][word[index]-'a'].second;
        cuv += chr;
        index++;
    }
    for(auto i:fina){
        if(pos == i){
            fout<<cuv;
            return true;
        }
    }
    return false;
}

int main(){
    std::ifstream fin("Tema_3/FST.txt");
    std::ofstream fout("output.txt");

    int n;
    fin >> n;

    int nr_stari;
    std::vector<std::vector<std::pair<char,int>>> table;
    fin>>nr_stari;

    for(int i = 0 ; i < nr_stari ; i ++){
        std::vector<std::pair<char,int>> aux;
        for(int j = 0 ; j < 27 ; j ++){
            std::pair<char,int> st;
            st.first = '-';
            st.second = -1;
            aux.push_back(st);
        }
        table.push_back(aux);
    }

    for(int i = 0 ; i < nr_stari ; i++){
        int a,b;
        char c1,c2;
        fin >> a >> c1 >> c2 >> b;
        table[a][c1-'a'].first = c2;
        table[a][c1-'a'].second = b;
    }

    int nr_stari_finale;
    std::vector<int> finale;
    fin>>nr_stari_finale;
    for(int i = 0 ; i < nr_stari_finale;i++){
        int a;
        fin >> a;
        finale.push_back(a);
    }

    std::string cuvant;
    fin>>cuvant;

    if(!solve(table,cuvant,finale)){
        fout<<"Cuvantul nu s-a putut convertii pentru nu apartine limbajului!";
    }
}