#include "../RHITestBase.h"
#include "RHI/Presentation/RHISurface.h"
#include "RHI/Presentation/RHISwapChain.h"
#include "Presentation/RHIVkSurface.h"

namespace ArisenEngine::Testing
{
    /**
     * @brief Verifies that virtual swapchains (used by the Editor) can be resized
     * and correctly recreate their shared Win32 handles.
     */
    class RHIVkVirtualResizeTest : public RHITestBase
    {
    public:
        const char* GetName() const override { return "RHIVkVirtualResizeTest"; }
        TestCategory GetCategory() const override { return TestCategory::Unit; }

        // We use headless mode because we don't want a native Win32 window,
        // but we will manually create a virtual surface.
        bool IsHeadless() const override { return true; }
        
        bool Setup() override
        {
            if (!InitializeRHI(GetName()))
            {
                return false;
            }

            // Create the virtual surface BEFORE InitializeDevice calls InitLogicDevices
            LOG_INFO("Creating Virtual Surface (ID 0xFFFFFFFF)...");
            m_Instance->CreateSurface(0xFFFFFFFF);
            
            auto& vkSurface = static_cast<RHI::RHIVkSurface&>(m_Instance->GetSurface(0xFFFFFFFF));
            vkSurface.SetVirtualResolution(1280, 720);

            if (!InitializeDevice())
            {
                LOG_ERROR("Failed to initialize device for virtual surface");
                return false;
            }

            return SetupTest();
        }

        bool SetupTest() override
        {
            // Device should already be initialized for 0xFFFFFFFF because of our Setup override
            m_Device = m_Instance->GetLogicalDevice(0xFFFFFFFF);
            
            if (!m_Device)
            {
                LOG_ERROR("Failed to resolve RHI Device for virtual surface 0xFFFFFFFF");
                return false;
            }

            return true;
        }

        bool Run() override
        {
            LOG_INFO("Running Virtual Resize Test...");

            // 1. Access the swapchain
            RHI::RHISurface* surface = m_Device->GetSurface();
            if (!surface)
            {
                LOG_ERROR("Virtual surface is null!");
                return false;
            }

            RHI::RHISwapChain* swapChain = surface->GetSwapChain();
            if (!swapChain)
            {
                LOG_ERROR("Virtual swapchain is null!");
                return false;
            }

            // 2. Verify initial shared handle
            void* h1 = swapChain->GetSharedWin32Handle(0);
            LOG_INFOF("Initial Shared Win32 Handle: {}", h1);
            if (!h1)
            {
                LOG_ERROR("Initial shared handle is null (interop export failed)!");
                return false;
            }

            // 3. Perform Resize
            LOG_INFO("Triggering Resize: 1920x1080");
            m_Device->SetResolution(1920, 1080);

            // 4. Verify post-resize state
            // RecreateSwapChainIfNeeded should have been triggered.
            void* h2 = swapChain->GetSharedWin32Handle(0);
            LOG_INFOF("Post-Resize Shared Win32 Handle: {}", h2);
            
            if (!h2)
            {
                LOG_ERROR("Shared handle became null after resize! RecreateSwapChainIfNeeded likely failed.");
                return false;
            }

            // The handle might be the same or different depending on the driver's memory management,
            // but it MUST be non-null.
            LOG_INFO("Virtual Resize Test PASSED.");
            return true;
        }

        void TeardownTest() override
        {
            // Device cleanup is handled by RHITestBase::Teardown
        }
    };
}
