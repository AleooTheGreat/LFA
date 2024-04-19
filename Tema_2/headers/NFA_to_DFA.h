//
// Created by aleoo on 4/15/24.
//

#ifndef LFA_NFA_TO_DFA_H
#define LFA_NFA_TO_DFA_H


#include <vector>
#include <queue>
#include <set>
#include "Global.h"

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

class NFA_to_DFA {

public:

    explicit NFA_to_DFA();
    static void citire(NFA &nfa);
    static void conversie(NFA &nfa, DFA &dfa);
    static void afisare(DFA &dfa);

private:
    NFA my_nfa;
    DFA my_dfa;
};


#endif //LFA_NFA_TO_DFA_H
