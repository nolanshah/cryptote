/*******************************************************************************
 * src/cryptote/wfind.cpp
 *
 * Part of CryptoTE, see http://panthema.net/2007/cryptote
 *******************************************************************************
 * Copyright (C) 2008-2014 Timo Bingmann <tb@panthema.net>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 ******************************************************************************/

#include "wcryptote.h"
#include "wfind.h"
#include "wtextpage.h"

#if HAVE_WXWIDGETS3
  #include <wx/stc/stc.h>
#else
  #include <stc.h>
#endif

#include "common/tools.h"

// begin wxGlade: ::extracode
// end wxGlade

WFindReplace::WFindReplace(class WCryptoTE* parent, int id, const wxPoint& pos, const wxSize& size, long WXUNUSED(style))
    : wxPanel(parent, id, pos, size),
      wmain(parent)
{
    // begin wxGlade: WFindReplace::WFindReplace
    sizer3_staticbox = new wxStaticBox(this, -1, _("Options"));
    const wxString* comboFind_choices = NULL;
    comboFind = new wxComboBox(this, myID_COMBO_FIND, wxT(""), wxDefaultPosition, wxDefaultSize, 0, comboFind_choices, wxCB_DROPDOWN | wxCB_DROPDOWN);
    labelReplace = new wxStaticText(this, wxID_ANY, _("Replace:"));
    const wxString* comboReplace_choices = NULL;
    comboReplace = new wxComboBox(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, 0, comboReplace_choices, wxCB_DROPDOWN | wxCB_DROPDOWN);
    checkboxMatchWholeWord = new wxCheckBox(this, wxID_ANY, _("Match whole words only."));
    checkboxMatchCaseInsensitive = new wxCheckBox(this, wxID_ANY, _("Match case-sensitive."));
    checkboxMatchRegex = new wxCheckBox(this, wxID_ANY, _("Match as regular expression."));
    checkboxSearchBackwards = new wxCheckBox(this, wxID_ANY, _("Search backwards."));
    staticline1 = new wxStaticLine(this, wxID_ANY);
    buttonFind = new wxButton(this, wxID_FIND, wxEmptyString);
    buttonReplace = new wxButton(this, wxID_REPLACE, _("&Replace"));
    buttonReplaceAll = new wxButton(this, myID_REPLACEALL, _("Replace &All"));
    buttonClose = new wxButton(this, wxID_CLOSE, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade

    ShowReplace(false);

    comboFind->SetFocus();
}

void WFindReplace::set_properties()
{
    // begin wxGlade: WFindReplace::set_properties
    // end wxGlade
}

void WFindReplace::do_layout()
{
    // begin wxGlade: WFindReplace::do_layout
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer* sizer3 = new wxStaticBoxSizer(sizer3_staticbox, wxVERTICAL);
    wxFlexGridSizer* sizer2 = new wxFlexGridSizer(2, 2, 0, 0);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* label1 = new wxStaticText(this, wxID_ANY, _("Find:"));
    sizer2->Add(label1, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 4);
    sizer_1->Add(comboFind, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 4);
    sizer2->Add(sizer_1, 1, wxEXPAND, 0);
    sizer2->Add(labelReplace, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 4);
    sizer_2->Add(comboReplace, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
    sizer2->Add(sizer_2, 1, wxEXPAND, 0);
    sizer2->AddGrowableRow(0);
    sizer2->AddGrowableRow(1);
    sizer2->AddGrowableCol(1);
    sizer1->Add(sizer2, 1, wxTOP | wxEXPAND, 4);
    sizer3->Add(checkboxMatchWholeWord, 0, wxALL, 2);
    sizer3->Add(checkboxMatchCaseInsensitive, 0, wxALL, 2);
    sizer3->Add(checkboxMatchRegex, 0, wxALL, 2);
    sizer3->Add(checkboxSearchBackwards, 0, wxALL, 2);
    sizer1->Add(sizer3, 0, wxALL | wxEXPAND, 4);
    sizer1->Add(staticline1, 0, wxEXPAND, 0);
    sizer4->Add(buttonFind, 0, wxALL, 4);
    sizer4->Add(buttonReplace, 0, wxALL, 4);
    sizer4->Add(buttonReplaceAll, 0, wxALL, 4);
    sizer4->Add(5, 5, 1, 0, 0);
    sizer4->Add(buttonClose, 0, wxALL, 4);
    sizer1->Add(sizer4, 0, wxEXPAND, 0);
    SetSizer(sizer1);
    sizer1->Fit(this);
    // end wxGlade
}

void WFindReplace::ShowReplace(bool show)
{
    showreplace = show;

    labelReplace->Show(showreplace);
    comboReplace->Show(showreplace);

    buttonReplace->Show(showreplace);
    buttonReplaceAll->Show(showreplace);

    Layout();
}

BEGIN_EVENT_TABLE(WFindReplace, wxPanel)
    // begin wxGlade: WFindReplace::event_table
    EVT_TEXT(myID_COMBO_FIND, WFindReplace::OnComboTextSearch)
    EVT_BUTTON(wxID_FIND, WFindReplace::OnButtonFind)
    EVT_BUTTON(wxID_REPLACE, WFindReplace::OnButtonReplace)
    EVT_BUTTON(myID_REPLACEALL, WFindReplace::OnButtonReplaceAll)
    EVT_BUTTON(wxID_ANY, WFindReplace::OnButtonClose)
    // end wxGlade
END_EVENT_TABLE();

void WFindReplace::OnComboTextSearch(wxCommandEvent& WXUNUSED(event))
{
    havefound = false;
}

void WFindReplace::OnButtonFind(wxCommandEvent& WXUNUSED(event))
{
    // directly access the wxStyledTextCtrl on the WTextPage, no other page
    // will ever use the find & replace dialog.

    WTextPage* wtextpage = wxDynamicCast(wmain->cpage, WTextPage);
    if (!wtextpage) return;

    wxString findtext = comboFind->GetValue();

    if (findtext.IsEmpty())
    {
        wmain->UpdateStatusBar(_("Nothing to search for."));

        return;
    }

    {   // Add text into combo box at beginning if it is not already in.
        int pos = comboFind->FindString(findtext);
        if (pos != wxNOT_FOUND) {
            comboFind->Delete(pos);
        }

        comboFind->Insert(findtext, 0);
    }

    bool forward = !checkboxSearchBackwards->GetValue();

    wxStyledTextCtrl* editctrl = wtextpage->editctrl;

    if (forward)
    {
        editctrl->SetTargetStart(editctrl->GetCurrentPos());
        editctrl->SetTargetEnd(editctrl->GetLength());
    }
    else
    {
        editctrl->SetTargetStart(editctrl->GetCurrentPos() - 1);
        editctrl->SetTargetEnd(0);
    }

    int flags = 0;
    if (checkboxMatchWholeWord->GetValue()) flags |= wxSTC_FIND_WHOLEWORD;
    if (checkboxMatchCaseInsensitive->GetValue()) flags |= wxSTC_FIND_MATCHCASE;
    if (checkboxMatchRegex->GetValue()) flags |= wxSTC_FIND_REGEXP;
    editctrl->SetSearchFlags(flags);

    int respos = editctrl->SearchInTarget(findtext);

    bool wrapped = false;

    if (respos < 0)
    {
        // wrap-around search
        wrapped = true;

        if (forward)
        {
            editctrl->SetTargetStart(0);
            editctrl->SetTargetEnd(editctrl->GetCurrentPos());
        }
        else
        {
            editctrl->SetTargetStart(editctrl->GetLength());
            editctrl->SetTargetEnd(editctrl->GetCurrentPos());
        }

        respos = editctrl->SearchInTarget(findtext);
    }

    bool found = false;
    if (respos >= 0)
    {
        found = true;
        int start = editctrl->GetTargetStart();
        int end = editctrl->GetTargetEnd();

        editctrl->EnsureVisible(editctrl->LineFromPosition(start));
        editctrl->SetSelection(start, end);
    }

    if (found && !wrapped) {
        wmain->UpdateStatusBar(wxT(""));
    }
    else if (found && wrapped) {
        if (forward)
            wmain->UpdateStatusBar(_("Search wrapped to beginning of document."));
        else
            wmain->UpdateStatusBar(_("Search wrapped to end of document."));
    }
    else if (!found) {
        wmain->UpdateStatusBar(_("Search string not found in document."));
    }

    havefound = found;
}

void WFindReplace::OnButtonReplace(wxCommandEvent& event)
{
    WTextPage* wtextpage = wxDynamicCast(wmain->cpage, WTextPage);
    if (!wtextpage) return;

    wxString replacetext = comboReplace->GetValue();

    {   // Add text into combo box at beginning if it is not already in.
        int pos = comboReplace->FindString(replacetext);
        if (pos != wxNOT_FOUND) {
            comboReplace->Delete(pos);
        }

        comboReplace->Insert(replacetext, 0);
    }

    if (havefound)
    {
        wtextpage->editctrl->ReplaceTarget(replacetext);
    }

    OnButtonFind(event);
}

void WFindReplace::OnButtonReplaceAll(wxCommandEvent& event)
{
    if (!wmain->cpage || !wmain->cpage->IsKindOf(CLASSINFO(WTextPage))) return;
    WTextPage* wtextpage = (WTextPage*)wmain->cpage;

    wxString replacetext = comboReplace->GetValue();

    {   // Add text into combo box at beginning if it is not already in.
        int pos = comboReplace->FindString(replacetext);
        if (pos != wxNOT_FOUND) {
            comboReplace->Delete(pos);
        }

        comboReplace->Insert(replacetext, 0);
    }

    if (!havefound) {
        OnButtonFind(event);
    }

    while (havefound)
    {
        wtextpage->editctrl->ReplaceTarget(replacetext);

        OnButtonFind(event);
    }
}

void WFindReplace::OnButtonClose(wxCommandEvent& WXUNUSED(event))
{
    wmain->HidePane(this);
}

// wxGlade: add WFindReplace event handlers

/******************************************************************************/
