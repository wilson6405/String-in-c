#include <safe_lib.h>
#include <gtest/gtest.h>

#define LEN   ( 128 )

static char   str1[LEN];
static char   str2[LEN];

static errno_t rc;
static int32_t ind;
static int32_t len1;
static int32_t len2;
static int32_t len3;

// 1. Test for NULL destination check
TEST(strcat_s, nulldest) {
    rc = strcat_s(NULL, LEN, str2);
    EXPECT_EQ(rc, ESNULLP);
}


// 2. Test for NULL source check
TEST(strcat_s, nullSrc) {
    rc = strcat_s(str1, LEN, NULL);
    EXPECT_EQ(rc, ESNULLP);
}

// 3. Test for zero length destination
TEST(strcat_s, zeroLengthDest) {
    rc = strcat_s(str1, 0, str2);
    EXPECT_EQ(rc, ESZEROL);
}

// 4. Test for too large destination size
TEST(strcat_s, largeSizeDest) {
    rc = strcat_s(str1, (RSIZE_MAX_STR + 1), str2);
    EXPECT_EQ(rc, ESLEMAX);
}

// 5. Test for destination is unterminated string 1.
TEST(strcat_s, unterminatedString_1) {
    strcpy(str1, "aaaaaaaaaa");
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 1, str2);
    EXPECT_EQ(rc, ESUNTERM);
    EXPECT_EQ(str1[0], '\0');
}

// 6. Test for destination is unterminated string 2.
TEST(strcat_s, unterminatedString_2) {
    strcpy(str1, "aaaaaaaaaa");
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 2, str2);
    EXPECT_EQ(rc, ESUNTERM);
    EXPECT_EQ(str1[0], '\0');
}

// 7. Test for destination maximum length over 
//    destination string length.
TEST(strcat_s, destMaxLenOverDestStrLen) {
    strcpy(&str1[0], "aaaaaaaaaa");
    strcpy(&str2[0], "keep it simple");

    len1 = strlen(str1);
    len2 = strlen(str2);

    rc = strcat_s(str1, 50, str2);
    EXPECT_EQ(rc, EOK);

    len3 = strlen(str1);
    EXPECT_EQ(len3, (len1 + len2));
}

// 8. Test for not enough space in destination 1
//    and null dest
TEST(strcat_s, notEnoughSpaceDestWithNullDest_1) {
    str1[0] = '\0';
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 1, str2);
    EXPECT_EQ(rc, ESNOSPC);
    EXPECT_EQ(str1[0], '\0');
}

// 9. Test for not enough space in destination 2
//    and null dest
TEST(strcat_s, notEnoughSpaceDestWithNullDest_2) {
    str1[0] = '\0';
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 2, str2);
    EXPECT_EQ(rc, ESNOSPC);
    EXPECT_EQ(str1[0], '\0');
}

// 10. Test for enough space in destination 1
//     and null dest
TEST(strcat_s, enoughSpaceDestWithNullDest_1) {
    str1[0] = '\0';
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 20, str2);
    EXPECT_EQ(rc, EOK);

    ind = strcmp(str1, str2);
    EXPECT_EQ(ind, 0);
}

// 11. Test for enough space in destination 2
//     and null dest
TEST(strcat_s, enoughSpaceDestWithNullDest_2) {
    str1[0] = '\0';
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, LEN, str2);
    EXPECT_EQ(rc, EOK);

    ind = strcmp(str1, str2);
    EXPECT_EQ(ind, 0);
}

// 12. Test for both destination and source are 
//     end of NULL string
TEST(strcat_s, sameDestAndSrc) {
    str1[0] = '\0';
    str2[0] = '\0';

    rc = strcat_s(str1, LEN, str2);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(str1[0], '\0');
}


// 13. Test for enough space in destination 1
TEST(strcat_s, concatenateDestAndSrc_1) {
    strcpy(str1, "qqweqq");
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, LEN, str2);
    EXPECT_EQ(rc, EOK);

    ind = strcmp(str1, "qqweqqkeep it simple");
    EXPECT_EQ(ind, 0);
}

// 14. Test for enough space in destination 2
TEST(strcat_s, enoughSpaceDest_2) {
    strcpy(str1, "1234");
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 52, str2);
    EXPECT_EQ(rc, EOK);

    ind = strcmp(str1, "1234keep it simple");
    EXPECT_EQ(ind, 0);
}

// 15. Test for enough space in destination 3
TEST(strcat_s, enoughSpaceDest_3) {
    strcpy(str2, "123");
    strcpy(str1, "keep it simple");

    rc = strcat_s(str2, 31, &str1[0]);
    EXPECT_EQ(rc, EOK);

    ind = strcmp(str2, "123keep it simple");
    EXPECT_EQ(ind, 0);
}

// 16. Test for not enough space in destination.
TEST(strcat_s, notEnoughSpaceDest) {
    strcpy(str1, "1234");
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 12, str2);
    EXPECT_EQ(rc, ESNOSPC);
}

// 17. Test for string overlap 1
TEST(strcat_s, sameStringOverlap_1) {
    strcpy(str1, "12345678901234567890");

    rc = strcat_s(str1, 8, &str1[7]);
    EXPECT_EQ(rc, ESOVRLP);
    EXPECT_EQ(str1[0], '\0');
}

// 18. Test for string overlap 2
TEST(strcat_s, sameStringOverlap_2) {
    strcpy(str1, "123456789");

    rc = strcat_s(str1, 9, &str1[8]);
    EXPECT_EQ(rc, ESOVRLP);
    EXPECT_EQ(str1[0], '\0');
}

// 19. Test for exactly space in destination
TEST(strcat_s, exactSpaceDest) {
    strcpy(str2, "1234");
    strcpy(str1, "56789");

    rc = strcat_s(str2, 10, str1);
    EXPECT_EQ(rc, EOK);

    ind = strcmp(str2, "123456789");
    EXPECT_EQ(ind, 0);
}