#include "SDKInitializer.h"

#include "../SDK/Classes/Engine_classes.h"
#include "../SDK/Classes/FortniteGame_classes.h"

#include "../../Utilities/Logger.h"

void SDKInitializer::WalkVFT(const char* TargetFunctionName, void** VFT, void* TargetFunction, uintptr_t& VFTIndex, int SearchRange) {
	DEBUG_LOG(LOG_INFO, skCrypt("Walking VFT searching for ").decrypt() + std::string(TargetFunctionName) + skCrypt(" VFT index").decrypt());

	for (int i = 0; !VFTIndex && i < SearchRange; ++i) {
		if (VFT[i] == TargetFunction) {
			VFTIndex = i;
			break;
		}
	}

	if (VFTIndex) {
		DEBUG_LOG(LOG_OFFSET, std::string(TargetFunctionName) + skCrypt(" VFT index found: ").decrypt() + std::to_string(VFTIndex));
	}
	else {
		THROW_ERROR(skCrypt("Failed to find ").decrypt() + std::string(TargetFunctionName) + skCrypt(" VFT index!").decrypt(), CRASH_ON_NOT_FOUND);
	}
}
void SDKInitializer::InitVFTIndex(const char* VFTName, std::vector<const char*> PossibleSigs, const wchar_t* SearchString, uintptr_t& VFTIndex, int SearchRange, int SearchBytesBehind) {
	DEBUG_LOG(LOG_INFO, skCrypt("Searching for ").decrypt() + std::string(VFTName) + skCrypt(" VFT index").decrypt());

	uint8_t* StringRef = Memory::FindByStringInAllSections(SearchString);

	DEBUG_LOG(LOG_INFO, skCrypt("Searching for VFT Index offset").decrypt());

	for (int i = 0; !VFTIndex && i < PossibleSigs.size(); ++i) {
		uint8_t* PatternAddress = reinterpret_cast<uint8_t*>(
			Memory::FindPatternInRange(PossibleSigs[i], (StringRef - SearchBytesBehind), SearchRange, false, 0)
			);

		if (PatternAddress) {
			DWORD Displacement = *reinterpret_cast<DWORD*>(PatternAddress + FindFirstWildCard(PossibleSigs[i]));
			VFTIndex = Displacement / sizeof(uintptr_t);
		}
	}

	PossibleSigs.clear();

	if (VFTIndex) {
		DEBUG_LOG(LOG_OFFSET, std::string(VFTName) + skCrypt(" VFT Index offset found: ").decrypt() + std::to_string(VFTIndex));
	}
	else {
		THROW_ERROR(skCrypt("Failed to find ").decrypt() + std::string(VFTName) + skCrypt(" VFT Index!").decrypt(), CRASH_ON_NOT_FOUND);
	}
}

void SDKInitializer::InitFunctionOffset(const char* FunctionName, std::vector<const char*> PossibleSigs, const wchar_t* SearchString, uintptr_t& FunctionOffset, int SearchRange, int SearchBytesBehind) {
	DEBUG_LOG(LOG_INFO, skCrypt("Searching for ").decrypt() + std::string(FunctionName) + skCrypt(" function offset").decrypt());

	uint8_t* StringRef = Memory::FindByStringInAllSections(SearchString);

	DEBUG_LOG(LOG_INFO, skCrypt("Searching for function offset").decrypt());

	for (int i = 0; !FunctionOffset && i < PossibleSigs.size(); ++i) {
		FunctionOffset = reinterpret_cast<uintptr_t>(
			Memory::FindPatternInRange(PossibleSigs[i], StringRef - SearchBytesBehind, SearchRange, true, -1)
			);
	}

	PossibleSigs.clear();

	if (FunctionOffset) {
		FunctionOffset -= SDK::GetBaseAddress();
		DEBUG_LOG(LOG_OFFSET, std::string(FunctionName) + skCrypt(" function offset found: ").decrypt() + std::to_string(FunctionOffset));
	}
	else {
		THROW_ERROR(skCrypt("Failed to find ").decrypt() + std::string(FunctionName) + skCrypt(" function offset!").decrypt(), CRASH_ON_NOT_FOUND);
	}
}
void SDKInitializer::InitFunctionOffset(const char* FunctionName, std::vector<const char*> PossibleSigs, const char* SearchString, uintptr_t& FunctionOffset, int SearchRange, int SearchBytesBehind) {
	DEBUG_LOG(LOG_INFO, skCrypt("Searching for ").decrypt() + std::string(FunctionName) + skCrypt(" function offset").decrypt());
	DEBUG_LOG(LOG_INFO, skCrypt("Searching for string reference: ").decrypt() + std::string(SearchString));

	uint8_t* StringRef = Memory::FindByStringInAllSections(SearchString);

	DEBUG_LOG(LOG_INFO, skCrypt("Searching for function offset").decrypt());

	for (int i = 0; !FunctionOffset && i < PossibleSigs.size(); ++i) {
		FunctionOffset = reinterpret_cast<uintptr_t>(
			Memory::FindPatternInRange(PossibleSigs[i], StringRef - SearchBytesBehind, SearchRange, true, -1)
			);
	}

	PossibleSigs.clear();

	if (FunctionOffset) {
		FunctionOffset -= SDK::GetBaseAddress();
		DEBUG_LOG(LOG_OFFSET, std::string(FunctionName) + skCrypt(" function offset found: ").decrypt() + std::to_string(FunctionOffset));
	}
	else {
		THROW_ERROR(skCrypt("Failed to find ").decrypt() + std::string(FunctionName) + skCrypt(" function offset!").decrypt(), CRASH_ON_NOT_FOUND);
	}
}

void SDKInitializer::InitPRIndex() {
	void** Vft = nullptr;

	for (int i = 0; i < SDK::UObject::ObjectArray.Num(); i++)
	{
		SDK::UObject* Obj = SDK::UObject::ObjectArray.GetByIndex(i);

		if (!Obj)
			continue;

		if (Obj->IsA(SDK::UGameViewportClient::StaticClass()) && Obj->IsDefaultObject() == false)
		{
			Vft = static_cast<SDK::UEngine*>(Obj)->Vft;
			break;
		}
	}

	if (Vft == nullptr) {
		THROW_ERROR(skCrypt("Failed to find VFT for UGameViewportClient!").decrypt(), false);
	}

	int bSuppressTransitionMessage = (int)SDK::Cached::Offsets::GameViewportClient::GameInstance + sizeof(void*);

	auto Resolve32BitRelativeJump = [](void* FunctionPtr) -> uint8_t*
	{
		uint8_t* Address = reinterpret_cast<uint8_t*>(FunctionPtr);
		if (*Address == 0xE9)
		{
			uint8_t* Ret = ((Address + 5) + *reinterpret_cast<int32_t*>(Address + 1));

			if (Memory::IsInProcessRange(uintptr_t(Ret)))
				return Ret;
		}

		return reinterpret_cast<uint8_t*>(FunctionPtr);
	};

	for (int i = 0; i < 0x150; i++)
	{
		if (!Vft[i] || !Memory::IsInProcessRange(reinterpret_cast<uintptr_t>(Vft[i])))
			continue;

		if (Memory::FindPatternInRange({ 0x80, 0xB9, bSuppressTransitionMessage, 0x00, 0x00, 0x00, 0x00 }, Resolve32BitRelativeJump(Vft[i]), 0x30))
		{
			SDK::Cached::VFT::PostRender = i;
			DEBUG_LOG(LOG_OFFSET, skCrypt("PostRender VFT index found: ").decrypt() + std::to_string(SDK::Cached::VFT::PostRender));

			return;
		}
	}

	if (SDK::Cached::VFT::PostRender == 0x0) {
		THROW_ERROR(skCrypt("Failed to find PostRender VFT index!").decrypt(), CRASH_ON_NOT_FOUND);
	}
}
void SDKInitializer::InitPEIndex() {
	void** Vft = SDK::UObject::ObjectArray.GetByIndex(0)->Vft;

	auto Resolve32BitRelativeJump = [](void* FunctionPtr) -> uint8_t*
	{
		uint8_t* Address = reinterpret_cast<uint8_t*>(FunctionPtr);
		if (*Address == 0xE9)
		{
			uint8_t* Ret = ((Address + 5) + *reinterpret_cast<int32_t*>(Address + 1));

			if (Memory::IsInProcessRange(uintptr_t(Ret)))
				return Ret;
		}

		return reinterpret_cast<uint8_t*>(FunctionPtr);
	};

	for (int i = 0; i < 0x150; i++)
	{
		if (!Vft[i] || !Memory::IsInProcessRange(reinterpret_cast<uintptr_t>(Vft[i])))
			break;

		if (Memory::FindPatternInRange({ 0xF7, -0x1, (int32_t)SDK::UFunction::FunctionFlagsOffset, 0x0, 0x0, 0x0, 0x0, 0x04, 0x0, 0x0 }, Resolve32BitRelativeJump(Vft[i]), 0x400)
			&& Memory::FindPatternInRange({ 0xF7, -0x1, (int32_t)SDK::UFunction::FunctionFlagsOffset, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0 }, Resolve32BitRelativeJump(Vft[i]), 0x400))
		{
			SDK::Cached::VFT::ProcessEvent = i;
			DEBUG_LOG(LOG_OFFSET, skCrypt("ProcessEvent VFT index found: ").decrypt() + std::to_string(SDK::Cached::VFT::ProcessEvent));
			return;
		}
	}



	uint8_t* StringRef = Memory::FindByStringInAllSections(skCrypt(L"Accessed None").decrypt());
	uintptr_t NextFunctionStart = Memory::FindNextFunctionStart(StringRef);

	SDKInitializer::WalkVFT(skCrypt("ProcessEvent").decrypt(), SDK::UObject::ObjectArray.GetByIndex(0)->Vft, reinterpret_cast<void*>(NextFunctionStart), SDK::Cached::VFT::ProcessEvent, 0x150);
}
void SDKInitializer::InitGPVIndex() {
	InitVFTIndex(
		skCrypt("GetPlayerViewpoint").decrypt(),
		std::vector<const char*>{ skCrypt("FF 90 ? ? ? ?").decrypt() },
		skCrypt(L"STAT_VolumeStreamingTickTime").decrypt(),
		SDK::Cached::VFT::GetPlayerViewpoint,
		0x400);
}
void SDKInitializer::InitGVIndex() {
	InitVFTIndex(
		skCrypt("GetViewpoint").decrypt(),
		std::vector<const char*>{ skCrypt("FF 90 ? ? ? ?").decrypt() },
		skCrypt(L"STAT_CalcSceneView").decrypt(),
		SDK::Cached::VFT::GetViewpoint,
		0x400);
}
void SDKInitializer::InitGetWeaponStatsIndex(const SDK::UObject* WeaponActor) {
	static bool HasTried = false;

	if (HasTried) {
		return;
	}
	
	HasTried = true;

	void** Vft = WeaponActor->Vft;

	if (Vft == nullptr) {
		THROW_ERROR(skCrypt("Failed to find VFT for AFortWeapon!").decrypt(), CRASH_ON_NOT_FOUND);
	}

	auto Resolve32BitRelativeJump = [](void* FunctionPtr) -> uint8_t*
	{
		uint8_t* Address = reinterpret_cast<uint8_t*>(FunctionPtr);
		if (*Address == 0xE9)
		{
			uint8_t* Ret = ((Address + 5) + *reinterpret_cast<int32_t*>(Address + 1));

			if (Memory::IsInProcessRange(uintptr_t(Ret)))
				return Ret;
		}

		return reinterpret_cast<uint8_t*>(FunctionPtr);
	};

	for (int i = 0; i < 0x100; i++)
	{
		if (!Vft[i] || !Memory::IsInProcessRange(reinterpret_cast<uintptr_t>(Vft[i])))
			continue;

		// 48 83 EC 58 48 8B 91 ? ? ? ? 48 85 D2 0F 84 ? ? ? ?
		// 48 83 EC 58 48 8B 89 ? ? ? ? 48 85 C9 0F 84 ? ? ? ?
		if (Memory::FindPatternInRange({ 0x48, 0x83, 0xEC, 0x58, 0x48, 0x8B, -0x01, -0x01, -0x01, -0x01, -0x01, 0x48, 0x85 }, Resolve32BitRelativeJump(Vft[i]), 0x50))
		{
			SDK::Cached::VFT::GetWeaponStats = i;
			DEBUG_LOG(LOG_OFFSET, skCrypt("GetWeaponStats VFT index found: ").decrypt() + std::to_string(SDK::Cached::VFT::GetWeaponStats));

			return;
		}
	}

	if (SDK::Cached::VFT::GetWeaponStats == 0x0) {
		THROW_ERROR(skCrypt("Failed to find GetWeaponStats VFT index!").decrypt(), CRASH_ON_NOT_FOUND);
	}
}

void SDKInitializer::InitAppendString() {
	InitFunctionOffset(
		skCrypt("AppendString").decrypt(),
		std::vector<const char*>
	{
		skCrypt("48 8D ? ? 48 8D ? ? E8").decrypt(),
		skCrypt("48 8D ? ? ? 48 8D ? ? E8").decrypt(),
		skCrypt("48 8D ? ? 49 8B ? E8").decrypt(),
		skCrypt("48 8D ? ? ? 49 8B ? E8").decrypt()
	},
		skCrypt("ForwardShadingQuality_").decrypt(),
		SDK::Cached::Functions::AppendString,
		0x60);
}
void SDKInitializer::InitFNameConstructor() {
	InitFunctionOffset(
		skCrypt("FName Constructor").decrypt(),
		std::vector<const char*> { skCrypt("E8").decrypt() },
		skCrypt(L"CanvasObject").decrypt(),
		SDK::Cached::Functions::FNameConstructor,
		0x32);
}
void SDKInitializer::InitLineTraceSingle() {
	SDK::Cached::Functions::LineTraceSingle = Memory::PatternScan(
		SDK::GetBaseAddress(),
		skCrypt("48 8B 43 20 48 8D 4D E0 0F 10 45 C0 44 0F B6 8D ? ? ? ? 48 85 C0 0F 10 4D D0 4C 8D 45 A0 40 0F 95 C7 66 0F 7F 45 ? 48 8D 55 B0 F2 0F 10 45 ? 48 03 F8 8B 45 88 F2 0F 11 45 ? F2 0F 10 45 ? 89 45 A8 8B 45 98 F2 0F 11 45 ? F3 0F 10 44 24 ? F3 0F 11 44 24 ? 48 89 4C 24 ? 48 8D 4D F0 48 89 4C 24 ? 48 8B 4C 24 ? 44 88 7C 24 ? 48 89 74 24 ? 89 45 B8 0F B6 85 ? ? ? ? 89 44 24 30 4C 89 74 24 ? 44 88 64 24 ? 48 89 7B 20 66 0F 7F 4D ? E8").decrypt(),
		155, // magic number, will improve pattern scanning function later
		true
	);

	if (!SDK::Cached::Functions::LineTraceSingle) {
		SDK::Cached::Functions::LineTraceSingle = Memory::PatternScan(
			SDK::GetBaseAddress(),
			skCrypt("4C 39 6B 20 4C 8D 45 A0 F2 0F 10 45 ? 48 8D 55 B0 44 0F B6 8D ? ? ? ? 49 8B C5 48 8B 4C 24 ? 0F 95 C0 48 01 43 20 8B 45 88 44 88 74 24 ? F2 0F 11 45 ? F2 0F 10 45 ? 89 45 A8 8B 45 98 48 89 7C 24 ? 48 89 74 24 ? 89 45 B8 F2 0F 11 45 ? 44 88 7C 24 ? E8 ? ? ? ?").decrypt(),
			92, // magic number, will improve pattern scanning function later
			true
		);
	}

	if (!SDK::Cached::Functions::LineTraceSingle) {
		THROW_ERROR(skCrypt("Failed to find LineTraceSingle!").decrypt(), CRASH_ON_NOT_FOUND);
	}

	SDK::Cached::Functions::LineTraceSingle -= SDK::GetBaseAddress();

	DEBUG_LOG(LOG_OFFSET, skCrypt("LineTraceSingle function offset found: ").decrypt() + std::to_string(SDK::Cached::Functions::LineTraceSingle));
}

void SDKInitializer::InitGObjects() {
	DEBUG_LOG(LOG_INFO, skCrypt("Searching for GObjects...").decrypt());

	SDK::UObject::ObjectArray.IsChunked = true;

	uintptr_t TUObjectArray = Memory::PatternScan(
		SDK::GetBaseAddress(),
		skCrypt("48 8B 05 ? ? ? ? 48 8B 0C C8 48 8D 04 D1").decrypt(),
		7,
		true
	);

	if (!SDK::IsValidPointer(TUObjectArray)) {
		SDK::UObject::ObjectArray.IsChunked = false;

		TUObjectArray = Memory::PatternScan(
			SDK::GetBaseAddress(),
			skCrypt("48 8B 05 ? ? ? ? 48 8D 14 C8 EB 02").decrypt(),
			7,
			true
		);
	}

	if (SDK::UObject::ObjectArray.IsChunked) {
		SDK::UObject::ObjectArray.ChunkedObjects = reinterpret_cast<SDK::Chunked_TUObjectArray*>(TUObjectArray);
	}
	else {
		SDK::UObject::ObjectArray.FixedObjects = reinterpret_cast<SDK::Fixed_TUObjectArray*>(TUObjectArray);
	}

	if (SDK::IsValidPointer(TUObjectArray)) {
		DEBUG_LOG(LOG_OFFSET, skCrypt("GObjects offset found: ").decrypt() + std::to_string(TUObjectArray - SDK::GetBaseAddress()));
	}
	else {
		THROW_ERROR(skCrypt("Failed to find GObjects!").decrypt(), CRASH_ON_NOT_FOUND);
	}
}