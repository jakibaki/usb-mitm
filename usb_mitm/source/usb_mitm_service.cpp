/*
 * Copyright (c) 2018 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <mutex>
#include <switch.h>
#include "usb_mitm_service.hpp"

void UsbMitmService::PostProcess(IMitmServiceObject *obj, IpcResponseContext *ctx) {
    /* No commands need postprocessing. */    
}

Result UsbMitmService::CreateInterfaceAvailableEvent(Out<CopiedHandle> event_hand, u8 index, UsbHsInterfaceFilter filter)
{
    // Let hid only get nintendo-devices
    filter.idVendor = 0x057e;
    filter.Flags |= 1;
    
    Event event;
    Result rc = usbHsCreateInterfaceAvailableEvent(&event, false, index, &filter);
    event_hand.SetValue(event.revent); // revent apparently is the handle that we want

    return rc;
}
