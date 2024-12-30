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
#ifndef INCLUDED_CUI_SOURCE_INC_SETTINGSDLG_HXX
#define INCLUDED_CUI_SOURCE_INC_SETTINGSDLG_HXX

#include <vcl/accel.hxx>
#include <vcl/button.hxx>
#include <vcl/fixed.hxx>
#include <vcl/fixedhyper.hxx>
#include <vcl/vclmedit.hxx>
#include <sfx2/basedlgs.hxx>
#include <vector>

// class SettingsDialog -----------------------------------------------------

class SettingsDialog : public SfxModalDialog
{
private:
    DECL_LINK(changesetHdl, Button*, void);
    VclPtr<ListBox>                aGAState;
	VclPtr<CheckBox>               m_sharedataCB;


protected:
    virtual bool Close() override;
    virtual void Resize() override;

public:
    SettingsDialog(vcl::Window* pParent);
    virtual ~SettingsDialog() override;
    virtual void dispose() override;
};

#endif // INCLUDED_CUI_SOURCE_INC_RATEDLG_HXX


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
