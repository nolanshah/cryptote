// $Id$

#include <wx/wx.h>

#include "wgenpass.h"

class App : public wxApp
{
public:
    /// This function is called during application start-up.
    virtual bool	OnInit()
    {
	wxInitAllImageHandlers();

	// Create main window frame
	WGeneratePassword dlg(NULL, false);
	dlg.ShowModal();

	return false;
    }

    /// Application exit function
    virtual int		OnExit()
    {
	return 0;
    }
};

// This implements main(), WinMain() or whatever
IMPLEMENT_APP(App)
