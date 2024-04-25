#pragma once

static inline void EnableConsole()
{
    static void* GEngine = StaticFindObject(nullptr, nullptr, L"/Engine/Transient.FortEngine_2147482646", false);

    if (GEngine)
    {
        void** VTable = *reinterpret_cast<void***>(GEngine);

        void* ConsoleClass = *reinterpret_cast<void**>(__int64(GEngine) + Offs::ConsoleClass);
        void* GameViewport = *reinterpret_cast<void**>(__int64(GEngine) + Offs::GameViewport);

        if (ConsoleClass && GameViewport)
        {
            static void* GameplayStatics = StaticFindObject(nullptr, nullptr, L"/Script/Engine.Default__GameplayStatics", false);
            static void* Function = StaticFindObject(nullptr, nullptr, L"/Script/Engine.GameplayStatics.SpawnObject", false);

            struct GameplayStatics_SpawnObject
            {
                void* ObjectClass;
                void* Param_Outer;
                void* ReturnValue;
            };

            GameplayStatics_SpawnObject Params{ ConsoleClass, GameViewport };

            reinterpret_cast<void(*)(void*, void*, void*)>(VTable[Offs::ProcessEvent])(GameplayStatics, Function, &Params);

            if (Params.ReturnValue)
            {
                *reinterpret_cast<void**>(__int64(GameViewport) + Offs::ViewportConsole) = Params.ReturnValue;
            }
        }
    }
}

static inline void ConsoleMessage(void* GWorld, const std::string& Message)
{
    void* AuthorityGameMode = *reinterpret_cast<void**>(uintptr_t(GWorld) + Offs::AuthorityGameMode);

    if (AuthorityGameMode)
    {
        void** VTable = *reinterpret_cast<void***>(AuthorityGameMode);

        static void* Say = StaticFindObject(nullptr, nullptr, L"/Script/Engine.GameMode.Say", false);
        FString Msg = std::wstring(Message.begin(), Message.end()).c_str();
        reinterpret_cast<void(*)(void*, void*, void*)>(VTable[Offs::ProcessEvent])(AuthorityGameMode, Say, &Msg);
    }
}

static inline void ConsoleCommand(void* GWorld, const std::string& Command)
{

}


static inline bool Handle_SpawnActor_Command(void* World, const std::string& ArgStr)
{
    void* PlayerController = UWorld__GetFirstPlayerController(World);

    if (PlayerController)
    {
        void* ActorClass = StaticLoadObject(StaticFindObject(nullptr, nullptr, L"/Script/Engine.BlueprintGeneratedClass", false), nullptr, std::wstring(ArgStr.begin(), ArgStr.end()).c_str(), L"", 0, nullptr, false, nullptr);

        if (ActorClass)
        {
            void* Pawn = *reinterpret_cast<void**>(uintptr_t(PlayerController) + Offs::Pawn);

            if (Pawn)
            {
                void** VTable = *reinterpret_cast<void***>(Pawn);

                static void* K2_GetActorLocation = StaticFindObject(nullptr, nullptr, L"/Script/Engine.Actor.K2_GetActorLocation", false);
                FVector ActorLocation;
                reinterpret_cast<void(*)(void*, void*, void*)>(VTable[Offs::ProcessEvent])(Pawn, K2_GetActorLocation, &ActorLocation);

                static void* K2_GetActorRotation = StaticFindObject(nullptr, nullptr, L"/Script/Engine.Actor.K2_GetActorRotation", false);
                FRotator ActorRotation;
                reinterpret_cast<void(*)(void*, void*, void*)>(VTable[Offs::ProcessEvent])(Pawn, K2_GetActorRotation, &ActorRotation);

                UWorld__SpawnActor(World, ActorClass, ActorLocation, ActorRotation, FActorSpawnParameters());
            }
        }
        else
        {
            ConsoleMessage(World, std::string(ArgStr + " not found."));
        }
    }

    return true;
}