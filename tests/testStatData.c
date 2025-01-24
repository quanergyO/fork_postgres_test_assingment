#include "../types/statData/StatData.h"

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(test_serialization_deserialization) {
    StatData testData[] = {
        { .id = 1, .count = 10, .cost = 100.5, .primary = 1, .mode = 3 },
        { .id = 2, .count = 5, .cost = 200.0, .primary = 0, .mode = 2 }
    };

    const char *filepath = "test_data.bin";
    StoreDump(filepath, testData, 2);

    size_t length;

    Result_t res = LoadDump(filepath, &length);
    ck_assert_int_eq(res.res1.error.errorEnum_, OK);
    
    StatData* loadedData = res.res1.result;

    ck_assert_int_eq(length, 2);
    ck_assert_int_eq(loadedData[0].id, 1);
    ck_assert_int_eq(loadedData[1].id, 2);
    ck_assert_float_eq(loadedData[0].cost, 100.5);
    ck_assert_float_eq(loadedData[1].cost, 200.0);

    free(loadedData);
} END_TEST

START_TEST(test_sorting) {
    StatData testData[] = {
        { .id = 1, .count = 10, .cost = 300.5, .primary = 1, .mode = 3 },
        { .id = 2, .count = 5, .cost = 100.0, .primary = 0, .mode = 2 }
    };

    SortDump(testData, 2);

    ck_assert_float_eq(testData[0].cost, 100.0);
    ck_assert_float_eq(testData[1].cost, 300.5);
} END_TEST

START_TEST(test_joining) {
    StatData data1[] = {
        { .id = 1, .count = 10, .cost = 100.5, .primary = 1, .mode = 3 },
        { .id = 2, .count = 5, .cost = 200.0, .primary = 0, .mode = 2 }
    };

    StatData data2[] = {
        { .id = 2, .count = 15, .cost = 300.0, .primary = 1, .mode = 1 },
        { .id = 3, .count = 20, .cost = 400.0, .primary = 1, .mode = 0 }
    };

    size_t resultLength;
    Result_t res = JoinDump(data1, 2, data2, 2, &resultLength);
    ck_assert_int_eq(res.res1.error.errorEnum_, OK);

    StatData *result = res.res1.result;


    ck_assert_int_eq(resultLength, 3);
    ck_assert_int_eq(result[0].id, 1);
    ck_assert_int_eq(result[1].id, 2);
    ck_assert_int_eq(result[2].id, 3);

    ck_assert_int_eq(result[1].count, 20);
    ck_assert_float_eq(result[1].cost, 500.0);
    ck_assert_int_eq(result[1].primary, 0);
    ck_assert_int_eq(result[1].mode, 2);

    free(result);
} END_TEST

Suite *statdata_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("StatData");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_serialization_deserialization);
    tcase_add_test(tc_core, test_sorting);
    tcase_add_test(tc_core, test_joining);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = statdata_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
