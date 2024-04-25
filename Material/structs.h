#pragma once

namespace Offs
{
	constexpr int32_t ProcessEvent = 0x4D;

	constexpr int32_t ConsoleClass = 0x00F0; // UEngine
	constexpr int32_t GameViewport = 0x0910; // UEngine

	constexpr int32_t ViewportConsole = 0x0040; // UGameViewportClient
	constexpr int32_t World = 0x0078; // UGameViewportClient
	constexpr int32_t GameInstance = 0x0080; // UGameViewportClient

	constexpr int32_t AuthorityGameMode = 0x0158; // UWorld
	constexpr int32_t GameState = 0x0160; // UWorld
	constexpr int32_t OwningGameInstance = 0x01D8; // UWorld

	constexpr int32_t PlayerState = 0x0298; // AController
	constexpr int32_t Pawn = 0x02D0; // AController
	constexpr int32_t Character = 0x02E0; // AController
}

namespace Sigs
{
	constexpr const char* StaticFindObject = "48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC ? 4C 8B E9 48 8D 4D";
	constexpr const char* StaticLoadObject = "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B 85 ? ? ? ? 45 33 E4 4C 8B B5";

	constexpr const char* GetFirstPlayerController = "45 33 C0 44 39 81 ? ? ? ? 7E ? 48 8B 81 ? ? ? ? 44 8B 50";
	constexpr const char* GetWorldSettings = "48 89 5C 24 ? 57 48 83 EC ? 48 8B 41 ? 33 DB 48 8B F9 48 85 C0 74 ? 48 8B 98";
	constexpr const char* SpawnActor = "48 89 5C 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 0F 28 0D ? ? ? ? 48 8B FA";

	constexpr const char* Exec = "48 89 5C 24 ? 48 89 4C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 83 EC ? 4D 8B E1";

	constexpr const char* CheatScript = "48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 8B 41";
	constexpr const char* Summon = "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 33 ED 48 89 55 ? 80 3D";
	constexpr const char* BugIt = "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 8B 41 ? 45 33 ED 4C 8B FA";
	constexpr const char* God = "40 53 48 83 EC ? 8B 41 ? 41 B0";
	constexpr const char* Ghost = "48 89 5C 24 ? 57 48 83 EC ? 8B 41 ? A8 ? 74 ? 33 DB EB ? 48 8B 59 ? 48 8B 9B ? ? ? ? 48 85 DB 74 ? 8B 41 ? A8 ? 74 ? 33 FF EB ? 48 8B 79 ? 48 8D 15 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 0F 57 DB 48 8D 54 24 ? 45 33 C0 48 8B CF E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? E8 ? ? ? ? 48 8B CB E8 ? ? ? ? 84 C0 74 ? 48 8B CB E8 ? ? ? ? 48 8B 03 48 8B CB FF 90 ? ? ? ? 84 C0 75 ? 48 8B 03 48 8B CB FF 90 ? ? ? ? 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC 40 53";
	constexpr const char* Fly = "48 89 5C 24 ? 57 48 83 EC ? 8B 41 ? A8 ? 74 ? 33 DB EB ? 48 8B 59 ? 48 8B 9B ? ? ? ? 48 85 DB 74 ? 8B 41 ? A8 ? 74 ? 33 FF EB ? 48 8B 79 ? 48 8D 15 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 0F 57 DB 48 8D 54 24 ? 45 33 C0 48 8B CF E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? E8 ? ? ? ? 48 8B CB E8 ? ? ? ? 84 C0 74 ? 48 8B CB E8 ? ? ? ? 48 8B 03 48 8B CB FF 90 ? ? ? ? 84 C0 75 ? 48 8B 03 48 8B CB FF 90 ? ? ? ? 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC CC 48 8B C4";
}

template<class T>
class TArray
{
protected:
	T* Data;
	int32_t NumElements;
	int32_t MaxElements;

public:
	inline TArray()
		:NumElements(0), MaxElements(0), Data(nullptr)
	{
	}

	inline T& operator[](uint32_t Index)
	{
		return Data[Index];
	}

	inline const T& operator[](uint32_t Index) const
	{
		return Data[Index];
	}

	inline int32_t Num()
	{
		return NumElements;
	}

	inline int32_t Max()
	{
		return MaxElements;
	}

	inline int32_t GetSlack()
	{
		return MaxElements - NumElements;
	}

	inline bool IsValid()
	{
		return Data != nullptr;
	}

	inline bool IsValidIndex(int32_t Index)
	{
		return Index >= 0 && Index < NumElements;
	}
};

class FString : public TArray<wchar_t>
{
public:
	inline FString() = default;

	using TArray::TArray;

	inline FString(const wchar_t* WChar)
	{
		MaxElements = NumElements = *WChar ? std::wcslen(WChar) + 1 : 0;

		if (NumElements)
		{
			Data = const_cast<wchar_t*>(WChar);
		}
	}

	inline FString operator=(const wchar_t*&& Other)
	{
		return FString(Other);
	}

	inline std::string ToString()
	{
		if (IsValid())
		{
			std::wstring WData(Data);
			return std::string(WData.begin(), WData.end());
		}

		return "";
	}
};


struct FVector
{
public:
	double X;
	double Y;
	double Z;

	inline FVector()
		: X(0.0), Y(0.0), Z(0.0)
	{
	}

	inline FVector(decltype(X) Value)
		: X(Value), Y(Value), Z(Value)
	{
	}

	inline FVector(decltype(X) x, decltype(Y) y, decltype(Z) z)
		: X(x), Y(y), Z(z)
	{
	}

	inline bool operator==(const FVector& Other) const
	{
		return X == Other.X && Y == Other.Y && Z == Other.Z;
	}

	inline bool operator!=(const FVector& Other) const
	{
		return X != Other.X || Y != Other.Y || Z != Other.Z;
	}
};

struct FRotator
{
public:
	double Pitch;
	double Yaw;
	double Roll;

	inline FRotator()
		: Pitch(0.0), Yaw(0.0), Roll(0.0)
	{
	}

	inline FRotator(decltype(Pitch) Value)
		: Pitch(Value), Yaw(Value), Roll(Value)
	{
	}

	inline FRotator(decltype(Pitch) pitch, decltype(Yaw) yaw, decltype(Roll) roll)
		: Pitch(pitch), Yaw(yaw), Roll(roll)
	{
	}

	inline bool operator==(const FRotator& Other) const
	{
		return Pitch == Other.Pitch && Yaw == Other.Yaw && Roll == Other.Roll;
	}

	inline bool operator!=(const FRotator& Other) const
	{
		return Pitch != Other.Pitch || Yaw != Other.Yaw || Roll != Other.Roll;
	}
};

struct FActorSpawnParameters
{
	char Pad[0x65];
};

struct FOutputDevice
{
	char Pad[0x8];
};