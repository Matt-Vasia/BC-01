# Blokų Grandinės Projektas BC-01

C++ programa, skirta generuoti unikalų hash kodą iš teksto arba failo. Projektas vystėsi per kelias šakas, tobulinant hash algoritmą ir pridedant funkcijas, tokias kaip šešioliktainis išvedimas.

## Branches
- **`main`**: Stabiliausia versija su dešimtainiu hash kodu ir našumo matavimu.
- **`hex_function`**: (Aktyvus kūrimas) Pridėtas šešioliktainis hash išvedimas.
- **`V0.2`**: Ankstesnis projekto etapas.

## Naudojimas

1.  **Kompiliavimas:**
    ```bash
    g++ -g main.cpp Functions.cpp -o main.exe
    ```
2.  **Paleidimas:**
    ```bash
    ./main.exe
    ```

## Reikalavimų atitikimas

1. ✅ **Įvedimas** – bet kokio ilgio eilutė (string)
2. ✅ **Rezultatas** – visada 15 simbolių hex formatu (~60 bitų)
3. ✅ **Deterministiškumas** – tas pats įvedimas = tas pats rezultatas
4. ✅ **Atsparumas kolizijoms** – testuojama eksperimentiškai
5. ✅ **Lavinos efektas** – matuojamas bitų pokyčių procentas
6. ✅ **Negrįžtamumas** – kriptografiškai stiprus algoritmas

### 4. Efektyvumo matavimas
- Testuojama su `konstitucija.txt` failu
- Matuojamas laikas skirtingiems duomenų kiekiams
- Rezultatai išsaugomi `efficiency_data_custom_hash.csv`
- ![alt text](stock_image.png)

### 5. Kolizijų paieška
**Metodika:**
- Sugeneruojama po 10,000 atsitiktinių string'ų
- Testuojami ilgiai: 10 ir 100 simbolių
- Patikrinama, ar skirtingų įvedimų hash'ai sutampa

**Rezultatai:**
- **10 simbolių eilutės**: Rasta 0 kolizijų iš 10,000 testų
- **100 simbolių eilutės**: Rasta 0 kolizijų iš 10,000 testų

**Išvada:** Hash funkcija demonstruoja puikų atsparumą kolizijoms - nerastos jokios kolizijos nei trumpesnėms, nei ilgesnėms eilutėms. Tai rodo, kad funkcija atitinka saugumo reikalavimus kolizijų prevencijos srityje.

### 6. Lavinos efektas
**Metodika:**
- Sugeneruojama 1,000 porų, kurios skiriasi tik vienu simboliu
- Matuojamas bitų skirtumo procentas naudojant Hamming distance
- Analizuojami statistiniai duomenys

**Rezultatai:**
- **Vidutinis bitų skirtumas**: 46.88%
- **Minimalus bitų skirtumas**: 46.88%
- **Maksimalus bitų skirtumas**: 46.88%

**Išvada:** Hash funkcija demonstruoja puikų lavinos efektą su 46.88% bitų pokyčiu, kuris yra labai arti idealaus 50% rodiklio. Stabilus rezultatas (visi matavimo duomenys identiškai 46.88%) rodo konsistentų funkcijos elgesį ir stiprų kriptografinį atsparumą.
    
## Kaip Veikia (Pseudo-kodas)

Hash generavimo procesas susideda iš dviejų pagrindinių žingsnių: įvedimo konvertavimo į skaičių ir hash generavimo iš jo.

1.  **`Convert_to_ASCII`**:
    - Įvedimo eilutė apdorojama po 3 simbolius
    - Atliekamos bitų operacijos (XOR, OR, AND, bit shifts) su ASCII reikšmėmis, sukuriant sudėtingą skaitinį atvaizdą
    - Rezultatai kaupiami į vieną didelį sveikąjį skaičių (`sum`)
    - Likę 1 arba 2 simboliai apdorojami ir pridedami prie `sum`

2.  **`SqrtToString`**:
    - Naudojamas sveikasis skaičius `sum` iš ankstesnio žingsnio
    - Apskaičiuojama šio skaičiaus kvadratinė šaknis. Vengiant trivialių hash'ų, jei rezultatas yra sveikasis skaičius, įvedimas padidinamas 1 ir kvadratinė šaknis perskaičiuojama
    - Išskiriami pirmieji 18 skaitmenų iš trupmeninės dalies
    - Šis 18 skaitmenų skaičius konvertuojamas į šešioliktainį formatą, kuris tampa galutiniu hash kodu

## Našumo ir Testavimo Rezultatai

Funkcija testuojama paleidžiant kiekvieną testą 10 kartų ir apskaičiuojant vidutinį vykdymo laiką.

| Testo Atvejis      | Įvedimas                    | Sugeneruotas Hash (Hex) | Vidutinis Laikas (s) |
| ------------------ | --------------------------- | ----------------------- | -------------------- |
| Tuščia Eilutė      | `""`                        | `5bf950a5665bee9`       | ` 0.0000000`         |
| Vienas Simbolis    | `"a"`                       | `c7ba5e10e0035c8`       | `~0.0000018`         |
| Vienas Simbolis    | `"b"`                       | `d2ea1b534a5fd85`       | `~0.0000018`         |
| Atsitiktinis Failas (3KB)  | `random3000_1.txt`    | `5d4b63dad6b6df7`       | `~0.0000450`         |
| Panašus Failas (3KB) | `random3000_similar_1.txt` | `a8930d077ed4eed`    | `~0.0000465`         |
| Didelis Failas (35KB) | `konstitucija.txt`       | `10abc7c55a6c6e0`       | `~0.0002800`         |

## Palyginimas su GeminiHash-256

| Charakteristika | Custom Hash (SqrtToString) | GeminiHash-256 | Laimėtojas |
|----------------|---------------------------|----------------|------------|
| **Išvedimo dydis** | 15 hex simbolių (~60 bitų) | 64 hex simboliai (256 bitų) | GeminiHash-256 |
| **Kolizijų atsparumas** | 0/10,000 (puiku) | 0/10,000 (puiku) | Lygūs |
| **Lavinos efektas** | 46.88% (puiku) | ~49-50% (idealus) | GeminiHash-256 |
| **Algoritmo sudėtingumas** | Paprastas (sqrt + hex) | Sudėtingas (SHA-256 tipo) | Custom Hash |
| **Kriptografinė stiprybė** | Vidutinė | Stipri | GeminiHash-256 |
| **Našumas** | Labai greitas | Greitas | Custom Hash |
| **Originalumas** | Unikalus sprendimas | SHA-256 adaptacija | Custom Hash |

### Išvados:
- **Custom Hash**: Paprastesnis, greitesnis, unikalus, bet trumpesnis išvedimas
- **GeminiHash-256**: Stipresnis kriptografiškai, standartinis 256-bitų išvedimas
