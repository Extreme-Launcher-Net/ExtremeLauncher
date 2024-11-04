// SPDX-FileCopyrightText: 2022 Rachel Powers <508861+Ryex@users.noreply.github.com>
//
// SPDX-License-Identifier: GPL-3.0-only

/*
 *  Extreme Launcher - Minecraft Launcher
 *  Copyright (C) 2022 Rachel Powers <508861+Ryex@users.noreply.github.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "ExtremeUpdater.h"
int main(int argc, char* argv[])
{
    ExtremeUpdaterApp wUpApp(argc, argv);

    switch (wUpApp.status()) {
        case ExtremeUpdaterApp::Starting:
        case ExtremeUpdaterApp::Initialized: {
            return wUpApp.exec();
        }
        case ExtremeUpdaterApp::Failed:
            return 1;
        case ExtremeUpdaterApp::Succeeded:
            return 0;
        default:
            return -1;
    }
}
