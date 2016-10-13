#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

bool input_int(const string& prompt, int& n, bool (*is_valid)(const int&)){
    string line;
    int value;
    while (1) {
        cout << prompt << endl;
        if (!getline(cin, line)) {
            cin.clear();
            return false;
        }
        if (line == "11111"){
            cin.clear();
            break;
        }
        istringstream iss(line);
        if (iss >> value) {
            if (is_valid(value)) {
                n = value;
                return true;
            }else
                cout << "invalid input int" << endl;
        } else
            iss.clear();
    }
    return false;
}
bool input_float(const string& prompt, float& n, bool (*is_valid)(const float&)){
    string line;
    float score;
    while (1) {
        cout << prompt << endl;
        if (!getline(cin, line)){
            cin.clear();
            return false;
        }
        if (line == "11111"){
            cin.clear();
            break;
        }
        istringstream iss(line);
        if (iss >> score) {
            if (is_valid(score)) {
                n = score;
                return true;
            }else
                cout << "invalid input float" << endl;
        } else
            iss.clear();
    }
    return false;
}

bool is_valid(const int& a){
    return (a >= 10000 && a <= 99999999);
}

bool is_valid(const float& a){
    return (a >= 0 && a <= 100);
}

bool is_valid_choice(const int& a){
    return (a == 1 || a == 2);
}
bool is_valid_option(const int& a){
    return !isalpha(a);
}

void display_record(fstream& fs){
    int pos = 0;
    char buffer[1024];
    string content;
    while (input_int("Please enter a integer for display", pos, is_valid_option)){
        buffer[0] = 0;
        if (pos > 0) {
            fs.clear();
            if (fs.seekg(ios::off_type((pos-1)*16), ios_base::beg) && fs.read(buffer, 15)) {
                buffer[8] = ':';
                cout << buffer << endl;
                buffer[0] = 0;
            }
            else
                cerr << "Cannot seek" << endl;
        }
        else if (pos < 0) {
            fs.clear();
            if (fs.seekg(ios::off_type((abs(pos)-1)*16), ios_base::beg) && getline(fs, content)){
                istringstream iss(content);
                int id;
                float score;
                while (iss >> id && iss >> score){
                    cout << 'A' << id << ": ";
                    cout.clear();
                    cout << fixed << setprecision(2) << score << endl;
                }
            }else
                cerr << "Cannot seek" << endl;
        }
        else if (pos == 0 || pos == 11111){
            cin.clear();
            break;
        }
    }
}

void input_record(fstream& fs){
    int n;
    float m = 0.0;
    fs.seekg(0, ios_base::end);
    while (input_int("Please enter the student ID ", n, is_valid) && input_float("Please enter the score ", m, is_valid)) {
        fs << setfill('0') << setw(8) << n;
        fs << ' ';
        fs << setprecision(2) << setfill(' ') << setw(6) << fixed << m;
        fs << ' ';
    }
}


int main(int argc, const char * argv[]) {
    int choice;
    fstream fs(argv[1], ios_base::out | ios_base::in | ios_base::binary | ios_base::trunc);
    if (!fs) {
        cerr << "Unable to open " << argv[1] << " for writing" << endl;
        return 0;
    }
    while(input_int("1. Input records\n2. Display records", choice, is_valid_choice)){
        if (choice == 1){
            input_record(fs);
        }
        else if (choice == 2 && fs.is_open())
            display_record(fs);
        choice = 0;
    }
    return 0;
}