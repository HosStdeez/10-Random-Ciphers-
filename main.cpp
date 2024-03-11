#include <iostream>

using namespace std;

string ch2[100];

void clearMatrix(int key){
    for (int i = 0; i < 100; ++i) {
        ch2[i] = "";
    }
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < key; ++j) {
            ch2[i] += 'x';
        }
    }
}

void initializeMatrixE(int key, string input) {
    clearMatrix(key);
    for (int i = 0; i < (input.size() + (key - 1)) / key; ++i) {
        for (int j = 0; j < key; ++j) {
            ch2[i][j] = input[j + i * key];
            if (j + i * key == input.size() - 1)break;
        }
    }
}

string routDecrypt(int key, string input) {
    initializeMatrixE(key,input);
    int top = 0, bot = ((input.size() + (key - 1)) / key) - 1, left = 0, right = key - 1;
    int cntr = 0;
    while (top <= bot && left <= right) {
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
    string dec = "";
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < key; ++j) {
            if (ch2[i][j] == 'X')break;
            dec+=ch2[i][j];
        }
      }
    return dec;
    }

void welcomeMsg() {}

void showMatrix(int key, string input) {
    for (int i = 0; i < (input.size() + (key - 1)) / key; ++i) {
        cout << ch2[i] << endl;
    }
}

string routeEncryption(string inputE, int key) {
    for (int i = 0; i < inputE.size() - 1; ++i) {
        if (inputE[i] == ' ') {
            inputE.erase(inputE.begin() + i);
        }
    }
    initializeMatrixE(key, inputE);
    showMatrix(key, inputE);
    cout << endl;
    string encrypt = "";
    int top = 0, bot = ((inputE.size() + (key - 1)) / key) - 1, left = 0, right = key - 1;
    while (top <= bot && left <= right) {
        // Traverse right column
        for (int i = top; i <= bot; ++i) {
            encrypt += ch2[i][right];
        }
        right--;
        // Traverse bottom row
        if (top <= bot) {
            for (int i = right; i >= left; --i) {
                encrypt += ch2[bot][i];
            }
            bot--;
        }
        // Traverse left column
        if (left <= right) {
            for (int i = bot; i >= top; --i) {
                encrypt += ch2[i][left];
            }
            left++;
        }
        // Traverse top row
        for (int i = left; i <= right; ++i) {
            encrypt += ch2[top][i];
        }
        top++;
    }
    return encrypt;
}

void cipher() {
    string inputD;
    getline(cin, inputD);
    int key;                            //erasing spaces yo
    cin >> key;
    for (int i = 0; i < inputD.size() - 1; ++i) {
        if (inputD[i] == ' ') {
            //inputD.erase(inputD.begin() + i);
            inputD.replace(i, 1, "");
        }
    }
    for (int i = 0; i < inputD.size(); ++i) {                   //upper case yo
        inputD[i] = toupper(inputD[i]);
    }

    int choice;
    cin>>choice;
    while (choice!=1 && choice!=2){
        cout<<"invalid choice, re-enter ur choice"<<endl;
        cin>>choice;
    }
    if (choice == 1){
        cout<<routeEncryption(inputD,key)<<endl;
    }else{
        cout<<routDecrypt(key, inputD)<<endl;
    }
}

int main() {
    //sss
    while (true)cipher();
    return 0;
}
