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
    if (soundex) { // Check if soundex is not NULL
        soundex[0] = toupper(firstChar);
        memset(soundex + 1, '0', SOUND_EX_LENGTH - 1);
        soundex[SOUND_EX_LENGTH] = '\0';
    }
}

static void addPadding(char *soundex, int *sIndex) {
    if (soundex) { // Check if soundex is not NULL
        while (*sIndex < SOUND_EX_LENGTH) {
            soundex[(*sIndex)++] = '0';
        }
        soundex[SOUND_EX_LENGTH] = '\0';
    }
}

static int canAddCode(char code, char *soundex, int *sIndex) {
    return code != '0' && *sIndex < SOUND_EX_LENGTH && soundex[*sIndex - 1] != code;
}

static void processSingleCharacter(char c, char *soundex, int *sIndex) {
    char code = getSoundexCodeForCharacter(c);
    if (canAddCode(code, soundex, sIndex)) {
        soundex[(*sIndex)++] = code;
    }
}

static int isInputInvalid(const char *name) {
    return !name || name[0] == '\0' || !isalpha(name[0]);
}

static void handleInvalidInput(char *soundex) {
    // If soundex is NULL, do nothing
    if (!soundex) return;

    strcpy(soundex, "0000");
}

static void processNameCharacters(const char *name, char *soundex, int *sIndex) {
    for (int i = 1; name[i] != '\0' && *sIndex < SOUND_EX_LENGTH; i++) {
        processSingleCharacter(name[i], soundex, sIndex);
    }
}

static void generateSoundex(const char *name, char *soundex) {
    if (isInputInvalid(name)) {
        handleInvalidInput(soundex);
        return;
    }

    initializeSoundex(soundex, name[0]);
    int sIndex = 1;
    processNameCharacters(name, soundex, &sIndex);
    addPadding(soundex, &sIndex);
}
