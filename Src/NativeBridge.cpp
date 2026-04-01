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

        // 2. Wrap them for the C# callback
        // This is a simple bridge that allows the C# TestRunner to "see" the native tests
        registerCallback("Vulkan.Native.SyncTest", []() {
             TestRunner::RunTestByName("RHISyncTest");
        });
        
        registerCallback("Vulkan.Native.MultiThreadedTest", []() {
             TestRunner::RunTestByName("RHIMultiThreadedTest");
        });

        registerCallback("Vulkan.Native.MemoryAliasingTest", []() {
             TestRunner::RunTestByName("RHIMemoryAliasingTest");
        });
    }
}
