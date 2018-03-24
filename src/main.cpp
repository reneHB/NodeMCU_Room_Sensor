/**
 * @file main.cpp
 * @author René Reimann
 * @date 15.03.2018
 * @brief File containing code.
 *
 * extensive explanation
 *
 * @see https://github.com/reneHB/NodeMCU_Room_Sensor
 *
 * @copyright (C) 2018 René Reimann <rreimann93@icloud.com>
 *
 * @section LICENSE
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>

// SSID and password for WiFi
#include "wifi_data.h"

#include "bme280.h"
#include "illumination.h"
#include "motion.h"
#include "main.h"



ROOM_DATA  room;

// Create an instance of the server
// specify the port to listen on as an argument
#if WIFI
WiFiServer  server(80);
string      readString;
#endif

/**
 *  @brief function
 *
 *  extensive explanation
 *
 */
void setup(void)
{
    uint8_t  ret = 0;

    Serial.begin(9600);

#if WIFI
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_Password);
    //WiFi.config(WIFI_IP, WIFI_GATEWAY, WIFI_NETMASK);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
#endif

    Serial.println("Connecting to BME280...");
    ret = BME280_Setup();
    if (!ret) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1) ;
    }

    MOTION_Setup();

    // Start the server
    server.begin();
}

/**
 *  @brief function
 *
 *  extensive explanation
 *
 */
void loop(void)
{
    WiFiClient  client = server.available();
    if (client) {
        while (client.connected()) {
            if (client.available()) {
                char  c = client.read();

                //read char by char HTTP request
                if (readString.length() < 100) {
                    //store characters to string
                    readString += c;
                }

                //if HTTP request has ended
                if (c == '\n') {
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: application/json;charset=utf-8");
                    client.println("Server: Arduino");
                    client.println("Connnection: close");
                    client.println();
                    client.print("{");
                    client.print("\"temperature\":");
                    client.print(room.temperature);
                    client.print(",");
                    client.print("\"humidity\":");
                    client.print(room.humidity);
                    client.print("}");

                    client.print(",");
                    client.print("{");
                    client.print("\"lightval\":");
                    client.print(room.illumination);
                    client.print(",");
                    client.print("\"pirval\":");
                    client.print(room.motion);
                    client.print("}");
                    client.println();

                    //stopping client
                    client.stop();

                    //clearing string for next read
                    readString = "";
                }
            }
        }
    }


    room.temperature = BME280_Temperature();
    room.humidity = BME280_Humidity();
    room.pressure = BME280_Pressure();
    room.illumination = LUX_read();
    room.motion = MOTION_Read();

    Serial.print("Temperature: ");
    Serial.print(room.temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(room.humidity);
    Serial.println(" %");

    Serial.print("Pressure: ");
    Serial.print(room.pressure);
    Serial.println(" hPa");

    Serial.print("Illumination: ");
    Serial.print(room.illumination);
    Serial.println(" lux");

    Serial.print("Motion: ");
    Serial.println(room.motion);

    delay(1000);
}
