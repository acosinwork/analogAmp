#include <Arduino.h>
#include <inttypes.h>

#include "pinMap.h"

#define REG_VOL  0
#define REG_LOW  1
#define REG_HIGH 2

// Регулятор хранит в себе все, что нужно для работы с регулаторами
class Regulator {

  public:
  
    void init(int analogInput)
    {
    	_analogInput = analogInput;
    	_value = map(analogRead(_analogInput), 0, 1023, 0, 127);
    }
    

    uint8_t value()
    {
    	return _value;
    }

    uint8_t readAInValue()
    {
    	return _value = map(analogRead(_analogInput), 0, 1023, 0, 127);
    }

    bool analogInChanged()
    {
    	return this->value() != this->readAInValue();
    }
  
  private:
  
    uint8_t  _analogInput;
    uint8_t  _value;
    int _analogValue;
};


Regulator rVol, rLow, rHigh;

void regulatorsInit()
{
	rVol.init(VOLUME_POT);
	rLow.init(LOW_POT);
	rHigh.init(HIGH_POT);
}

bool regulatorsChanged()
{
    bool needChange = false;

    needChange |= rVol.analogInChanged();
    needChange |= rLow.analogInChanged();
    needChange |= rHigh.analogInChanged();

    return needChange;
}

