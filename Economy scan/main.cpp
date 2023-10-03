// main.cpp : This program made by redpoint03

#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace fs = std::filesystem;

long long int totallock = 0;
long long int wlmiktar, dlmiktar, bglmiktar = 0;
long long int totalgems = 0;
bool detayli = false;
std::string cinicin;


int main()
{
    std::cout << "This program is made by redpoint03." << std::endl; 
    std::cout << "At the end of scan, you will get total locks and gems at the players." << std::endl;
    system("color e");
    std::cout << "Press any key to start. (PRESS 2 FOR DETAILED MODE)" << std::endl;
    std::cin >> cinicin;
    if (cinicin == "2") detayli = true;
    system("cls");
    system("color a");
    std::cout << "Scanning players...\n" << std::endl;

    const std::string folderPath = "players/";
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::ifstream file(entry.path());

            if (!file.is_open()) {
                std::cerr << "Unable to open file: " << entry.path() << std::endl;
                continue;
            }

            json jsonData;
            file >> jsonData;
            file.close();
            int anlikwl, anlikdl, anlikbgl, anlikgems = 0;

            if (jsonData.contains("cli")) {
                bool clistValue = jsonData["cli"];
                if (clistValue) continue;
            }
            if (jsonData.contains("gems")) {
                int gemsValue = jsonData["gems"];
                totalgems += gemsValue;
                anlikgems = gemsValue;
            }

            if (jsonData.contains("inv") && jsonData["inv"].is_array()) {
                for (const auto& item : jsonData["inv"]) {
                    if (item.contains("i") && item.contains("c")) {
                        int iValue = item["i"];
                        int cValue = item["c"];

                        if (iValue == 242 || iValue == 1796 || iValue == 7188) {
                            if (iValue == 242) totallock += cValue, wlmiktar += cValue, anlikwl = cValue;
                            if (iValue == 1796) totallock += cValue * 100, dlmiktar += cValue, anlikdl = cValue;
                            if (iValue == 7188) totallock += cValue * 10000, bglmiktar += cValue, anlikbgl = cValue;
                            continue;
                        }
                    }
                }
            }
            else {
                std::cerr << " Couldn't find inv list: " << entry.path() << std::endl;
            }
            if (detayli) std::cout << "Player " << entry.path().filename() << " scanned. WLS: " << anlikwl << ", DLS: " << anlikdl << ", BGLS: " << anlikbgl << ", GEMS: " << anlikgems << std::endl;
            else std::cout << "Player " << entry.path().filename() << " scanned!" << std::endl;
        }
    }
    std::cout << "\nScanning worlds...\n" << std::endl;
    const std::string folderPath2 = "worlds/";
    for (const auto& entry : fs::directory_iterator(folderPath2)) {
        if (entry.is_regular_file()) {
            std::ifstream file(entry.path());

            if (!file.is_open()) {
                std::cerr << "Unable to open file: " << entry.path() << std::endl;
                continue;
            }

            json jsonData;
            file >> jsonData;
            file.close();
            int anlikwl = 0, anlikdl = 0, anlikbgl = 0, anlikgems = 0;

            if (jsonData.contains("drop") && jsonData["drop"].is_array()) {
                for (const auto& item : jsonData["drop"]) {
                    if (item.contains("i") && item.contains("c")) {
                        int iValue = item["i"];
                        int cValue = item["c"];

                        if (iValue == 242 || iValue == 1796 || iValue == 7188 || iValue == 112) {
                            if (iValue == 242) totallock += cValue, wlmiktar += cValue, anlikwl += cValue;
                            if (iValue == 1796) totallock += cValue * 100, dlmiktar += cValue, anlikdl += cValue;
                            if (iValue == 7188) totallock += cValue * 10000, bglmiktar += cValue, anlikbgl += cValue;
                            if (iValue == 112) totalgems += cValue, anlikgems += cValue;
                            continue;
                        }
                        
                    }
                }
            }
            else {
                std::cerr << "Couldn't find drop list: " << entry.path() << std::endl;
            }
            if (detayli) std::cout << "World " << entry.path().filename() << " scanned. WLS: " << anlikwl << ", DLS: " << anlikdl << ", BGLS: " << anlikbgl << ", GEMS: " << anlikgems << std::endl;
            else std::cout << "World " << entry.path().filename() << " scanned!" << std::endl;
        }
    }


    if (!detayli) system("cls");
    system("color e");
    std::cout << "\nEconomy scan is successfully completed. Results:\n\n\n" << std::endl;
    std::cout << "Total WL: " << wlmiktar << "\n" << std::endl;
    std::cout << "Total DL: " << dlmiktar << "\n" << std::endl;
    std::cout << "Total BGL: " << bglmiktar << "\n" << std::endl;
    std::cout << "Total lock: " << totallock << "\n" << std::endl;
    std::cout << "Total gems: " << totalgems << "\n" << std::endl;
    system("pause");
}
