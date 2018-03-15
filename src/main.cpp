/**
 * @file main.cpp
 * @author René Reimann
 * @date 15.03.2018
 * @brief File containing code.
 *
 * extensive explanation
 *
 * @copyright (C) 2018 René Reimann <rreimann93@icloud.com>
 *
 * @license This project is released under the MIT License.
 *
 * @see https://github.com/reneHB/NodeMCU_Room_Sensor
 */

#include <Arduino.h>




void setup()
{
    Serial.begin(9600);
}

void loop()
{
    delay(1000);
    Serial.println("Hello World!");
}
