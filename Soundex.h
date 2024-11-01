#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define SOUND_EX_LENGTH 4

typedef struct {
    char letter;
    char code;
} SoundexMapping;

static const SoundexMapping soundexTable[] = {
    {'A', '0'}, {'B', '1'}, {'C', '2'}, {'D', '3'},
    {'E', '0'}, {'F', '1'}, {'G', '2'}, {'H', '0'},
    {'I', '0'}, {'J', '2'}, {'K', '2'}, {'L', '4'},
    {'M', '5'}, {'N', '5'}, {'O', '0'}, {'P', '1'},
    {'Q', '2'}, {'R', '6'}, {'S', '2'}, {'T', '3'},
    {'U', '0'}, {'V', '1'}, {'W', '0'}, {'X', '2'},
    {'Y', '0'}, {'Z', '2'}
};

static char getSoundexCodeForCharacter(char c) {
    c = toupper(c);
    for (int i = 0; i < sizeof(soundexTable) / sizeof(soundexTable[0]); i++) {
        if (soundexTable[i].letter == c) {
            return soundexTable[i].code;
        }
    }
    return '0'; // Return '0' for characters not in the mapping
}

static void initializeSoundex(char *soundex, char firstChar) {
    soundex[0] = toupper(firstChar);
    memset(soundex + 1, '0', SOUND_EX_LENGTH - 1);
    soundex[SOUND_EX_LENGTH] = '\0';
}

static void addPadding(char *soundex, int *sIndex) {
    while (*sIndex < SOUND_EX_LENGTH) {
        soundex[(*sIndex)++] = '0';
    }
    soundex[SOUND_EX_LENGTH] = '\0';
}

static void processSingleCharacter(char c, char *soundex, int *sIndex) {
    char code = getSoundexCodeForCharacter(c);

    // Early return if the code is '0' or if we reached Soundex length
    if (code == '0' || *sIndex >= SOUND_EX_LENGTH) {
        return;
    }

    // Check if the last added code is the same as the current one
    if (soundex[*sIndex - 1] != code) {
        soundex[(*sIndex)++] = code;
    }
}

static void processNameCharacters(const char *name, char *soundex, int *sIndex) {
    for (int i = 1; name[i] != '\0' && *sIndex < SOUND_EX_LENGTH; i++) {
        processSingleCharacter(name[i], soundex, sIndex);
    }
}

static int isInputInvalid(const char *name, char *soundex) {
    return !name || !soundex || name[0] == '\0';
}

static void generateSoundex(const char *name, char *soundex) {
    if (isInputInvalid(name, soundex)) {
        if (soundex) { // Only copy if soundex is not NULL
            strcpy(soundex, "0000");
        }
        return;
    }

    // Check if the first character is alphabetic
    if (!isalpha(name[0])) {
        strcpy(soundex, "0000");
        return;
    }

    initializeSoundex(soundex, name[0]);
    int sIndex = 1;
    processNameCharacters(name, soundex, &sIndex);
    addPadding(soundex, &sIndex);
}
