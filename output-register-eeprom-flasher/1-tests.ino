#include <AUnit.h>

test(intArrayLengthHappyFlow) {
  const int testArray[] = {1, 2, 4};
  assertEqual(intArrayLength(testArray), 3);
}

test(intArrayLengthEmptyArray) {
  const int testArray[] = {};
  assertEqual(intArrayLength(testArray), 0);
}

test(getBase10DigitsDigitsOrder) {
  const int number = 123;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hunderds,  1);
  assertEqual(digits.tens,      2);
  assertEqual(digits.units,     3);
}

test(getBase10Digits4Digits) {
  const int number = 5678;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hunderds,  6);
  assertEqual(digits.tens,      7);
  assertEqual(digits.units,     8);
}

test(getBase10Digits3Digits) {
  const int number = 125;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hunderds,  1);
  assertEqual(digits.tens,      2);
  assertEqual(digits.units,     5);
}

test(getBase10Digits2Digits) {
  const int number = 54;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hunderds,  0);
  assertEqual(digits.tens,      5);
  assertEqual(digits.units,     4);
}

test(getBase10Digits1Digits) {
  const int number = 6;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hunderds,  0);
  assertEqual(digits.tens,      0);
  assertEqual(digits.units,     6);
}

test(getBase10DigitsZero) {
  const int number = 0;
  Base10Digits digits = getBase10Digits(number);
  assertEqual(digits.hunderds,  0);
  assertEqual(digits.tens,      0);
  assertEqual(digits.units,     0);
}
