#define BLYNK_TEMPLATE_ID "TMPL3lG9PnOm_"
#define BLYNK_TEMPLATE_NAME "DHT IoT"
#define BLYNK_AUTH_TOKEN "s-7elCeQlL7dFJY7vhfSqBUn7PmirJr7"

#include <DHT.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "s-7elCeQlL7dFJY7vhfSqBUn7PmirJr7";
char ssid[] = "OnePlus Nord 2T 5G";
char pass[] = "j6khrwig";

#define DHTPIN 4 //Data pin is connected to D2 on ESP
#define DHTTYPE DHT11 //Name the sensor as an object

float pH = 0; // Previous value of Humidity
float pT = 0; // Previous value of Temperature 
float dH = 0; // Change in Humidity 
float dT = 0; // Change in Temperature 

DHT dht(DHTPIN,DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println("DHT Test SUCCESS!!!!!!!!");
  Blynk.begin(auth, ssid, pass);
  Serial.println("Blynk Connected Successfully!!!!!!");
  dht.begin();
}

void loop()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float flag = dht.readTemperature(true);
  if(isnan(humidity) || isnan(temperature) || isnan(flag))
  {
    Serial.println("Something has gone terribly wrong");
    return;
  }
  dH = humidity - pH; 
  dT = temperature - pT;

  if (dH != 0 || dT != 0)
  {
    Serial.print("Humid: ");
    Serial.print(humidity);
    Serial.print("% ");

    Serial.print("dHumid: ");
    Serial.print(dH);
    Serial.print("% ");
    Serial.println();

    Serial.print("Temp: ");  
    Serial.print(temperature);
    Serial.print(" C ");

    Serial.print("dTemp: ");
    Serial.print(dT);
    Serial.print(" C");
    Serial.println();
  }
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, dT);
  Blynk.virtualWrite(V3, dH);
  delay (1000);
  pH = humidity;
  pT = temperature;
}