#pragma once

#include <Engine/EngineGlobals.h>

namespace Neowise {
    /** 
    * Return value from CEngineBoot class' methods.
    */
    enum EEngineBoot {
        E_ENGINE_BOOT_SUCCESS,
        E_ENGINE_BOOT_ERROR_CANT_INSTANTIATE_LOOP,
        E_ENGINE_BOOT_ERROR_SETUP_SYSTEMS
    };

    /** 
    * Initial information to tell engine to boot with
    * a specific set of options.
    */
    struct DEngineBootInfo {
        CStringView baseScenePath;
    };

    /** 
    * A 'bootloader' of an entire engine, since there starts whole initialization
    * process and ends it's execution with ***Shutdown() function called.
    */
    class NW_API CEngineBoot {
    public:
        /** 
        * EarlyInit(info) function initializes memory system and setups basic things
        * like virtual filesystem.
        */
        EEngineBoot earlyInit(DEngineBootInfo const& info);

        /** 
        * LateInit() function initializes window, graphics, audio and physics systems.
        * Also create and setup minimal barebones scene, if no scene path was provided
        * at EarlyInit() call.
        */
        EEngineBoot lateInit();

        /** 
        * EarlyShutdown() function forces all systems, that allocated resources either
        * on CPU or GPU to release it, and wait till this completes.
        */
        void earlyShutdown();

        /** 
        * LateShutdown() function destroys all systems, frees all allocated memory.
        * Exits application.
        */
        void lateShutdown();
    };
}
