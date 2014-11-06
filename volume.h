#include <Arduino.h>
#include <inttypes.h>

#include <pinMap.h>


#define REG_VOL  0
#define REG_LOW  1
#define REG_HIGH 2

// Регулятор хранит в себе все, что нужно для работы с регулаторами
class Regulator {

  public:
  
    void init(int analogInput)
    {
    	_analogInput = analogInput;
    	_value = map(analogRead(analogInput), 0, 1023, 0, 127);
    }
    
    void setAInValue(int analogValue)
    {
    	_analogValue = analogValue;
    	_value = map(analogValue, 0, 1023, 0, 127);
    }

    void setValue(uint8_t value)
    {
    	_value = value;
    }

    uint8_t getValue()
    {
    	return _value;
    }

    int getAInValue()
    {
    	return _analogValue;
    }

    int readAInValue()
    {
    	return analogRead(_analogInput);
    }

    bool analogInChanged(uint16_t treshold)
    {
    	bool result = false;
    	int aiDiff = abs(_analogValue - analogRead(_analogInput));
    	if (aiDiff > treshold)
    		result = true;

    	return result;
    }
  
  private:
  
    uint8_t  _analogInput;
    uint8_t  _value;
    int _analogValue;
};


Regulator rVol, rLow, rhigh;

void regulatorsInit()
{
	rVol.init(VOLUME_POT);
	rLow.init(LOW_POT);
	rhigh.init(HIGH_POT);
}

void regulatorsUpdate()
{
	rVol.setAInValue(VOLUME_POT);
	rLow.setAInValue(LOW_POT);
	rhigh.setAInValue(HIGH_POT);
}

// TODO
bool regulatorsCheckChange(int treshold)
{
	bool result = false;


	if (rVol.analogInChanged())
		rVol.setAInValue(rVol.readAInValue());



}