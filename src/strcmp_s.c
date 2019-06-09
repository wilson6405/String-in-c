#include <safe_lib.h>
#include <gtest/gtest.h>

#define LEN   ( 128 )
#define SHORT_LEN  ( 5 )

static char   str1[LEN];
static char   str2[LEN];

static errno_t rc;
static int32_t ind;
static int std_ind;


// 1. Test for NULL destination check
TEST(strcmp_s, srcToNullDest) {
    rc = strcmp_s(NULL, LEN, str2, &ind);
    EXPECT_EQ(rc, ESNULLP);
    EXPECT_EQ(ind, 0);
}

// 2. Test for NULL source check
TEST(strcmp_s, nullSrcToDest) {
    rc = strcmp_s(str1, LEN, NULL, &ind);
    EXPECT_EQ(rc, ESNULLP);
    EXPECT_EQ(ind, 0);
}

// 3. Test for NULL indicator check
TEST(strcmp_s, nullIndicator) {
    rc = strcmp_s(str1, LEN, str2, NULL);
    EXPECT_EQ(rc, ESNULLP);
}

// 4. Test for zero length destination
TEST(strcmp_s, zeroLengthDest) {
    rc = strcmp_s(str1, 0, str2, &ind);
    EXPECT_EQ(rc, ESZEROL);
    EXPECT_EQ(ind, 0);
}

// 5. Test for too large destination size
TEST(strcmp_s, largeSizeDest) {
    rc = strcmp_s(str1, RSIZE_MAX_STR + 1, str2, &ind);
    EXPECT_EQ(rc, ESLEMAX);
    EXPECT_EQ(ind, 0);
}

// 6. Test for comparing both destination and source are 
//    end of NULL string
TEST(strcmp_s, sameDestAndSrc_1) {
    str1[0] = '\0';
    str2[0] = '\0';

    rc = strcmp_s(str1, LEN, str2, &ind);
    EXPECT_EQ(rc, EOK);

    std_ind = strcmp(str1, str2);
    EXPECT_EQ(ind, std_ind);
}

// 7. Test for comparing both destination and source are 
//    the same.
TEST(strcmp_s, sameDestAndSrc_2) {
    strcpy (str1, "keep it simple");
    strcpy (str2, "keep it simple");

    rc = strcmp_s(str1, SHORT_LEN, str2, &ind);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(ind, 0);
}

// 8. Test for comparing different string but length the same 1.
TEST(strcmp_s, cmpDiffString_1) {
    /*   K - k ==  -32  */
    strcpy (str1, "Keep it simple");
    strcpy (str2, "keep it simple");

    rc = strcmp_s(str1, LEN, str2, &ind);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(ind, (-32));

    std_ind = strcmp(str1, str2);
    EXPECT_EQ(ind, std_ind);
}

// 9. Test for comaring different string but length the same 2.
TEST(strcmp_s, cmpDiffString_2) {
    /*   p - P ==  32  */
    strcpy (str1, "keep it simple");
    strcpy (str2, "keeP it simple");

    rc = strcmp_s(str1, LEN, str2, &ind);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(ind, 32);

    std_ind = strcmp(str1, str2);
    EXPECT_EQ(ind, std_ind);
}

// 10. Test for comparing string with itself.
TEST(strcmp_s, cmpToItself) {
    strcpy (str1, "keep it simple");

    rc = strcmp_s(str1, LEN, str1, &ind);
    EXPECT_EQ(rc, EOK);
    EXPECT_EQ(ind, 0);

    std_ind = strcmp(str1, str1);
    EXPECT_EQ(ind, std_ind);
}

// 11. Test for comparing different content and length string 1.
TEST(strcmp_s, cmpDiffLengthStr_1) {
    strcpy (str1, "keep it simplified");
    strcpy (str2, "keep it simple");

    rc = strcmp_s(str1, LEN, str2, &ind);
    EXPECT_EQ(rc, EOK);
    EXPECT_GE(ind, 0);

    std_ind = strcmp(str1, str2);
    EXPECT_EQ(ind, std_ind);
}

// 12. Test for comparing different content and length string 2.
TEST(strcmp_s, cmpDiffLengthStr_2) {
    strcpy (str1, "keep it simple");
    strcpy (str2, "keep it simplified");

    rc = strcmp_s(str1, LEN, str2, &ind);
    EXPECT_EQ(rc, EOK);
    EXPECT_LE(ind, 0);

    std_ind = strcmp(str1, str2);
    EXPECT_EQ(ind, std_ind);
}