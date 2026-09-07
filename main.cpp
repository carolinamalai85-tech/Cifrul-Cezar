#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<string> ALFABET_BAZA = {
    "A", "Ă", "Â", "B", "C", "D", "E", "F", "G", "H", "I", "Î", 
    "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "Ș", "T", 
    "Ț", "U", "V", "W", "X", "Y", "Z"
};

const vector<string> ALFABET_MIC = {
    "a", "ă", "â", "b", "c", "d", "e", "f", "g", "h", "i", "î", 
    "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "ș", "t", 
    "ț", "u", "v", "w", "x", "y", "z"
};

vector<string> extrageCaractereUTF8(const string& str) {
    vector<string> caractere;
    for (size_t i = 0; i < str.length(); ) {
        unsigned char c = str[i];
        int lungimeSecventa = 1;

        if ((c & 0x80) == 0) lungimeSecventa = 1;
        else if ((c & 0xE0) == 0xC0) lungimeSecventa = 2;
        else if ((c & 0xF0) == 0xE0) lungimeSecventa = 3;
        else if ((c & 0xF8) == 0xF0) lungimeSecventa = 4;

        caractere.push_back(str.substr(i, lungimeSecventa));
        i += lungimeSecventa;
    }
    return caractere;
}

int gasestePozitieBaza(const string& litera) {
    for (size_t i = 0; i < ALFABET_BAZA.size(); ++i) {
        if (ALFABET_BAZA[i] == litera || ALFABET_MIC[i] == litera) {
            return i;
        }
    }
    return -1;
}

int gasestePozitieInVector(const vector<string>& alfabet, const string& litera) {
    for (size_t i = 0; i < alfabet.size(); ++i) {
        if (alfabet[i] == litera) return i;
    }
    return -1;
}

bool curataText(const string& text_str, vector<string>& textCurat) {
    textCurat.clear();
    vector<string> simboluri = extrageCaractereUTF8(text_str);

    for (const string& s : simboluri) {
        if (s == " " || s == "\t") continue;

        int pos = gasestePozitieBaza(s);
        if (pos != -1) {
            textCurat.push_back(ALFABET_BAZA[pos]);
        } else {
            cout << "Eroare: Simbolul '" << s << "' nu este o litera valida in alfabetul roman!\n";
            return false;
        }
    }
    return true;
}

void proceseazaCezarSimplu() {
    int operatie, k1;
    string text_str;
    vector<string> textCurat, rezultat;

    cout << "\n--- CIFRUL CEZAR SIMPLU (O CHEIE) ---\n";
    cout << "1. Criptare\n2. Decriptare\nAlege operatia (1 sau 2): ";
    cin >> operatie;
    if (operatie != 1 && operatie != 2) {
        cout << "Opțiune invalida!\n";
        return;
    }

    cout << "Introduce cheia k1 (1 - 30): ";
    cin >> k1;
    if (k1 < 1 || k1 > 30) {
        cout << "Eroare: Cheia k1 trebuie sa fie intre 1 si 30!\n";
        return;
    }

    cin.ignore();
    cout << "Introduce textul/criptograma: ";
    getline(cin, text_str);

    if (!curataText(text_str, textCurat)) return;

    for (const string& litera : textCurat) {
        int pos = gasestePozitieBaza(litera);
        int posNoua;

        if (operatie == 1) {
            posNoua = (pos + k1) % 31;
        } else {
            posNoua = (pos - k1 + 31) % 31;
        }

        rezultat.push_back(ALFABET_BAZA[posNoua]);
    }

    cout << "\n-----------------------------------\n";
    cout << "Text procesat: ";
    for (const string& s : textCurat) cout << s;
    cout << "\nRezultat:      ";
    for (const string& s : rezultat) cout << s;
    cout << "\n-----------------------------------\n";
}

void proceseazaCezarCuPermutare() {
    int operatie, k1;
    string k2_str, text_str;
    vector<string> A_permutat;
    vector<string> textCurat, rezultat;

    cout << "\n--- CIFRUL CEZAR CU PERMUTARE (DOUA CHEI) ---\n";
    cout << "1. Criptare\n2. Decriptare\nAlege operatia (1 sau 2): ";
    cin >> operatie;
    if (operatie != 1 && operatie != 2) {
        cout << "Opțiune invalida!\n";
        return;
    }

    cout << "Introduce cheia k1 (1 - 30): ";
    cin >> k1;
    if (k1 < 1 || k1 > 30) {
        cout << "Eroare: Cheia k1 trebuie sa fie intre 1 si 30!\n";
        return;
    }

    cin.ignore();
    cout << "Introduce cheia k2 (minim 7 litere): ";
    getline(cin, k2_str);

    vector<string> k2_simboluri = extrageCaractereUTF8(k2_str);
    vector<string> k2_valide;

    for (const string& s : k2_simboluri) {
        if (s == " " || s == "\t") continue;
        int pos = gasestePozitieBaza(s);
        if (pos != -1) {
            k2_valide.push_back(ALFABET_BAZA[pos]);
        } else {
            cout << "Eroare: Cheia k2 contine caractere invalide ('" << s << "')!\n";
            return;
        }
    }

    if (k2_valide.size() < 7) {
        cout << "Eroare: Cheia k2 trebuie sa aiba cel putin 7 litere!\n";
        return;
    }

    // Construim alfabetul permutat
    for (const string& litera : k2_valide) {
        if (gasestePozitieInVector(A_permutat, litera) == -1) {
            A_permutat.push_back(litera);
        }
    }
    for (const string& litera : ALFABET_BAZA) {
        if (gasestePozitieInVector(A_permutat, litera) == -1) {
            A_permutat.push_back(litera);
        }
    }

    cout << "Alfabetul permutat este: ";
    for (const string& s : A_permutat) cout << s;
    cout << "\n";

    cout << "Introduce textul/criptograma: ";
    getline(cin, text_str);

    if (!curataText(text_str, textCurat)) return;

    for (const string& litera : textCurat) {
        int pos = gasestePozitieInVector(A_permutat, litera);
        int posNoua;

        if (operatie == 1) {
            posNoua = (pos + k1) % 31;
        } else {
            posNoua = (pos - k1 + 31) % 31;
        }

        rezultat.push_back(A_permutat[posNoua]);
    }

    cout << "\n-----------------------------------\n";
    cout << "Text procesat: ";
    for (const string& s : textCurat) cout << s;
    cout << "\nRezultat:      ";
    for (const string& s : rezultat) cout << s;
    cout << "\n-----------------------------------\n";
}

int main() {
    int optiuneMeniu;

    do {
        cout << "\n================ MENIU PRINCIPAL ================\n";
        cout << "1. Criptare / Decriptare cu O CHEIE (Cezar Simplu)\n";
        cout << "2. Criptare / Decriptare cu DOUA CHEI (Cezar cu Permutare)\n";
        cout << "3. Iesire din program\n";
        cout << "Alege opțiunea (1-3): ";
        cin >> optiuneMeniu;

        switch (optiuneMeniu) {
            case 1:
                proceseazaCezarSimplu();
                break;
            case 2:
                proceseazaCezarCuPermutare();
                break;
            case 3:
                cout << "Programul s-a incheiat. La revedere!\n";
                break;
            default:
                cout << "Opțiune invalida! Te rog sa alegi 1, 2 sau 3.\n";
                break;
        }
    } while (optiuneMeniu != 3);

    return 0;
}