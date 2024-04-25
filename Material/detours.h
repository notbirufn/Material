#pragma once

static bool (*Exec)(void* World, void* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);

static bool ExecDetour(void* World, void* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
    void* PlayerController = UWorld__GetFirstPlayerController(World);

    if (PlayerController)
    {
        std::wstring Command(Cmd);

        std::string CmdStr = std::string(Command.begin(), Command.end());
        std::string ArgStr;

        if (CmdStr.find(" ") != std::string::npos)
        {
            ArgStr = CmdStr.substr(CmdStr.find(" ") + 1);
        }

        transform(CmdStr.begin(), CmdStr.end(), CmdStr.begin(), toupper);

        if (CmdStr.starts_with("SPAWNACTOR")) // SpawnActor <args...>
        {
            return Handle_SpawnActor_Command(World, ArgStr);
        }
    }

    return Exec(World, InWorld, Cmd, Ar);
}

#define DetoursEasy(address, detour) \
    DetourTransactionBegin(); \
    DetourUpdateThread(GetCurrentThread()); \
    DetourAttach(reinterpret_cast<PVOID*>(&address), detour); \
    DetourTransactionCommit(); \

namespace Detours
{
	inline bool Init()
	{
        uintptr_t ExecAddress = Memcury::Scanner::FindPattern(Sigs::Exec).Get();

        Exec = decltype(Exec)(ExecAddress);

        DetoursEasy(Exec, ExecDetour);

        return true;
	}
}