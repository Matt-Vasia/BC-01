#include "LIB.h"
#include "block.cpp"

long int Convert_to_ASCII(string str)
{
    long int sum = 1; // suma = 1, nes duodant tuscia faila gaunamas 0

    while (str.length() >= 3)
    { // Jei stringas turi bent 3 simbolius
        const int OrBit = ((str[0] | str[1]) ^ (str[2] << 2) ^ 31) >> 4;
        const int OrBit2 = ((str[2] | str[1]) ^ (str[0] << 1) ^ 31) >> 3;
        const int AndBit = ((str[1] & str[2]) ^ (str[0] << 3) ^ 31) >> 7;
        const int AndBit2 = ((str[2] & str[0]) ^ (str[1] << 4) ^ 31) >> 5;
        sum *= 31;
        sum += ((OrBit * AndBit2) ^ (OrBit2 * AndBit) ^ static_cast<int>(str[0]) ^ static_cast<int>(str[1]) ^ static_cast<int>(str[2]) ^ str.length());
        str.erase(0, 3);
    }

    if (str.length() >= 2)
    { // Jei stringas turi bent 2 simbolius
        const int OrBit = (str[0] | str[1]) >> 2;
        if (OrBit >= 0)
            sum += sqrt(OrBit) + static_cast<int>(str[1]);
        else
            sum += static_cast<int>(str[1]);
        str.erase(0, 2);
    }

    if (!str.empty())
    { // jei stringas turi 1 simboli
        for (char c : str)
        {
            str[0] >> 2;
            sum += static_cast<int>(c);
        }
        str.erase(0, 1);
    }

    return static_cast<double>(abs(sum));
}

string SqrtToString(const string input)
{
    long int inputInAscii = Convert_to_ASCII(input);

    long double sqrtOfInputInAscii = sqrt(inputInAscii);
    if (sqrtOfInputInAscii == static_cast<int>(sqrtOfInputInAscii))
        inputInAscii += 1;
    sqrtOfInputInAscii = sqrt(inputInAscii);

    ostringstream oss;
    oss << setprecision(25) << fixed << sqrtOfInputInAscii;
    string sqrtAsString = oss.str();

    size_t decimalPos = sqrtAsString.find('.');
    string answer = "";
    if (decimalPos != string::npos)
    {
        string decimalPart = sqrtAsString.substr(decimalPos + 1, 18); // 18 skaitmenu, nes long long priima max 19 skaitmenu
        long long decimalAsNumber = stoll(decimalPart);               // string to long long
        ostringstream hexOss;
        hexOss << hex << decimalAsNumber;
        answer = hexOss.str();
    }
    return answer;
}

void ReadFromFile()
{
    cout << "Empty 1" << endl;
    cout << "Char 2" << endl;
    cout << "Random 3" << endl;
    cout << "Random similar 4" << endl;
    cout << "Konstitucija 5" << endl;

    string input;
    do
    {
        cin >> input;
    } while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5");

    {
        string warmupInput = "warmup";
        SqrtToString(warmupInput); // Call function to trigger JIT compilation/caching

        // Additional warm-up calls to ensure system is fully ready
        for (int i = 0; i < 5; i++)
        {
            SqrtToString("warmup" + to_string(i));
        }
    }

    if (input == "1")
    {
        const int NUM_RUNS = 10;
        double total_duration = 0.0;
        string hash;
        for (int i = 0; i < NUM_RUNS; ++i)
        {
            auto start = chrono::high_resolution_clock::now();
            hash = SqrtToString("");
            auto end = chrono::high_resolution_clock::now();
            total_duration += chrono::duration_cast<chrono::duration<double>>(end - start).count();
        }
        cout << hash << " " << fixed << setprecision(7) << total_duration / NUM_RUNS << " s" << endl;
    }
    if (input == "2")
    {
        const int NUM_RUNS = 10;
        vector<string> data = {"a", "b", "c"};
        for (const string &sample : data)
        {
            double total_duration = 0.0;
            string hash;
            for (int i = 0; i < NUM_RUNS; ++i)
            {
                auto start = chrono::high_resolution_clock::now();
                hash = SqrtToString(sample);
                auto end = chrono::high_resolution_clock::now();
                total_duration += chrono::duration_cast<chrono::duration<double>>(end - start).count();
            }
            cout << hash << " " << fixed << setprecision(7) << total_duration / NUM_RUNS << " s" << endl;
        }
    }
    if (input == "3")
    {
        const int NUM_RUNS = 10;
        vector<string> files = {"test_files/random3000_1.txt", "test_files/random3000_2.txt", "test_files/random3000_3.txt"};
        for (const auto &filename : files)
        {
            ifstream file(filename);
            if (file.is_open())
            {
                stringstream buffer;
                buffer << file.rdbuf();
                string content = buffer.str();
                file.close();

                double total_duration = 0.0;
                string hash;
                for (int i = 0; i < NUM_RUNS; ++i)
                {
                    auto start = chrono::high_resolution_clock::now();
                    hash = SqrtToString(content);
                    auto end = chrono::high_resolution_clock::now();
                    total_duration += chrono::duration_cast<chrono::duration<double>>(end - start).count();
                }
                cout << hash << " " << fixed << setprecision(7) << total_duration / NUM_RUNS << " s" << endl;
            }
            else
            {
                cerr << "Unable to open file: " << filename << endl;
            }
        }
    }
    if (input == "4")
    {
        const int NUM_RUNS = 10;
        vector<string> files = {"test_files/random3000_similar_1.txt", "test_files/random3000_similar_2.txt", "test_files/random3000_similar_3.txt"};
        for (const auto &filename : files)
        {
            ifstream file(filename);
            if (file.is_open())
            {
                stringstream buffer;
                buffer << file.rdbuf();
                string content = buffer.str();
                file.close();

                double total_duration = 0.0;
                string hash;
                for (int i = 0; i < NUM_RUNS; ++i)
                {
                    auto start = chrono::high_resolution_clock::now();
                    hash = SqrtToString(content);
                    auto end = chrono::high_resolution_clock::now();
                    total_duration += chrono::duration_cast<chrono::duration<double>>(end - start).count();
                }
                cout << hash << " " << fixed << setprecision(7) << total_duration / NUM_RUNS << " s" << endl;
            }
            else
            {
                cerr << "Unable to open file: " << filename << endl;
            }
        }
    }
    if (input == "5")
    {
        const int NUM_RUNS = 10;
        ifstream file("test_files/konstitucija.txt");
        if (file.is_open())
        {
            stringstream buffer;
            buffer << file.rdbuf();
            string content = buffer.str();
            file.close();

            double total_duration = 0.0;
            string hash;
            for (int i = 0; i < NUM_RUNS; ++i)
            {
                auto start = chrono::high_resolution_clock::now();
                hash = SqrtToString(content);
                auto end = chrono::high_resolution_clock::now();
                total_duration += chrono::duration_cast<chrono::duration<double>>(end - start).count();
            }
            cout << hash << " " << fixed << setprecision(7) << total_duration / NUM_RUNS << " s" << endl;
        }
        else
        {
            cerr << "Unable to open file: " << "test_files/konstitucija.txt" << endl;
        }
    }
}

// --- Helper functions for experiments ---

string get_random_string(int length)
{

    const string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, chars.size() - 1);
    string random_string;
    for (int i = 0; i < length; ++i)
    {
        random_string += chars[distribution(generator)];
    }
    return random_string;
}

string get_string_with_one_diff(const string &original)
{
    if (original.empty())
        return "a";
    string modified = original;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, original.size() - 1);
    int pos = dist(gen);
    char old_char = modified[pos];
    char new_char;
    do
    {
        new_char = get_random_string(1)[0];
    } while (new_char == old_char);
    modified[pos] = new_char;
    return modified;
}

bitset<64> hex_to_bitset64(const string &hex)
{
    unsigned long long val;
    stringstream ss;
    ss << std::hex << hex;
    ss >> val;
    return bitset<64>(val);
}

int hamming_distance(const string &h1, const string &h2)
{
    return (hex_to_bitset64(h1) ^ hex_to_bitset64(h2)).count();
}

void run_hash_experiments()
{
    cout << "--- Running Custom Hash Experimental Analysis ---" << endl;

    // 1. Test data preparation
    cout << "\n[1. Preparing test data]" << endl;
    map<string, string> test_data;
    test_data["empty"] = "";
    test_data["a"] = "a";
    test_data["b"] = "b";
    test_data["long_1"] = get_random_string(1500);
    test_data["long_2"] = get_string_with_one_diff(test_data["long_1"]);
    cout << "Test data prepared in memory." << endl;

    // 2. Output size check
    cout << "\n[2. Checking output size]" << endl;
    for (const auto &pair : test_data)
    {
        string h = SqrtToString(pair.second);
        cout << "Input '" << pair.first << "' -> Output length: " << h.length() << " | Hash: " << h << endl;
    }

    // 3. Determinism check
    cout << "\n[3. Checking determinism]" << endl;
    string h1 = SqrtToString("Hello World");
    string h2 = SqrtToString("Hello World");
    cout << "Hash 1 'Hello World': " << h1 << endl;
    cout << "Hash 2 'Hello World': " << h2 << endl;
    if (h1 == h2)
    {
        cout << "Determinism confirmed." << endl;
    }
    else
    {
        cout << "WARNING: Determinism check failed!" << endl;
    }

    // 4. Efficiency test
    cout << "\n[4. Efficiency test]" << endl;
    ifstream constitution_file("test_files/konstitucija.txt");
    if (constitution_file.is_open())
    {
        string content((istreambuf_iterator<char>(constitution_file)), istreambuf_iterator<char>());
        ofstream results_file("gemini/efficiency_data_custom_hash.csv");
        results_file << "InputSize,TimeSeconds\n";
        const int NUM_ITERATIONS = 100;
        for (int i = 10; i <= 100; i += 10)
        {
            string chunk = content.substr(0, content.size() * i / 100);

            auto start = chrono::high_resolution_clock::now();
            for (int iter = 0; iter < NUM_ITERATIONS; ++iter)
            {
                SqrtToString(chunk);
            }
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double> diff = end - start;
            double avg_time = diff.count() / NUM_ITERATIONS;
            results_file << chunk.size() << "," << avg_time << "\n";
        }
        results_file.close();
        cout << "Efficiency test data saved to 'efficiency_data_custom_hash.csv'." << endl;
    }
    else
    {
        cout << "File 'test_files/konstitucija.txt' not found. Skipping efficiency test." << endl;
    }

    // 5. Collision search
    cout << "\n[5. Collision search]" << endl;
    const int TOTAL_PAIRS = 10000;
    for (int length : {10, 100})
    {
        map<string, string> hash_to_string;
        int collisions = 0;
        for (int i = 0; i < TOTAL_PAIRS; ++i)
        {
            string s = get_random_string(length);
            string h = SqrtToString(s);

            if (hash_to_string.count(h))
            {
                if (hash_to_string[h] != s)
                {
                    collisions++;
                    cout << "Collision found! Hash: " << h << endl;
                    cout << "String 1: " << hash_to_string[h] << endl;
                    cout << "String 2: " << s << endl;
                }
            }
            else
            {
                hash_to_string[h] = s;
            }
        }
        cout << "Found " << collisions << " collisions out of " << TOTAL_PAIRS << " random strings of length " << length << "." << endl;
        if (collisions > 0)
        {
            cout << "WARNING: Collisions found! The hash function may not be collision-resistant." << endl;
        }
    }

    // 6. Avalanche effect
    cout << "\n[6. Avalanche effect]" << endl;
    const int NUM_AVALANCHE_PAIRS = 1000;
    vector<double> bit_diffs;
    for (int i = 0; i < NUM_AVALANCHE_PAIRS; ++i)
    {
        string s1 = get_random_string(100);
        string s2 = get_string_with_one_diff(s1);
        string h1_hex = SqrtToString(s1);
        string h2_hex = SqrtToString(s2);

        int diff = hamming_distance(h1_hex, h2_hex);
        bit_diffs.push_back((static_cast<double>(diff) / 64.0) * 100.0);
    }

    double sum = 0.0;
    double min_diff = 101.0, max_diff = -1.0;
    for (double diff : bit_diffs)
    {
        sum += diff;
        if (diff < min_diff)
            min_diff = diff;
        if (diff > max_diff)
            max_diff = diff;
    }

    cout << "Analysis of " << NUM_AVALANCHE_PAIRS << " pairs differing by one character:" << endl;
    cout << "  - Average bit difference: " << fixed << setprecision(2) << (sum / bit_diffs.size()) << "%" << endl;
    cout << "  - Minimum bit difference: " << min_diff << "%" << endl;
    cout << "  - Maximum bit difference: " << max_diff << "%" << endl;

    cout << "\n--- Experiment finished ---" << endl;
}

void UIfunc()
{
    cout << "Manually 1 \nRead from file 2\nRun experiments 3\n";
    string input;
    do
    {
        cin >> input;
    } while (input != "1" && input != "2" && input != "3" && input != "4");

    if (input == "1")
    {
        string hash;

        cout << "enter input: \n";
        cin >> hash;
        cout << SqrtToString(hash);
    }
    else if (input == "2")
    {
        ReadFromFile();
    }
    else if (input == "3")
    {
        run_hash_experiments();
    }
}

void create_users()
{
    static std::mt19937 rng{std::random_device{}()};         // kazka cia turetu reikst, kad random.. klausti DI.
    std::uniform_real_distribution<double> d(10.0, 10000.0); // nusato nuo 10 iki 10000 random skaiciu

    Users.clear();

    int count = 0;

    cout << "choose the number of users: ";
    cin >> count;

    string newName = "";
    string newKey = "";
    double newBal = 0;

    for (size_t i = 0; i < count; i++)
    {
        newName = "User" + to_string(i);
        newKey = SqrtToString(newName);
        newBal = d(rng);

        User newUser(newName, newKey, newBal);
        Users.push_back(newUser);
    }
}

void trans_generator()
{
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<int> d(10, 100000);

    int count = 0;

    cout << "choose the number of transactions: ";
    cin >> count;

    for (size_t i = 0; i < count; i++)
    {
        int sender_index = d(rng);
        int receiver_index = d(rng);
        while (sender_index == receiver_index)
            receiver_index = d(rng);

        double sum = d(rng);

        string sender_key = Users[sender_index].getPublicKey();
        string receiver_key = Users[receiver_index].getPublicKey();

        Transaction trans = Transaction(sender_key, receiver_key, sum);
        Txs.push_back(trans);
    }
}