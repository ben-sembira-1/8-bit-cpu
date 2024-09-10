const int ADDRESS_PINS[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int IO_PINS[] = {A0, A1, A2, A3, A4, A5, A6, A7};
const int CHIP_ENABLE_PIN = 11;
const int OUTPUT_ENABLE_PIN = 12;
const int WRITE_ENABLE_PIN = 13;

int intArrayLength(int[] array) {
  return (sizeof(array) / sizeof(int))
}

void setPinsToModeOutput(int[] pins) {
  for (int i = 0; i < intArrayLength(pins); i++) {
    pinMode(pins[i], OUTPUT)
  }
}

const int SEVEN_SEGMENT_DISPLAY_DIGITS[10][8] = {
  //  A B C D E F G RDP
  {   1,1,1,1,1,1,0, 0  },
  {   0,1,1,0,0,0,0, 0  },
  {   1,1,0,1,1,0,1, 0  },
  {   1,1,1,1,0,0,1, 0  },
  {   0,1,1,0,0,1,1, 0  },
  {   1,0,1,1,0,1,1, 0  },
  {   1,0,1,1,1,1,1, 0  },
  {   1,1,1,0,0,0,0, 0  },
  {   1,1,1,1,1,1,1, 0  },
  {   1,1,1,0,0,1,1, 0  },
}

void setup() {
  setPinsToModeOutput(ADDRESS_PINS)
  setPinsToModeOutput(IO_INPUTS)
  setPinsToModeOutput([CHIP_ENABLE_PIN, OUTPUT_ENABLE_PIN, WRITE_ENABLE_PIN])

}

void loop() {
  // put your main code here, to run repeatedly:

}
