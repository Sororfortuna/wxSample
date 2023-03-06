#include "./main.hpp"
 
wxIMPLEMENT_APP(wxSampleApp);
 
bool wxSampleApp::OnInit() {
    FrameMain *frame = new FrameMain();
    frame->Show(true);
    return true;
}
 
FrameMain::FrameMain() : wxFrame(nullptr, wxID_ANY, "wxSampleApp") {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
 
    Bind(wxEVT_MENU, &FrameMain::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &FrameMain::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &FrameMain::OnExit, this, wxID_EXIT);
}
 
void FrameMain::OnExit(wxCommandEvent& event) {
    Close(true);
}
 
void FrameMain::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is an example to test different graphics API on a wxWidgets window...",
                 "About", wxOK | wxICON_INFORMATION);
}
 
void FrameMain::OnHello(wxCommandEvent& event) {
    wxLogMessage("Hello world from wxWidgets!");
}