#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <functional>

using namespace std;

struct Nfa {
    int n;
    vector<vector<pair<int, int>>> g;
    int start;
    vector<int> finalStates;

    Nfa() : n(0), start(-1) {}

    void addEdge(int from, int to, int c) {
        if (from >= (int)g.size() || to >= (int)g.size())
            g.resize(max(from, to) + 1);
        g[from].push_back({to, c});
    }

    void print() {
        cout << "Start State: " << start << "\n";
        cout << "Edges (from, to, char):\n";
        for (int i = 0; i < (int)g.size(); i++) {
            for (auto& p : g[i]) {
                cout << i << " -> " << p.first << " by ";
                if (p.second == 26)
                    cout << "#";
                else
                    cout << char('a' + p.second);
                cout << "\n";
            }
        }
        cout << "Final States: ";
        for (int fin : finalStates)
            cout << fin << " ";
        cout << "\n";
    }
};

Nfa parseRegexToNfa(const string& s) {

    int p = 0;
    function<Nfa(int&)> parseExpr, parseTerm, parseFactor;

    parseExpr = [&](int& pos) -> Nfa {
        Nfa result;
        result = parseTerm(pos);
        while (pos < s.size() && s[pos] == '|') {
            pos++;
            Nfa parsed = parseTerm(pos);

            Nfa new_nfa;
            new_nfa.n = result.n + parsed.n + 1;
            new_nfa.start = 0;
            new_nfa.finalStates.push_back(new_nfa.n - 1);


            new_nfa.addEdge(0, 1, 26);
            new_nfa.addEdge(0, 1 + result.n, 26);


            for (int i = 0; i < result.n; i++) {
                for (auto& p : result.g[i]) {
                    new_nfa.addEdge(1 + i, 1 + p.first, p.second);
                }
                if (find(result.finalStates.begin(), result.finalStates.end(), i) != result.finalStates.end()) {
                    new_nfa.addEdge(1 + i, new_nfa.n - 1, 26);
                }
            }

            for (int i = 0; i < parsed.n; i++) {
                for (auto& p : parsed.g[i]) {
                    new_nfa.addEdge(1 + result.n + i, 1 + result.n + p.first, p.second);
                }
                if (find(parsed.finalStates.begin(), parsed.finalStates.end(), i) != parsed.finalStates.end()) {
                    new_nfa.addEdge(1 + result.n + i, new_nfa.n - 1, 26);
                }
            }

            result = new_nfa;
        }
        return result;
    };

    parseTerm = [&](int& pos) -> Nfa {
        Nfa result;
        result = parseFactor(pos);
        while (pos < s.size() && s[pos] != '|' && s[pos] != ')') {
            Nfa parsed = parseFactor(pos);

            Nfa new_nfa;
            new_nfa.n = result.n + parsed.n;
            new_nfa.start = result.start;


            for (int i = 0; i < result.n; i++) {
                for (auto& p : result.g[i]) {
                    new_nfa.addEdge(i, p.first, p.second);
                }
                if (find(result.finalStates.begin(), result.finalStates.end(), i) != result.finalStates.end()) {
                    new_nfa.addEdge(i, result.n + parsed.start, 26);
                }
            }


            for (int i = 0; i < parsed.n; i++) {
                for (auto& p : parsed.g[i]) {
                    new_nfa.addEdge(result.n + i, result.n + p.first, p.second);
                }
                if (find(parsed.finalStates.begin(), parsed.finalStates.end(), i) != parsed.finalStates.end()) {
                    new_nfa.finalStates.push_back(result.n + i);
                }
            }

            result = new_nfa;
        }
        return result;
    };

    parseFactor = [&](int& pos) -> Nfa {
        Nfa result;
        if (s[pos] == '(') {
            pos++;
            result = parseExpr(pos);
            assert(s[pos] == ')');
            pos++;
        } else {
            assert(islower(s[pos]));
            result.n = 2;
            result.start = 0;
            result.finalStates.push_back(1);
            result.addEdge(0, 1, s[pos] - 'a');
            pos++;
        }

        while (pos < s.size() && s[pos] == '*') {
            pos++;

            Nfa new_nfa;
            new_nfa.n = result.n + 1;
            new_nfa.start = 0;
            new_nfa.finalStates.push_back(0);


            for (int i = 0; i < result.n; i++) {
                for (auto& p : result.g[i]) {
                    new_nfa.addEdge(1 + i, 1 + p.first, p.second);
                }
                if (find(result.finalStates.begin(), result.finalStates.end(), i) != result.finalStates.end()) {
                    new_nfa.addEdge(1 + i, 0, 26);
                }
            }
            new_nfa.addEdge(0, 1 + result.start, 26);

            result = new_nfa;
        }
        return result;
    };

    Nfa nfa = parseExpr(p);
    assert(p == s.size());
    return nfa;
}

int main() {
    string regex;
    cout << "Enter a regular expression: ";
    cin >> regex;

    Nfa nfa = parseRegexToNfa(regex);
    nfa.print();
    return 0;
}