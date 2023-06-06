#include "./app.hpp"

wxIMPLEMENT_APP(wxSampleApp);

bool wxSampleApp::OnInit() {
    MainFrame* frame = new MainFrame();
    frame->Show(true);

#if PLATFORM_WIN32
    Diligent::Win32NativeWindow Window{frame->GetHandle()};
    if (m_DeviceType == Diligent::RENDER_DEVICE_TYPE_UNDEFINED)
#if D3D12_SUPPORTED
        m_DeviceType = Diligent::RENDER_DEVICE_TYPE_D3D12;
#elif VULKAN_SUPPORTED
        m_DeviceType = Diligent::RENDER_DEVICE_TYPE_VULKAN;
#elif GL_SUPPORTED
        m_DeviceType = Diligent::RENDER_DEVICE_TYPE_GL;
#endif
#elif PLATFORM_LINUX
    Diligent::LinuxNativeWindow Window;
    WXWidget Widget = frame->GetHandle();
    if (Widget) {
        GdkWindow* gdkWin = gtk_widget_get_window(GTK_WIDGET(Widget));
        if (gdkWin != nullptr) {
            Window.pDisplay = GDK_WINDOW_XDISPLAY(gdkWin);
            Window.WindowId = GDK_WINDOW_XID(gdkWin);
            // alert message with the window id
            wxMessageBox(wxString::Format("Window id: %u", Window.WindowId));
        }
    }
    if (m_DeviceType == Diligent::RENDER_DEVICE_TYPE_UNDEFINED)
#if VULKAN_SUPPORTED
        m_DeviceType = Diligent::RENDER_DEVICE_TYPE_VULKAN;
#elif GL_SUPPORTED
        m_DeviceType = Diligent::RENDER_DEVICE_TYPE_GL;
#endif
#endif // PLATFORM

    return true;
}

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "wxSampleApp") {
    wxMenu* menuFile = new wxMenu;
    wxMenu* menuHelp = new wxMenu;
    wxMenuBar* menuBar = new wxMenuBar;
    m_canvas = new wxGLCanvas(this, wxID_ANY, nullptr, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);

    menuFile->Append(ID_Hello, "&Hello!\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    menuHelp->Append(wxID_ABOUT);

    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("WxSampleApp is running...");

    Bind(wxEVT_MENU, &MainFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_PAINT, &MainFrame::OnPaint, this);

}

/* Callbacks */

void MainFrame::OnExit(wxCommandEvent &event) {
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent &event) {
    wxMessageBox("This is an example to test different graphics API on a wxWidgets window...",
                 "About", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnHello(wxCommandEvent& event) {
    wxGLContext context(m_canvas);
    m_canvas->SetCurrent(context);

    const GLubyte* version = glGetString(GL_VERSION);
    if (version) {
        std::cout << "OpenGL version: " << version << std::endl;
    } else {
        std::cout << "Failed to retrieve OpenGL version" << std::endl;
    }
}


void MainFrame::OnPaint(wxPaintEvent &event) {
    // Set up the OpenGL context
    wxGLContext context(m_canvas);
    m_canvas->SetCurrent(context);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffers to display the rendered content
    m_canvas->SwapBuffers();
}