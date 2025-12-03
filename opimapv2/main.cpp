#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>

std::string toLower(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return r;
}

int main() {
    std::unordered_map<std::string, std::pair<double, double>> cities = {
        // Київ
        {"київ", {50.4501, 30.5234}},
        {"киев", {50.4501, 30.5234}},
        // Львів
        {"львів", {49.8397, 24.0297}},
        {"львов", {49.8397, 24.0297}},
        // Одеса
        {"одеса", {46.4775, 30.7326}},
        {"одесса", {46.4775, 30.7326}},
        // Харків
        {"харків", {49.9935, 36.2304}},
        {"харьков", {49.9935, 36.2304}},
        // Дніпро
        {"дніпро", {48.4647, 35.0462}},
        {"днепр", {48.4647, 35.0462}},
        // Запоріжжя
        {"запоріжжя", {47.8388, 35.1396}},
        {"запорожье", {47.8388, 35.1396}},
        // Миколаїв
        {"миколаїв", {46.9750, 31.9946}},
        {"николаев", {46.9750, 31.9946}},
        // Херсон
        {"херсон", {46.6354, 32.6169}},
        // Чернігів
        {"чернігів", {51.4982, 31.2893}},
        {"чернигов", {51.4982, 31.2893}},
        // Полтава
        {"полтава", {49.5883, 34.5514}},
        // Черкаси
        {"черкаси", {49.4444, 32.0598}},
        {"черкассы", {49.4444, 32.0598}},
        // Житомир
        {"житомир", {50.2547, 28.6587}},
        // Рівне
        {"рівне", {50.6199, 26.2516}},
        {"ровно", {50.6199, 26.2516}},
        // Івано-Франківськ
        {"івано-франківськ", {48.9226, 24.7111}},
        {"ивано-франковск", {48.9226, 24.7111}},
        // Тернопіль
        {"тернопіль", {49.5535, 25.5948}},
        {"тернополь", {49.5535, 25.5948}},
        // Луцьк
        {"луцьк", {50.7472, 25.3254}},
        {"луцк", {50.7472, 25.3254}},
        // Ужгород
        {"ужгород", {48.6208, 22.2879}},
        // Суми
        {"суми", {50.9077, 34.7981}},
        {"сумы", {50.9077, 34.7981}},
        // Вінниця
        {"вінниця", {49.2328, 28.4810}},
        {"винница", {49.2328, 28.4810}},
        // Кропивницький (Кіровоград)
        {"кропивницький", {48.5079, 32.2623}},
        {"кировоград", {48.5079, 32.2623}}
    };

    std::cout << "Введiть назву мiста України: ";
    std::string userCity;
    std::getline(std::cin, userCity);

    std::string key = toLower(userCity);

    if (cities.find(key) == cities.end()) {
        std::cerr << "Мiсто не знайдено у базi.\n";
        std::cerr << "Приклади: Київ, Львів, Одеса, Харків, Дніпро, Запоріжжя...\n";
        return 1;
    }

    auto coords = cities[key];

    std::ofstream out("map.html");
    if (!out) {
        std::cerr << "Помилка створення map.html\n";
        return 1;
    }

    out <<
"<!DOCTYPE html>\n"
"<html lang=\"uk\">\n"
"<head>\n"
"    <meta charset=\"UTF-8\">\n"
"    <title>Мапа мiста " << userCity << "</title>\n"
"    <link rel=\"stylesheet\" href=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.css\" />\n"
"    <style>\n"
"        body { margin: 0; padding: 0; }\n"
"        #map { height: 100vh; width: 100vw; }\n"
"    </style>\n"
"</head>\n"
"<body>\n"
"    <div id=\"map\"></div>\n"
"\n"
"    <script src=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.js\"></script>\n"
"    <script>\n"
"        var map = L.map('map').setView([" << coords.first << ", " << coords.second << "], 12);\n"
"\n"
"        L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {\n"
"            maxZoom: 18,\n"
"        }).addTo(map);\n"
"\n"
"        L.marker([" << coords.first << ", " << coords.second << "])\n"
"            .addTo(map)\n"
"            .bindPopup('" << userCity << "')\n"
"            .openPopup();\n"
"    </script>\n"
"</body>\n"
"</html>\n";

    out.close();

    std::cout << "Готово! Вiдкрийте map.html у браузерi.\n";
    return 0;
}
