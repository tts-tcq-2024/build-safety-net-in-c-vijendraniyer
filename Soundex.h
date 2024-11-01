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
    return '0';
}

static void initializeSoundex(char *soundex, char firstChar) {
    soundex[0] = toupper(firstChar);
    memset(soundex + 1, '0', SOUND_EX_LENGTH - 1);
    soundex[SOUND_EX_LENGTH] = '\0';
}

static int canAddCode(char code, char prevCode, int sIndex) {
    return code != '0' && code != prevCode && sIndex < SOUND_EX_LENGTH;
}

static void addPadding(char *soundex, int *sIndex) {
    while (*sIndex < SOUND_EX_LENGTH) {
        soundex[(*sIndex)++] = '0';
    }
    soundex[SOUND_EX_LENGTH] = '\0';
}

static void processSingleCharacter(char c, char *soundex, int *sIndex, char *prevCode) {
    char code = getSoundexCodeForCharacter(c);
    if (canAddCode(code, *prevCode, *sIndex)) {
        soundex[(*sIndex)++] = code;
    }
    *prevCode = code;
}

static void processNameCharacters(const char *name, char *soundex, int *sIndex) {
    char prevCode = '0';
    for (int i = 1; name[i] != '\0' && *sIndex < SOUND_EX_LENGTH; i++) {
        processSingleCharacter(name[i], soundex, sIndex, &prevCode);
    }
}

static void generateSoundex(const char *name, char *soundex) {
    if (!name || !soundex) {
        strcpy(soundex, "0000");
        return;
    }

    initializeSoundex(soundex, name[0]);
    int sIndex = 1;
    processNameCharacters(name, soundex, &sIndex);
    addPadding(soundex, &sIndex);
}
