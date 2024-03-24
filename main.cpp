#include <iostream>
#include "bits/stdc++.h"


using namespace std;
// File name: CS112_A2_T4_section(23,24)_ 20230475 _20230650_20230121.cpp
// Hussam Muhammed Ahmed Abdelaziz
// email: saulgoodman2005@gmail.com
// ID: 20230121
// Ahmed Mahmoud Ibrahim Mahmoud
// Email: ahmedmahmoudpes41@gmail.com
// ID: 20230650
// Youssef abo el yousr
// Email:
// ID: 20230475
// Section: 23,24


//hossam
string ch2[100];

void clearMatrix(
        int key) {                   //func that clears the matrix with every initialization and fills it all with 'x's
    for (int i = 0; i < 100; ++i) {          //and set the dimensions of the matrix by taking columns as input(key).
        ch2[i] = "";
    }
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < key; ++j) {
            ch2[i] += 'X';
        }
    }
}

void
initializeMatrixE(int key, string input) {         //func that fills every char of the input into the matrix one by one.
    clearMatrix(key);
    for (int i = 0; i < (input.size() + (key - 1)) / key; ++i) {
        for (int j = 0; j < key; ++j) {
            ch2[i][j] = input[j + i * key];
            if (j + i * key == input.size() - 1)break;
        }
    }
}

string routeEncryption(string inputE, int key) {    //func that does the Encryption and returns the output
    initializeMatrixE(key, inputE);
//    showMatrix(key, inputE);
    cout << endl;
    string encrypt = "";              //string that will have the output of the Encryption
    int top = 0, bot = ((inputE.size() + (key - 1)) / key) - 1, left = 0, right =
            key - 1;          //setting variables to traverse through every column and row.
    while (top <= bot && left <=
                         right) {               //doing the actual spiral movement through the matrix and adding it to our string.
        // Traversing right column
        for (int i = top; i <= bot; ++i) {
            encrypt += ch2[i][right];
        }
        right--;                                //removing the row or column that we already traversed through every time we finish one so that we update the array's dimensions and making it smaller.
        // Traversing bottom row
        if (top <= bot) {
            for (int i = right; i >= left; --i) {
                encrypt += ch2[bot][i];
            }
            bot--;
        }
        // Traversing left column
        if (left <= right) {
            for (int i = bot; i >= top; --i) {
                encrypt += ch2[i][left];
            }
            left++;
        }
        // Traversing top row
        for (int i = left; i <= right; ++i) {
            encrypt += ch2[top][i];
        }
        top++;
    }
    return encrypt;
}

string routDecrypt(int key, string input) {                 //func that does the Decryption and returns the output.
    initializeMatrixE(key, input);                           //using same func of initializing.
    int top = 0, bot = ((input.size() + (key - 1)) / key) - 1, left = 0, right =
            key - 1; //setting variables to traverse through every column and row.
    int cntr = 0;
    while (top <= bot && left <=
                         right) {                   //basically doing the same spiral movement but instead of adding it too a string we fill the matrix with the input.
        for (int i = top; i <= bot; ++i) {
            ch2[i][right] = input[cntr];
            cntr++;
        }
        right--;
        if (top <= bot) {
            for (int i = right; i >= left; --i) {
                ch2[bot][i] = input[cntr];
                cntr++;
            }
            bot--;
        }
        if (left <= right) {
            for (int i = bot; i >= top; --i) {
                ch2[i][left] = input[cntr];
                cntr++;
            }
            left++;
        }
        for (int i = left; i <= right; ++i) {
            ch2[top][i] = input[cntr];
            cntr++;
        }
        top++;
    }
    string dec = "";        //string that will have the decrypted text.
    for (int i = 0; i < 100; ++i) {         //filling it with the text in the matrix until an 'x' appears.
        for (int j = 0; j < key; ++j) {
            if (ch2[i][j] == 'X')break;
            dec += ch2[i][j];
        }
    }
    return dec;
}

void routeCipher(int choice, string inputD) {//func that takes inputs and runs the routeCipher
    cout << "Enter your key (number of columns): ";
    cin.ignore();
    int key;                            //erasing spaces from input.
    cin >> key;
    for (int i = 0; i < inputD.size(); ++i) {
        if (inputD[i] == ' ') {
            inputD.erase(inputD.begin() + i);
            i--;
        }
    }
    for (int i = 0; i < inputD.size(); ++i) {                   //upper-casing the input.
        inputD[i] = toupper(inputD[i]);
    }

    if (choice == 1) {
        cout << "Encrypted: " << routeEncryption(inputD, key) << endl;
    } else {
        cout << "Decrypted: " << routDecrypt(key, inputD) << endl;
    }
}


//-------------------------------------------------------------------------------------------------------------------
//Ahmed Mahmoud Ibrahim Mahmoud
//Id:20230650
string encryptAffine(const string &text, int a, int b) {
    string encrypted = "";
    for (char q: text) {
        if (isalpha(q)) {
            char base = isupper(q) ? 'A' : 'a';
            int x = q - base;
            int E = (a * x + b) % 26;// E(x) = (a x + b) mod 26 where x is the numeric value
            encrypted += base + E;

        } else {
            encrypted += q;
        }
    }
    return encrypted;
}

//this function for decipher the massage
string decryptAffine(const string &text, int b, int c) {
    string decrypted = "";
    for (char q: text) {
        if (isalpha(q)) {
            char base = isupper(q) ? 'A' : 'a';
            int y = q - base;
            int D = (c * (y - b + 26)) % 26;//D(y) = c (y - b) mod 26 where x is the numeric value
            decrypted += base + D;
        } else {
            decrypted += q;
        }
    }
    return decrypted;
}

void affineCipher(int choice, string word) {
    int a, b, c;
    do {
        cin.ignore(); // Clear the input buffer
        cout << "Enter the values for a, b, and c (where (a * c) mod 26 = 1): ";
        cin >> a >> b >> c;
        cin.ignore(); // Ignore the newline character left in the input stream
        switch (choice) {
            case 1:
                cout << "Encrypted text: " << encryptAffine(word, a, b) << endl;
                break;
            case 2:
                cout << "Decrypted text: " << decryptAffine(word, b, c) << endl;
                break;
            case 3:
                cout << "Thanks for using affine cipher." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
}

//---------------------------------------------------------------------------------------------------------
//Youssef Abo El-Yosr
string encodeSS(string input, string key) {
    map<char, int> map1; // mapping the alphabet to the encrypted text
    map<char, int> map2; // counts the number of character occurences in the key so we dont use those letters later
    char cntr = 'a';  // start of the alphabet
    for (int i = 0; i < key.size(); ++i) {
        map1[cntr++] = key[i];  //mapping the first few letters to the key
        map2[key[i]]++;
    }
    for (int i = 'a'; i <= 'z'; ++i) {
        if (map2[i] != 0)continue; // if letter is in the key then dont use it
        map1[cntr++] = i; // iterate and move the cntr forward int the alphabet
    }
    string ans = "";
    for (int i = 0; i < input.size(); ++i) {
        ans += map1[input[i]];  // add every mapped letter to the answer
    }
    return ans;
}


string decodeSS(string input, string key) {
    map<char, int> map1; // counts the number of character occurences in the key so we dont use those letters later
    map<char, int> map2;
    for (int i = 0; i < key.size(); ++i) {
        map1[key[i]]++;
    }
    char cntr = 'a';
    for (int i = 0; i < key.size(); ++i) {
        map2[key[i]] = cntr++;  //map the key letters to the first few letters
    }
    for (char i = 'a'; i <= 'z'; i++) {
        if (map1[i] != 0)continue; //  if letter is used in the key then don't use it
        map2[i] = cntr++; // map every alphabet letter to its corresponding letter
    }
    string ans = "";
    for (int i = 0; i < input.size(); ++i) {
        ans += map2[input[i]];  // add every mapped letter to the answer
    }
    return ans;
}

void SSCipher(int choice, string input) {
    cin >> choice;
    choice = toupper(choice); // make the answer upper
    cout << "enter your key: " << endl;
    string key;
    cin >> key;
    if (choice == 1) { // if user want to encode
        cout << encodeSS(input, key);
    } else {
        cout << decodeSS(input, key);
    }
}

//-----------------------------------------------------------------------------------------------
//Youssef Abo El-Yosr

//in atbash both encryption and decryption are the same
void atbashEncrypt(string input) {              //this is the normal version
    map<char, char> mapE;
    mapE[' '] = ' ';
    for (char i = 'a', j = 'z'; i <= 'z' && j >=
                                            'a'; ++i, j--) {        //mapping the first characters in the alphabet to the last ones and vice versa
        mapE[i] = j;
    }
    string ans = "";                    //adding every mapped letter to the answer
    for (int i = 0; i < input.size(); ++i) {
        ans += mapE[input[i]];
    }
    cout << ans << endl;
}

void atbashhalfEncrypt(string input) {              //this is the 2 halves version
    map<char, char> mapE;
    mapE[' '] = ' ';
    for (char i = 'a', j = 'm'; i <= 'm' && j >=
                                            'a'; ++i, j--) {           //doing the same as normal version but instead splitting the alphabet into two equal halves
        mapE[i] = j;
    }
    for (char i = 'n', j = 'z'; i <= 'z' && j >= 'n'; ++i, j--) {
        mapE[i] = j;
    }
    string ans = "";
    for (int i = 0; i < input.size(); ++i) {
        ans += mapE[input[i]];
    }
    cout << ans << endl;
}

void atbash(int choice, string input) {                     //separate func to combine
    cout << "which version do u want to use? 1) half 2) full" << endl;
    int choice_which;
    cin >> choice_which;
    if (choice == 1)cout << "Encrypted: ";
    else cout << "Decrypted: ";
    if (choice_which == 1) {
        atbashhalfEncrypt(input);
    } else {
        atbashEncrypt(input);
    }
}

//--------------------------------------------------------------------------------------------

//hossam

void baconianEncrypt(string input, map<char, string> mapE) {        //printing ans
    cout << "Encrypted message is : ";
    for (int i = 0; i < input.size(); ++i) {
        cout << mapE[input[i]] << ' ';
    }
    cout << endl;
}

void baconainDecrypt(string input, map<string, char> mapD) {
    cout << "Decrypted message is : ";
    string temp;
    for (int i = 0; i < input.size(); ++i) {
        if (i == input.size() - 1) {
            temp += input[i];
            cout << mapD[temp];
            break;
        }
        if (input[i] ==
            ' ') {          //when there is a space that means we are done with one char then we reset the string ans repeat again for next char
            cout << mapD[temp];
            temp = "";
            continue;
        }
        temp += input[i];
    }
    cout << endl;
}

void baconianCipher(int choice, string input) {
    map<char, string> mapE;
    map<string, char> mapD;
    for (char i = 'a'; i <= 'z'; ++i) {
        int temp = i - 'a';            // turning char into int in order
        string binary = bitset<5>(temp).to_string();    //turning that int into binary num of 5 bits
        for (int j = 0; j < binary.size(); ++j) {       //setting zeros to 'a' and ones to 'b'
            if (binary[j] == '0')binary[j] = 'a';
            else binary[j] = 'b';
        }
        mapE[i] = binary;       //mapping every char of alphabet to encrypted string
        mapD[binary] = i;       //mapping the encrypted string to every char (decrypting)
    }
    if (choice == 1)
        baconianEncrypt(input, mapE);

    else baconainDecrypt(input, mapD);
}
//------------------------------------------------------------------------------------------------------------

//hossam

void railEncrypt(string input, int key, string mat[240]) { //encryption
    int column = 0; //counts chars of input which equals the column which that char will be
    while (column <= input.size()) {        //putting input char by char in the zigzag form
        for (int i = 0; i < key; ++i) {     //from top to bottom while increasing columns
            mat[i][column] = input[column];
            column++;
        }
        for (int i = key - 2; i > 0; --i) {     //from bottom to top while still increasing
            mat[i][column] = input[column];
            column++;
        }
    }   //finished putting chars into our zigzag form now to extract out encrypted msg
    string encrypt;
    for (int i = 0; i < key; ++i) {
        for (int j = 0; j < input.size(); ++j) {
            if (mat[i][j] !=
                '.') {         //basically start from beginning of array if there is a char add it to our answer
                encrypt += mat[i][j];
            }
        }
    }
    cout << encrypt << endl;
}

void railDecrypt(string input, int key, string mat[240]) { //decryption
    int columnD = 0;
    while (columnD <= input.size()) {
        for (int i = 0; i < key; ++i) {     //filling the matrix with a random char just to get the zigzag form
            mat[i][columnD] = 'Z';
            columnD++;
        }
        for (int i = key - 2; i > 0; --i) {
            mat[i][columnD] = 'Z';
            columnD++;
        }
    }
    int cntr = 0;
    for (int i = 0; i < key; ++i) {
        for (int j = 0; j <
                        input.size(); ++j) {        //now start form pass through in order and if we find that random char put one of our encrypted chars in it in order
            if (mat[i][j] == 'Z') {
                mat[i][j] = input[cntr++];
            }
        }
    }

    columnD = 0;
    string decrypt;
    while (columnD <=
           input.size()) {       //now do the zigzag from as before in the encryption but add the chars into our answer
        bool end = false;
        for (int i = 0; i < key; ++i) {
            if (mat[i][columnD] == 'Z' || mat[i][columnD] == '.') {
                end = true;
                break;
            }
            decrypt += mat[i][columnD];
            columnD++;
        }
        if (end)break;
        for (int i = key - 2; i > 0; --i) {
            if (mat[i][columnD] == 'Z' || mat[i][columnD] == '.') {
                end = true;
                break;
            }
            decrypt += mat[i][columnD];
            columnD++;
        }
        if (end)break;

    }
    cout << decrypt << endl;
}

void railFenceCipher(int choice, string input) {
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] == ' ') {              //erasing spaces from input
            input.erase(input.begin() + i);
            i--;
        }
    }
    cout << "Enter your key (num of rows):";
    int key;
    cin >> key;
    string mat[240];        //initialized our matrix with a big value just in case if input is too big
    for (int i = 0; i < 240; ++i) {
        for (int j = 0; j < 100; ++j) {
            mat[i] += '.';
        }
    }
    if (choice == 1) {
        cout << "Encrypted message is : ";
        railEncrypt(input, key, mat);
    } else {
        cout << "Decrypted message is : ";
        railDecrypt(input, key, mat);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//ahmed
string vingereEncrypt(string word, string key) {
    string result;
    string extended_key = key;
    while (extended_key.length() < word.length()) {
        extended_key += key;
    }
    extended_key = extended_key.substr(0, word.length());
    for (int j = 0; j < word.length(); ++j) {
        if (isalpha(word[j])) {
            char C = toupper(word[j]);
            char K = toupper(extended_key[j]);
            char encryptedChar = ((C - 'A') + (K - 'A')) % 26 + 'A';
            result += encryptedChar;
        } else {
            result += word[j];
        }
    }
    return result;
}

void vignereCipher(string input) {
    string key;
    cout << "Enter your key:";
    getline(cin, key);
    string encrypted_message = vingereEncrypt(input, key);
    cout << "Encrypted message:" << encrypted_message << endl;
}

//--------------------------------------------------------------------------------------------------------------
//Ahmed
void morseEncrypt(string input) {
    //mapping of each value to its corresponding value
    for (int i = 0; i < input.size(); ++i) {
        input[i] = toupper(input[i]);
    }
    map<char, string> map;
    map['A'] = ".-";
    map['B'] = "-...";
    map['C'] = "-.-,";
    map['D'] = "-..";
    map['E'] = ".";
    map['F'] = "..-.";
    map['G'] = "--.";
    map['H'] = "....";
    map['I'] = "..";
    map['J'] = ".---";
    map['K'] = "-.-";
    map['L'] = ".-..";
    map['M'] = "--";
    map['N'] = "-.";
    map['O'] = "---";
    map['P'] = ".--.";
    map['Q'] = "--.-";
    map['R'] = ".-.";
    map['S'] = "...";
    map['T'] = "-";
    map['U'] = "..-";
    map['V'] = "...-";
    map['W'] = ".--";
    map['X'] = "-..-";
    map['Y'] = "-.--";
    map['Z'] = "--..";
    string ans;
    //grouping the values
    for (int i = 0; i < input.size(); ++i) {
        ans += map[input[i]] + ' ';
    }
    cout << "encrypted: " << ans << endl;
}

void morseDecrypt(string input) {
    //mapping of each value to its corresponding value
    map<string, char> map;
    map[".-"] = 'A';
    map["-..."] = 'B';
    map["-.-."] = 'C';
    map["-.."] = 'D';
    map["."] = 'E';
    map["..-."] = 'F';
    map["--."] = 'G';
    map["...."] = 'H';
    map[".."] = 'I';
    map[".---"] = 'J';
    map["-.-"] = 'K';
    map[".-.."] = 'L';
    map["--"] = 'M';
    map["-."] = 'N';
    map["---"] = 'O';
    map[".--."] = 'P';
    map["--.-"] = 'Q';
    map[".-."] = 'R';
    map["..."] = 'S';
    map["-"] = 'T';
    map["..-"] = 'U';
    map["...-"] = 'V';
    map[".--"] = 'W';
    map["-..-"] = 'X';
    map["-.--"] = 'Y';
    map["--.."] = 'Z';
    string ans;
    cout << "decrypted: ";

    //grouping the values between each space

    for (int i = 0; i < input.size(); ++i) {
        if (i == input.size() - 1) {
            ans += input[i];
            cout << map[ans];
            break;
        }
        if (input[i] == ' ') {
            cout << map[ans];
            ans = "";
            continue;
        }
        ans += input[i];
    }
    cout << endl;
}

void morse(string input, int choice) {
    cout << input << endl;
    if (choice == 1) {
        morseEncrypt(input);
    } else {
        morseDecrypt(input);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------
//hossam

void encPolybius(string input, string key) {
    string matrix[6];
    // make input lowercase for easier processing
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] == 'j')input[i] = 'i';
        input[i] = tolower(input[i]);
    }
    int cntr = 0;

    // the following two for loops fills the edges of the matrix with the key
    for (int i = 1; i < 6; ++i) {
        matrix[0][i] = key[cntr];
        cntr++;
    }
    cntr = 0;
    for (int i = 1; i < 6; ++i) {
        matrix[i][0] = key[cntr];
        cntr++;
    }
    cntr = 0;
    char alpha = 'a';
    //fill the matrix with the alphabet
    for (int i = 1; i < 6; ++i) {
        for (int j = 1; j < 6; ++j) {
            if (alpha == 'j') {
                alpha++;
            }
            matrix[i][j] = alpha;
            alpha++;
        }
    }
//    cntr = 0;
    string ans;
    //search for every letter in the input and print the corresponding key indexes
    for (int cntr = 0; cntr < input.size(); ++cntr) {
        for (int i = 1; i < 6; ++i) {
            for (int j = 1; j < 6; ++j) {
                if (matrix[i][j] == input[cntr]) {
                    cout << matrix[i][0] << matrix[0][j];
                    cntr++;
                }
            }
        }
    }
    cout << endl;
}

void decPolypius(string poly, string key) {
    map<char, int> map1;
    //mapping the key values to the original values, ex: 54321 becomes 01234 to access the array
    for (int i = 0; i < key.size(); ++i) {
        map1[key[i]] = i;
    }

    string matrix[6];
    char cntr = 'a';
    // making a matrix of the alphabet
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (cntr == 'j')cntr++; // skip j
            matrix[i] += cntr++;
        }
    }
    string temp = "";
    for (int i = 0; i < poly.size(); ++i) {
        if (poly[i] == ' ')continue; // if letter is a space continue
        temp += poly[i];
        if (temp.size() == 2) { // decrypt every two letters (or numbers :))
            char first = temp[0];
            char second = temp[1];
            cout << matrix[map1[first]][map1[second]];
            temp = "";
        }
    }
    cout << endl;
}

void polypius(string input, int choice) {
    string key;
    cout << "enter your key: " << endl;
    cin >> key;
    if (choice == 1) {
        cout << "Encrypted is: ";
        encPolybius(input, key);
    } else {
        cout << "Decrypted is: ";
        decPolypius(input, key);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//hossam
//2 functions to help with Xor
string int_to_hex(int i) {
    ostringstream ss;
    ss << hex << i;
    return ss.str();
}

int hexadecimalToDecimal(string hexVal) {
    int len = hexVal.size();

    int base = 1;

    int dec_val = 0;

    for (int i = len - 1; i >= 0; i--) {
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;

            base = base * 16;
        } else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
            dec_val += (int(hexVal[i]) - 55) * base;

            base = base * 16;
        }
    }
    return dec_val;
}

void encXor(string input, string key) {
    string ans = "";
    string ans2 = "";
    //xor with key
    for (int i = 0; i < input.size(); ++i) {
        ans += char(input[i] ^ key[i]);
    }
    string temp = ""; // the same value in hexa
    for (int i = 0; i < input.size(); ++i) {
        ans2 += int_to_hex((int) char(input[i] ^ key[i]));  // do the same as above but convert to hexa
        ans2 += ' ';
    }
    //output in both ways
    cout << "Encrypted: " << ans << endl;
    cout << "hexa: " << ans2 << endl;
}

void decXor(string input, string key) {
    cout << "input as hexa? 1)yes 2)no" << endl;  //ask if input is hexadecimal or not
    cout << input << " " << key;
    int choice;
    cin >> choice;
    string ans;
    if (choice == 1) {
        string temp2 = "";
        //translate the hexa string to characters to be XORed
        for (int i = 0; i < input.size(); ++i) {
            if (input[i] == ' ')continue;
            temp2 += input[i];
            if (temp2.size() == 2) {
                int characterAscii = hexadecimalToDecimal(temp2);
                ans += (char) characterAscii;
                temp2 = "";
                continue;
            }
        }
        //xor with the key again to decrypt
        for (int i = 0; i < ans.size(); ++i) {
            ans[i] ^= key[i];
        }
        cout << "Decrypted: ";
        cout << ans << endl;
        return;
    } else {
        ans = "";
    }
    //xor with the key again to decrypt
    for (int i = 0; i < input.size(); ++i) {
        ans += char(input[i] ^ key[i]);
    }
    cout << "Decrypted: ";
    cout << ans << endl;

}

void xorCypher(string input, int choice) {
    string key;
    cout << "enter your key" << endl;
    cin >> key;
    //repeat key to size it up with the input
    while (key.size() < input.size()) {
        key += key;
    }
    if (choice == 1) {
        encXor(input, key);
    } else {
        decXor(input, key);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------

void menu() {
    cout << "Ahlan ya user ya habibi." << endl << "What do you want to do today?" << endl;
    cout << "1- Cipher a message" << endl << "2-Decipher a message" << endl << "3-End" << endl;
    int choice1;
    cin >> choice1;
    while (choice1 != 1 && choice1 != 2 && choice1 != 3) {
        cout << "invalid choice, re-enter ur choice: ";
        cin >> choice1;
    }
    if (choice1 == 3)return void(cout << "goodbye :(" << endl);
    if (choice1 == 1) {
        cout << "Please enter the message to Cipher: ";
    } else if (choice1 == 2) {
        cout << "Please enter the message to decipher: ";
    }
    cin.ignore();
    string input;
    getline(cin, input);

    cout << "Which Cipher do you want to choose?" << endl;
    cout << "1-Affine Cipher" << endl << "2-Route Cipher" << endl << "3-Simple Substitution Cipher" << endl
         << "4-Atbash Cipher" << endl << "5-Baconian Cipher" << endl << "6-Rail-fence cipher" << endl
         << "7-Vingere Cipher (only encrypting)" << endl << "8-Polypius Cipher" << endl << "9-XorCypher" << endl
         << "10-Morse" << endl
         << "any other number- exit" << endl;
    int choice2;
    cin >> choice2;

    switch (choice2) {
        case 1:
            affineCipher(choice1, input);
            break;
        case 2:
            routeCipher(choice1, input);
            break;
        case 3:
            SSCipher(choice1, input);
            break;
        case 4:
            atbash(choice1, input);
            break;
        case 5:
            baconianCipher(choice1, input);
            break;
        case 6:
            railFenceCipher(choice1, input);
            break;
        case 7:
            vignereCipher(input);
            break;
        case 8:
            polypius(input, choice1);
            break;
        case 9:
            xorCypher(input, choice1);
            break;
        case 10:
            morse(input, choice1);
            break;
        default:
            cout << "goodbye :(" << endl;
            break;
    }
}


//-----------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
int main() {
    while (true)menu();
    return 0;
}

