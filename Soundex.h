#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <ctype.h>
#include <string.h>

char getSoundexCode(char c) {
    static const char soundexTable[26] = {
        '0', '1', '2', '3', '0', '1', '2', '0', '0', '1', '2', '0', '5', '0', '0', '1', '0', '2', '0', '3', '0', '1', '0', '2', '0', '2'
    };

    c = toupper(c); // Convert character to uppercase
    return (c >= 'A' && c <= 'Z') ? soundexTable[c - 'A'] : '0';
}

// Initialization function
void initializeSoundex(char *soundex, char firstChar) {
    soundex[0] = toupper(firstChar);
    memset(soundex + 1, '0', 3); // Set the rest of the soundex string to '0'
    soundex[4] = '\0';
}

// Processing function
void processName(const char *name, char *soundex) {
    int sIndex = 1, cIndex = 1;

    for (cIndex = 1; name[cIndex] && sIndex < 4; cIndex++) {
        char code = getSoundexCode(name[cIndex]);
        if (code != '0' && code != soundex[sIndex - 1]) {
            soundex[sIndex++] = code;
        }
    }
}

void generateSoundex(const char *name, char *soundex) {
    if (name == NULL || soundex == NULL) return; // Handle NULL inputs
    
    initializeSoundex(soundex, name[0]);
    processName(name, soundex);
}

#endif // SOUNDEX_H
