/*
 * EEZ PSU Firmware
 * Copyright (C) 2015-present, Envox d.o.o.
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

#include "eez/psu/psu.h"

#include "eez/psu/platform/simulator/front_panel/control.h"
#include "eez/psu/platform/simulator/front_panel/render.h"
#include "eez/platform/simulator/imgui/window.h"
#include "eez/psu/persist_conf.h"
#if OPTION_ENCODER
#include "eez/psu/platform/simulator/encoder.h"
#endif

#ifdef _WIN32
#undef INPUT
#undef OUTPUT
#endif

#include <stdio.h>

using namespace eez::platform::simulator::imgui;

namespace eez {
namespace psu {
namespace simulator {
namespace front_panel {

static Window* g_window;
static Data g_data;

#if OPTION_DISPLAY

bool isOpened() {
    return g_window ? true : false;
}

bool open() {
    if (g_window) {
        return true;
    }

    int w, h;
    getDesktopResolution(&w, &h);

    g_window = createWindow(getWindowDefinition(w, h));

    if (!persist_conf::devConf.gui_opened) {
        persist_conf::devConf.gui_opened = true;
        persist_conf::saveDevice();
    }

    return g_window != 0;
}

void close() {
    if (g_window) {
        delete g_window;
        g_window = 0;

        if (persist_conf::devConf.gui_opened) {
            persist_conf::devConf.gui_opened = false;
            persist_conf::saveDevice();
        }
    }
}
#endif

void tick() {
#if OPTION_DISPLAY
    if (g_window) {
        if (g_window->pollEvent()) {
            g_window->beginUpdate();

            fillData(&g_data);

            render(g_window, &g_data);

            processData(&g_data);

#if OPTION_ENCODER
            int x, y;
            g_window->getMouseWheelData(&x, &y);

            MouseData mouseData;
            g_window->getMouseData(&mouseData);

            encoder::write(y, mouseData.button2IsUp);
#endif

            g_window->endUpdate();
        }
        else {
            close();
        }
    }
#endif
}

}
}
}
} // namespace eez::psu::simulator::front_panel;

