#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct MitreTechnique {
    string id;
    string name;
    string description;
    string phase;
    string url;
    string platforms;
    string kill_chain_phases;
    string data_sources;
};


string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\"");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r\"");
    return str.substr(first, last - first + 1);
}

vector<MitreTechnique> loadCSV(const string& filename) {
    vector<MitreTechnique> techniques;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Dosya acilamadi!" << endl;
        return techniques;
    }

    getline(file, line); 
    while (getline(file, line)) {
        string name, id, url, phase, description, platforms, kill_chain_phases, data_sources;

        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, id, ',');
        getline(ss, url, ',');
        getline(ss, phase, ',');
        getline(ss, description, ',');
        getline(ss, platforms, ',');
        getline(ss, kill_chain_phases, ',');
        getline(ss, data_sources, ',');

        techniques.push_back({
            trim(id),
            trim(name),
            trim(description),
            trim(phase),
            trim(url),
            trim(platforms),
            trim(kill_chain_phases),
            trim(data_sources)
            });
    }
    file.close();
    return techniques;
}

void searchTechnique(const vector<MitreTechnique>& techniques, const string& query) {
    string query_lower = trim(query);
    transform(query_lower.begin(), query_lower.end(), query_lower.begin(), ::tolower);

    for (const auto& tech : techniques) {
        string id = tech.id, name = tech.name;
        transform(id.begin(), id.end(), id.begin(), ::tolower);
        transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (id == query_lower || name == query_lower) {
            cout << "Technique ID: " << tech.id << endl;
            cout << "Name: " << tech.name << endl;
            cout << "Phase: " << tech.phase << endl;
            cout << "Description: " << tech.description << endl;
            cout << "URL: " << tech.url << endl;
            cout << "Platforms: " << tech.platforms << endl;
            cout << "Kill Chain Phases: " << tech.kill_chain_phases << endl;
            cout << "Data Sources: " << tech.data_sources << endl;
            return;
        }
    }
    cout << "Bu ID veya isimle eslesen bir teknik bulunamadi." << endl;
}

int main() {
    string filename = "enterprise-attack.csv";
    vector<MitreTechnique> techniques = loadCSV(filename);

    if (techniques.empty()) {
        cerr << "CSV dosyasi yuklenemedi veya bos!" << endl;
        return 1;
    }

    string query;
    cout << "MITRE Technique ID veya ismi girin: ";
    getline(cin, query);

    searchTechnique(techniques, query);

    return 0;
}
