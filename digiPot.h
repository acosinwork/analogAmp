#include <Arduino.h>
// У нас 7-битные потенциометры
#define D_POT_BITS    7

// Количество цифровых потенциометров
#define D_POT_COUNT   6

// Громкость левый-правый
#define VOLUME_LEFT   0
#define VOLUME_RIGHT  1

#define LOW_LEFT      2
#define LOW_RIGHT     3

#define HIGH_LEFT     4
#define HIGH_RIGHT    5

// Здесь храятся все настройки громкостей 
byte dPotValues[D_POT_COUNT];

// Шлём данные одного потенциометра
void sendPotData(byte data)
{

  for (int i = 0; i < D_POT_BITS; ++i) {
    digitalWrite(D_POT_SCK, LOW);

    digitalWrite(D_POT_MOSI, bitRead(data, i));

    digitalWrite(D_POT_SCK, HIGH);    
  }

}

// Обновляем показания всех потенциометров
void dPotUpdate()
{
  digitalWrite(D_POT_CS, LOW);
  
  for (int i = 0; i < D_POT_COUNT; ++i)
    sendPotData(dPotValues[i]);
  
  digitalWrite(D_POT_CS, HIGH);
}

// Устанавлиаем громкость
void setVolume(byte value)
{
  dPotValues[VOLUME_LEFT] = value;
  dPotValues[VOLUME_RIGHT] = value;
  dPotUpdate();
}

// Устанавлиаем низкие частоты
void setLow(byte value)
{
  dPotValues[LOW_LEFT] = value;
  dPotValues[LOW_RIGHT] = value;
  dPotUpdate();
}
// Устанавлиаем высокие частоты
void setHigh(byte value)
{
  dPotValues[HIGH_LEFT] = value;
  dPotValues[HIGH_RIGHT] = value;
  dPotUpdate();
}
// устанвливаем все настойки потнциометров
void setAllVolumes(byte vol, byte low, byte high)
{
  dPotValues[VOLUME_LEFT] = vol;
  dPotValues[VOLUME_RIGHT] = vol;
  
  dPotValues[LOW_LEFT] = low;
  dPotValues[LOW_RIGHT] = low;
  
  dPotValues[HIGH_LEFT] = high;
  dPotValues[HIGH_RIGHT] = high;
  
  dPotUpdate();
}

// Это нужнобудет вызать в setup() 
// и передать сюда значения с потенциометров-крутилок
void digiPotInit(byte vol, byte low, byte high)
{
  pinMode(D_POT_MOSI, OUTPUT);
  pinMode(D_POT_SCK, OUTPUT);
  pinMode(D_POT_CS, OUTPUT);

  setAllVolumes(vol, low, high);
}

