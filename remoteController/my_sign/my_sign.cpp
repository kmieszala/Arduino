#include "my_sign.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

const uint32_t km[] = {
		0x4a253,
		0x662a5224,
		0xa24a2000
};

void addSign() {
  matrix.begin();
  matrix.loadFrame(km);
}
