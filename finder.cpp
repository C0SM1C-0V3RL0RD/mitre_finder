#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct MitreTeknik {
    string kimlik;
    string ad;
    string aciklama;
    string asama;
    string url;
    string platformlar;
    string zincir_asamalari;
    string veri_kaynaklari;
};

string temizle(const string& metin) {
    size_t ilk = metin.find_first_not_of(" \t\n\r\"");
    if (ilk == string::npos) return "";
    size_t son = metin.find_last_not_of(" \t\n\r\"");
    return metin.substr(ilk, son - ilk + 1);
}

vector<MitreTeknik> csvYukle(const string& dosyaAdi) {
    vector<MitreTeknik> teknikler;
    ifstream dosya(dosyaAdi);
    string satir;

    if (!dosya.is_open()) {
        cerr << "Dosya acilamadi!" << endl;
        return teknikler;
    }

    getline(dosya, satir);
    while (getline(dosya, satir)) {
        string ad, kimlik, url, asama, aciklama, platformlar, zincir_asamalari, veri_kaynaklari;

        stringstream ss(satir);
        getline(ss, ad, ',');
        getline(ss, kimlik, ',');
        getline(ss, url, ',');
        getline(ss, asama, ',');
        getline(ss, aciklama, ',');
        getline(ss, platformlar, ',');
        getline(ss, zincir_asamalari, ',');
        getline(ss, veri_kaynaklari, ',');

        teknikler.push_back({
            temizle(kimlik),
            temizle(ad),
            temizle(aciklama),
            temizle(asama),
            temizle(url),
            temizle(platformlar),
            temizle(zincir_asamalari),
            temizle(veri_kaynaklari)
            });
    }
    dosya.close();
    return teknikler;
}

void teknikAra(const vector<MitreTeknik>& teknikler, const string& arama) {
    string arama_kucuk = temizle(arama);
    transform(arama_kucuk.begin(), arama_kucuk.end(), arama_kucuk.begin(), ::tolower);

    for (const auto& teknik : teknikler) {
        string kimlik = teknik.kimlik, ad = teknik.ad;
        transform(kimlik.begin(), kimlik.end(), kimlik.begin(), ::tolower);
        transform(ad.begin(), ad.end(), ad.begin(), ::tolower);

        if (kimlik == arama_kucuk || ad == arama_kucuk) {
            cout << "Teknik Kimligi: " << teknik.kimlik << endl;
            cout << "Ad: " << teknik.ad << endl;
            cout << "Asama: " << teknik.asama << endl;
            cout << "Aciklama: " << teknik.aciklama << endl;
            cout << "URL: " << teknik.url << endl;
            cout << "Platformlar: " << teknik.platformlar << endl;
            cout << "Zincir Asamalari: " << teknik.zincir_asamalari << endl;
            cout << "Veri Kaynaklari: " << teknik.veri_kaynaklari << endl;
            return;
        }
    }
    cout << "Bu ID ile eslesen teknik bulunamadi." << endl;
}

int main() {
    string dosyaAdi = "enterprise-attack.csv";
    vector<MitreTeknik> teknikler = csvYukle(dosyaAdi);

    if (teknikler.empty()) {
        cerr << "CSV dosyasi yuklenemedi!" << endl;
        return 1;
    }

    string arama;
    cout << "MITRE Teknik Kimligi girin: ";
    getline(cin, arama);

    teknikAra(teknikler, arama);

    return 0;
}
