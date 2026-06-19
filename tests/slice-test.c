#include "assert.h"
#include "log.h"
#include "setjmp.h"
#include "zslice.h"
#include <unistd.h>

int get_el_from_slice(const Slice *s, size_t i);

static int rslt;

static int expected_code;
static int should_exit;
static jmp_buf jump_env;

static int done;
static int num_tests;
static int test_passed;

void enreachSlice(Slice *slice) {
  int values[] = {1, 2, 3, 4, 5, 6};
  APPEND_ARR(slice, values);
}

void TestStart(char *name) {
  num_tests++;
  rslt = 1;
  LOG(LOG_INFO, "-- Testing %s ...", name);
}

void TestEnd() {
  if (rslt)
    test_passed++;
  LOG(LOG_INFO, "%s\n", rslt ? "success" : "fail");
}

void exit(int code) {
  if (!done) {
    assert(should_exit == 1);
    assert(expected_code == code);
    longjmp(jump_env, 1);
  } else {
    _exit(code);
  }
}

void test_normal(void) {
  TestStart("test_normal");
  should_exit = 0;
  if (setjmp(jump_env) == 0) {
    Slice *s = SNew(5, sizeof(int));
    int v = get_el_from_slice(s, 2);
    if (v != 0)
      rslt = 0;
  } else {
    rslt = 0;
  }
  TestEnd();
}

void test_out_of_bounds(void) {
  TestStart("test_out_of_bounds");
  should_exit = 1;
  expected_code = 1;
  if (setjmp(jump_env) == 0) {
    Slice *s = SNew(4, sizeof(int));
    get_el_from_slice(s, 999);
    rslt = 0;
  }
  TestEnd();
}

int main(void) {
  test_normal();
  test_out_of_bounds();
  done = 1;
  LOG(LOG_INFO, "passed %d/%d", test_passed, num_tests);
  return test_passed == num_tests ? 0 : 1;
}
