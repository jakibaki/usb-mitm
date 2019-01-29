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

#pragma once
#include <switch.h>
#include <stratosphere.hpp>

enum UsbCmd : u32
{
    UsbCmd_CreateInterfaceAvailableEvent = 4
};

class UsbMitmService : public IMitmServiceObject
{
  public:
    UsbMitmService(std::shared_ptr<Service> s, u64 pid) : IMitmServiceObject(s, pid)
    {
        /* ... */
    }

    static bool ShouldMitm(u64 pid, u64 tid)
    {
        // TODO: hid only
        return tid == 0x0100000000000013UL;
    }

    static void PostProcess(IMitmServiceObject *obj, IpcResponseContext *ctx);

  protected:
    /* Overridden commands. */
    //virtual Result CreateAppletResource(Out<std::shared_ptr<IAppletResourceMitmService>> out,PidDescriptor pid, u64 arid) final;
    virtual Result CreateInterfaceAvailableEvent(Out<CopiedHandle> event_hand, u8 input_u8, UsbHsInterfaceFilter filter);

  public:
    DEFINE_SERVICE_DISPATCH_TABLE{
        MakeServiceCommandMeta<UsbCmd_CreateInterfaceAvailableEvent, &UsbMitmService::CreateInterfaceAvailableEvent>(),
    };
};
