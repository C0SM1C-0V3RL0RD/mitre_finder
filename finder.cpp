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
    string chain_phases;
    string data_sources;
};

string clean(const string& text) {
    size_t first = text.find_first_not_of(" \t\n\r\"");
    if (first == string::npos) return "";
    size_t last = text.find_last_not_of(" \t\n\r\"");
    return text.substr(first, last - first + 1);
}

vector<MitreTechnique> loadCSV(const string& fileName) {
    vector<MitreTechnique> techniques;
    ifstream file(fileName);
    string line;

    if (!file.is_open()) {
        cerr << "File could not be opened!" << endl;
        return techniques;
    }

    getline(file, line);
    while (getline(file, line)) {
        string name, id, url, phase, description, platforms, chain_phases, data_sources;

        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, id, ',');
        getline(ss, url, ',');
        getline(ss, phase, ',');
        getline(ss, description, ',');
        getline(ss, platforms, ',');
        getline(ss, chain_phases, ',');
        getline(ss, data_sources, ',');

        techniques.push_back({
            clean(id),
            clean(name),
            clean(description),
            clean(phase),
            clean(url),
            clean(platforms),
            clean(chain_phases),
            clean(data_sources)
            });
    }
    file.close();
    return techniques;
}

void searchTechnique(const vector<MitreTechnique>& techniques, const string& search) {
    string search_lower = clean(search);
    transform(search_lower.begin(), search_lower.end(), search_lower.begin(), ::tolower);

    for (const auto& technique : techniques) {
        string id = technique.id, name = technique.name;
        transform(id.begin(), id.end(), id.begin(), ::tolower);
        transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (id == search_lower || name == search_lower) {
            cout << "Technique ID: " << technique.id << endl;
            cout << "Name: " << technique.name << endl;
            cout << "Phase: " << technique.phase << endl;
            cout << "Description: " << technique.description << endl;
            cout << "URL: " << technique.url << endl;
            cout << "Platforms: " << technique.platforms << endl;
            cout << "Chain Phases: " << technique.chain_phases << endl;
            cout << "Data Sources: " << technique.data_sources << endl;
            return;
        }
    }
    cout << "No technique found with this ID." << endl;
}

int main() {
    string fileName = "enterprise-attack.csv";
    vector<MitreTechnique> techniques = loadCSV(fileName);

    if (techniques.empty()) {
        cerr << "CSV file could not be loaded!" << endl;
        return 1;
    }

    string search;
    cout << "Enter MITRE Technique ID: ";
    getline(cin, search);

    searchTechnique(techniques, search);

    return 0;
}
