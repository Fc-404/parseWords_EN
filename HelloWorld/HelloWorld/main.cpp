//
//  main.cpp
//  HelloWorld
//
//  Created by Mao on 2020/11/22.
//

#include <iostream>

bool setStr(char* array, const char* str);
bool strJoint(const char* str1, const char* str2, char* str);

struct WORD {
    char word[24];
    WORD* next;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std;
    
    /**
     hint of input file path;
     */
    char filePath[24];
    
    cout << "Hello Mao!\n formatting words\n" << endl;
    cout << "Please input file path: ";
    
    FILE* file = NULL;
    
    while (!file) {
        cin >> filePath;
        file = fopen(filePath, "r");
        if (!file)
            cout << "non file...\nPlease again: ";
    }
    
    /**
     read file in words, and addition at linked;
     */
    WORD* head = (WORD*) malloc(sizeof(WORD)), * temp = head;
    setStr(head->word, "head");
    head->next = NULL;
    
    char ch;
    char str[24];
    short indexStr = 0, sign = 0;;
    while ( ( ch = fgetc(file) ) != EOF ) {
        if ( (ch >= 65 && ch <= 90 ) ||
             (ch >= 97 && ch <= 122) ) {
            sign = 1;
            str[indexStr] = ch;
            ++indexStr;
            str[indexStr] = '\0';
        } else if (sign == 1) {
            sign = 0;
            indexStr = 0;
            WORD* node = (WORD*) malloc(sizeof(WORD));
            setStr(node->word, str);
            node->next = NULL;
            temp->next = node;
            temp = node;
        }
    }
    fclose(file);
    
    /**
     words in linked, output to file;
     */
    char fileNew[48];
    strJoint(filePath, ".new", fileNew);
    FILE* newFile = fopen(fileNew, "w");
    
    temp = head;
    while (temp->next){
        temp = temp->next;
        for (short i = 0; i < 24; ++i){
            if (temp->word[i] == '\0')
                break;
            fputc(temp->word[i], newFile);
        }
        fputc('\n', newFile);
    }
    
    fclose(newFile);
    
    return 0;
}

bool setStr(char* array, const char* str){
    short strLength = strlen(str);
    for (short i = 0; i < strLength; ++i, array[i] = '\0')
        array[i] = str[i];
    
    return true;
}

bool strJoint(const char* str1, const char* str2, char* str){
    short index = 0, str1L = strlen(str1), str2L = strlen(str2);
    
    if (str1L + str2L > 48)
        return false;
    
    for (short i = 0; i < str1L; ++i, str[i] = '\0', index = i)
        str[i] = str1[i];
    
    for (short i = 0; i < str2L; ++i, str[i + index] = '\0')
        str[i + index] = str2[i];
    
    return true;
}
