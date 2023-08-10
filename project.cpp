#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include <map>

using namespace std;


// method 1
string encrypt1(string plaintext, int shift) {
    string ciphertext = "";
    for (char c : plaintext) {
        if (isalpha(c)) {
            if (isupper(c)){
                char shifted = (c - 'A' + shift) % 26 + 'A';
                ciphertext += shifted;
            }
            else if (islower(c)){
                char shifted = (c - 'a' + shift) % 26 + 'a';
                ciphertext += shifted;
            }
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

string decrypt1(string ciphertext, int shift) {
    string plaintext = "";
    for (char c : ciphertext) {
        if (isalpha(c)) {
            if (isupper(c)){
                char shifted = (c - 'A' - shift + 26) % 26 + 'A';
                plaintext += shifted;
            }
            else if(islower(c)){
                char shifted = (c - 'a' - shift + 26) % 26 + 'a';
                plaintext += shifted;
            }
        } else {
            plaintext += c;
        }
    }
    return plaintext;
}

// method 2
string generateKey(string str, string key)
{
	int x = str.size();

	for (int i = 0; ; i++)
	{
		if (x == i)
			i = 0;
		if (key.size() == str.size())
			break;
		key.push_back(key[i]);
	}
	return key;
}

string encrypt2(string str, string key)
{
	string cipher_text;
	for (int i = 0; i < str.size(); i++)
	{
		char x = (str[i] + key[i]) %26;
		x += 'A';
		cipher_text.push_back(x);
	}
	return cipher_text;
}

string decrypt2(string cipher_text, string key)
{
	string orig_text;
	for (int i = 0 ; i < cipher_text.size(); i++)
	{
		char x = (cipher_text[i] - key[i] + 26) %26;
		x += 'A';
		orig_text.push_back(x);
	}
	return orig_text;
}

//method 3
string encrypt3(string plaintext, string key)
{
    map<char, char> encryptionKey;
    for(int i = 0; i < 26; i++)
    {
        encryptionKey[char(i + 97)] = key[i];
    }
    string ciphertext = "";
    for(int i = 0; i < plaintext.length(); i++)
    {
        if(isalpha(plaintext[i]))
        {
            if(isupper(plaintext[i]))
            {
                ciphertext += toupper(encryptionKey[tolower(plaintext[i])]);
            }
            else
            {
                ciphertext += encryptionKey[plaintext[i]];
            }
        }
        else
        {
            ciphertext += plaintext[i];
        }
    }
    return ciphertext;
}

string decrypt3(string ciphertext, string key)
{
    map<char, char> decryptionKey;
    for(int i = 0; i < 26; i++)
    {
        decryptionKey[key[i]] = char(i + 97);
    }
    string plaintext = "";
    for(int i = 0; i < ciphertext.length(); i++)
    {
        if(isalpha(ciphertext[i]))
        {
            if(isupper(ciphertext[i]))
            {
                plaintext += toupper(decryptionKey[tolower(ciphertext[i])]);
            }
            else
            {
                plaintext += decryptionKey[ciphertext[i]];
            }
        }
        else
        {
            plaintext += ciphertext[i];
        }
    }

    return plaintext;
}

void signup(){
    cout << "SIGN-UP\n";
    fstream fout;
    fout.open("signup.csv", ios::out | ios::app);
    cout << "Enter username: ";
    string username;
    cin >> username;
    cout << "Enter Password: ";
    string password;
    fflush(stdin);
    cin >> password;
    int tempRand = rand();
    int encr = (tempRand % (3)) + 1 ;
    cout << "Temp Value"<<tempRand;
    if (encr == 1){
        int shift = 3;
        string encrpass = encrypt1(password, shift);
        fout << username << ",";
        fout << encrpass << ",";
        fout << encr << ",";
        fout << shift << "\n";
    }
    else if (encr == 2){
        string keyword = "AYUSH";
        string newpass;
        for (int i=0; i<password.size();i++){
            newpass += toupper(password[i]);
        }
        string key = generateKey(newpass, keyword);
        string encrpass = encrypt2(newpass, key);
        fout << username << ",";
        fout << encrpass << ",";
        fout << encr << ",";
        fout << key << "\n";
    }
    else if (encr == 3){
        string key = "zyxwvutsrqponmlkjihgfedcba";
        string encrpass = encrypt3(password, key);
        fout << username << ",";
        fout << encrpass << ",";
        fout << encr << ",";
        fout << key << "\n";
    }
}

void login(){
    cout << "LOGIN\n";
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    fflush(stdin);
    cin >> password;
    fstream fin;
    fin.open("signup.csv");
    int count = 0 ;
    vector<vector<string>> content;
    vector<string> row;
    string line,word;

    fstream file("signup.csv", ios::in);
    if (file.is_open()){
        while (getline(file, line)){
            row.clear();
            stringstream str(line);
            while(getline(str, word, ',')){
                row.push_back(word);
            }
            content.push_back(row);
        }
    }
    else{
        cout << "Could not open the file.\n";
    }
    for (int i=0; i<content.size(); i++){
        if (content[i][0].compare(username) == 0){
            int key;
            key = stoi(content[i][2]);
            string decrpass;
            if (key == 1){
                decrpass = decrypt1(content[i][1], 3);
                if (decrpass.compare(password) == 0){
                    cout << "Login successfully";
                }
                else{
                    cout << "Invalid credentials";
                }
                count = 1;
            }
            else if (key == 2){
                decrpass = decrypt2(content[i][1], content[i][3]);
                string newpass;
                for (int i=0; i<password.size();i++){
                    newpass += toupper(password[i]);
                }
                if (decrpass.compare(newpass) == 0){
                    cout << "Login successfully";
                }
                else{
                    cout << "Invalid credentials";
                }
                count = 1;
            }
            else if (key == 3){
                decrpass = decrypt3(content[i][1], content[i][3]);
                cout << endl << decrpass;
                if (decrpass.compare(password) == 0){
                    cout << "Login successfully";
                }
                else{
                    cout << "Invalid credentials";
                }
                count = 1;
            }
        }
    }
    if (count == 0){
        cout << "Invalid Username";
    }
}

int main(){
    cout << "1. Sign Up\n";
    cout << "2. Login\n";
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == 1){
        signup();
    }
    else if (choice == 2){
        login();
    }
    else {
        cout << "Enter valid choice";
    }
    return 0;
}