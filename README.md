# Blockchain Project BC-01

A C++ application to generate a unique hash from a string or file. The project has evolved through several branches to improve the hashing algorithm and add features like hexadecimal output.

## Branches

- **`main`**: The most stable version with a decimal-based hash and performance timing.
- **`hex_function`**: (Active Development) Adds hexadecimal hash output.
- **`V0.2`**: An earlier project milestone.

## Usage

1.  **Compile:**
    ```bash
    g++ -g main.cpp Functions.cpp -o main.exe
    ```
2.  **Run:**
    ```bash
    ./main.exe
    ```

## How It Works (Pseudo-code)

The hashing process involves two main steps: converting the input to a number and then generating a hash from it.

1.  **`Convert_to_ASCII`**:
    - The input string is processed in chunks of 3 characters.
    - A series of bitwise operations (XOR, OR, AND, bit shifts) are applied to the ASCII values of the characters to create a complex numerical representation.
    - The results are accumulated into a single large integer (`sum`).
    - Any remaining 1 or 2 characters are processed and added to the `sum`.

2.  **`SqrtToString`**:
    - The integer `sum` from the previous step is used.
    - The square root of this number is calculated. To avoid trivial hashes, if the result is a whole number, the input is incremented by 1 and the square root is recalculated.
    - The first 18 digits of the fractional part of the square root are extracted.
    - This 18-digit number is converted into its hexadecimal representation, which becomes the final hash.

## Performance & Testing Results

The function is benchmarked by running each test case 10 times and calculating the average execution time.

| Test Case          | Input                       | Generated Hash (Hex) | Average Time (s) |
| ------------------ | --------------------------- | -------------------- | ---------------- |
| Empty String       | `""`                        | `5bf950a5665bee9`    | ` 0.0000000`     |
| Single Character   | `"a"`                       | `3def37a22d8`        | `~0.0000018`     |
| Single Character   | `"b"`                       | `3e43341a4d4`        | `~0.0000018`     |
| Random File (3KB)  | `random3000_1.txt`          | `3a43b7c1a2d`        | `~0.0000450`     |
| Similar File (3KB) | `random3000_similar_1.txt`  | `3a43b7c18f1`        | `~0.0000465`     |
| Large File (35KB)  | `konstitucija.txt`          | `3c1a2d8b7f`         | `~0.0002800`     |