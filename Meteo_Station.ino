#include <DS3231.h>
#include <Wire.h>
// Видеообзоры и уроки работы с ARDUINO на YouTube-канале IOMOIO: https://www.youtube.com/channel/UCmNXABaTjX_iKH28TTJpiqA

#include "Adafruit_GFX.h"     // Библиотека обработчика графики
#include "Adafruit_ILI9341.h" // Программные драйвера для дисплеев ILI9341
//#include "URTouch.h"          // Библиотека для работы с сенсорным экраном

#include "SPI.h"
#include "SdFat.h"                // SD card & FAT filesystem library
#include "Adafruit_ImageReader.h" // Image-reading functions
//#include "XPT2046_Touchscreen.h"

/*#define TFT_DC 9              // Пин подключения вывода D/C дисплея
#define TFT_CS 10             // Пин подключения вывода CS дисплея
// Для управления очисткой экрана с помощью кнопки RESET на Arduino подключить вывод дисплея RESET через резистор к пину RESET на плате Arduino
#define TFT_RST 8             // Пин подключения вывода RESET (Если подключен к питанию или кнопке, то эту строку закомментировать, а следующую раскомментировать)
// #define TFT_RST -1         // Если вывод дисплея RESET подключен к питанию или через кнопку RESET на Arduino
// Uno Hardware SPI
#define TFT_MISO 12           // Пин подключения вывода дисплея SDO(MISO)
#define TFT_MOSI 11           // Пин подключения вывода дисплея SDI(MOSI)
#define TFT_CLK 13            // Пин подключения вывода дисплея SCK
*/

#define TFT_CS 10
#define TFT_DC 9
#define TFT_MOSI 11
#define TFT_CLK 13
#define TFT_RST 8
#define TFT_MISO 12


//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);  // Создаем объект дисплея и сообщаем библиотеке распиновку для работы с графикой
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
#define t_SCK 12               // Пин подключения вывода дисплея T_CLK
#define t_CS 7                // Пин подключения вывода дисплея T_CS
#define t_MOSI 11              // Пин подключения вывода дисплея T_DIN
#define t_MISO 12              // Пин подключения вывода дисплея T_DOUT
#define t_IRQ 7               // Пин подключения вывода дисплея T_IRQ

#define TS_CS 7
#define SD_CS 6

//URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ); // Создаем объект сенсорного модуля и сообщаем библиотеке распиновку для работы с ним
DS3231 clock;
//RTCDateTime dt;

SdFat                SD;         // SD card filesystem
Adafruit_ImageReader reader(SD); // Image-reader object, pass in SD filesys


void setup() {
  //tft.setTextWrap(0); //0 Без переноса, 1 - с переносом
  Serial.begin(9600);
  pinMode(TS_CS, OUTPUT);
  digitalWrite(TS_CS, HIGH);
  pinMode(TFT_CS, OUTPUT);
  digitalWrite(TFT_CS, HIGH);
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  
  tft.begin();                      // Инициализируем начало работы с графическим дисплеем
  tft.setRotation(3);               // Переводим дисплей в альбомную ориентацию
  
  //ts.InitTouch();                   // Инициализируем сенсорный модуль дисплея
  //ts.setPrecision(PREC_LOW);    // Определяем необходимую точность обработки нажатий: PREC_LOW - низкая, PREC_MEDIUM - средняя, PREC_HI - высокая, PREC_EXTREME - максимальная
  tft.fillScreen(ILI9341_BLACK);
  //tft.setTextColor(0xF3E0);  // Определяем цвет текста для вывода на дисплей
  /*tft.setTextSize(2);               // Определяем размер шрифта для вывода на дисплей
    tft.setCursor(0,0);              // Определяем координаты верхнего левого угла области вывода
    tft.print("25.04.2021 13:26");
    //tft.print(utf8rus("Тестируем") + " TouchTFT");  // Выводим текст; Функция utf8rus конвертирует текст в русский, если библиотека Adafruit_GFX оптимизирована для работы с кириллицей
    //tft.drawFastHLine(66, 20, 320, ILI9341_GREEN);
    tft.setTextSize(4);
    tft.setCursor(78,22);              // Определяем координаты верхнего левого угла области вывода
    tft.print(utf8rus("Тестируем") + " TouchTFT");
    tft.setTextSize(3);
    tft.setTextColor(ILI9341_GREEN);  // Определяем цвет текста для вывода на экран
    tft.setCursor(20,220);            // Определяем координаты верхнего левого угла области вывода
    tft.print("http://iomoio.ru");    // Выводим текст
    delay(2000);
    tft.setCursor(20,220);
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft.print("gwygwhwhwehwtwer");*/
  //tft.fillScreen(ILI9341_BLACK);
  clock.begin();
  //clock.setDateTime(2021, 7, 3, 22, 41, 30);
  //clock.setDateTime(__DATE__, __TIME__);
}

void drawBoxes
(
  int xLeftCorner,
  int yLeftCorner,
  int BoxAndTextColor
)
{
  tft.fillRect(0 + xLeftCorner, 0 + yLeftCorner, 148, 4, BoxAndTextColor);
  tft.fillRect(0 + xLeftCorner, 0 + yLeftCorner, 4, 110, BoxAndTextColor);
  tft.fillRect(0 + xLeftCorner, 106 + yLeftCorner, 148, 4, BoxAndTextColor);
  tft.fillRect(144 + xLeftCorner, 0 + yLeftCorner, 4, 110, BoxAndTextColor);
  tft.fillRect(4 + xLeftCorner, 20 + yLeftCorner, 140, 2, BoxAndTextColor);
  tft.fillRect(73 + xLeftCorner, 4 + yLeftCorner, 2, 16 , BoxAndTextColor);
  tft.setTextSize(2);
  tft.setCursor(20 + xLeftCorner, 5 + yLeftCorner);
  tft.setTextColor(BoxAndTextColor);
  tft.print("DAY");
  tft.setCursor(85 + xLeftCorner, 5 + yLeftCorner);
  tft.print("HOUR");
}

void drawSkelet
(
  int SkeletColor
)
{
  drawBoxes(8, 17, SkeletColor);
  drawBoxes(8, 129, SkeletColor);
  drawBoxes(164, 17, SkeletColor);
  drawBoxes(164, 129, SkeletColor);
  if(!SD.begin(SD_CS)) { 
    Serial.println(F("SD begin() failed"));
    for(;;); // Fatal error, do not continue
  }
  ImageReturnCode stat;
  reader.drawBMP("thermo.bmp", tft, 31, 41);
  reader.drawBMP("co2.bmp", tft, 15, 153);
  reader.drawBMP("waterDrop.bmp", tft, 179, 41);
  reader.drawBMP("pressure .bmp", tft, 179, 153);
}

void loop()
{
  static String checkDateTime;
  tft.setTextSize(2);
  tft.setCursor(32, 0);
  tft.setTextColor(0xFFFF, ILI9341_BLACK); //0xF3E0
  if (checkDateTime != clock.getStringDateTime()) {
    checkDateTime = clock.getStringDateTime();
    tft.print(checkDateTime);
  }
  drawSkelet(ILI9341_WHITE);
  ImageReturnCode stat;
  reader.drawBMP("wifiGreen.bmp", tft, 305, 0);
  
  /*int x, y;                         // Переменные для работы с координатами нажатий

    while(ts.dataAvailable())         // Пока имеются данные с сенсорного модуля
    {
    ts.read();                      // Считываем с него данные
    x = ts.getX();                  // Считываем координату нажатия X
    y = ts.getY();                  // Считываем координату нажатия Y
    if((x!=-1) && (y!=-1))          // Если обе координаты в положительном диапазоне (т.е. если есть нажатие)
    {
      x += 0;                      // Корректируем координату с учетом калибровочных данных
      y += 0;                       // Корректируем координату с учетом калибровочных данных
      int radius = 5;               // Определяем радиус разрисовки
      tft.fillCircle(x, y, radius, ILI9341_YELLOW); // Рисуем окружность, закрашенную желтым
    }
    }
    }
    // Начало функции обработки кириллических символов
    String utf8rus(String source)  // Функция для конвертации русских символов из двубайтовой кодировки в однобайтовую
    {
    int i,k;
    String target;
    unsigned char n;
    char m[2] = { '0', '\0' };
    k = source.length(); i = 0;
    while (i < k) {
    n = source[i]; i++;

    if (n >= 0xBF){
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x2F;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB7; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x6F;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
    }
    return target;*/
}
// Конец функции обработки кириллических символов
