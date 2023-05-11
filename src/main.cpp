#include "./app.hpp"
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

wxIMPLEMENT_APP(wxSampleApp);

bool wxSampleApp::OnInit() {
    FrameMain *frame = new FrameMain();
    frame->Show(true);

#if PLATFORM_WIN32
    Diligent::Win32NativeWindow Window{frame->GetHandle()};
    if (m_DeviceType == Diligent::RENDER_DEVICE_TYPE_UNDEFINED)
#if D3D12_SUPPORTED
        m_DeviceType = Diligent::RENDER_DEVICE_TYPE_D3D12;
#elif VULKAN_SUPPORTED
        m_DeviceType = Diligent::RENDER_DEVICE_TYPE_VULKAN;
#endif
#endif
#if PLATFORM_LINUX
    Diligent::LinuxNativeWindow Window;
    WXWidget Widget = frame->GetHandle();
    if (Widget) {
        GdkWindow *gdkWin = gtk_widget_get_window(GTK_WIDGET(Widget));
        if (gdkWin != nullptr) {
            Window.pDisplay = GDK_WINDOW_XDISPLAY(gdkWin);
            Window.WindowId = GDK_WINDOW_XID(gdkWin);
        }
    }
#endif

    return true;
}

FrameMain::FrameMain() : wxFrame(nullptr, wxID_ANY, "wxSampleApp") {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello!\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("WxSampleApp is running...");

    Bind(wxEVT_MENU, &FrameMain::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &FrameMain::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &FrameMain::OnExit, this, wxID_EXIT);
}

void FrameMain::OnExit(wxCommandEvent &event) {
    Close(true);
}

void FrameMain::OnAbout(wxCommandEvent &event) {
    wxMessageBox("This is an example to test different graphics API on a wxWidgets window...",
                 "About", wxOK | wxICON_INFORMATION);
}

void FrameMain::OnHello(wxCommandEvent &event) {
    wxLogMessage("Hello world from wxWidgets!");
}