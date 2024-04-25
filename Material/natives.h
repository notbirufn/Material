#pragma once

static void* (*StaticFindObject)(void* Class, void* InOuter, const TCHAR* Name, bool ExactClass);
static void* (*StaticLoadObject)(void* Class, void* InOuter, const TCHAR* Name, const TCHAR* Filename, uint32_t LoadFlags, void* Sandbox, bool bAllowObjectReconciliation, void* InSerializeContext);

static void* (*UWorld__GetFirstPlayerController)(void* World);
static void* (*UWorld__GetWorldSettings)(void* World, bool bCheckStreamingPersistent, bool bChecked);
static void* (*UWorld__SpawnActor)(void* World, void* InClass, FVector const& Location, FRotator const& Rotation, const FActorSpawnParameters& SpawnParameters);

static void (*UCheatManager__CheatScript)(void* CheatManager, FString ScriptName);
static void (*UCheatManager__Summon)(void* CheatManager, const FString& ClassName);
static void (*UCheatManager__BugIt)(void* CheatManager, const FString& ScreenShotDescription);
static void (*UCheatManager__God)(void* CheatManager);
static void (*UCheatManager__Ghost)(void* CheatManager);
static void (*UCheatManager__Fly)(void* CheatManager);

namespace Natives
{
	inline bool Init()
	{
        uintptr_t StaticFindObjectAddress = Memcury::Scanner::FindPattern(Sigs::StaticFindObject).Get();
        uintptr_t StaticLoadObjectAddress = Memcury::Scanner::FindPattern(Sigs::StaticLoadObject).Get();

        uintptr_t GetFirstPlayerControllerAddress = Memcury::Scanner::FindPattern(Sigs::GetFirstPlayerController).Get();
        uintptr_t GetWorldSettingsAddress = Memcury::Scanner::FindPattern(Sigs::GetWorldSettings).Get();
        uintptr_t SpawnActorAddress = Memcury::Scanner::FindPattern(Sigs::SpawnActor).Get();

        uintptr_t CheatScriptAddress = Memcury::Scanner::FindPattern(Sigs::CheatScript).Get();
        uintptr_t SummonAddress = Memcury::Scanner::FindPattern(Sigs::Summon).Get();
        uintptr_t BugItAddress = Memcury::Scanner::FindPattern(Sigs::BugIt).Get();
        uintptr_t GodAddress = Memcury::Scanner::FindPattern(Sigs::God).Get();
        uintptr_t GhostAddress = Memcury::Scanner::FindPattern(Sigs::Ghost).Get();
        uintptr_t FlyAddress = Memcury::Scanner::FindPattern(Sigs::Fly).Get();

        StaticFindObject = decltype(StaticFindObject)(StaticFindObjectAddress);
        StaticLoadObject = decltype(StaticLoadObject)(StaticLoadObjectAddress);

        UWorld__GetFirstPlayerController = decltype(UWorld__GetFirstPlayerController)(GetFirstPlayerControllerAddress);
        UWorld__GetWorldSettings = decltype(UWorld__GetWorldSettings)(GetWorldSettingsAddress);
        UWorld__SpawnActor = decltype(UWorld__SpawnActor)(SpawnActorAddress);

        UCheatManager__CheatScript = decltype(UCheatManager__CheatScript)(CheatScriptAddress);
        UCheatManager__Summon = decltype(UCheatManager__Summon)(SummonAddress);
        UCheatManager__BugIt = decltype(UCheatManager__BugIt)(BugItAddress);
        UCheatManager__God = decltype(UCheatManager__God)(GodAddress);
        UCheatManager__Ghost = decltype(UCheatManager__Ghost)(GhostAddress);
        UCheatManager__Fly = decltype(UCheatManager__Fly)(FlyAddress);

        return true;
	}
}