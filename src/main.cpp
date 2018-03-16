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

#include "main.h"

/**
 *  @brief function
 *
 *  extensive explanation
 *
 */
void setup(void)
{
    pinMode(BUILTIN_LED, OUTPUT);
    Serial.begin(9600);

#if WIFI
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_Password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
#endif
}

/**
 *  @brief function
 *
 *  extensive explanation
 *
 */
void loop(void)
{
}
