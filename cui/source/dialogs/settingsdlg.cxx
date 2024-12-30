/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <config_features.h>
#include <osl/process.h>
#include <vcl/layout.hxx>
#include <vcl/weld.hxx>
#include <vcl/svapp.hxx>
#include <vcl/settings.hxx>

#include <tools/stream.hxx>
#include <rtl/bootstrap.hxx>
#include <unotools/configmgr.hxx>
#include <unotools/bootstrap.hxx>
#include <com/sun/star/uno/Any.h>
#include <vcl/graph.hxx>
#include <vcl/graphicfilter.hxx>
#include <svtools/langhelp.hxx>

#include <com/sun/star/system/SystemShellExecuteFlags.hpp>
#include <com/sun/star/system/SystemShellExecute.hpp>
#include <comphelper/processfactory.hxx>
#include <comphelper/anytostring.hxx>
#include <cppuhelper/exc_hlp.hxx>
#include <cppuhelper/bootstrap.hxx>
#include <basegfx/numeric/ftools.hxx>
#include <com/sun/star/geometry/RealRectangle2D.hpp>
#include <svtools/optionsdrawinglayer.hxx>

#include <sfx2/sfxuno.hxx>
#include <settingsdlg.hxx>
#include <config_buildid.h>
#include <sfx2/app.hxx>
#include <rtl/ustrbuf.hxx>

#include <officecfg/Office/Common.hxx>

#include <Windows.h>


using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star;


typedef bool (WINAPI *IsGAEnabled)();
typedef void (WINAPI *SetGAEnabled)(bool);
typedef bool (WINAPI *GASendEvent)(char*, char*, char*, int);


bool getGAState()
{
    bool ret = true;

    try
    {
        HINSTANCE hGetProcIDDLL = LoadLibrary("IAPWrapper.dll");
        IsGAEnabled isgaEnabled = (IsGAEnabled)GetProcAddress(hGetProcIDDLL, "IsGAEnabled");
        if (isgaEnabled)
        {
            ret = isgaEnabled();
        }
    }
    catch (const Exception&)
    {
    }

    return ret;
}

void setGAState(bool state)
{
    try
    {
        HINSTANCE hGetProcIDDLL = LoadLibrary("IAPWrapper.dll");
        SetGAEnabled setgaEnabled = (SetGAEnabled)GetProcAddress(hGetProcIDDLL, "SetGAEnabled");
        if (setgaEnabled)
        {
            setgaEnabled(state);
        }
    }
    catch (const Exception&)
    {
    }

    return ;
}

void SettingsSendGAEvent(char* strCategory, char* strAction, char* strLabel, int value)
{
    HINSTANCE hGetProcIDDLL = LoadLibrary("IAPWrapper.dll");
    GASendEvent gaSendEvent = (GASendEvent)GetProcAddress(hGetProcIDDLL, "GASendEvent");
    if (gaSendEvent)
    {
        gaSendEvent(strCategory, strAction, strLabel, value);
    }
}

SettingsDialog::SettingsDialog(vcl::Window* pParent)
    : SfxModalDialog(pParent, "SettingsDialog", "cui/ui/settingsdialog.ui")
{
	get(m_sharedataCB, "sharedata");

    bool gaEnabled = getGAState();

    m_sharedataCB->Check(gaEnabled);

    get<PushButton>("ok")->SetClickHdl(LINK(this, SettingsDialog, changesetHdl));
//    get<PushButton>("ok")->GrabFocus();
}

SettingsDialog::~SettingsDialog()
{
    m_sharedataCB.clear();
    disposeOnce();
}

void SettingsDialog::dispose()
{
    SfxModalDialog::dispose();
}

IMPL_LINK_NOARG(SettingsDialog, changesetHdl, Button*, void)
{
    try
    {
        if (m_sharedataCB->IsChecked() == true)
        {
            setGAState(true);
        }
        else
        {
            setGAState(false);
        }
    }
    catch (const Exception&)
    {
    }
    EndDialog(RET_OK);
}

void SettingsDialog::Resize()
{
    SfxModalDialog::Resize();
}

bool SettingsDialog::Close()
{
    EndDialog(RET_OK);
    return false;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
