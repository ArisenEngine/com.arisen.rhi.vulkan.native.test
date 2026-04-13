#include "../Framework/TestRunner.h"
#include "../RHI/Unit/RHISyncTest.h"
#include "../RHI/Unit/RHIBindlessTest.h"
#include "../RHI/Unit/RHIMultiThreadedTest.h"
#include "../RHI/Unit/RHIBatchApiTest.h"
#include "../RHI/Unit/RHIMemoryAliasingTest.h"
#include "../RHI/Unit/RHISecondaryCommandBufferTest.h"
#include "../RHI/Unit/RHIAsyncComputeTest.h"
#include "../RHI/Unit/RHIDebugTest.h"
#include "../RHI/Unit/RHIInspectorTest.h"
#include "../RHI/Unit/RHIMultiQueueNativeTest.h"
#include "../RHI/Unit/RHIMultiQueueResourceDisposalTest.h"
#include "../RHI/Unit/RHIVkVirtualResizeTest.h"

// Rendering Tests
#include "../RHI/Rendering/RHIBasicRenderingTest.h"
#include "../RHI/Rendering/RHIGPUParticleTest.h"
#include "../RHI/Rendering/RHIGeometryShaderTest.h"
#include "../RHI/Rendering/RHIMeshShaderTest.h"
#include "../RHI/Rendering/RHIMultiDrawIndirectTest.h"
#include "../RHI/Rendering/RHIRayTracingTest.h"
#include "../RHI/Rendering/RHITessellationShaderTest.h"
#include "../RHI/Rendering/RHIVRSShadingRateTest.h"

#include <iostream>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

using namespace ArisenEngine::Testing;

extern "C"
{
    /**
     * @brief Exports all native tests to the Arisen Test Runner.
     */
    EXPORT void RegisterNativeTests(void (*registerCallback)(const char*, void (*)()))
    {
        // 1. Locally register all tests in the C++ registry
        TestRunner::RegisterTest<RHIBindlessTest>();
        TestRunner::RegisterTest<RHISyncTest>();
        TestRunner::RegisterTest<RHIMultiThreadedTest>();
        TestRunner::RegisterTest<RHIBatchApiTest>();
        TestRunner::RegisterTest<RHISecondaryCommandBufferTest>();
        TestRunner::RegisterTest<RHIAsyncComputeTest>();
        TestRunner::RegisterTest<RHIDebugTest>();
        TestRunner::RegisterTest<RHIInspectorTest>();
        TestRunner::RegisterTest<RHIMemoryAliasingTest>();
        TestRunner::RegisterTest<RHIMultiQueueNativeTest>();
        TestRunner::RegisterTest<RHIMultiQueueResourceDisposalTest>();
        TestRunner::RegisterTest<RHIVkVirtualResizeTest>();

        // Register Rendering Tests
        TestRunner::RegisterTest<RHIBasicRenderingTest>();
        TestRunner::RegisterTest<RHIGPUParticleTest>();
        TestRunner::RegisterTest<RHIGeometryShaderTest>();
        TestRunner::RegisterTest<RHIMeshShaderTest>();
        TestRunner::RegisterTest<RHIMultiDrawIndirectTest>();
        TestRunner::RegisterTest<RHIRayTracingTest>();
        TestRunner::RegisterTest<RHITessellationShaderTest>();
        TestRunner::RegisterTest<RHIVRSShadingRateTest>();

        // 2. Wrap them for the C# callback
        // This is a simple bridge that allows the C# TestRunner to "see" the native tests

        // --- Unit Tests ---
        registerCallback("Vulkan.Native.SyncTest", []() { TestRunner::RunTestByName("RHISyncTest"); });
        registerCallback("Vulkan.Native.BindlessTest", []() { TestRunner::RunTestByName("RHIBindlessTest"); });
        registerCallback("Vulkan.Native.MultiThreadedTest", []() { TestRunner::RunTestByName("RHIMultiThreadedTest"); });
        registerCallback("Vulkan.Native.BatchApiTest", []() { TestRunner::RunTestByName("RHIBatchApiTest"); });
        registerCallback("Vulkan.Native.SecondaryCommandBufferTest", []() { TestRunner::RunTestByName("RHISecondaryCommandBufferTest"); });
        registerCallback("Vulkan.Native.AsyncComputeTest", []() { TestRunner::RunTestByName("RHIAsyncComputeTest"); });
        registerCallback("Vulkan.Native.DebugTest", []() { TestRunner::RunTestByName("RHIDebugTest"); });
        registerCallback("Vulkan.Native.InspectorTest", []() { TestRunner::RunTestByName("RHIInspectorTest"); });
        registerCallback("Vulkan.Native.MemoryAliasingTest", []() { TestRunner::RunTestByName("RHIMemoryAliasingTest"); });
        registerCallback("Vulkan.Native.MultiQueueNativeTest", []() { TestRunner::RunTestByName("RHIMultiQueueNativeTest"); });
        registerCallback("Vulkan.Native.MultiQueueResourceDisposalTest", []() { TestRunner::RunTestByName("RHIMultiQueueResourceDisposalTest"); });
        registerCallback("Vulkan.Native.VirtualResizeTest", []() { TestRunner::RunTestByName("RHIVkVirtualResizeTest"); });

        // --- Rendering Tests ---
        registerCallback("Vulkan.Native.BasicRenderingTest", []() { TestRunner::RunTestByName("RHIBasicRenderingTest"); });
        registerCallback("Vulkan.Native.GPUParticleTest", []() { TestRunner::RunTestByName("RHIGPUParticleTest"); });
        registerCallback("Vulkan.Native.GeometryShaderTest", []() { TestRunner::RunTestByName("RHIGeometryShaderTest"); });
        registerCallback("Vulkan.Native.MeshShaderTest", []() { TestRunner::RunTestByName("RHIMeshShaderTest"); });
        registerCallback("Vulkan.Native.MultiDrawIndirectTest", []() { TestRunner::RunTestByName("RHIMultiDrawIndirectTest"); });
        registerCallback("Vulkan.Native.RayTracingTest", []() { TestRunner::RunTestByName("RHIRayTracingTest"); });
        registerCallback("Vulkan.Native.TessellationShaderTest", []() { TestRunner::RunTestByName("RHITessellationShaderTest"); });
        registerCallback("Vulkan.Native.VRSShadingRateTest", []() { TestRunner::RunTestByName("RHIVRSShadingRateTest"); });
    }
}
