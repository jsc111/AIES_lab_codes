#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Structure for a term
struct Term {
    string name;
    vector<Term> arguments;
    
    // Default constructor
    Term() : name("") {}

    Term(string name) : name(name) {}

    Term(string name, vector<Term> arguments) : name(name), arguments(arguments) {}

    bool isVariable() const {
        return arguments.empty() && !isdigit(name[0]) && islower(name[0]);
    }

    bool isFunction() const {
        return !arguments.empty();
    }
};

// Type alias for the substitution map
using Substitution = unordered_map<string, Term>;

// Function to check for circular references (occurs check)
bool occursCheck(const string& var, const Term& term) {
    if (term.name == var) {
        return true;
    }
    for (const auto& arg : term.arguments) {
        if (occursCheck(var, arg)) {
            return true;
        }
    }
    return false;
}

// Function to apply a substitution to a term
Term applySubstitution(const Term& term, const Substitution& substitution) {
    if (term.isVariable() && substitution.find(term.name) != substitution.end()) {
        return applySubstitution(substitution.at(term.name), substitution);
    } else if (term.isFunction()) {
        vector<Term> newArguments;
        for (const Term& arg : term.arguments) {
            newArguments.push_back(applySubstitution(arg, substitution));
        }
        return Term(term.name, newArguments);
    }
    return term;
}

// Function to unify two terms
bool unify(const Term& term1, const Term& term2, Substitution& substitution) {
    Term t1 = applySubstitution(term1, substitution);
    Term t2 = applySubstitution(term2, substitution);

    if (t1.name == t2.name && t1.arguments.size() == t2.arguments.size()) {
        for (size_t i = 0; i < t1.arguments.size(); ++i) {
            if (!unify(t1.arguments[i], t2.arguments[i], substitution)) {
                return false;
            }
        }
        return true;
    } else if (t1.isVariable()) {
        if (occursCheck(t1.name, t2)) {
            return false; // Fail due to circular reference
        }
        substitution[t1.name] = t2;
        return true;
    } else if (t2.isVariable()) {
        if (occursCheck(t2.name, t1)) {
            return false; // Fail due to circular reference
        }
        substitution[t2.name] = t1;
        return true;
    }

    return false;
}

// Function to print a term
void printTerm(const Term& term) {
    if (term.arguments.empty()) {
        cout << term.name;
    } else {
        cout << term.name << "(";
        for (size_t i = 0; i < term.arguments.size(); ++i) {
            printTerm(term.arguments[i]);
            if (i < term.arguments.size() - 1) {
                cout << ", ";
            }
        }
        cout << ")";
    }
}

// Function to print a substitution
void printSubstitution(const Substitution& substitution) {
    for (const auto& pair : substitution) {
        const string& var = pair.first;
        const Term& term = pair.second;
        cout << var << " -> ";
        printTerm(term);
        cout << endl;
    }
}

int main() {
    // Test Cases

    // Test Case 1: Simple Unification
    Term term1("f", {Term("x"), Term("a")});
    Term term2("f", {Term("b"), Term("a")});
    Substitution substitution1;

    if (unify(term1, term2, substitution1)) {
        cout << "Unification succeeded. Substitution:" << endl;
        printSubstitution(substitution1);
    } else {
        cout << "Unification failed." << endl;
    }

    cout << endl;

    // Test Case 2: Unification with Variables
    Term term3("g", {Term("y"), Term("z")});
    Term term4("g", {Term("f", {Term("a")}), Term("z")});
    Substitution substitution2;

    if (unify(term3, term4, substitution2)) {
        cout << "Unification succeeded. Substitution:" << endl;
        printSubstitution(substitution2);
    } else {
        cout << "Unification failed." << endl;
    }

    cout << endl;

    // Test Case 3: Unification Failure
    Term term5("h", {Term("x"), Term("b")});
    Term term6("h", {Term("a"), Term("c")});
    Substitution substitution3;

    if (unify(term5, term6, substitution3)) {
        cout << "Unification succeeded. Substitution:" << endl;
        printSubstitution(substitution3);
    } else {
        cout << "Unification failed." << endl;
    }

    return 0;   
}
