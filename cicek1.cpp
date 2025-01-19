#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <conio.h>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

struct Cicek {
    string isim;
    string tur;
    double fiyat;
};

Cicek cicek;
void dosyaYaz();
void dosyaListele();
void dosyaAra();
void dosyaSil();
void dosyaGuncelle();

int main() {
    char secim;

    do {
        cout << "-------CICEKCI OTOMASYONU-----" << endl;
        cout << "1-CICEK BILGILERI EKLE" << endl;
        cout << "2-CICEKLERI LISTELE" << endl;
        cout << "3-CICEK ARA" << endl;
        cout << "4-CICEK SIL" << endl;
        cout << "5-CICEK GUNCELLE" << endl;
        cout << "0-CIKIS" << endl;
        cout << "Bir secim yapiniz: ";
        cin >> secim;

        switch (secim) {
            case '1':
                dosyaYaz();
                break;
            case '2':
                dosyaListele();
                break;
            case '3':
                dosyaAra();
                break;
            case '4':
                dosyaSil();
                break;
            case '5':
                dosyaGuncelle();
                break;
            case '0':
                cout << "Programdan cikiliyor..." << endl;
                break;
            default:
                cout << "Gecersiz secim!" << endl;
        }
    } while (secim != '0');

    return 0;
}

void dosyaYaz() {
    
    cout << "Cicek ismi: ";
    cin >> cicek.isim;
    cout << "Cicek turu: ";
    cin >> cicek.tur;
    cout << "Cicek fiyati: ";
    cin >> cicek.fiyat;

    ofstream dosya("cicekler.txt", ios::binary | ios::app); 
    if (dosya.is_open()) {
        dosya << cicek.isim << "," << cicek.tur << "," << cicek.fiyat << endl;
        dosya.close();
        cout << "Cicek kaydedildi!" << endl;
}
}
void dosyaListele() {
    ifstream dosya("cicekler.txt");
    string satir;

    if (dosya.is_open()) {
        cout << "Cicekler Listesi:" << endl;
        while (getline(dosya, satir)) {
            cout << satir << endl;
        }
        dosya.close();
    } 
}

void dosyaAra() {
    string dosyaAdi = "cicekler.txt";
    string arananIsim;
    cout << "Aranacak Isim: "; cin >> arananIsim;

    ifstream dosya("cicekler.txt");
    if (dosya.is_open()) {
        string satir;
        bool bulunduMu = false;
        while (getline(dosya, satir)) {
            size_t ilkVirgul = satir.find(",");
            string isim = satir.substr(0, ilkVirgul);
            if (isim == arananIsim) {
                cout << "Bulunan kayit: " << satir << endl;
                bulunduMu = true;
                break;
            }
        }
        dosya.close();
        if (!bulunduMu) {
            cout << "Kayit bulunamadi!" << endl;
        }
    } 
}
void dosyaSil() {
    string silinecekIsim;
    cout << "Silinecek cicek ismini giriniz: ";
    cin >> silinecekIsim;

    ifstream dosya("cicekler.txt");
    ofstream geciciDosya("gecici.txt"); 

    string satir;
    bool silindiMi = false;

    if (dosya.is_open() && geciciDosya.is_open()) {
        while (getline(dosya, satir)) {
            stringstream ss(satir);
            string isim;
            getline(ss, isim, ',');

            if (isim != silinecekIsim) {
                geciciDosya << satir << endl; 
            } else {
                silindiMi = true;
            }
        }
        dosya.close();
        geciciDosya.close();

        if (silindiMi) {
            remove("cicekler.txt");
            rename("gecici.txt", "cicekler.txt");
            cout << "Cicek silindi!" << endl;
        } else {
            cout << "Cicek bulunamadi!" << endl;
        }
    } 
}

void dosyaGuncelle() {
    string guncellenecekIsim;
    cout << "Guncellenecek cicek ismini giriniz: ";
    cin >> guncellenecekIsim;

    ifstream dosya("cicekler.txt"); 
    ofstream geciciDosya("gecici.txt");

    string satir;
    bool guncellendiMi = false;

    if (dosya.is_open() && geciciDosya.is_open()) {
        while (getline(dosya, satir)) {
            stringstream ss(satir);
            string isim, tur;
            double fiyat;

            getline(ss, isim, ',');
            getline(ss, tur, ',');
            ss >> fiyat;

            if (isim == guncellenecekIsim) {
                
                Cicek yeniCicek;
                yeniCicek.isim = isim;
                cout << "Yeni cicek Turu: ";
                cin >> yeniCicek.tur;
                cout << "Yeni cicek fiyati: ";
                cin >> yeniCicek.fiyat;

                geciciDosya << yeniCicek.isim << "," << yeniCicek.tur << "," << yeniCicek.fiyat << endl;
                guncellendiMi = true;
            } else {
                
                geciciDosya << satir << endl;
            }
        }
        dosya.close();
        geciciDosya.close();

        if (guncellendiMi) {
           
            remove("cicekler.txt");
            rename("gecici.txt", "cicekler.txt");
            cout << "cicek guncellendi!" << endl;
        } else {
            
            remove("gecici.txt");
            cout << "cicek bulunamadi!" << endl;
        }
    }
}


