#include <safe_lib.h>
#include <gtest/gtest.h>

#define LEN   ( 128 )
#define SHORT_LEN  ( 5 )

static char   str1[LEN];
static char   str2[LEN];

static errno_t rc;
static char *sub; 
static char *std_sub; 
static rsize_t len1;
static rsize_t len2;

// 1. Test for NULL destination check
TEST(strstr_s, nulldest) {
    rc = strstr_s(NULL, LEN, str2, LEN, &sub);
    EXPECT_EQ(rc, ESNULLP);
    EXPECT_FALSE(sub);
}

// 2. Test for NULL source check
TEST(strstr_s, nullSrc) {
    rc = strstr_s(str1, LEN, NULL, LEN, &sub);
    EXPECT_EQ(rc, ESNULLP);
    EXPECT_FALSE(sub);
}

// 3. Test for NULL substring
TEST(strstr_s, nullSubstring) {
    rc = strstr_s(str1, LEN, str2, LEN, NULL);
    EXPECT_EQ(rc, ESNULLP);
}

// 4. Test for zero length destination
TEST(strstr_s, zeroLengthDest) {
    rc = strstr_s(str1, 0, str2, LEN, &sub);
    EXPECT_EQ(rc, ESZEROL);
    EXPECT_FALSE(sub);
}

// 5. Test for too large destination size
TEST(strstr_s, largeSizeDest) {
    rc = strstr_s(str1, RSIZE_MAX_STR + 1, str2, LEN, &sub);
    EXPECT_EQ(rc, ESLEMAX);
    EXPECT_FALSE(sub);
}


// 6. Test for zero length source
TEST(strstr_s, zeroLengthSrc) {
    rc = strstr_s(str1, LEN, str2, 0, &sub);
    EXPECT_EQ(rc, ESZEROL);
    EXPECT_FALSE(sub);
}

// 7. Test for too large source size
TEST(strstr_s, largeSizeSrc) {
    rc = strstr_s(str1, LEN, str2, RSIZE_MAX_STR + 1, &sub);
    EXPECT_EQ(rc, ESLEMAX);
    EXPECT_FALSE(sub);
}

// 8. Test for searching both destination and source are 
//    end of NULL string
TEST(strstr_s, sameDestAndSrc_1) {
    *str1 = '\0';
    *str2 = '\0';

    rc = strstr_s(str1, LEN, str2, LEN, &sub);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(sub, str1);
}

// 9. Test for the string to search for is Null character 
TEST(strstr_s, searchNULL) {
    strcpy(str1, "keep it all together");
    *str2 = '\0';

    rc = strstr_s(str1, LEN, str2, LEN, &sub);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(sub, str1);
}

// 10. Test for searching substring at beginning
TEST(strstr_s, substringAtBegin) {
    strcpy(str1, "keep it all together");
    strcpy(str2, "kee");

    rc = strstr_s(str1, LEN, str2, LEN, &sub);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(sub, &str1[0]);
}

// 11. Test for searching substring in the middle - left
TEST(strstr_s, substringInMidLeft) {
    strcpy(str1, "keep it all together");
    strcpy(str2, "eep it");

    rc = strstr_s(str1, LEN, str2, LEN, &sub);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(sub, &str1[1]);
}

// 12. Test for searching substring in the middle - right
TEST(strstr_s, substringInMidRight) {
    strcpy(str1, "keep it all together");
    strcpy(str2, "ethe");

    rc = strstr_s(str1, LEN, str2, LEN, &sub);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(sub, &str1[15]);
}

// 13. Test for just right length 1
TEST(strstr_s, justRightLength_1) {
    strcpy(str1, "keep it all together");
    strcpy(str2, "he");

    len1 = strlen(str1);
    len2 = strlen(str2);

    rc = strstr_s(str1, len1, str2, len2, &sub);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(sub, &str1[17]);
}

// 14. Test for just right length 2
TEST(strstr_s, justRightLength_2) {
    strcpy(str1, "keep it all together");
    strcpy(str2, "er");

    len1 = strlen(str1);
    len2 = strlen(str2);

    rc = strstr_s(str1, len1, str2, len2, &sub);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(sub, &str1[18]);
}

// 15. Test for searching for nothing 1
TEST(strstr_s, searchingForNothing_1) {
    strcpy(str1, "keep it all together");
    strcpy(str2, "it all");

    rc = strstr_s(str1, 3, str2, LEN, &sub);
    EXPECT_EQ(rc, ESNOTFND);
}

// 16. Test for searching for nothing 2
TEST(strstr_s, searchingForNothing_2) {
    strcpy(str1, "keep it all together");
    strcpy(str2, "1234");

    len1 = strlen(str1);

    rc = strstr_s(str1, len1, str2, LEN, &sub);
    EXPECT_EQ(rc, ESNOTFND);
    EXPECT_EQ(sub, nullptr);
}

// 17. Test for comparing to legacy
TEST(strstr_s, compareToLegacy) {
    strcpy(str1, "keep it all together");
    strcpy(str2, "eep");

    rc = strstr_s(str1, LEN, str2, LEN, &sub);
    EXPECT_EQ(rc, EOK);

    std_sub = strstr(str1, str2);
    EXPECT_EQ(sub, std_sub);
}

