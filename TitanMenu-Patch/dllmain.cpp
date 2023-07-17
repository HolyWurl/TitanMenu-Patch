#include "pch.h"

DWORD WINAPI go(LPVOID lp)
{
    if (AllocConsole()) {
        freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    }

    uint64_t base_addr = NULL;
    do
    {
        base_addr = (uint64_t)GetModuleHandleA("Titan.dll");
        Sleep(1500);
        std::cout << "Waiting Titan.dll to patch" << std::endl;
    } while (!base_addr);

    std::cout << "Start to patch!" << std::endl;
    while (true)
    {
        *(bool*)(base_addr + 0x323838) = true;  //A cunning method, xD. Make sure it's in the loop.
        *(bool*)(base_addr + 0x342c22) = true;  //Crash you when you enter the game.
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, go, nullptr, 0, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

