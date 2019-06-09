#include <safe_lib.h>
#include <gtest/gtest.h>

#define MAX ( 128 )
#define LEN ( 128 )

static char   str1[LEN];
static char   str2[LEN];

static errno_t rc;
static int32_t ind;

// 1. Test for NULL destination check
TEST(strcpy_s, srcToNullDest) {
    rc = strcpy_s(NULL, LEN, str2);
    EXPECT_EQ(rc, ESNULLP);
}

// 2. Test for NULL source check
TEST(strcpy_s, nullSrcToDest) {
    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    rc = strcpy_s(str1, 5, NULL);
    EXPECT_EQ(rc, ESNULLP);
    EXPECT_EQ(str1[0], '\0');
}

// 3. Test for zero length destination
TEST(strcpy_s, zeroLengthDest) {
    rc = strcpy_s(str1, 0, str2);
    EXPECT_EQ(rc, ESZEROL);
}

// 4. Test for too large destination size
TEST(strcpy_s, largeSizeDest) {
    rc = strcpy_s(str1, (RSIZE_MAX_STR + 1), str2);
    EXPECT_EQ(rc, ESLEMAX);
}

// 5. Test copying the null string (zero length string)
//    into another existing string, and overwriting
TEST(strcpy_s, copyNullString) {
    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    str2[0] = '\0';

    rc = strcpy_s(str1, (LEN / 2), str2);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(str1[0], '\0');
}

// 6. Test copy the same string onto itself
TEST(strcpy_s, copyToItself) {
    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    rc = strcpy_s(str1, LEN, str1);
    EXPECT_EQ(rc, EOK);
}

// 7. Test for string overlap, destination < src, and
//    dest overlaps onto the src string, so a copy would
//    change the src string.
TEST(strcpy_s, sameStringOverlap) {
    strcpy(&str1[0], "keep it simple");

    rc = strcpy_s(&str1[0], LEN, &str1[5]);
    EXPECT_EQ(rc, ESOVRLP);
    EXPECT_EQ(str1[0], '\0');
}

// 8. Test for copying end of NULL string over existing string
TEST(strcpy_s, copyEndNullStroverExistStr) {
    strcpy(&str1[0], "keep it simple");
    str2[0] = '\0';

    rc = strcpy_s(str1, LEN, str2);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(str1[0], '\0');
}

// 9. Test for copying existing string over end of NULL string
TEST(strcpy_s, copyExistStrOverEndNullStr) {
    str1[0] = '\0';
    strcpy(&str2[0], "keep it simple");

    rc = strcpy_s(str1, LEN, str2);
    EXPECT_EQ(rc, EOK);

    /* be sure the results are the same as strcmp */
    ind = strcmp(str1, str2);
    EXPECT_EQ(ind, 0);
}


// 10. Test for accurate String copy over existing string
TEST(strcpy_s, copyAccurateStrOverExistStr) {
    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "keep it simple");

    rc = strcpy_s(str1, LEN, str2);
    EXPECT_EQ(rc, EOK);

    /* be sure the results are the same as strcmp */
    ind = strcmp(str1, str2);
    EXPECT_EQ(ind, 0);
}

// 11. Test for not enough space in destination (src > dest)
TEST(strcpy_s, notEnoughSpaceDest_1) {
    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "keep it simple");

    rc = strcpy_s(str1, 1, str2);
    EXPECT_EQ(rc, ESNOSPC);
    EXPECT_EQ(str1[0], '\0');
}

// 12. Test for not enough space in destination (dest > src)
TEST(strcpy_s, notEnoughSpaceDest_2) {
    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "keep it simple");

    rc = strcpy_s(str2, 1, str1);
    EXPECT_EQ(rc, ESNOSPC);
    EXPECT_EQ(str2[0], '\0');
}

// 13. Test for just enough space in destination
TEST(strcpy_s, EnoughSpaceDest) {
    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "it");

    rc = strcpy_s(str1, 3, str2);
    EXPECT_EQ(rc, EOK);

    /* be sure the results are the same as strcmp */
    ind = strcmp(str1, str2);
    EXPECT_EQ(ind, 0);
}

// 14. Test copy short string over long string
TEST(strcpy_s, copyShortStrOverLongStr) {
    strcpy(str1, "qq12345weqeqeqeq");
    strcpy(str2, "it");

    rc = strcpy_s(str1, 10, str2);
    EXPECT_EQ(rc, EOK);

    /* be sure the results are the same as strcpy */
    ind = strcmp(str1, str2);
    EXPECT_EQ(ind, 0);

}