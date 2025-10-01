#include "LIB.h"

long int Convert_to_ASCII(string &str)
{
    long int sum = 0;

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
            sum += static_cast<int>(c);
        }
        str.erase(0, 1);
    }

    return static_cast<double>(abs(sum));
}

string SqrtToString(const string &input)
{
    long double value = Convert_to_ASCII(const_cast<string &>(input));
    value = sqrt(value + 0.1); // visada prideda 0.1, jog nebutu atveju, kad saknis issitraukia be liekanos
    ostringstream oss;
    oss << setprecision(20) << fixed << value;
    return oss.str();
}

string ReadFromFile()
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
    } while (input != "1" || input != "2" || input != "3" || input != "4" || input != "5");


    if (input == "1")
    {
        cout << SqrtToString("") << endl;
    }
    if (input == "2")
    {
        vector<string> hashes;
        vector<string> files = {"test_files/random3000_1.txt", "test_files/random3000_2.txt", "test_files/random3000_3.txt"};
        vector<string> data = {"a", "b", "c"};
        for (const string sample : data)
        {
            hashes.push_back(SqrtToString(sample));
        }
        cout << "Generated Hashes:" << endl;
        for (const auto &hash : hashes)
        {
            cout << hash << endl;
        }
    }
    if (input == "3")
    {
        vector<string> hashes;
        vector<string> files = {"test_files/random3000_1.txt", "test_files/random3000_2.txt", "test_files/random3000_3.txt"};
        for (const auto &filename : files)
        {
            ifstream file(filename);
            if (file.is_open())
            {
                stringstream buffer;
                buffer << file.rdbuf();
                string content = buffer.str();
                hashes.push_back(SqrtToString(content));
                file.close();
            }
            else
            {
                cerr << "Unable to open file: " << filename << endl;
            }
        }
        cout << "Generated Hashes:" << endl;
        for (const auto &hash : hashes)
        {
            cout << hash << endl;
        }
    }
    if (input == "4")
    {
        vector<string> hashes;
        vector<string> files = {"test_files/random3000_similar_1.txt", "test_files/random3000_similar_2.txt", "test_files/random3000_similar_3.txt"};
        for (const auto &filename : files)
        {
            ifstream file(filename);
            if (file.is_open())
            {
                stringstream buffer;
                buffer << file.rdbuf();
                string content = buffer.str();
                hashes.push_back(SqrtToString(content));
                file.close();
            }
            else
            {
                cerr << "Unable to open file: " << filename << endl;
            }
        }
        cout << "Generated Hashes:" << endl;
        for (const auto &hash : hashes)
        {
            cout << hash << endl;
        }
    }
    if (input == "5")
    {
        string hash;
        ifstream file("test_files/konstitucija.txt");
        if (file.is_open())
        {
            stringstream buffer;
            buffer << file.rdbuf();
            string content = buffer.str();
            hash = SqrtToString(content);
            file.close();
        }
        else
        {
            cerr << "Unable to open file: " << "test_files/konstitucija.txt" << endl;
        }
        cout << "Generated Hashes:" << endl;
        cout<< hash <<endl;
    }
}