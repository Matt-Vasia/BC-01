# BC-01 v0.1 — Supaprastinta blokų grandinė (pagal slides.pdf)

Šis failas aprašo v0.1 užduotį ir kaip naudotis programa.

## Tikslas (v0.1)

- Turėti paprastą maišos funkciją tekstui („custom hash“ — `SqrtToString`).
- Sugeneruoti vartotojus su viešais raktų atvaizdais (naudojant `SqrtToString`).
- Sugeneruoti atsitiktines transakcijas tarp vartotojų.
- Paruošti bazę blokui su ankstesnio bloko hash, merkle šaknimi, nonce ir difficulty (minavimas kaip procesas yra paruoštas, tačiau blokų klasė dar neužbaigta — žr. „Žinomos spragos“).
- Atlikti bazinius hash eksperimentus (efektyvumas, lavinos efektas, kolizijų paieška).

## Projekto struktūra (aktualu v0.1)

- `Functions.cpp` — custom hash (`SqrtToString`) ir pagalbinės funkcijos:
  - `Convert_to_ASCII`, `SqrtToString`
  - `create_users`, `trans_generator`
  - `run_hash_experiments`, `ReadFromFile`, `UIfunc`
- `LIB.h` — bendros deklaracijos.
- `test_files/` — testo duomenys (pvz., `konstitucija.txt`, kiti failai).
- `block.cpp`, `block.h` — blokų/operacijų struktūros.

## Kaip sukompiliuoti ir paleisti

## Custom hash (SqrtToString) eksperimentai (v0.1)

Šiuo metu `Functions.cpp` turi visą logiką ir CLI funkcijas, tačiau nėra dedikuoto `main()` į ją iškviesti. Yra du greiti pasirinkimai:

- g++ -g  main.cpp -o  main.exe

- ./main.exe

- Sekti nurodymus konsolėje