#pragma once
#include <Boot/InitParams.hpp>

struct eventhandler_entry;
struct eventhandler_list;
typedef eventhandler_entry* eventhandler_tag;

extern "C"
{
    #include <sys/param.h>
    #include <sys/proc.h>
    #include <sys/sysproto.h> // ioctl_args

    void mira_entry(void* args);
};

extern "C" 

namespace Mira
{
    namespace OrbisOS
    {
        class ThreadManager;
    }

    namespace Driver
    {
        class CtrlDriver;
    }

    namespace Plugins
    {
        class PluginManager;
    }

    namespace Messaging
    {
        namespace Rpc
        {
            class Server;
        }

        class MessageManager;
    }

    namespace Utils
    {
        class Hook;
    }

    class Framework
    {
    private:
        static Framework* m_Instance;
        Mira::Boot::InitParams m_InitParams;

        bool m_EventHandlersInstalled;
        struct eventhandler_entry* m_SuspendTag;
        struct eventhandler_entry* m_ResumeTag;
        struct eventhandler_entry* m_ShutdownTag;

        Mira::Plugins::PluginManager* m_PluginManager;
        Mira::Messaging::MessageManager* m_MessageManager;

        Mira::Driver::CtrlDriver* m_CtrlDriver;

    public:
        static Framework* GetFramework();

    protected:
        Framework();
        ~Framework();

        bool InstallEventHandlers();
        bool RemoveEventHandlers();

    public:
        bool SetInitParams(Mira::Boot::InitParams* p_Params);
        Mira::Boot::InitParams* GetInitParams() { return &m_InitParams; }

        bool Initialize();
        bool Terminate();

        Mira::Plugins::PluginManager* GetPluginManager() { return m_PluginManager; }
        Mira::Messaging::MessageManager* GetMessageManager() { return m_MessageManager; }

        struct thread* GetMainThread();
        struct thread* GetSyscoreThread();
        struct thread* GetShellcoreThread();
        
    private:
        static void OnMiraSuspend(void* __unused p_Reserved);
        static void OnMiraResume(void* __unused p_Reserved);
        static void OnMiraShutdown(void* __unused p_Reserved);
    };
}