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

// TEST(strstr_s, ) {

// }

// TEST(strstr_s, ) {

// }

// TEST(strstr_s, ) {

// }

// TEST(strstr_s, ) {

// }

// TEST(strstr_s, ) {

// }

// TEST(strstr_s, ) {

// }

// TEST(strstr_s, ) {

// }

// TEST(strstr_s, ) {

// }

// TEST(strstr_s, ) {

// }

// TEST(strstr_s, ) {

// }

