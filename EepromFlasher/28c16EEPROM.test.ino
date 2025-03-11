#include <AUnit.h>

test(intArrayLengthHappyFlow) {
  const int testArray[] = {1, 2, 4};
  assertEqual(intArrayLength(testArray), 3);
}

test(intArrayLengthEmptyArray) {
  const int testArray[] = {};
  assertEqual(intArrayLength(testArray), 0);
}
