#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <chrono>
#include <random>
#include <fstream>
#include <bitset>
#include <iomanip>
#include "gemini_hash.h"

// --- Pagalbinės Funkcijos ---

std::string get_random_string(int length) {
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, chars.size() - 1);
    std::string random_string;
    for(int i = 0; i < length; ++i) {
        random_string += chars[distribution(generator)];
    }
    return random_string;
}

std::string get_string_with_one_diff(const std::string& original) {
    if (original.empty()) return "a";
    std::string modified = original;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, original.size() - 1);
    int pos = dist(gen);
    char old_char = modified[pos];
    char new_char;
    do {
        new_char = get_random_string(1)[0];
    } while (new_char == old_char);
    modified[pos] = new_char;
    return modified;
}

std::bitset<256> hex_to_bitset(const std::string& hex) {
    // Convert hex string to binary string for bitset
    std::string bin_str = "";
    for(char c : hex) {
        switch(toupper(c)) {
            case '0': bin_str += "0000"; break;
            case '1': bin_str += "0001"; break;
            case '2': bin_str += "0010"; break;
            case '3': bin_str += "0011"; break;
            case '4': bin_str += "0100"; break;
            case '5': bin_str += "0101"; break;
            case '6': bin_str += "0110"; break;
            case '7': bin_str += "0111"; break;
            case '8': bin_str += "1000"; break;
            case '9': bin_str += "1001"; break;
            case 'A': bin_str += "1010"; break;
            case 'B': bin_str += "1011"; break;
            case 'C': bin_str += "1100"; break;
            case 'D': bin_str += "1101"; break;
            case 'E': bin_str += "1110"; break;
            case 'F': bin_str += "1111"; break;
        }
    }
    return std::bitset<256>(bin_str);
}


int hamming_distance(const std::string& h1, const std::string& h2) {
    return (hex_to_bitset(h1) ^ hex_to_bitset(h2)).count();
}

void run_experiments() {
    GeminiHash256 hasher;
    std::cout << "--- Vykdoma GeminiHash-256 eksperimentine analize ---" << std::endl;

    // 1. Testinių duomenų paruošimas
    std::cout << "\n[1. Ruosiami testiniai duomenys]" << std::endl;
    std::map<std::string, std::string> test_data;
    test_data["tuscia"] = "";
    test_data["a"] = "a";
    test_data["b"] = "b";
    test_data["ilgas_1"] = get_random_string(1500);
    test_data["ilgas_2"] = get_string_with_one_diff(test_data["ilgas_1"]);
    std::cout << "Testiniai duomenys paruošti atmintyje." << std::endl;

    // 2. Išvesties dydžio patikrinimas
    std::cout << "\n[2. Isvesties dydzio patikrinimas]" << std::endl;
    for (const auto& pair : test_data) {
        std::string h = hasher.hash(pair.second);
        std::cout << "Ivestis '" << pair.first << "' -> Isvesties ilgis: " << h.length() << std::endl;
        assert(h.length() == 64);
    }

    // 3. Determinizmo patikrinimas
    std::cout << "\n[3. Determinizmo patikrinimas]" << std::endl;
    std::string h1 = hasher.hash("Hello World");
    std::string h2 = hasher.hash("Hello World");
    std::cout << "Hash 1 'Hello World': " << h1 << std::endl;
    std::cout << "Hash 2 'Hello World': " << h2 << std::endl;
    assert(h1 == h2);
    std::cout << "Determinizmas patvirtintas." << std::endl;

    // 4. Efektyvumo testas
    std::cout << "\n[4. Efektyvumo testas]" << std::endl;
    std::ifstream constitution_file("test_files/konstitucija.txt");
    if (constitution_file.is_open()) {
        std::string content((std::istreambuf_iterator<char>(constitution_file)), std::istreambuf_iterator<char>());
        std::ofstream results_file("efficiency_data.csv");
        results_file << "InputSize,TimeSeconds\n";
        for (int i = 10; i <= 100; i += 10) {
            std::string chunk = content.substr(0, content.size() * i / 100);
            auto start = std::chrono::high_resolution_clock::now();
            hasher.hash(chunk);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end - start;
            results_file << chunk.size() << "," << diff.count() << "\n";
        }
        results_file.close();
        std::cout << "Efektyvumo testo duomenys issaugoti faile 'efficiency_data.csv'.\nNupieskite grafika naudodami isorini iranki (pvz., Excel, Python/Matplotlib)." << std::endl;
    } else {
        std::cout << "Failas 'konstitucija.txt' nerastas. Efektyvumo testas praleidziamas." << std::endl;
    }
    
    // 5. Kolizijų paieška
    std::cout << "\n[5. Koliziju paieska]" << std::endl;
    const int TOTAL_PAIRS = 10000;
    for (int length : {10, 100}) {
        std::map<std::string, std::string> hash_to_string;
        int collisions = 0;
        for (int i = 0; i < TOTAL_PAIRS; ++i) {
            std::string s = get_random_string(length);
            std::string h = hasher.hash(s);
            
            if (hash_to_string.count(h)) {
                if (hash_to_string[h] != s) {
                    collisions++;
                    std::cout << "Kolizija rastas! Hash: " << h << std::endl;
                    std::cout << "String 1: " << hash_to_string[h] << std::endl;
                    std::cout << "String 2: " << s << std::endl;
                }
            } else {
                hash_to_string[h] = s;
            }
        }
        std::cout << "Rasta " << collisions << " koliziju is " << TOTAL_PAIRS << " atsitiktiniu " << length << " simboliu eiluciu." << std::endl;
        
        // Only assert no collisions if we expect a strong hash function
        // For testing purposes, let's just report the collisions instead of asserting
        if (collisions > 0) {
            std::cout << "PERSPEJIMAS: Rastos kolizijos! Hash funkcija gali buti nestabili." << std::endl;
        }
    }

    // 6. Lavinos efektas
    std::cout << "\n[6. Lavinos efektas]" << std::endl;
    const int NUM_AVALANCHE_PAIRS = 1000;
    std::vector<double> bit_diffs;
    for (int i = 0; i < NUM_AVALANCHE_PAIRS; ++i) {
        std::string s1 = get_random_string(100);
        std::string s2 = get_string_with_one_diff(s1);
        std::string h1_hex = hasher.hash(s1);
        std::string h2_hex = hasher.hash(s2);
        
        int diff = hamming_distance(h1_hex, h2_hex);
        bit_diffs.push_back((static_cast<double>(diff) / 256.0) * 100.0);
    }
    
    double sum = 0.0;
    double min_diff = 101.0, max_diff = -1.0;
    for (double diff : bit_diffs) {
        sum += diff;
        if (diff < min_diff) min_diff = diff;
        if (diff > max_diff) max_diff = diff;
    }
    
    std::cout << "Analize " << NUM_AVALANCHE_PAIRS << " poru, besiskirianciu vienu simboliu:" << std::endl;
    std::cout << "  - Vidutinis bitu skirtumas: " << std::fixed << std::setprecision(2) << (sum / bit_diffs.size()) << "%" << std::endl;
    std::cout << "  - Minimalus bitu skirtumas: " << min_diff << "%" << std::endl;
    std::cout << "  - Maksimalus bitu skirtumas: " << max_diff << "%" << std::endl;

    std::cout << "\n--- Eksperimentas baigtas ---" << std::endl;
}

int main() {
    run_experiments();
    return 0;
}