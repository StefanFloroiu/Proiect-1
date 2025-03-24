#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Clasa Jucator gestionează informațiile despre un jucător
class Jucator {
private:
    string nume;  // Numele jucătorului
    char simbol;  // Simbolul folosit de jucător ('X' sau 'O')

public:
    // Constructor implicit - setează valori implicite
    Jucator() : nume("Necunoscut"), simbol(' ') {}

    // Constructor cu parametri - inițializează un jucător cu nume și simbol
    Jucator(string nume, char simbol) : nume(nume), simbol(simbol) {}

    // Constructor de copiere - creează o copie a unui alt obiect Jucator
    Jucator(const Jucator& other) : nume(other.nume), simbol(other.simbol) {}

    // Destructor - eliberează resursele 
    ~Jucator() {}

    // Operator de atribuire - copiază valorile dintr-un alt obiect Jucator
    Jucator& operator=(const Jucator& other) {
        if (this != &other) {  // Verificăm să nu fie auto-atribuire
            nume = other.nume;
            simbol = other.simbol;
        }
        return *this;  // Returnăm referința la obiectul curent
    }

    // Setteri - metode pentru a seta valorile private
    void setNume(string n) { nume = n; }      // Setează numele jucătorului
    void setSimbol(char s) { simbol = s; }    // Setează simbolul jucătorului

    // Getteri - metode pentru a accesa valorile private
    string getNume() const { return nume; }   // Returnează numele jucătorului
    char getSimbol() const { return simbol; } // Returnează simbolul jucătorului

    // Operator de citire - permite introducerea datelor de la tastatură
    friend istream& operator>>(istream& in, Jucator& j) {
        cout << "Introduceti numele jucatorului: ";
        in >> j.nume;  // Citește numele introdus de utilizator
        return in;    
    }

    // Operator de scriere - afișează informațiile despre jucător
    friend ostream& operator<<(ostream& out, const Jucator& j) {
        out << "Jucator: " << j.nume << " | Simbol: " << j.simbol;
        return out;  
    }
};

// Clasa Tabla reprezintă tabla de joc 3x3
class Tabla {
private:
    vector<vector<char>> tabla;  // Matrice 3x3 pentru a stoca simbolurile

public:
    // Constructor implicit - inițializează tabla goală cu spații
    Tabla() : tabla(3, vector<char>(3, ' ')) {}

    // Constructor de copiere - creează o copie a unei alte table
    Tabla(const Tabla& other) : tabla(other.tabla) {}

    // Destructor - eliberează resursele 
    ~Tabla() {}

    // Operator de atribuire - copiază o altă tablă
    Tabla& operator=(const Tabla& other) {
        if (this != &other) {  // Verificăm să nu fie auto-atribuire
            tabla = other.tabla;
        }
        return *this;  // Returnăm referința la obiectul curent
    }

    // Afișează tabla de joc într-un format clar
    void afiseazaTabla() const {
        cout << "\n";
        for (int i = 0; i < 3; i++) {  
            for (int j = 0; j < 3; j++) {  
                cout << tabla[i][j];  // Afișează simbolul curent
                if (j < 2) cout << " | ";  // Adaugă separator între poziții
            }
            cout << "\n";
            if (i < 2) cout << "---------\n";  // Adaugă linie de separare între rânduri
        }
        cout << "\n";
    }

    // Execută o mutare pe tablă dacă poziția este validă și liberă
    bool mutare(int linie, int coloana, char simbol) {
        if (linie >= 0 && linie < 3 && coloana >= 0 && coloana < 3 && tabla[linie][coloana] == ' ') {
            tabla[linie][coloana] = simbol;  // Plasează simbolul pe tablă
            return true;  // Mutare reușită
        }
        return false;  // Mutare invalidă
    }

    // Verifică dacă există un câștigător cu simbolul dat
    bool verificaCastigator(char simbol) {
        // Verifică rândurile
        for (int i = 0; i < 3; i++) {
            if (tabla[i][0] == simbol && tabla[i][1] == simbol && tabla[i][2] == simbol) return true;
            // Verifică coloanele
            if (tabla[0][i] == simbol && tabla[1][i] == simbol && tabla[2][i] == simbol) return true;
        }
        // Verifică diagonalele
        if (tabla[0][0] == simbol && tabla[1][1] == simbol && tabla[2][2] == simbol) return true;
        if (tabla[0][2] == simbol && tabla[1][1] == simbol && tabla[2][0] == simbol) return true;
        return false;  // Nu există câștigător
    }

    // Verifică dacă tabla este plină (toate pozițiile ocupate)
    bool estePlina() {
        for (auto& rand : tabla)  // Parcurge fiecare rând
            for (char c : rand)   // Parcurge fiecare caracter din rând
                if (c == ' ') return false;  // Dacă găsește un spațiu, tabla nu e plină
        return true;  // Tabla este plină
    }
};

// Clasa Joc gestionează logica jocului
class Joc {
private:
    Jucator jucator1, jucator2;  // Cei doi jucători
    Tabla tabla;                 // Tabla de joc
    char jucatorCurent;          // Simbolul jucătorului curent ('X' sau 'O')

public:
    // Constructor implicit - setează jucătorul curent la 'X'
    Joc() : jucatorCurent('X') {}

    // Destructor - eliberează resursele (nu este necesar în acest caz)
    ~Joc() {}

    // Metoda principală care rulează jocul
    void start() {
        cout << "Jucator 1: \n";
        cin >> jucator1;           // Citește datele pentru jucătorul 1
        jucator1.setSimbol('X');   // Setează simbolul 'X' pentru jucătorul 1

        cout << "Jucator 2: \n";
        cin >> jucator2;           // Citește datele pentru jucătorul 2
        jucator2.setSimbol('O');   // Setează simbolul 'O' pentru jucătorul 2

        jucatorCurent = 'X';       // Jocul începe cu jucătorul 1

        while (true) {  // Bucla principală a jocului
            tabla.afiseazaTabla();  // Afișează starea curentă a tablei
            cout << "Este randul jucatorului " << (jucatorCurent == 'X' ? jucator1.getNume() : jucator2.getNume()) << ".\n";
            int linie, coloana;
            cout << "Introduceti linia si coloana (0, 1, 2): ";

            if (!(cin >> linie >> coloana)) {  // Verifică dacă inputul este valid
                cout << "Input invalid! Introduceti doar numere intre 0 si 2.\n";
                cin.clear();      // Resetează starea de eroare a fluxului
                cin.ignore(1000, '\n'); // Curăță buffer-ul de intrare
                continue;         // Reia cererea de input
            }

            if (!tabla.mutare(linie, coloana, jucatorCurent)) {  // Încearcă mutarea
                cout << "Mutare invalida! Incearca din nou.\n";
                continue;  // Reia cererea de input dacă mutarea e invalidă
            }

            if (tabla.verificaCastigator(jucatorCurent)) {  // Verifică dacă există câștigător
                tabla.afiseazaTabla();  // Afișează tabla finală
                cout << "Jucatorul " << (jucatorCurent == 'X' ? jucator1.getNume() : jucator2.getNume()) << " a castigat!\n";
                break;  // Jocul se termină
            }

            if (tabla.estePlina()) {  // Verifică dacă tabla e plină (remiză)
                tabla.afiseazaTabla();  // Afișează tabla finală
                cout << "Jocul s-a terminat cu remiza!\n";
                break;  // Jocul se termină
            }

            jucatorCurent = (jucatorCurent == 'X') ? 'O' : 'X';  // Schimbă jucătorul curent
        }
    }
};

// Clasa Meniu gestionează interfața utilizatorului
class Meniu {
public:
    // Afișează meniul și gestionează opțiunile utilizatorului
    void afiseazaMeniu() {
        int optiune;
        while (true) {  // Bucla meniului principal
            cout << "\n===== Meniu X si 0 =====\n";
            cout << "1. Incepe jocul\n";
            cout << "2. Iesire\n";
            cout << "Alegeti o optiune: ";

            cin >> optiune;  // Citește opțiunea utilizatorului

            if (cin.fail()) {  // Verifică dacă inputul este invalid
                cout << "Input invalid! Introduceti 1 sau 2.\n";
                cin.clear();              // Resetează starea de eroare
                cin.ignore(1000, '\n');   // Curăță buffer-ul de intrare
                continue;  // Reia cererea de input
            }

            if (optiune == 1) {  // Opțiunea de a începe jocul
                Joc joc;  // Creează un obiect Joc
                joc.start();  // Pornește jocul
            } else if (optiune == 2) {  // Opțiunea de ieșire
                cout << "Iesire...\n";
                break;  // Iese din bucla meniului
            } else {  
                cout << "Optiune invalida. Incearca din nou!\n";
            }
        }
    }
};

// Funcția principală - punctul de intrare al programului
int main() {
    Meniu meniu;         // Creează un obiect Meniu
    meniu.afiseazaMeniu();  // Pornește meniul jocului
    return 0;            
}