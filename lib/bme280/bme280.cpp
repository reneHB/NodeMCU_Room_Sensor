/**
 * @file bme280.cpp
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

#include <Adafruit_BME280.h>
#include "bme280.h"


Adafruit_BME280  bme;

uint8_t BME280_Setup(void)
{
    return (uint8_t)bme.begin(0x76);
}

float BME280_Temperature(void)
{
    return bme.readTemperature();
}

float BME280_Pressure(void)
{
    return bme.readPressure() / 100.0;
}

float BME280_Humidity(void)
{
    return bme.readHumidity();
}
