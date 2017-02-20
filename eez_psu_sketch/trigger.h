/*
 * EEZ PSU Firmware
 * Copyright (C) 2017-present, Envox d.o.o.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#pragma once

namespace eez {
namespace psu {
namespace trigger {

static const float DELAY_DEFAULT = 0;
static const float DELAY_MIN = 0;
static const float DELAY_MAX = 3600.0f;

enum Source {
    SOURCE_BUS,
    SOURCE_IMMEDIATE,
    SOURCE_KEY,
    SOURCE_PIN1
};

enum Polarity {
    POLARITY_POSITIVE = 1,
    POLARITY_NEGATIVE = 0
};

void init();
void reset();

void setDelay(float delay);
float getDelay();

void setSource(Source source);
Source getSource();

void setPolarity(Polarity polarity);
Polarity getPolarity();

void setVoltage(int iChannel, float value);
float getVoltage(int iChannel);

void setCurrent(int iChannel, float value);
float getCurrent(int iChannel);

int generateTrigger(Source source, bool checkImmediatelly = true);
int startImmediately();
int initiate();
int enableInitiateContinuous(bool enable);
bool isContinuousInitializationEnabled();
void abort();

void tick(uint32_t tick_usec);

}
}
} // namespace eez::psu::trigger