//
// Created by aleoo on 4/15/24.
//

#include <vector>
#include <deque>
#include <set>
#include <iostream>
#include <array>
#include <map>

#ifndef LFA_GLOBAL_H
#define LFA_GLOBAL_H

#endif //LFA_GLOBAL_H

struct NFA{
    int nr_st; ///nr de stari
    std::vector<int> st; ///starile
    int nr_l; ///nr de litere
    std::vector<char> l; ///literele
    int st_in; ///starea initiala
    int nr_st_f; ///numarul de stari finale
    std::vector<int> st_fi; ///starile finale
    int nr_tranz; ///numarul de tranzitii
    std::vector<std::vector<std::deque<int>>> tranz;  ///tranzitiile care functioneaza pe ideea EX: pleci din 1 cu a si ajungi in 1 si 2, deci tranz[1][int(a-'a')] = {1,2}
};

struct DFA{
    std::map<std::set<int>, std::map<char, std::set<int>>> tranzi_dfa;
    std::set<std::set<int>> finale_dfa;
    int initial_dfa;
};
