#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Instruktor{
    char naziv[50];
    char zvanje[30];
    int godineIskustva;
    int Ocjena;
};

struct Ucenik {
    char imePrezime[50];
    string emailAdresa;
    int godiste;
};

struct Kurs{
    string nazivKursa;
    string oblast;
    bool freeCertifikat;
    Instruktor instruktor;
    vector<Ucenik> uceniciKursa;
};


double prosjek(const vector<Instruktor>& instruktori){
    double suma = 0.0;
    for (const Instruktor& temp : instruktori) {
        suma += temp.Ocjena;
    }
    return suma / instruktori.size();
}

void unesiOblast(vector<string*> oblasti){
    string* noviString = new string;
    cout << "Unesite naziv oblasti: ";
    cin >> *noviString;
    oblasti.push_back(noviString);
}

void unesiInstruktora(vector<Instruktor>& instruktori){
    Instruktor temp;
    cin.ignore();
    cout << "Unesi naziv instruktora: ";
    cin.getline(temp.naziv, 50);
    cout << "Unesi zvanje instruktora: ";
    cin.getline(temp.zvanje, 30);
    cout << "Unesite godine iskustva: ";
    cin >> temp.godineIskustva;
    cout << "Unesite ocjenu instruktora (1-5): ";
    cin >> temp.Ocjena;

    instruktori.push_back(temp);

    ofstream unesiInstruktora("instruktori.txt", ios::app);
    if(unesiInstruktora.is_open()) {
        unesiInstruktora << temp.naziv << " " << temp.zvanje << " " << temp.godineIskustva << " " << temp.Ocjena
                         << endl;
        unesiInstruktora.close();
    }else {
        cout << "Nije moguce otvoriti datoteku." << endl;
    }
}

void unesiUcenika(vector<Ucenik>& ucenici){
    Ucenik temp;
    cin.ignore();
    cout << "Unesite ime i prezime ucenika: ";
    cin.getline(temp.imePrezime, 50); // char
    cout << "Unesite email ucenika: ";
    getline(cin, temp.emailAdresa); // string
    cout << "Godiste ucenika: ";
    cin >> temp.godiste; // int-float-double

    ucenici.push_back(temp);

    ofstream unesiUcenika("ucenici.txt", ios::app);
    if(unesiUcenika.is_open()){
        unesiUcenika << temp.imePrezime << " " << temp.emailAdresa << " " << temp.godiste << endl;
        unesiUcenika.close();
    } else {
        cerr << "Nije moguce otvoriti datoteku." << endl;
    }
}

void unesiKurs(vector<Kurs>& kursevi, vector<Instruktor>& instruktori){
    Kurs temp;
    cin.ignore();
    cout << "Unesi naziv kursa: ";
    getline(cin, temp.nazivKursa);
    cout << "Da li se kurs placa? (1-Da, 0-Ne): ";
    cin >> temp.freeCertifikat;
    cout << "Dostupni instruktori: \n";
    for(const Instruktor& instruktor : instruktori){
        cout << instruktor.naziv << endl;
    }
    cin.ignore();
    cout << "Unesite naziv instruktora kursa: ";
    cin >> temp.instruktor.naziv;

    kursevi.push_back(temp);

    ofstream unosKurseva("kursevi.txt", ios::app);
    if(unosKurseva.is_open()){
        unosKurseva << temp.nazivKursa << " " << temp.oblast << " "
                       << temp.freeCertifikat << " " << temp.instruktor.naziv << endl;
        unosKurseva.close();
    } else {
        cerr << "Nije moguce otvoriti datoteku." << endl;
    }
}

void ispisInstruktora(vector<Kurs>& kursevi){
    cout << "Dostupni kursevi: " << endl;
    for (const Kurs& kurs : kursevi) {
        cout << kurs.nazivKursa << endl;
    }
    cin.ignore();
    string odabraniKurs;
    cout << "Unesi kurs za pretragu: ";
    getline(cin, odabraniKurs);

    bool kursPronadjen = false;
    for (const Kurs& kurs : kursevi){
        if(kurs.nazivKursa == odabraniKurs){
            cout << "instruktor kursa " << kurs.instruktor.naziv << " " << kurs.instruktor.zvanje << " " << kurs.instruktor.godineIskustva << endl;
            kursPronadjen = true;
            break;
        }
    }
    if(!kursPronadjen) {
        cout << "Kurs ne postoji" << endl;
    }
}

void upisiUcenikaNaKurs(vector<Kurs>& kursevi, vector<Ucenik>& ucenici){
    ifstream ucitajUcenike("ucenici.txt");
    if (ucitajUcenike.is_open()){
        Ucenik tempUcenik;
        while(ucitajUcenike >> tempUcenik.imePrezime >> tempUcenik.emailAdresa >> tempUcenik.godiste){
            ucenici.push_back(tempUcenik);
        }
        ucitajUcenike.close();
        cout << "Ime i prezimena svih ucenika: " << endl;
        for (int i = 0; i < ucenici.size(); ++i) {
            cout << i+1 << ". " << ucenici[i].imePrezime << endl;
        }
    } else {
        cerr << "Nije moguce otvoriti datoteku.\n";
    }

    ifstream ucitajKurseve("kursevi.txt");
    if (ucitajKurseve.is_open()){
        Kurs tempkurs;
        while(ucitajKurseve >> tempkurs.nazivKursa >> tempkurs.freeCertifikat >> tempkurs.instruktor.naziv){
            kursevi.push_back(tempkurs);
        }
        ucitajKurseve.close();
        cout << "Dostupni kursevi: ";
        for (int i = 0; i < kursevi.size(); ++i) {
            cout << i+1 << ". " << kursevi[i].nazivKursa << endl;
        }
    } else {
        cerr << "Nije moguce otvoriti datoteku\n";
    }

    int redniBrojUcenika;
    cout << "Unesi redni broj ucenika: ";
    cin >> redniBrojUcenika;

    if(redniBrojUcenika > 0 && redniBrojUcenika <= ucenici.size()){

        int redniBrojKursa;
        cout << "Unesite redni broj kursa: ";
        cin >> redniBrojKursa;

        if(redniBrojKursa > 0 && redniBrojKursa <= kursevi.size()){
            kursevi[redniBrojKursa - 1].uceniciKursa.push_back(ucenici[redniBrojUcenika-1]);


            ofstream ucitajKurseve("kursevi.txt");
            if (ucitajKurseve.is_open()){
                for (const Kurs& kurs : kursevi){
                    ucitajKurseve << kurs.nazivKursa << " " << kurs.freeCertifikat << " " << kurs.instruktor.naziv << endl;

                }
                ucitajKurseve.close();
            } else {
                cout << "Nije moguce otvoriti datoteku" << endl;
            }
        }
    }
}

int main(){

    vector<Instruktor> instruktori;
    vector<Ucenik> ucenici;
    vector<Kurs> kursevi;
    vector<string*> oblasti;


    int izbor;
    do {
        cout << "\n----- MENI -----" << endl;
        cout << "1. Unesi Oblast" << endl;
        cout << "2. Unesi Instruktora" << endl;
        cout << "3. Unesi Ucenika" << endl;
        cout << "4. Unesi Kurs" << endl;
        cout << "5. Ispisi Instruktora" << endl;
        cout << "6. Upis Ucenika na Kurs" << endl;
        cout << "7. Izracunaj prosjek ocjena instruktora" << endl;
        cout << "8. Izlaz" << endl;
        cout << "Izaberite opciju: ";
        cin >> izbor;

        switch (izbor) {
            case 1:
                unesiOblast(oblasti);
                break;
            case 2:
                unesiInstruktora(instruktori);
                break;
            case 3:
                unesiUcenika(ucenici);
                break;
            case 4:
                unesiKurs(kursevi, instruktori);
                break;
            case 5:
                ispisInstruktora(kursevi);
                break;
            case 6:
                upisiUcenikaNaKurs(kursevi, ucenici);
                break;
            case 7:
                cout << "Prosjek ocjena instruktora: " << prosjek(instruktori) << endl;
                break;
            case 8:
                cout << "Izlaz iz programa." << endl;
                break;
            default:
                cout << "Nepoznata opcija. Molimo vas da unesete ponovo." << endl;
        }
    } while (izbor != 8);


    return 0;
}