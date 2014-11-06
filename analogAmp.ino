
// Здесь назначаем пины
#include "pinMap.h"
//Здесь работаем с цифровыми потенциометрами
#include "digiPot.h"
//Здесь работаем с громкостью
#include "volume.h"

//struct reg

//int a = IR_PIN;

void setup()
{

	regulatorsInit();
	digiPotInit(rVol.value(), rLow.value(), rHigh.value());

}

void loop()
{
	// если хоть одна из крутилок изменилась - мы обновим все потенциометры
	if (regulatorsChanged())
		setAllVolumes(rVol.value(), rLow.value(), rHigh.value());
}
