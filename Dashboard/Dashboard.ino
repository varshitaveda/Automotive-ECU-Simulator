//Blynk credentials
#define BLYNK_TEMPLATE_ID "TMPL3Lsoq8n6o"
#define BLYNK_TEMPLATE_NAME "ECU Simulator"
#define BLYNK_AUTH_TOKEN "6YfXd4dY4vHVzp1IDScGYxu4kfJQ4NvE"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "";
char pass[] = "";


/* ECU Data */

int temperature = 0;
int speed = 0;
int rpm = 0;
int fuel = 0;

String fault = "OK";
String engine = "OFF";

char faultBuffer[20];
char engineBuffer[10];

void parseData(String data)
{
    if(data == "IGNITION ON")
    {
        engine = "ON";
        return;
    }

    if(data == "IGNITION OFF")
    {
        engine = "OFF";

        /* Optional: Reset values when engine is OFF */
        temperature = 0;
        speed = 0;
        rpm = 0;
        fuel = 0;
        fault = "OK";

        return;
    }
    int result = sscanf(data.c_str(),
                        "T=%d,S=%d,R=%d,F=%d,ST=%[^,],E=%s",
                        &temperature,
                        &speed,
                        &rpm,
                        &fuel,
                        faultBuffer,
                        engineBuffer);

    if(result == 6)
    {
        fault = String(faultBuffer);
        engine = String(engineBuffer);
        Serial.println("Packet Parsed Successfully");

        Serial.println("-----------");
        Serial.print("Temperature : ");
        Serial.println(temperature);

        Serial.print("Speed : ");
        Serial.println(speed);

        Serial.print("RPM : ");
        Serial.println(rpm);

        Serial.print("Fuel : ");
        Serial.println(fuel);

        Serial.print("Fault : ");
        Serial.println(fault);

        Serial.print("Engine : ");
        Serial.println(engine);

        Serial.println("-----------");
    }
}

void setup()
{
    Serial.begin(115200);

    Serial.println("Connecting WiFi...");

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    Serial.println("Blynk Connected");
}

void loop()
{
    Blynk.run();

    if (Serial.available())
    {
        String data = Serial.readStringUntil('\n');

        data.trim();

        if (data.length() > 0)
        {
            Serial.print("Received: ");
            Serial.println(data);

            parseData(data);

            /* Send immediately after parsing */
            Blynk.virtualWrite(V0, temperature);
            Blynk.virtualWrite(V1, speed);
            Blynk.virtualWrite(V2, rpm);
            Blynk.virtualWrite(V3, fuel);
            Blynk.virtualWrite(V4, fault);
            Blynk.virtualWrite(V5, engine);
        }
    }
}
