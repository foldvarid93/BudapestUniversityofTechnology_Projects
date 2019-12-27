#include <SPI.h>
#include <Ticker.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "RTClib.h"
#include "string.h"
#include "lm75.h"
#include "application.h"
#include "characters.h"
#include "stdlib.h"
/***************************************************************/
#define WifiMode 0
#define TimeMode 1
#define DateMode 2
#define TempMode 3
/***************************************************************///RTC
RTC_DS3231 rtc;
uint8_t hour_ten_old;
uint8_t hour_single_old;
uint8_t min_ten_old;
uint8_t min_single_old;
String daysOfTheWeek[7] = {"Vasarnap", "Hetfo", "Kedd", "Szerda", "Csutortok", "Pentek", "Szombat"};
/***************************************************************///LM75
TempI2C_LM75 termo = TempI2C_LM75(0x4F, TempI2C_LM75::nine_bits);
/***************************************************************///Private variable
char TextArray[256];
uint8_t DisplayDataArray[1536];//256*6 karakterenkÄ‚Â©nt 6 oszlop
bool ScrollText = false;
bool ScrollEnd = false;
uint8_t TextLength;
int StartFrom;
/*******************************/
const char* ssid = "HP8570W-foldvarid93";
const char* password = "19701971";
const int slaveSelectPin = D0;
const int WifiCommunicationPin = D3;
int scrollInterruptCounter = 0;
int adcInterruptCounter = 0;
uint16_t rtcInterruptCounter = 0;
bool WiFiIsOn = false;
uint8_t DisplayMode = TimeMode;
uint8_t LastShowedText = TempMode;
WiFiClient client;
WiFiServer server(80);
IPAddress ip;
char IPdata[16];
/***************************************************************/
void GetTemperature(void) {
  float TempValue = termo.getTemp();
  strcpy(TextArray, "    Homerseklet: ");
  uint8_t i = strlen(TextArray);
  TextArray[i] = 0x30;
  while (TempValue > 10) {
    TempValue -= 10;
    TextArray[i]++;
  }
  i++;
  TextArray[i] = 0x30;
  while (TempValue > 1) {
    TempValue -= 1;
    TextArray[i]++;
  }
  i++;
  TextArray[i++] = '.';
  TextArray[i] = 0x30;
  while (TempValue > 0.1) {
    TempValue -= 0.1;
    TextArray[i]++;
  }
  i++;
  TextArray[i] = 0x30;
  while (TempValue > 0.01) {
    TempValue -= 0.01;
    TextArray[i]++;
  }
  i++;
  TextArray[i++] = 0xB0;
  TextArray[i++] = 'C';
  TextArray[i++] = ' ';
  TextArray[i++] = ' ';
  TextArray[i++] = ' ';
  TextArray[i++] = ' ';
  TextArray[i++] = '\0';
}
void GetDate(void) {
  DateTime Date = rtc.now();
  uint16_t year = Date.year();
  uint8_t month = Date.month();
  uint8_t day = Date.day();
  uint8_t dayOfWeek = Date.dayOfTheWeek();
  char tmp[20];
  daysOfTheWeek[dayOfWeek].toCharArray(tmp, daysOfTheWeek[dayOfWeek].length() + 1);
  strcpy(TextArray, "    A mai datum: ");
  uint8_t i = strlen(TextArray);

  TextArray[i++] = (year / 1000) + 0x30;
  TextArray[i++] = ((year % 1000) / 100) + 0x30;
  TextArray[i++] = (((year % 1000) % 100) / 10) + 0x30;
  TextArray[i++] = ((((year % 1000) % 100) % 100) % 10) + 0x30;
  TextArray[i++] = '.';
  TextArray[i++] = (month / 10) + 0x30;
  TextArray[i++] = (month % 10) + 0x30;
  TextArray[i++] = '.';
  TextArray[i++] = (day / 10) + 0x30;
  TextArray[i++] = (day % 10) + 0x30;
  TextArray[i++] = '.';
  TextArray[i++] = ',';
  for (uint8_t j = 0; tmp[j] != '\0'; j++) {
    TextArray[i++] = tmp[j];
  }
  TextArray[i++] = ' ';
  TextArray[i++] = ' ';
  TextArray[i++] = ' ';
  TextArray[i++] = ' ';
  TextArray[i++] = '\0';
}
void CreateTextArray(char *From) {
  ScrollText = false; //ne legyen lÄ‚Â©ptetÄ‚Â©s amikor dolgozunk a tÄ‚Â¶mbÄ‚Â¶n
  TextLength = 0;
  while (From[TextLength] != '\0') {
    TextLength++;
  }
  for (uint8_t i = 0; i < TextLength; i++) {
    for (uint8_t j = 0; j < 6; j++) {
      DisplayDataArray[(i * 6) + j] = BitSwapping(characters[From[i]][j]);
    }
  }
  StartFrom = 0;
  ScrollEnd = false;
  ScrollText = true;
}
void SendToDisplay(uint16_t from) {
  SPI_send(REG_SHTDWN, SHUTDOWN_MODE);
  for (uint8_t i = 1; i < 9; i++) {
    digitalWrite(slaveSelectPin, LOW);
    for (uint8_t j = 0; j < 3; j++) {
      SPI.transfer(i);//address
      SPI.transfer(DisplayDataArray[from + ((2 - j) * 8) + (i - 1)]); //data
    }
    digitalWrite(slaveSelectPin, HIGH);
  }
  SPI_send(REG_SHTDWN, NORMAL_MODE);
}
void CreateTimeDisplayFrame() {
  DateTime newDataTime = rtc.now();
  uint8_t hour_ten_new = newDataTime.hour() / 10;
  uint8_t hour_single_new = newDataTime.hour() % 10;
  uint8_t min_ten_new = newDataTime.minute() / 10;
  uint8_t min_single_new = newDataTime.minute() % 10;
  uint8_t sec_ten_new = newDataTime.second() / 10;
  uint8_t sec_single_new = newDataTime.second() % 10;

  if ((sec_ten_new == 3) && (sec_single_new == 0)) {
    if (LastShowedText == TempMode) {
      DisplayMode = DateMode;
    }
    if (LastShowedText == DateMode) {
      DisplayMode = TempMode;
    }
    LastShowedText = DisplayMode;
  }
  for (uint8_t i = 0; i < 5; i++) {
    if(hour_ten_new==0){
      DisplayDataArray[i]=0x00;
    }
    else{
      DisplayDataArray[i] = BitSwapping(characters[hour_ten_new + 0x30][i]);      
    }
    DisplayDataArray[i + 5] = BitSwapping(characters[hour_single_new + 0x30][i]);
    DisplayDataArray[i + 13] = BitSwapping(characters[min_ten_new + 0x30][i]);
    DisplayDataArray[i + 18] = BitSwapping(characters[min_single_new + 0x30][i]);
  }
  DisplayDataArray[10] = 0;
  DisplayDataArray[11] = 0x22;
  DisplayDataArray[12] = 0;
  DisplayDataArray[23] = 0;
  hour_ten_old = hour_ten_new;
  hour_single_old = hour_single_new;
  min_ten_old = min_ten_new;
  min_single_old = min_single_new;
}
void SendTimeFrameToDisplay(void) {
  SPI_send(REG_SHTDWN, SHUTDOWN_MODE);
  for (uint8_t i = 1; i < 9; i++) {
    digitalWrite(slaveSelectPin, LOW);
    for (uint8_t j = 0; j < 3; j++) {
      SPI.transfer(i);//address
      SPI.transfer(DisplayDataArray[((2 - j) * 8) + (i - 1)]); //data
    }
    digitalWrite(slaveSelectPin, HIGH);
  }
  SPI_send(REG_SHTDWN, NORMAL_MODE);
}
uint8_t BitSwapping(uint8_t ch) {
  uint8_t retval = 0x00;
  if (ch & 0B00000001) retval |= 0B10000000;
  if (ch & 0B00000010) retval |= 0B01000000;
  if (ch & 0B00000100) retval |= 0B00100000;
  if (ch & 0B00001000) retval |= 0B00010000;
  if (ch & 0B00010000) retval |= 0B00001000;
  if (ch & 0B00100000) retval |= 0B00000100;
  if (ch & 0B01000000) retval |= 0B00000010;
  if (ch & 0B10000000) retval |= 0B00000001;
  return ~retval;
}
void SPI_send(uint8_t ADDR, uint8_t DATA) {
  digitalWrite(slaveSelectPin, LOW);
  for (uint8_t i = 0; i < 3; i++) {
    SPI.transfer(ADDR);
    SPI.transfer(DATA);
  }
  digitalWrite(slaveSelectPin, HIGH);
}
void Init_MAX7219(void) {
  SPI_send(REG_NO_OP, NOP);
  SPI_send(REG_NO_OP, NOP);
  SPI_send(REG_SHTDWN, SHUTDOWN_MODE);
  SPI_send(REG_DECODE, NO_DECODE);
  SPI_send(REG_SCANLIMIT, DISP0_7);
  SPI_send(REG_DISPTEST, 0);
  SPI_send(REG_SHTDWN, SHUTDOWN_MODE);
  for (uint8_t i = 1; i < 9; i++) {
    SPI_send(i, 0);
  }
  SPI_send(REG_SHTDWN, NORMAL_MODE);
  SPI_send(REG_INTENSITY, INTENSITY_1);
}
void DisplayIntensity(void) {
  uint16_t ADCRes = analogRead(A0);
  ADCRes >>= 5;
  if (ADCRes < 3) {
    SPI_send(REG_INTENSITY, INTENSITY_1);
  }
  else if (3 <= ADCRes && ADCRes < 5) {
    SPI_send(REG_INTENSITY, INTENSITY_3);
  }
  else if (5 <= ADCRes && ADCRes < 7) {
    SPI_send(REG_INTENSITY, INTENSITY_5);
  }
  else if (7 <= ADCRes && ADCRes < 9) {
    SPI_send(REG_INTENSITY, INTENSITY_7);
  }
  else if (9 <= ADCRes && ADCRes < 11) {
    SPI_send(REG_INTENSITY, INTENSITY_9);
  }
  else if (11 <= ADCRes && ADCRes < 13) {
    SPI_send(REG_INTENSITY, INTENSITY_11);
  }
  else if (13 <= ADCRes && ADCRes < 15) {
    SPI_send(REG_INTENSITY, INTENSITY_13);
  }
  else if (15 <= ADCRes && ADCRes < 17) {
    SPI_send(REG_INTENSITY, INTENSITY_15);
  }
  else if (17 <= ADCRes && ADCRes < 19) {
    SPI_send(REG_INTENSITY, INTENSITY_17);
  }
  else if (19 <= ADCRes && ADCRes < 21) {
    SPI_send(REG_INTENSITY, INTENSITY_19);
  }
  else if (21 <= ADCRes && ADCRes < 23) {
    SPI_send(REG_INTENSITY, INTENSITY_21);
  }
  else if (23 <= ADCRes && ADCRes < 25) {
    SPI_send(REG_INTENSITY, INTENSITY_23);
  }
  else if (25 <= ADCRes && ADCRes < 27) {
    SPI_send(REG_INTENSITY, INTENSITY_25);
  }
  else if (27 <= ADCRes && ADCRes < 29) {
    SPI_send(REG_INTENSITY, INTENSITY_27);
  }
  else if (29 <= ADCRes && ADCRes < 31) {
    SPI_send(REG_INTENSITY, INTENSITY_29);
  }
  else if (31 <= ADCRes) {
    SPI_send(REG_INTENSITY, INTENSITY_31);
  }
}
void ICACHE_RAM_ATTR onTimerISR() {
  scrollInterruptCounter += 1;
  adcInterruptCounter += 1;
  rtcInterruptCounter += 1;

  if (scrollInterruptCounter == 4) { //100ms megszakÄ‚Â­tÄ‚Ë‡s
    if (ScrollText) {
      if (StartFrom == ((TextLength * 6) - 24) || DisplayMode == TimeMode) {
        StartFrom = 0;
        ScrollEnd = true;
        ScrollText = false;
      }
      else {
        SendToDisplay(StartFrom);
        StartFrom++;
      }
    }
    scrollInterruptCounter = 0;
  }
  if (rtcInterruptCounter == 16) { //400ms megszakÄ‚Â­tÄ‚Ë‡s
    if (DisplayMode == TimeMode) {
      CreateTimeDisplayFrame();
      SendTimeFrameToDisplay();
    }
    rtcInterruptCounter = 0;
  }
  if (adcInterruptCounter == 40) { //1s megszakÄ‚Â­tÄ‚Ë‡s
    adcInterruptCounter = 0;
    DisplayIntensity();
  }
  timer1_write(125000);//25ms megszakÄ‚Â­tÄ‚Ë‡s
}
void handleInterrupt() {
  if (DisplayMode == WifiMode)
    DisplayMode = TimeMode;
  else DisplayMode = WifiMode;
  if (WiFiIsOn && DisplayMode == TimeMode) {
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(slaveSelectPin, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(SPISettings(250000, MSBFIRST, SPI_MODE0));
  Init_MAX7219();
  pinMode(WifiCommunicationPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WifiCommunicationPin), handleInterrupt, FALLING);
  timer1_attachInterrupt(onTimerISR);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
  timer1_write(125000); //25ms megszakÄ‚Â­tÄ‚Ë‡s
}
void loop() {
  if (DisplayMode == WifiMode) {
    if (!WiFiIsOn) { //connect
      strcpy(TextArray, "Connecting to WiFI");
      CreateTextArray(TextArray);
      WiFi.begin(ssid, password);
      bool timeout = false;
      uint8_t i = 0;
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        i++;
        if (i == 20) {
          timeout = true;
          break;
        }
      }
      if (!timeout) {
        server.begin();
        ip = WiFi.localIP();
        sprintf(IPdata, "    IP:%d.%d.%d.%d    ", ip[0], ip[1], ip[2], ip[3] );
        WiFiIsOn = true;
        ScrollEnd == true;
      }
      else {
        strcpy(TextArray, "No connection. :( ");
        CreateTextArray(TextArray);
        while (ScrollEnd == false) {
          delay(1);
        }
        WiFiIsOn = false;
        DisplayMode = TimeMode;
      }
    }
    if (WiFiIsOn) {
      client = server.available();
      if (ScrollEnd == true) {
        strcpy(TextArray, IPdata);
        CreateTextArray(TextArray);
      }
      if (client) {
        String request = client.readStringUntil('\r');
        if (request[0] == 'G'&&request[1] == 'E'&&request[2] == 'T'&&request[3] == ' '&&request[4] == '/'&&
            request[5] == 'S'&&request[6] == 'T'&&request[7] == 'A'&&request[8] == 'R'&&request[9] == 'T'&&request[10] == '/'&&
            '0'<=request[11] <= '9'&&'0'<=request[12] <= '9'&&'0'<=request[13] <= '9'&&'0'<=request[14] <= '9'&&//year
            request[15] == '.'&&//year
            '0'<=request[16] <= '9'&&'0'<=request[17] <= '9'&&//month
            request[18] == '.'&&//month
            '0'<=request[19] <= '9'&& '0'<=request[20] <= '9'&&//day
            request[21] == '.'&&//day
            request[22] == ','&&//day
            '0'<=request[23] <= '9'&&'0'<=request[24] <= '9'&&//hour
            request[25] == ':'&&//hour
            '0'<=request[26] <= '9'&& '0'<=request[27] <= '9'&&//minute
            request[28] == '/'&&request[29] == 'S'&&request[30] == 'T'&&request[31] == 'O'&&request[32] == 'P'&&request[33] == '/') 
        {
          Serial.println(request);
          char tmpbuf[18];
          tmpbuf[17]='\0';
          for(uint8_t i=0;i<17;i++){
            tmpbuf[i]=request[11+i];
          }
          int year, month, day, hour, minute;
          sscanf(tmpbuf,"%d.%d.%d.,%d:%d",&year,&month,&day,&hour,&minute);
          DateTime SetDateTime(year,month,day,hour,minute);
          rtc.adjust(SetDateTime);
        }
        client.flush();
        // Return the response
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println(""); //  do not forget this one
        client.println("<!DOCTYPE HTML>");
        client.println("<html>");
        client.println("<body>");
        client.println("<form>");
        client.println("<input id='data' type='text' name='data'>");
        client.println("<br>");
        client.println("YYYY.MM.DD.,HH:MM");
        client.println("<br>");
        client.println("<input type='button' value='Set' onclick='SendData();'>");
        client.println("</form>");
        client.println("<script>");
        client.println("function SendData(){");
        client.println("nocache = '/STOP/' + Math.random() * 1000000;");
        client.println("var request = new XMLHttpRequest();");
        client.println("request.onreadystatechange=function(){");
        client.println("if (this.readyState==4){");
        client.println("if (this.status==200){");
        client.println("if (this.responseText!=null){");
        client.println("}}}}");
        client.println("strText = '/START/' + document.getElementById('data').value;");
        client.println("request.open('GET', strText + nocache, true);");
        client.println("request.send(null);");
        client.println("}");
        client.println("</script>");
        client.println("</body>");
        client.println("</html>");
      }
    }
  }
  if (DisplayMode == TimeMode) {
  }
  if (DisplayMode == TempMode) {
    GetTemperature();
    CreateTextArray(TextArray);
    while (ScrollEnd == false) {
      delay(1);
    }
    DisplayMode = TimeMode;
  }
  if (DisplayMode == DateMode) {
    GetDate();
    CreateTextArray(TextArray);
    while (ScrollEnd == false) {
      delay(1);
    }
    DisplayMode = TimeMode;
  }
}
