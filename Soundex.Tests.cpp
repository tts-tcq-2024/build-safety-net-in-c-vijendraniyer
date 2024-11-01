#include <gtest/gtest.h>
#include "Soundex.h"

// Test case for generating Soundex code for a standard name
TEST(SoundexTestsuite, GeneratesSoundexForStandardName) {
    char soundex[5];
    generateSoundex("Vijendran", soundex);
    ASSERT_STREQ(soundex, "V253");
}

// Test case for handling mixed case letters
TEST(SoundexTestsuite, GeneratesSoundexForMixedCaseName) {
    char soundex[5];
    generateSoundex("vIjeNDran", soundex);
    ASSERT_STREQ(soundex, "V253"); // Soundex should be case-insensitive
}

// Test case for handling empty strings
TEST(SoundexTestsuite, GeneratesSoundexForEmptyString) {
    char soundex[5];
    generateSoundex("", soundex);
    ASSERT_STREQ(soundex, "0000"); // Should return the default Soundex code
}

// Test case for handling a single alphabetic character
TEST(SoundexTestsuite, GeneratesSoundexForSingleCharacter) {
    char soundex[5];
    generateSoundex("A", soundex);
    ASSERT_STREQ(soundex, "A000"); // Should return the character followed by three zeros
}

// Test case for handling repeated consonants
TEST(SoundexTestsuite, GeneratesSoundexForRepeatedConsonants) {
    char soundex[5];
    generateSoundex("AABB", soundex);
    ASSERT_STREQ(soundex, "A100"); // Only the first unique consonant should be counted
}

// Test case for handling non-alphabetic characters mixed with letters
TEST(SoundexTestsuite, GeneratesSoundexForNonAlphabeticCharacters) {
    char soundex[5];
    generateSoundex("A1B2C", soundex);
    ASSERT_STREQ(soundex, "A120"); // Non-alphabetic characters should not affect the Soundex
}

// Test case for handling longer names
TEST(SoundexTestsuite, GeneratesSoundexForLongName) {
    char soundex[5];
    generateSoundex("Alexander", soundex);
    ASSERT_STREQ(soundex, "A425"); // Expected Soundex code for "Alexander"
}

// Test case for handling NULL input for Soundex array
TEST(SoundexTestsuite, HandlesNullSoundexArray) {
    generateSoundex("Alexander", NULL); // No assertion, checks for no crash
}

// Test case for handling NULL input for name
TEST(SoundexTestsuite, GeneratesSoundexForNullName) {
    char soundex[5];
    generateSoundex(NULL, soundex);
    ASSERT_STREQ(soundex, "0000"); // Should return the default Soundex code
}

// Test case for handling name with all non-alphabetic characters
TEST(SoundexTestsuite, GeneratesSoundexForAllNonAlphabetic) {
    char soundex[5];
    generateSoundex("1234", soundex);
    ASSERT_STREQ(soundex, "0000"); // Should return default Soundex code since there are no letters
}

// Test case for consonants replaced with appropriate digits
TEST(SoundexTestsuite, ReplacesConsonantsWithAppropriateDigits) {
    char soundex[5];
    generateSoundex("AX", soundex);
    ASSERT_STREQ(soundex, "A200"); // A corresponds to 0, X corresponds to 2
}
