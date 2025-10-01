#include "LIB.h"

long int Convert_to_ASCII(string str)
{
    long int sum = 1;

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
            str[0]>>2;
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
    if(sqrtOfInputInAscii == static_cast<int>(sqrtOfInputInAscii))
        inputInAscii+=1;
    sqrtOfInputInAscii = sqrt(inputInAscii);

    ostringstream oss;
    oss << setprecision(25) << fixed << sqrtOfInputInAscii;
    string sqrtAsString = oss.str();

    size_t decimalPos = sqrtAsString.find('.');
    string answer = "";
    if (decimalPos != string::npos) {
        string decimalPart = sqrtAsString.substr(decimalPos + 1, 18); // 19 skaitmenu, nes long long priima max 19 skaitmenu
        long long decimalAsNumber = stoll(decimalPart); // string to long long
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
        for (int i = 0; i < 5; i++) {
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

void UIfunc(){
    cout << "Manually 1 \nRead from file 2\n";
     string input;
    do
    {
        cin >> input;
    } while (input != "1" && input != "2");

    if(input == "1"){
        string hash;

        cout << "enter input: \n";
        cin >> hash;
        cout << SqrtToString(hash);
    }

    else {
        ReadFromFile();
    }

}