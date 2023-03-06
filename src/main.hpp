#pragma once

#include <wx/wxprec.h>
#include <wx/nativewin.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

/* Graphics API */

#include "Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h"
#include "Graphics/GraphicsEngine/interface/RenderDevice.h"
#include "Graphics/GraphicsEngine/interface/DeviceContext.h"
#include "Graphics/GraphicsEngine/interface/SwapChain.h"

#include "Graphics/GraphicsTools/interface/CommonlyUsedStates.h"
#include "Graphics/GraphicsTools/interface/MapHelper.hpp"

#include "Common/interface/BasicMath.hpp"
#include "Common/interface/RefCntAutoPtr.hpp"
 

class wxSampleApp : public wxApp {
private:
    Diligent::RefCntAutoPtr<Diligent::IRenderDevice>  m_pDevice;           // Render device used to create all other graphics object
    Diligent::RefCntAutoPtr<Diligent::IDeviceContext> m_pImmediateContext; // Immediate context is used to submit commands to the device
    Diligent::RefCntAutoPtr<Diligent::ISwapChain>     m_pSwapChain;        // Swap chain is used to present the rendered image to the screen
    Diligent::RefCntAutoPtr<Diligent::IPipelineState> m_pPSO;              // Pipeline State Object used to render the scene
    Diligent::RENDER_DEVICE_TYPE m_DeviceType = Diligent::RENDER_DEVICE_TYPE_VULKAN;
public:
    Diligent::IEngineFactory* GetEngineFactory() {return m_pDevice->GetEngineFactory();}
    Diligent::IRenderDevice*  GetDevice()        {return m_pDevice;}
    Diligent::IDeviceContext* GetContext()       {return m_pImmediateContext;}
    Diligent::ISwapChain*     GetSwapChain()     {return m_pSwapChain;}
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