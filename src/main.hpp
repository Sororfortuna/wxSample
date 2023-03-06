#pragma once

#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
 

class wxSampleApp : public wxApp {
public:
    virtual bool OnInit();
};
 
class FrameMain : public wxFrame {
public:
    FrameMain();
 
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
 
enum {
    ID_Hello = 1
};