#include <ModbusMaster.h>
#include "REG_CONFIG.h"
#include <HardwareSerial.h>
#include "HardwareSerial_NB_BC95.h"
#include <TaskScheduler.h>
#define _TASK_TIMECRITICAL
HardwareSerial modbus(2);
#define NUMSLAVES 10
int SlaveCnt = 0;
#define CHANNEL 3
#define PRINTSCANRESULTS 0
ModbusMaster node;
void t1CallgetMeter();
Task t1(10000, TASK_FOREVER, &t1CallgetMeter);
Scheduler runner;

#include "HardwareSerial_NB_BC95.h"
String deviceToken = "VetTTONV2iPynmNX4n4Z";
String serverIP = "103.27.203.77"; // Your Server IP;
String serverPort = "9956"; // Your Server Port;
String json = "";
String udpData = "{\"Tn\":\"VetTTONV2iPynmNX4n4Z\",\"temp\":34.3}";
HardwareSerial_NB_BC95 AISnb;
const long interval = 5000;  //millisecond
unsigned long previousMillis = 0;
bool Check = true;
struct Nipat
{
  String Temp;
  String Humid;
  String CO2;
  String PM2_5;
  String cA;
  String vAN;
  String apTotal;
  String freq;
  String Current_Avg_1;
  String Current_Avg_2;
  String Current_Avg_3;
  String Voltage_Avg_1 ;
  String Voltage_Avg_2 ;
  String Voltage_Avg_3 ;
  String Frequency_1;
  String Frequency_2;
  String Frequency_3;
  String apTotal_1;
  String apTotal_2;
  String apTotal_3;
};
Nipat nipat;
signal meta ;

struct Meter
{
  String Current_Avg_1;
  String Current_Avg_2;
  String Current_Avg_3;
  String Voltage_Avg_1 ;
  String Voltage_Avg_2 ;
  String Voltage_Avg_3 ;
  String Frequency_1;
  String Frequency_2;
  String Frequency_3;
  String apTotal_1;
  String apTotal_2;
  String apTotal_3;
};
Meter meter;
long cnt = 0;
void setup()
{
  Serial.begin(115200);
  AISnb.debug = true;
  AISnb.setupDevice(serverPort);
  String ip1 = AISnb.getDeviceIP();
  delay(1000);
  pingRESP pingR = AISnb.pingIP(serverIP);
  previousMillis = millis();
  modbus.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println(F("Starting... Sintrol Monitor"));
  Serial.println();
  Serial.println(F("***********************************"));
  runner.init();
  Serial.println("Initialized scheduler");
  runner.addTask(t1);
  Serial.println("added t1");
  Serial.println("added t2");
  delay(2000);
  t1.enable();  Serial.println("Enabled t1");
}
void readMeter()
{

  nipat.Temp = read_Modbus(T);
  Serial.println("  nipat.Temp = read_Modbus(T);");
  nipat.Humid = read_Modbus(H);
  Serial.println(" nipat.Humid = read_Modbus(H);");
  nipat.CO2 = read_Modbus(C);
  Serial.println("  nipat.CO2 = read_Modbus(C);");
  nipat.PM2_5 = read_Modbus(P);
  Serial.println(" nipat.PM2_5 = read_Modbus(P);");

  /* node.begin(2, modbus);
    nipat.cA = read_Modbus(c_A);
    Serial.println("  nipat.cA = read_Modbus(c_A);");
    nipat.vAN = read_Modbus(v_A_N);
    Serial.println(" nipat.vAN = read_Modbus(v_A_N);");
    nipat.apTotal = read_Modbus(ap_Total);
    Serial.println(" nipat.apTotal = read_Modbus(ap_Total);");
    nipat.freq = read_Modbus(v_Freq);
    Serial.println(" nipat.freq = read_Modbus(v_Freq);");*/
  if ( nipat.Temp.toInt() >= 5 && nipat.Humid.toInt() >= 5 && nipat.CO2.toInt() >= 5 && nipat.PM2_5.toInt() >= 5 ) {
    Serial.println("++++++++++ eyc device ++++++++++++++++++++");
    Serial.print("Powered By Nipat Academy Temp  : ");
    Serial.print(nipat.Temp);
    Serial.println(" Degree C :");
    Serial.print("Powered By Nipat Academy Humid : ");
    Serial.print(nipat.Humid);
    Serial.println(" %RH");
    Serial.print("Powered By Nipat Academy CO2   : ");
    Serial.print(nipat.CO2);
    Serial.println(" ppm");
    Serial.print("Powered By Nipat Academy PM2_5 : ");
    Serial.print(nipat.PM2_5);
    Serial.println(" ug/m3");
    delay(200);

    /* Serial.println("++++++++++ power meter device ++++++++++++");
      Serial.print("Powered By Nipat Academy Current A: ");
      Serial.print(nipat.cA);
      Serial.println(" Amp");
      Serial.print("Powered By Nipat Academy Voltage A-N: ");
      Serial.print(nipat.vAN);
      Serial.println(" Volt");
      Serial.print("Powered By Nipat Academy Frequency: ");
      Serial.print(nipat.freq);
      Serial.println(" Hz");
      Serial.print("Powered By Nipat Academy Active Power Total: ");
      Serial.print(nipat.apTotal);
      Serial.println(" Kw");
      Serial.println("++++++++++ end device ++++++++++++++++++++");*/
  }
  else {
    Serial.println("Connect modbus fail.  >>> Return ");
    for (int x = 1 ; x <= 5 ; x++) {
      Serial.println("Waiting for Return " + String(x));
      delay(200);
      if (x == 5) {
        Serial.println("Just Retrun --> ++ <3 ^_^");
        return;
      }
    }
  }
}

void readMeter2()
{
  Serial.println("++++++++++ device 2 ++++++++++++");
  meter.Current_Avg_1 = read_Modbus(c_Avg);
  meter.Voltage_Avg_1 = read_Modbus(v_LN_Avg);
  meter.Frequency_1 = read_Modbus(v_Freq);
  meter.apTotal_1 = read_Modbus(ap_Total);
  Serial.print("Current Avg: ");
  Serial.print(meter.Current_Avg_1);
  Serial.println(" Amp");
  Serial.print("Volt AVG: ");
  Serial.print(meter.Voltage_Avg_1);
  Serial.println(" Volt");
  Serial.print("Frequency: ");
  Serial.print(meter.Frequency_1);
  Serial.println(" Hz");
  Serial.print("meter.apTotal_1 : ");
  Serial.print(meter.apTotal_1);
  Serial.println(" kW");
  Serial.println("++++++++++ device 2 ++++++++++++");
  delay(2000);
}
void readMeter3()
{
  Serial.println("++++++++++ device 3 ++++++++++++");
  meter.Current_Avg_2 = read_Modbus(c_Avg);
  meter.Voltage_Avg_2 = read_Modbus(v_LN_Avg);
  meter.Frequency_2 = read_Modbus(v_Freq);
  meter.apTotal_2 = read_Modbus(ap_Total);
  Serial.print("Current Avg: ");
  Serial.print(meter.Current_Avg_2);
  Serial.println(" Amp");
  Serial.print("Volt AVG: ");
  Serial.print(meter.Voltage_Avg_2);
  Serial.println(" Volt");
  Serial.print("Frequency: ");
  Serial.print(meter.Frequency_2);
  Serial.println(" Hz");
  Serial.print("meter.apTotal_2 : ");
  Serial.print(meter.apTotal_2);
  Serial.println(" kW");
  Serial.println("++++++++++ device 3 ++++++++++++");
  delay(2000);
}
void readMeter4()
{
  Serial.println("++++++++++ device 4 ++++++++++++");
  meter.Current_Avg_3 = read_Modbus(c_Avg);
  meter.Voltage_Avg_3 = read_Modbus(v_LN_Avg);
  meter.Frequency_3 = read_Modbus(v_Freq);
  meter.apTotal_3 = read_Modbus(ap_Total);
  Serial.print("Current Avg: ");
  Serial.print(meter.Current_Avg_3);
  Serial.println(" Amp");
  Serial.print("Volt AVG: ");
  Serial.print(meter.Voltage_Avg_3);
  Serial.println(" Volt");
  Serial.print("Frequency: ");
  Serial.print(meter.Frequency_3);
  Serial.println(" Hz");
  Serial.print("meter.apTotal_3 : ");
  Serial.print(meter.apTotal_3);
  Serial.println(" kW");
  Serial.println("++++++++++ device 4 ++++++++++++");
  delay(2000);
}

void t1CallgetMeter() {     // Update read all data
  Serial.println("++++++++++start device++++++++++++");
  node.begin(1, modbus);
  readMeter();
  node.begin(2, modbus);
  readMeter2();
  node.begin(3, modbus);
  readMeter3();
  node.begin(4, modbus);
  readMeter4();
}


float HexTofloat(uint32_t x)
{
  return (*(float*)&x);
}

float read_Modbus(uint16_t  REG)
{
  static uint32_t i;
  uint8_t j, result;
  uint16_t data[2];
  uint32_t value = 0;
  float val = 0.0;
  result = node.readHoldingRegisters(REG, 2);
  Serial.print("result : ");
  Serial.println(result);
  Serial.print("node.ku8MBSuccess : ");
  Serial.println(node.ku8MBSuccess);
  Serial.print("REG : ");
  Serial.println(REG);
  delay(10);
  // do something with data if read is successful
  if (result == node.ku8MBSuccess)
  {
    for (j = 0; j < 2; j++)
    {
      data[j] = node.getResponseBuffer(j);
      //Serial.println(data[j]);
      delay(100);
    }
    value = data[0];
    Serial.print("data[0] : ");
    Serial.println(value);
    delay(10);
    Serial.print("data[1] : ");
    Serial.println(data[1]);
    delay(10);
    value = value << 16;
    Serial.print("value << 16 : ");
    Serial.println(value);
    delay(10);
    value = value + data[1];
    Serial.print("value + data[1] : ");
    Serial.println(value);
    delay(10);
    val = HexTofloat(value);
    Serial.print("HexTofloat(value) : ");
    Serial.println(val);
    delay(10);
    return val;
    Serial.print("return val : ");
    Serial.println(val);
    delay(10);
  } else {
    Serial.print("Connec modbus fail. REG >>> "); Serial.println(REG, HEX); // Debug
    delay(10);
    return 0;
  }

}


void loop()
{
  runner.execute();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    cnt++;
    String json = "";
    json.concat("{\"Tn\":\"");
    json.concat(deviceToken);
    json.concat("\",\"nipat.Temp\":");
    json.concat(nipat.Temp.toFloat());
    json.concat(",\"nipat.Humid\":");
    json.concat(nipat.Humid.toFloat());
    json.concat(",\"nipat.CO2\":");
    json.concat(nipat.CO2.toFloat());
    json.concat(",\"nipat.PM2_5\":");
    json.concat(nipat.PM2_5.toFloat());
    json.concat(",\" meter.Current_Avg_1\":");
    json.concat( meter.Current_Avg_1.toFloat());
    json.concat(",\"meter.Voltage_Avg_1\":");
    json.concat(meter.Voltage_Avg_1.toFloat());
    json.concat(",\"meter.Frequency_1\":");
    json.concat(meter.Frequency_1.toFloat());
    json.concat(",\" meter.Current_Avg_2\":");
    json.concat( meter.Current_Avg_2.toFloat());
    json.concat(",\"meter.Voltage_Avg_2\":");
    json.concat(meter.Voltage_Avg_2.toFloat());
    json.concat(",\"meter.Frequency_2\":");
    json.concat(meter.Frequency_2.toFloat());
    json.concat(",\" meter.Current_Avg_3\":");
    json.concat( meter.Current_Avg_3.toFloat());
    json.concat(",\"meter.Voltage_Avg_3\":");
    json.concat(meter.Voltage_Avg_3.toFloat());
    json.concat(",\"meter.Frequency_3\":");
    json.concat(meter.Frequency_3.toFloat());
    json.concat("}");
    Serial.println(json);
    // Send data in String
    UDPSend udp = AISnb.sendUDPmsgStr(serverIP, serverPort, json);
    previousMillis = currentMillis;
    String nccid = AISnb.getNCCID();
    Serial.print("nccid:");
    Serial.println(nccid);

  }
  UDPReceive resp = AISnb.waitResponse();
}
