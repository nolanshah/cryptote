// -*- C++ -*- generated by wxGlade 0.6.3 on Tue Mar 11 23:21:53 2008
// $Id$

#include <wx/wx.h>
// begin wxGlade: ::dependencies
#include <wx/statline.h>
// end wxGlade

#ifndef WPASS_H
#define WPASS_H

// begin wxGlade: ::extracode
// end wxGlade

class WSetPassword : public wxDialog
{
public:
    // begin wxGlade: WSetPassword::ids
    enum {
        myID_TEXTPASS = wxID_HIGHEST + 1000
    };
    // end wxGlade

    WSetPassword(wxWindow* parent, const wxString& filename, int id=wxID_ANY, const wxString& title=wxEmptyString, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

    /// Return pass after user enters it.
    wxString	GetPass() const;

private:
    // begin wxGlade: WSetPassword::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: WSetPassword::attributes
    wxStaticText* labelQuery;
    wxTextCtrl* textctrlPass;
    wxGauge* gaugeStrength;
    wxButton* buttonOK;
    wxButton* buttonCancel;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    virtual void OnTextPassEnter(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void OnTextPass(wxCommandEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class

class WGetPassword : public wxDialog
{
public:
    // begin wxGlade: WGetPassword::ids
    enum {
        myID_TEXTPASS = wxID_HIGHEST + 1002
    };
    // end wxGlade

    WGetPassword(wxWindow* parent, const wxString& filename, int id=wxID_ANY, const wxString& title=wxEmptyString, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

    /// Return pass after user enters it.
    wxString	GetPass() const;

private:
    // begin wxGlade: WGetPassword::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: WGetPassword::attributes
    wxStaticText* labelQuery;
    wxTextCtrl* textctrlPass;
    wxButton* buttonOK;
    wxButton* buttonCancel;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    virtual void OnTextPassEnter(wxCommandEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class

#endif // WPASS_H
