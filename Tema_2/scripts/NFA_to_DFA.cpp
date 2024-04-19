//
// Created by aleoo on 4/15/24.
//

#include "Tema_2/headers/NFA_to_DFA.h"
#include <fstream>
#include <map>
#include <algorithm>

/// Citirea se face dupa dormatul acesta :
/// 3  -> numarul de stari
/// 0 1 2 -> starile trebuie sa fie consecutive incepand de la 0
/// 2     -> numarul de litere
/// a b   -> literele sa fie consecutive incepand de la a si sa fie din litere mici din alfabetul engelez
/// 0     -> starea initiala
/// 2     -> numarul de stari finale
/// 2 1   -> starile finale
/// 7     -> numarul de tranzitii
/// 0 a 0
/// 0 a 1
/// 0 b 2
/// 1 a 0
/// 1 b 1
/// 2 b 1
/// 2 b 0


NFA_to_DFA::NFA_to_DFA(){

    citire(my_nfa);
    conversie(my_nfa,my_dfa);
    afisare(my_dfa);

}

void NFA_to_DFA::citire(NFA &nfa) {

    std::ifstream in("txts/input_NFA_to_DFA.txt");

    in >> nfa.nr_st;

    for(auto i = 0; i < nfa.nr_st; i++){
        int x;
        in >> x;
        nfa.st.push_back(x);
    }

    in >> nfa.nr_l;

    for(auto i = 0; i < nfa.nr_l; i++){
        char x;
        in >> x;
        nfa.l.push_back(x);
    }

    in >> nfa.st_in;

    in >> nfa.nr_st_f;

    for(auto i = 0 ; i < nfa.nr_st_f; i++){
        int x;
        in >> x;
        nfa.st_fi.push_back(x);
    }

    in >> nfa.nr_tranz;

    /// Well alocarea dinamica a unei matrici nu este chiar amuzanta asa ca vom creea prima data dimensiunea
    /// Am ales ca umplu cu -1 pentru a verifica daca este sau nu empty mai usor
    for(auto i = 0 ; i < nfa.nr_st ; i++){

        std::vector<std::deque<int>> aux;

        for(auto j = 0 ; j < nfa.nr_l; j++){
            std::deque<int> q;
            q.push_front(-1);
            aux.push_back(q);
        }

        nfa.tranz.push_back(aux);
    }


    for(auto i = 0 ; i < nfa.nr_tranz ; i++){

        int x1,x3;
        char x2;

        in >> x1 >> x2 >> x3;

        if(nfa.tranz[x1][int(x2 - 'a')].front() == -1){
            nfa.tranz[x1][int(x2 - 'a')].pop_front();
        }

        nfa.tranz[x1][int(x2 - 'a')].push_front(x3);
    }
}

void NFA_to_DFA::conversie(NFA &nfa, DFA &dfa) {

    ///viz ne spune daca am fost sau nu in starea pe care am o aveam in coada
    std::map<std::set<int>, bool> viz;
    std::queue<std::set<int>> next;

    ///Tinem minte ultimul nod pentru a putea insera "stari vide"
    std::set<int> last_node;
    last_node.insert(nfa.nr_st + 1);

    ///Punem pozitia initiala in dfa
    std::set<int> start;
    start.insert(nfa.st_in);
    next.push(start);

    dfa.initial_dfa = nfa.st_in;

    while (!next.empty()) {

        std::set<int> aux = next.front();
        next.pop();

        if (!viz[aux]) {

            viz[aux] = true;

            for(int i = 0 ; i < nfa.nr_l; i++){

                std::set<int> my_aux_set;

                for(auto it : aux){
                    for(auto it2: nfa.tranz[it][i]){
                        if(it2 != -1) {
                            my_aux_set.insert(it2);
                            if(std::find(nfa.st_fi.begin(),nfa.st_fi.end(),it2) != nfa.st_fi.end()){
                                dfa.finale_dfa.insert(my_aux_set);
                            }
                        }
                    }
                }

                if(my_aux_set.empty()){

                    dfa.tranzi_dfa[aux][char(i+'a')] = last_node;

                    for(int ii = 0 ; ii < nfa.nr_l; ii++){
                        dfa.tranzi_dfa[last_node][char(ii + 'a')] = last_node;
                    }

                }else{
                    next.push(my_aux_set);
                    dfa.tranzi_dfa[aux][char(i+'a')] = my_aux_set;
                }
            }
        }
    }
}

void NFA_to_DFA::afisare(DFA &dfa) {

    std::ofstream out("txts/tema2_output.txt");

    for (auto& state : dfa.tranzi_dfa) {

        out << "DFA State: { ";

        for (int s : state.first) {
            out << s << " ";
        }

        out << "}:\n";

        for (auto& trans : state.second) {

            out << "  Utilizand '" << trans.first << "' mergem in starea { ";

            for (int s1 : trans.second) {
                out << s1;
            }

            out << " }\n";
        }
    }

    out << "Starea initiala este : { "<<dfa.initial_dfa<<" }\n";


        out << "Stariile finale sunt : { ";
        for (auto &it: dfa.finale_dfa) {
            for (auto it2: it) {
                out << it2;
            }
            out << " ";
        }
        out<<"}";
}
