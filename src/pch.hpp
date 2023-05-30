#pragma once
// Precompiled headers file.

/* Standard Library */

/* Window */

#include <wx/wxprec.h>
#include <wx/nativewin.h>
#include <wx/msgdlg.h>
#include <wx/glcanvas.h>

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