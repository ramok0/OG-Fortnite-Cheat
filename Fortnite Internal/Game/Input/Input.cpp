#include "Input.h"

#include "../Game.h"
#include "../../Utilities/Logger.h"

#ifdef _IMGUI
#include "../../Drawing/ImGui/imgui.h"
#include "../../Hooks/Hooks.h"
#endif // _IMGUI

inline std::unordered_map<Input::KeyName, Input::KeyData> Input::Keys = {
	{ Input::KeyName::NONE, {0x0, Input::KeyName::NONE, SDK::FName(), skCrypt("None").decrypt() } },

	{ Input::KeyName::AnyKey, { 0x0, Input::KeyName::AnyKey, SDK::FName(), skCrypt("Any Key").decrypt() } },

	{ Input::KeyName::MouseX, { 0x0, Input::KeyName::MouseX, SDK::FName(), skCrypt("Mouse X").decrypt() } },
	{ Input::KeyName::MouseY, { 0x0, Input::KeyName::MouseY, SDK::FName(), skCrypt("Mouse Y").decrypt() } },
	{ Input::KeyName::MouseScrollUp, { 0x0, Input::KeyName::MouseScrollUp, SDK::FName(), skCrypt("Scroll Up").decrypt() } },
	{ Input::KeyName::MouseScrollDown, { 0x0, Input::KeyName::MouseScrollDown, SDK::FName(), skCrypt("Scroll Down").decrypt() } },
	{ Input::KeyName::LeftMouseButton, { VK_LBUTTON, Input::KeyName::LeftMouseButton, SDK::FName(), skCrypt("LMB").decrypt() } },
	{ Input::KeyName::RightMouseButton, { VK_RBUTTON, Input::KeyName::RightMouseButton, SDK::FName(), skCrypt("RMB").decrypt() } },
	{ Input::KeyName::MiddleMouseButton, { VK_MBUTTON, Input::KeyName::RightMouseButton,SDK::FName(), skCrypt("MMB").decrypt() } },
	{ Input::KeyName::ThumbMouseButton, { VK_XBUTTON1, Input::KeyName::ThumbMouseButton, SDK::FName(), skCrypt("Thumb MB").decrypt() } },
	{ Input::KeyName::ThumbMouseButton2, { VK_XBUTTON2, Input::KeyName::ThumbMouseButton, SDK::FName(), skCrypt("Thumb MB2").decrypt() } },

	{ Input::KeyName::BackSpace, { VK_BACK, Input::KeyName::BackSpace, SDK::FName(), skCrypt("BackSpace").decrypt() } },
	{ Input::KeyName::Tab, { VK_TAB, Input::KeyName::BackSpace, SDK::FName(), skCrypt("Tab").decrypt() } },
	{ Input::KeyName::Enter, { VK_RETURN, Input::KeyName::Enter, SDK::FName(), skCrypt("Enter").decrypt() } },
	{ Input::KeyName::Pause, { VK_PAUSE, Input::KeyName::Pause, SDK::FName(), skCrypt("Pause").decrypt() } },
	{ Input::KeyName::CapsLock, { VK_CAPITAL, Input::KeyName::CapsLock, SDK::FName(), skCrypt("CapsLock").decrypt() } },
	{ Input::KeyName::Escape, { VK_ESCAPE, Input::KeyName::Escape, SDK::FName(), skCrypt("Escape").decrypt() } },
	{ Input::KeyName::SpaceBar, { VK_SPACE, Input::KeyName::SpaceBar, SDK::FName(), skCrypt("Space").decrypt() } },
	{ Input::KeyName::PageUp, { VK_PRIOR, Input::KeyName::SpaceBar, SDK::FName(), skCrypt("PageUp").decrypt() } },
	{ Input::KeyName::PageDown, { VK_NEXT, Input::KeyName::PageDown, SDK::FName(), skCrypt("PageDown").decrypt() } },
	{ Input::KeyName::End, { VK_END, Input::KeyName::End, SDK::FName(), skCrypt("End").decrypt() } },
	{ Input::KeyName::Home, { VK_HOME, Input::KeyName::Home, SDK::FName(), skCrypt("Home").decrypt() } },

	{ Input::KeyName::Left, { VK_LEFT, Input::KeyName::Left, SDK::FName(), skCrypt("Left Arrow").decrypt() } },
	{ Input::KeyName::Up, { VK_UP, Input::KeyName::Up, SDK::FName(), skCrypt("Up Arrow").decrypt() } },
	{ Input::KeyName::Right, { VK_RIGHT, Input::KeyName::Right, SDK::FName(), skCrypt("Right Arrow").decrypt() } },
	{ Input::KeyName::Down, { VK_DOWN, Input::KeyName::Down, SDK::FName(), skCrypt("Down Arrow").decrypt() } },

	{ Input::KeyName::Insert, { VK_INSERT, Input::KeyName::Insert, SDK::FName(), skCrypt("Insert").decrypt() } },
	{ Input::KeyName::Delete, { VK_DELETE, Input::KeyName::Delete, SDK::FName(), skCrypt("Delete").decrypt() } },

	{ Input::KeyName::Zero, { '0', Input::KeyName::Zero, SDK::FName(), skCrypt("0").decrypt() } },
	{ Input::KeyName::One, { '1', Input::KeyName::One, SDK::FName(), skCrypt("1").decrypt() } },
	{ Input::KeyName::Two, { '2', Input::KeyName::Two, SDK::FName(), skCrypt("2").decrypt() } },
	{ Input::KeyName::Three, { '3', Input::KeyName::Three, SDK::FName(), skCrypt("3").decrypt() } },
	{ Input::KeyName::Four, { '4', Input::KeyName::Four, SDK::FName(), skCrypt("4").decrypt() } },
	{ Input::KeyName::Five, { '5', Input::KeyName::Five, SDK::FName(), skCrypt("5").decrypt() } },
	{ Input::KeyName::Six, { '6', Input::KeyName::Six, SDK::FName(), skCrypt("6").decrypt() } },
	{ Input::KeyName::Seven, { '7', Input::KeyName::Seven, SDK::FName(), skCrypt("7").decrypt() } },
	{ Input::KeyName::Eight, { '8', Input::KeyName::Eight, SDK::FName(), skCrypt("8").decrypt() } },
	{ Input::KeyName::Nine, { '9', Input::KeyName::Nine, SDK::FName(), skCrypt("9").decrypt() } },

	{ Input::KeyName::A, { 'A', Input::KeyName::A, SDK::FName(), skCrypt("A").decrypt() } },
	{ Input::KeyName::B, { 'B', Input::KeyName::B, SDK::FName(), skCrypt("B").decrypt() } },
	{ Input::KeyName::C, { 'C', Input::KeyName::C, SDK::FName(), skCrypt("C").decrypt() } },
	{ Input::KeyName::D, { 'D', Input::KeyName::D, SDK::FName(), skCrypt("D").decrypt() } },
	{ Input::KeyName::E, { 'E', Input::KeyName::E, SDK::FName(), skCrypt("E").decrypt() } },
	{ Input::KeyName::F, { 'F', Input::KeyName::F, SDK::FName(), skCrypt("F").decrypt() } },
	{ Input::KeyName::G, { 'G', Input::KeyName::G, SDK::FName(), skCrypt("G").decrypt() } },
	{ Input::KeyName::H, { 'H', Input::KeyName::H, SDK::FName(), skCrypt("H").decrypt() } },
	{ Input::KeyName::I, { 'I', Input::KeyName::I, SDK::FName(), skCrypt("I").decrypt() } },
	{ Input::KeyName::J, { 'J', Input::KeyName::J, SDK::FName(), skCrypt("J").decrypt() } },
	{ Input::KeyName::K, { 'K', Input::KeyName::K, SDK::FName(), skCrypt("K").decrypt() } },
	{ Input::KeyName::L, { 'L', Input::KeyName::L, SDK::FName(), skCrypt("L").decrypt() } },
	{ Input::KeyName::M, { 'M', Input::KeyName::M, SDK::FName(), skCrypt("M").decrypt() } },
	{ Input::KeyName::N, { 'N', Input::KeyName::N, SDK::FName(), skCrypt("N").decrypt() } },
	{ Input::KeyName::O, { 'O', Input::KeyName::O, SDK::FName(), skCrypt("O").decrypt() } },
	{ Input::KeyName::P, { 'P', Input::KeyName::P, SDK::FName(), skCrypt("P").decrypt() } },
	{ Input::KeyName::Q, { 'Q', Input::KeyName::Q, SDK::FName(), skCrypt("Q").decrypt() } },
	{ Input::KeyName::R, { 'R', Input::KeyName::R, SDK::FName(), skCrypt("R").decrypt() } },
	{ Input::KeyName::S, { 'S', Input::KeyName::S, SDK::FName(), skCrypt("S").decrypt() } },
	{ Input::KeyName::T, { 'T', Input::KeyName::T, SDK::FName(), skCrypt("T").decrypt() } },
	{ Input::KeyName::U, { 'U', Input::KeyName::U, SDK::FName(), skCrypt("U").decrypt() } },
	{ Input::KeyName::V, { 'V', Input::KeyName::V, SDK::FName(), skCrypt("V").decrypt() } },
	{ Input::KeyName::W, { 'W', Input::KeyName::W, SDK::FName(), skCrypt("W").decrypt() } },
	{ Input::KeyName::X, { 'X', Input::KeyName::X, SDK::FName(), skCrypt("X").decrypt() } },
	{ Input::KeyName::Y, { 'Y', Input::KeyName::Y, SDK::FName(), skCrypt("Y").decrypt() } },
	{ Input::KeyName::Z, { 'Z', Input::KeyName::Z, SDK::FName(), skCrypt("Z").decrypt() } },

	{ Input::KeyName::NumPadZero, { VK_NUMPAD0, Input::KeyName::NumPadZero, SDK::FName(), skCrypt("NumPad 0").decrypt() } },
	{ Input::KeyName::NumPadOne, { VK_NUMPAD1, Input::KeyName::NumPadOne, SDK::FName(), skCrypt("NumPad 1").decrypt() } },
	{ Input::KeyName::NumPadTwo, { VK_NUMPAD2, Input::KeyName::NumPadTwo, SDK::FName(), skCrypt("NumPad 2").decrypt() } },
	{ Input::KeyName::NumPadThree, { VK_NUMPAD3, Input::KeyName::NumPadThree, SDK::FName(), skCrypt("NumPad 3").decrypt() } },
	{ Input::KeyName::NumPadFour, { VK_NUMPAD4, Input::KeyName::NumPadFour, SDK::FName(), skCrypt("NumPad 4").decrypt() } },
	{ Input::KeyName::NumPadFive, { VK_NUMPAD5, Input::KeyName::NumPadFive, SDK::FName(), skCrypt("NumPad 5").decrypt() } },
	{ Input::KeyName::NumPadSix, { VK_NUMPAD6, Input::KeyName::NumPadSix, SDK::FName(), skCrypt("NumPad 6").decrypt() } },
	{ Input::KeyName::NumPadSeven, { VK_NUMPAD7, Input::KeyName::NumPadSeven, SDK::FName(), skCrypt("NumPad 7").decrypt() } },
	{ Input::KeyName::NumPadEight, { VK_NUMPAD8, Input::KeyName::NumPadEight, SDK::FName(), skCrypt("NumPad 8").decrypt() } },
	{ Input::KeyName::NumPadNine, { VK_NUMPAD9, Input::KeyName::NumPadNine, SDK::FName(), skCrypt("NumPad 9").decrypt() } },

	{ Input::KeyName::Multiply, { VK_MULTIPLY, Input::KeyName::Multiply, SDK::FName(), skCrypt("Multiply").decrypt() } },
	{ Input::KeyName::Add, { VK_ADD, Input::KeyName::Add, SDK::FName(), skCrypt("Add").decrypt() } },
	{ Input::KeyName::Subtract, { VK_SUBTRACT, Input::KeyName::Subtract, SDK::FName(), skCrypt("Subtract").decrypt() } },
	{ Input::KeyName::Decimal, { VK_DECIMAL, Input::KeyName::Decimal, SDK::FName(), skCrypt("Decimal").decrypt() } },
	{ Input::KeyName::Divide, { VK_DIVIDE, Input::KeyName::Divide, SDK::FName(), skCrypt("Divide").decrypt() } },

	{ Input::KeyName::F1, { VK_F1, Input::KeyName::F1, SDK::FName(), skCrypt("F1").decrypt() } },
	{ Input::KeyName::F2, { VK_F2, Input::KeyName::F2, SDK::FName(), skCrypt("F2").decrypt() } },
	{ Input::KeyName::F3, { VK_F3, Input::KeyName::F3, SDK::FName(), skCrypt("F3").decrypt() } },
	{ Input::KeyName::F4, { VK_F4, Input::KeyName::F4, SDK::FName(), skCrypt("F4").decrypt() } },
	{ Input::KeyName::F5, { VK_F5, Input::KeyName::F5, SDK::FName(), skCrypt("F5").decrypt() } },
	{ Input::KeyName::F6, { VK_F6, Input::KeyName::F6, SDK::FName(), skCrypt("F6").decrypt() } },
	{ Input::KeyName::F7, { VK_F7, Input::KeyName::F7, SDK::FName(), skCrypt("F7").decrypt() } },
	{ Input::KeyName::F8, { VK_F8, Input::KeyName::F8, SDK::FName(), skCrypt("F8").decrypt() } },
	{ Input::KeyName::F9, { VK_F9, Input::KeyName::F9, SDK::FName(), skCrypt("F9").decrypt() } },
	{ Input::KeyName::F10, { VK_F10, Input::KeyName::F10, SDK::FName(), skCrypt("F10").decrypt() } },
	{ Input::KeyName::F11, { VK_F11, Input::KeyName::F11, SDK::FName(), skCrypt("F11").decrypt() } },
	{ Input::KeyName::F12, { VK_F12, Input::KeyName::F12, SDK::FName(), skCrypt("F12").decrypt() } },

	{ Input::KeyName::NumLock, { 0x0, Input::KeyName::NumLock, SDK::FName(), skCrypt("NumLock").decrypt() } },
	{ Input::KeyName::ScrollLock, { 0x0, Input::KeyName::ScrollLock, SDK::FName(), skCrypt("ScrollLock").decrypt() } },
	{ Input::KeyName::LeftShift, { 0x0, Input::KeyName::LeftShift, SDK::FName(), skCrypt("Left Shift").decrypt() } },
	{ Input::KeyName::RightShift, { 0x0, Input::KeyName::RightShift, SDK::FName(), skCrypt("Right Shift").decrypt() } },
	{ Input::KeyName::LeftControl, { 0x0, Input::KeyName::LeftControl, SDK::FName(), skCrypt("Left Control").decrypt() } },
	{ Input::KeyName::RightControl, { 0x0, Input::KeyName::RightControl, SDK::FName(), skCrypt("Right Control").decrypt() } },
	{ Input::KeyName::LeftAlt, { 0x0, Input::KeyName::LeftAlt, SDK::FName(), skCrypt("Left Alt").decrypt() } },
	{ Input::KeyName::RightAlt, { 0x0, Input::KeyName::RightAlt, SDK::FName(), skCrypt("Right Alt").decrypt() } },
	{ Input::KeyName::LeftCommand, { 0x0, Input::KeyName::LeftCommand, SDK::FName(), skCrypt("Left Command").decrypt() } },
	{ Input::KeyName::RightCommand, { 0x0, Input::KeyName::RightCommand, SDK::FName(), skCrypt("Right Command").decrypt() } },

	{ Input::KeyName::Semicolon, { 0x0, Input::KeyName::Semicolon, SDK::FName(), skCrypt("Semicolon").decrypt() } },
	{ Input::KeyName::Equals, { 0x0, Input::KeyName::Equals, SDK::FName(), skCrypt("Equals").decrypt() } },
	{ Input::KeyName::Comma, { 0x0, Input::KeyName::Comma, SDK::FName(), skCrypt("Comma").decrypt() } },
	{ Input::KeyName::Underscore, { 0x0, Input::KeyName::Underscore, SDK::FName(), skCrypt("Underscore").decrypt() } },
	{ Input::KeyName::Period, { 0x0, Input::KeyName::Period, SDK::FName(), skCrypt("Period").decrypt() } },
	{ Input::KeyName::Slash, { 0x0, Input::KeyName::Slash, SDK::FName(), skCrypt("Slash").decrypt() } },
	{ Input::KeyName::Tilde, { 0x0, Input::KeyName::Tilde, SDK::FName(), skCrypt("Tilde").decrypt() } },
	{ Input::KeyName::LeftBracket, { 0x0, Input::KeyName::LeftBracket, SDK::FName(), skCrypt("Left Bracket").decrypt() } },
	{ Input::KeyName::Backslash, { 0x0, Input::KeyName::Backslash, SDK::FName(), skCrypt("Backslash").decrypt() } },
	{ Input::KeyName::RightBracket, { 0x0, Input::KeyName::RightBracket, SDK::FName(), skCrypt("Right Bracket").decrypt() } },
	{ Input::KeyName::Quote, { 0x0, Input::KeyName::Quote, SDK::FName(), skCrypt("Quote").decrypt() } },
	{ Input::KeyName::Asterix, { 0x0, Input::KeyName::Asterix, SDK::FName(), skCrypt("Asterix").decrypt() } },
	{ Input::KeyName::Ampersand, { 0x0, Input::KeyName::Ampersand, SDK::FName(), skCrypt("Ampersand").decrypt() } },
	{ Input::KeyName::Caret, { 0x0, Input::KeyName::Caret, SDK::FName(), skCrypt("Caret").decrypt() } },
	{ Input::KeyName::Dollar, { 0x0, Input::KeyName::Dollar, SDK::FName(), skCrypt("Dollar").decrypt() } },
	{ Input::KeyName::Exclamation, { 0x0, Input::KeyName::Exclamation, SDK::FName(), skCrypt("Exclamation").decrypt() } },
	{ Input::KeyName::Colon, { 0x0, Input::KeyName::Colon, SDK::FName(), skCrypt("Colon").decrypt() } },

	{ Input::KeyName::A_AccentGrave, { 0x0, Input::KeyName::A_AccentGrave, SDK::FName(), skCrypt("A Accent Grave").decrypt() } },
	{ Input::KeyName::E_AccentGrave, { 0x0, Input::KeyName::E_AccentGrave, SDK::FName(), skCrypt("E Accent Grave").decrypt() } },
	{ Input::KeyName::E_AccentAigu, { 0x0, Input::KeyName::E_AccentAigu, SDK::FName(), skCrypt("E Accent Aigu").decrypt() } },
	{ Input::KeyName::C_Cedille, { 0x0, Input::KeyName::C_Cedille, SDK::FName(), skCrypt("C Cedille").decrypt() } },

	{ Input::KeyName::Section, { 0x0, Input::KeyName::Section, SDK::FName(), skCrypt("Section").decrypt() } },

	{ Input::KeyName::Gamepad_LeftX, { 0x0, Input::KeyName::Gamepad_LeftX, SDK::FName(), skCrypt("Gamepad Left X").decrypt() } },
	{ Input::KeyName::Gamepad_LeftY, { 0x0, Input::KeyName::Gamepad_LeftY, SDK::FName(), skCrypt("Gamepad Left Y").decrypt() } },
	{ Input::KeyName::Gamepad_RightX, { 0x0, Input::KeyName::Gamepad_RightX, SDK::FName(), skCrypt("Gamepad Right X").decrypt() } },
	{ Input::KeyName::Gamepad_RightY, { 0x0, Input::KeyName::Gamepad_RightY, SDK::FName(), skCrypt("Gamepad Right Y").decrypt() } },
	{ Input::KeyName::Gamepad_LeftTriggerAxis, { 0x0, Input::KeyName::Gamepad_LeftTriggerAxis, SDK::FName(), skCrypt("Gamepad Left Trigger Axis").decrypt() } },
	{ Input::KeyName::Gamepad_RightTriggerAxis, { 0x0, Input::KeyName::Gamepad_RightTriggerAxis, SDK::FName(), skCrypt("Gamepad Right Trigger Axis").decrypt() } },
	{ Input::KeyName::Gamepad_LeftThumbstick, { 0x0, Input::KeyName::Gamepad_LeftThumbstick, SDK::FName(), skCrypt("Gamepad Left Thumbstick").decrypt() } },
	{ Input::KeyName::Gamepad_RightThumbstick, { 0x0, Input::KeyName::Gamepad_RightThumbstick, SDK::FName(), skCrypt("Gamepad Right Thumbstick").decrypt() } },
	{ Input::KeyName::Gamepad_Special_Left, { 0x0, Input::KeyName::Gamepad_Special_Left, SDK::FName(), skCrypt("Gamepad Special Left").decrypt() } },
	{ Input::KeyName::Gamepad_Special_Left_X, { 0x0, Input::KeyName::Gamepad_Special_Left_X, SDK::FName(), skCrypt("Gamepad Special Left X").decrypt() } },
	{ Input::KeyName::Gamepad_Special_Left_Y, { 0x0, Input::KeyName::Gamepad_Special_Left_Y, SDK::FName(), skCrypt("Gamepad Special Left Y").decrypt() } },
	{ Input::KeyName::Gamepad_Special_Right, { 0x0, Input::KeyName::Gamepad_Special_Right, SDK::FName(), skCrypt("Gamepad Special Right").decrypt() } },
	{ Input::KeyName::Gamepad_FaceButton_Bottom, { 0x0, Input::KeyName::Gamepad_FaceButton_Bottom, SDK::FName(), skCrypt("Gamepad Face Button Bottom").decrypt() } },
	{ Input::KeyName::Gamepad_FaceButton_Right, { 0x0, Input::KeyName::Gamepad_FaceButton_Right, SDK::FName(), skCrypt("Gamepad Face Button Right").decrypt() } },
	{ Input::KeyName::Gamepad_FaceButton_Left, { 0x0, Input::KeyName::Gamepad_FaceButton_Left, SDK::FName(), skCrypt("Gamepad Face Button Left").decrypt() } },
	{ Input::KeyName::Gamepad_FaceButton_Top, { 0x0, Input::KeyName::Gamepad_FaceButton_Top, SDK::FName(), skCrypt("Gamepad Face Button Top").decrypt() } },
	{ Input::KeyName::Gamepad_LeftShoulder, { 0x0, Input::KeyName::Gamepad_LeftShoulder, SDK::FName(), skCrypt("Gamepad Left Shoulder").decrypt() } },
	{ Input::KeyName::Gamepad_RightShoulder, { 0x0, Input::KeyName::Gamepad_RightShoulder, SDK::FName(), skCrypt("Gamepad Right Shoulder").decrypt() } },
	{ Input::KeyName::Gamepad_LeftTrigger, { 0x0, Input::KeyName::Gamepad_LeftTrigger, SDK::FName(), skCrypt("Gamepad Left Trigger").decrypt() } },
	{ Input::KeyName::Gamepad_RightTrigger, { 0x0, Input::KeyName::Gamepad_RightTrigger, SDK::FName(), skCrypt("Gamepad Right Trigger").decrypt() } },
	{ Input::KeyName::Gamepad_DPad_Up, { 0x0, Input::KeyName::Gamepad_DPad_Up, SDK::FName(), skCrypt("Gamepad DPad Up").decrypt() } },
	{ Input::KeyName::Gamepad_DPad_Down, { 0x0, Input::KeyName::Gamepad_DPad_Down, SDK::FName(), skCrypt("Gamepad DPad Down").decrypt() } },
	{ Input::KeyName::Gamepad_DPad_Left, { 0x0, Input::KeyName::Gamepad_DPad_Left, SDK::FName(), skCrypt("Gamepad DPad Left").decrypt() } },
	{ Input::KeyName::Gamepad_DPad_Right, { 0x0, Input::KeyName::Gamepad_DPad_Right, SDK::FName(), skCrypt("Gamepad DPad Right").decrypt() } },
	{ Input::KeyName::Gamepad_LeftStick_Up, { 0x0, Input::KeyName::Gamepad_LeftStick_Up, SDK::FName(), skCrypt("Gamepad Leftstick Up").decrypt() } },
	{ Input::KeyName::Gamepad_LeftStick_Down, { 0x0, Input::KeyName::Gamepad_LeftStick_Down, SDK::FName(), skCrypt("Gamepad Leftstick Down").decrypt() } },
	{ Input::KeyName::Gamepad_LeftStick_Left, { 0x0, Input::KeyName::Gamepad_LeftStick_Left, SDK::FName(), skCrypt("Gamepad Leftstick Left").decrypt() } },
	{ Input::KeyName::Gamepad_LeftStick_Right, { 0x0, Input::KeyName::Gamepad_LeftStick_Right, SDK::FName(), skCrypt("Gamepad Leftstick Right").decrypt() } },
	{ Input::KeyName::Gamepad_RightStick_Up, { 0x0, Input::KeyName::Gamepad_RightStick_Up, SDK::FName(), skCrypt("Gamepad Rightstick Up").decrypt() } },
	{ Input::KeyName::Gamepad_RightStick_Down, { 0x0, Input::KeyName::Gamepad_RightStick_Down, SDK::FName(), skCrypt("Gamepad Rightstick Down").decrypt() } },
	{ Input::KeyName::Gamepad_RightStick_Left, { 0x0, Input::KeyName::Gamepad_RightStick_Left, SDK::FName(), skCrypt("Gamepad Rightstick Left").decrypt() } },
	{ Input::KeyName::Gamepad_RightStick_Right, { 0x0, Input::KeyName::Gamepad_RightStick_Right, SDK::FName(), skCrypt("Gamepad Rightstick Right").decrypt() } },
};
inline Input::MouseCache Input::Mouse;

SDK::FVector2D Input::GetMousePosition() {
#if (INPUT_TYPE == ENGINE_INPUT)
	if (Mouse.FrameUpdated != Game::CurrentFrame) {
		Mouse.FrameUpdated = Game::CurrentFrame;

		float LocationX = 0.f;
		float LocationY = 0.f;

		if (SDK::GetLocalController()->GetMousePosition(&LocationX, &LocationY)) {
			Mouse.Position = SDK::FVector2D(LocationX, LocationY);
		}
	}
#endif // (INPUT_TYPE == ENGINE_INPUT)

	return Mouse.Position;
}

bool Input::IsKeyDown(KeyName Key) {
	auto& KeyData = Keys[Key];

	if (KeyData.IsDown.FrameUpdated != Game::CurrentFrame) {
#if (INPUT_TYPE == ENGINE_INPUT)
		KeyData.IsDown.FrameUpdated = Game::CurrentFrame;

		SDK::FKey FKey{};
		FKey.KeyName = KeyData.FName;

		KeyData.IsDown.Value = SDK::GetLocalController()->IsInputKeyDown(FKey);
#else
		KeyData.IsDown.Value = false;
#endif // (INPUT_TYPE == WNDPROC_INPUT)
	}

	return KeyData.IsDown.Value;
}
bool Input::WasKeyJustReleased(KeyName Key) {
	auto& KeyData = Keys[Key];

	if (KeyData.WasJustReleased.FrameUpdated != Game::CurrentFrame) {
#if (INPUT_TYPE == ENGINE_INPUT)
		KeyData.WasJustReleased.FrameUpdated = Game::CurrentFrame;

		SDK::FKey FKey{};
		FKey.KeyName = KeyData.FName;

		KeyData.WasJustReleased.Value = SDK::GetLocalController()->WasInputKeyJustReleased(FKey);
#else
		KeyData.WasJustReleased.Value = false;
#endif // (INPUT_TYPE == WNDPROC_INPUT)
	}

	return KeyData.WasJustReleased.Value;
}
bool Input::WasKeyJustPressed(KeyName Key) {
	auto& KeyData = Keys[Key];

	if (KeyData.WasJustPressed.FrameUpdated != Game::CurrentFrame) {
#if (INPUT_TYPE == ENGINE_INPUT)
		KeyData.WasJustPressed.FrameUpdated = Game::CurrentFrame;

		SDK::FKey FKey{};
		FKey.KeyName = KeyData.FName;

		KeyData.WasJustPressed.Value = SDK::GetLocalController()->WasInputKeyJustPressed(FKey);
#else
		KeyData.WasJustPressed.Value = false;
#endif // (INPUT_TYPE == WNDPROC_INPUT)
	}

	return KeyData.WasJustPressed.Value;
}

std::vector<Input::KeyName> Input::GetAllDownKeys() {
	std::vector<Input::KeyName> KeysDown{};

	for (auto& Key : Keys) {
		if (IsKeyDown(Key.first)) {
			KeysDown.push_back(Key.first);
		}
	}

	return KeysDown;
}
std::vector<Input::KeyName> Input::GetAllJustReleasedKeys() {
	std::vector<Input::KeyName> KeysJustReleased{};

	for (auto& Key : Keys) {
		if (WasKeyJustReleased(Key.first)) {
			KeysJustReleased.push_back(Key.first);
		}
	}

	return KeysJustReleased;
}
std::vector<Input::KeyName> Input::GetAllJustPressedKeys() {
	std::vector<Input::KeyName> KeysJustPressed{};

	for (auto& Key : Keys) {
		if (WasKeyJustPressed(Key.first)) {
			KeysJustPressed.push_back(Key.first);
		}
	}

	return KeysJustPressed;
}

std::string Input::GetKeyNameString(Input::KeyName Key) {
	return Keys[Key].Name;
}

void Input::Init() {
	DEBUG_LOG(LOG_OFFSET, skCrypt("Initializing input system...").decrypt());

	// Init KeyNames
	{
		Keys[KeyName::NONE].FName = SDK::FName(skCrypt(L"NONE").decrypt());

		Keys[KeyName::AnyKey].FName = SDK::FName(skCrypt(L"AnyKey").decrypt());

		Keys[KeyName::MouseX].FName = SDK::FName(skCrypt(L"MouseX").decrypt());
		Keys[KeyName::MouseY].FName = SDK::FName(skCrypt(L"MouseY").decrypt());
		Keys[KeyName::MouseScrollUp].FName = SDK::FName(skCrypt(L"MouseScrollUp").decrypt());
		Keys[KeyName::MouseScrollDown].FName = SDK::FName(skCrypt(L"MouseScrollDown").decrypt());
		Keys[KeyName::LeftMouseButton].FName = SDK::FName(skCrypt(L"LeftMouseButton").decrypt());
		Keys[KeyName::RightMouseButton].FName = SDK::FName(skCrypt(L"RightMouseButton").decrypt());
		Keys[KeyName::MiddleMouseButton].FName = SDK::FName(skCrypt(L"MiddleMouseButton").decrypt());
		Keys[KeyName::ThumbMouseButton].FName = SDK::FName(skCrypt(L"ThumbMouseButton").decrypt());
		Keys[KeyName::ThumbMouseButton2].FName = SDK::FName(skCrypt(L"ThumbMouseButton2").decrypt());

		Keys[KeyName::BackSpace].FName = SDK::FName(skCrypt(L"BackSpace").decrypt());
		Keys[KeyName::Tab].FName = SDK::FName(skCrypt(L"Tab").decrypt());
		Keys[KeyName::Enter].FName = SDK::FName(skCrypt(L"Enter").decrypt());
		Keys[KeyName::Pause].FName = SDK::FName(skCrypt(L"Pause").decrypt());
		Keys[KeyName::CapsLock].FName = SDK::FName(skCrypt(L"CapsLock").decrypt());
		Keys[KeyName::Escape].FName = SDK::FName(skCrypt(L"Escape").decrypt());
		Keys[KeyName::SpaceBar].FName = SDK::FName(skCrypt(L"SpaceBar").decrypt());
		Keys[KeyName::PageUp].FName = SDK::FName(skCrypt(L"PageUp").decrypt());
		Keys[KeyName::PageDown].FName = SDK::FName(skCrypt(L"PageDown").decrypt());
		Keys[KeyName::End].FName = SDK::FName(skCrypt(L"End").decrypt());
		Keys[KeyName::Home].FName = SDK::FName(skCrypt(L"Home").decrypt());

		Keys[KeyName::Left].FName = SDK::FName(skCrypt(L"Left").decrypt());
		Keys[KeyName::Up].FName = SDK::FName(skCrypt(L"Up").decrypt());
		Keys[KeyName::Right].FName = SDK::FName(skCrypt(L"Right").decrypt());
		Keys[KeyName::Down].FName = SDK::FName(skCrypt(L"Down").decrypt());

		Keys[KeyName::Insert].FName = SDK::FName(skCrypt(L"Insert").decrypt());
		Keys[KeyName::Delete].FName = SDK::FName(skCrypt(L"Delete").decrypt());

		Keys[KeyName::Zero].FName = SDK::FName(skCrypt(L"Zero").decrypt());
		Keys[KeyName::One].FName = SDK::FName(skCrypt(L"One").decrypt());
		Keys[KeyName::Two].FName = SDK::FName(skCrypt(L"Two").decrypt());
		Keys[KeyName::Three].FName = SDK::FName(skCrypt(L"Three").decrypt());
		Keys[KeyName::Four].FName = SDK::FName(skCrypt(L"Four").decrypt());
		Keys[KeyName::Five].FName = SDK::FName(skCrypt(L"Five").decrypt());
		Keys[KeyName::Six].FName = SDK::FName(skCrypt(L"Six").decrypt());
		Keys[KeyName::Seven].FName = SDK::FName(skCrypt(L"Seven").decrypt());
		Keys[KeyName::Eight].FName = SDK::FName(skCrypt(L"Eight").decrypt());
		Keys[KeyName::Nine].FName = SDK::FName(skCrypt(L"Nine").decrypt());

		Keys[KeyName::A].FName = SDK::FName(skCrypt(L"A").decrypt());
		Keys[KeyName::B].FName = SDK::FName(skCrypt(L"B").decrypt());
		Keys[KeyName::C].FName = SDK::FName(skCrypt(L"C").decrypt());
		Keys[KeyName::D].FName = SDK::FName(skCrypt(L"D").decrypt());
		Keys[KeyName::E].FName = SDK::FName(skCrypt(L"E").decrypt());
		Keys[KeyName::F].FName = SDK::FName(skCrypt(L"F").decrypt());
		Keys[KeyName::G].FName = SDK::FName(skCrypt(L"G").decrypt());
		Keys[KeyName::H].FName = SDK::FName(skCrypt(L"H").decrypt());
		Keys[KeyName::I].FName = SDK::FName(skCrypt(L"I").decrypt());
		Keys[KeyName::J].FName = SDK::FName(skCrypt(L"J").decrypt());
		Keys[KeyName::K].FName = SDK::FName(skCrypt(L"K").decrypt());
		Keys[KeyName::L].FName = SDK::FName(skCrypt(L"L").decrypt());
		Keys[KeyName::M].FName = SDK::FName(skCrypt(L"M").decrypt());
		Keys[KeyName::N].FName = SDK::FName(skCrypt(L"N").decrypt());
		Keys[KeyName::O].FName = SDK::FName(skCrypt(L"O").decrypt());
		Keys[KeyName::P].FName = SDK::FName(skCrypt(L"P").decrypt());
		Keys[KeyName::Q].FName = SDK::FName(skCrypt(L"Q").decrypt());
		Keys[KeyName::R].FName = SDK::FName(skCrypt(L"R").decrypt());
		Keys[KeyName::S].FName = SDK::FName(skCrypt(L"S").decrypt());
		Keys[KeyName::T].FName = SDK::FName(skCrypt(L"T").decrypt());
		Keys[KeyName::U].FName = SDK::FName(skCrypt(L"U").decrypt());
		Keys[KeyName::V].FName = SDK::FName(skCrypt(L"V").decrypt());
		Keys[KeyName::W].FName = SDK::FName(skCrypt(L"W").decrypt());
		Keys[KeyName::X].FName = SDK::FName(skCrypt(L"X").decrypt());
		Keys[KeyName::Y].FName = SDK::FName(skCrypt(L"Y").decrypt());
		Keys[KeyName::Z].FName = SDK::FName(skCrypt(L"Z").decrypt());

		Keys[KeyName::NumPadZero].FName = SDK::FName(skCrypt(L"NumPadZero").decrypt());
		Keys[KeyName::NumPadOne].FName = SDK::FName(skCrypt(L"NumPadOne").decrypt());
		Keys[KeyName::NumPadTwo].FName = SDK::FName(skCrypt(L"NumPadTwo").decrypt());
		Keys[KeyName::NumPadThree].FName = SDK::FName(skCrypt(L"NumPadThree").decrypt());
		Keys[KeyName::NumPadFour].FName = SDK::FName(skCrypt(L"NumPadFour").decrypt());
		Keys[KeyName::NumPadFive].FName = SDK::FName(skCrypt(L"NumPadFive").decrypt());
		Keys[KeyName::NumPadSix].FName = SDK::FName(skCrypt(L"NumPadSix").decrypt());
		Keys[KeyName::NumPadSeven].FName = SDK::FName(skCrypt(L"NumPadSeven").decrypt());
		Keys[KeyName::NumPadEight].FName = SDK::FName(skCrypt(L"NumPadEight").decrypt());
		Keys[KeyName::NumPadNine].FName = SDK::FName(skCrypt(L"NumPadNine").decrypt());

		Keys[KeyName::Multiply].FName = SDK::FName(skCrypt(L"Multiply").decrypt());
		Keys[KeyName::Add].FName = SDK::FName(skCrypt(L"Add").decrypt());
		Keys[KeyName::Subtract].FName = SDK::FName(skCrypt(L"Subtract").decrypt());
		Keys[KeyName::Decimal].FName = SDK::FName(skCrypt(L"Decimal").decrypt());
		Keys[KeyName::Divide].FName = SDK::FName(skCrypt(L"Divide").decrypt());

		Keys[KeyName::F1].FName = SDK::FName(skCrypt(L"F1").decrypt());
		Keys[KeyName::F2].FName = SDK::FName(skCrypt(L"F2").decrypt());
		Keys[KeyName::F3].FName = SDK::FName(skCrypt(L"F3").decrypt());
		Keys[KeyName::F4].FName = SDK::FName(skCrypt(L"F4").decrypt());
		Keys[KeyName::F5].FName = SDK::FName(skCrypt(L"F5").decrypt());
		Keys[KeyName::F6].FName = SDK::FName(skCrypt(L"F6").decrypt());
		Keys[KeyName::F7].FName = SDK::FName(skCrypt(L"F7").decrypt());
		Keys[KeyName::F8].FName = SDK::FName(skCrypt(L"F8").decrypt());
		Keys[KeyName::F9].FName = SDK::FName(skCrypt(L"F9").decrypt());
		Keys[KeyName::F10].FName = SDK::FName(skCrypt(L"F10").decrypt());
		Keys[KeyName::F11].FName = SDK::FName(skCrypt(L"F11").decrypt());
		Keys[KeyName::F12].FName = SDK::FName(skCrypt(L"F12").decrypt());

		Keys[KeyName::NumLock].FName = SDK::FName(skCrypt(L"NumLock").decrypt());
		Keys[KeyName::ScrollLock].FName = SDK::FName(skCrypt(L"ScrollLock").decrypt());
		Keys[KeyName::LeftShift].FName = SDK::FName(skCrypt(L"LeftShift").decrypt());
		Keys[KeyName::RightShift].FName = SDK::FName(skCrypt(L"RightShift").decrypt());
		Keys[KeyName::LeftControl].FName = SDK::FName(skCrypt(L"LeftControl").decrypt());
		Keys[KeyName::RightControl].FName = SDK::FName(skCrypt(L"RightControl").decrypt());
		Keys[KeyName::LeftAlt].FName = SDK::FName(skCrypt(L"LeftAlt").decrypt());
		Keys[KeyName::RightAlt].FName = SDK::FName(skCrypt(L"RightAlt").decrypt());
		Keys[KeyName::LeftCommand].FName = SDK::FName(skCrypt(L"LeftCommand").decrypt());
		Keys[KeyName::RightCommand].FName = SDK::FName(skCrypt(L"RightCommand").decrypt());
		Keys[KeyName::Semicolon].FName = SDK::FName(skCrypt(L"Semicolon").decrypt());
		Keys[KeyName::Equals].FName = SDK::FName(skCrypt(L"Equals").decrypt());
		Keys[KeyName::Comma].FName = SDK::FName(skCrypt(L"Comma").decrypt());
		Keys[KeyName::Underscore].FName = SDK::FName(skCrypt(L"Underscore").decrypt());
		Keys[KeyName::Period].FName = SDK::FName(skCrypt(L"Period").decrypt());
		Keys[KeyName::Slash].FName = SDK::FName(skCrypt(L"Slash").decrypt());
		Keys[KeyName::Tilde].FName = SDK::FName(skCrypt(L"Tilde").decrypt());
		Keys[KeyName::LeftBracket].FName = SDK::FName(skCrypt(L"LeftBracket").decrypt());
		Keys[KeyName::Backslash].FName = SDK::FName(skCrypt(L"Backslash").decrypt());
		Keys[KeyName::RightBracket].FName = SDK::FName(skCrypt(L"RightBracket").decrypt());
		Keys[KeyName::Quote].FName = SDK::FName(skCrypt(L"Quote").decrypt());
		Keys[KeyName::Asterix].FName = SDK::FName(skCrypt(L"Asterix").decrypt());
		Keys[KeyName::Ampersand].FName = SDK::FName(skCrypt(L"Ampersand").decrypt());
		Keys[KeyName::Caret].FName = SDK::FName(skCrypt(L"Caret").decrypt());
		Keys[KeyName::Dollar].FName = SDK::FName(skCrypt(L"Dollar").decrypt());
		Keys[KeyName::Exclamation].FName = SDK::FName(skCrypt(L"Exclamation").decrypt());
		Keys[KeyName::Colon].FName = SDK::FName(skCrypt(L"Colon").decrypt());

		Keys[KeyName::A_AccentGrave].FName = SDK::FName(skCrypt(L"A_AccentGrave").decrypt());
		Keys[KeyName::E_AccentGrave].FName = SDK::FName(skCrypt(L"E_AccentGrave").decrypt());
		Keys[KeyName::E_AccentAigu].FName = SDK::FName(skCrypt(L"E_AccentAigu").decrypt());
		Keys[KeyName::C_Cedille].FName = SDK::FName(skCrypt(L"C_Cedille").decrypt());

		Keys[KeyName::Section].FName = SDK::FName(skCrypt(L"Section").decrypt());

		Keys[KeyName::Gamepad_LeftX].FName = SDK::FName(skCrypt(L"Gamepad_LeftX").decrypt());
		Keys[KeyName::Gamepad_LeftY].FName = SDK::FName(skCrypt(L"Gamepad_LeftY").decrypt());
		Keys[KeyName::Gamepad_RightX].FName = SDK::FName(skCrypt(L"Gamepad_RightX").decrypt());
		Keys[KeyName::Gamepad_RightY].FName = SDK::FName(skCrypt(L"Gamepad_RightY").decrypt());	
		Keys[KeyName::Gamepad_LeftTriggerAxis].FName = SDK::FName(skCrypt(L"Gamepad_LeftTriggerAxis").decrypt());
		Keys[KeyName::Gamepad_RightTriggerAxis].FName = SDK::FName(skCrypt(L"Gamepad_RightTriggerAxis").decrypt());
		Keys[KeyName::Gamepad_LeftThumbstick].FName = SDK::FName(skCrypt(L"Gamepad_LeftThumbstick").decrypt());
		Keys[KeyName::Gamepad_RightThumbstick].FName = SDK::FName(skCrypt(L"Gamepad_RightThumbstick").decrypt());
		Keys[KeyName::Gamepad_Special_Left].FName = SDK::FName(skCrypt(L"Gamepad_Special_Left").decrypt());	
		Keys[KeyName::Gamepad_Special_Left_X].FName = SDK::FName(skCrypt(L"Gamepad_Special_Left_X").decrypt());
		Keys[KeyName::Gamepad_Special_Left_Y].FName = SDK::FName(skCrypt(L"Gamepad_Special_Left_Y").decrypt());
		Keys[KeyName::Gamepad_Special_Right].FName = SDK::FName(skCrypt(L"Gamepad_Special_Right").decrypt());

		Keys[KeyName::Gamepad_FaceButton_Bottom].FName = SDK::FName(skCrypt(L"Gamepad_FaceButton_Bottom").decrypt());
		Keys[KeyName::Gamepad_FaceButton_Right].FName = SDK::FName(skCrypt(L"Gamepad_FaceButton_Right").decrypt());
		Keys[KeyName::Gamepad_FaceButton_Left].FName = SDK::FName(skCrypt(L"Gamepad_FaceButton_Left").decrypt());
		Keys[KeyName::Gamepad_FaceButton_Top].FName = SDK::FName(skCrypt(L"Gamepad_FaceButton_Top").decrypt());
		Keys[KeyName::Gamepad_LeftShoulder].FName = SDK::FName(skCrypt(L"Gamepad_LeftShoulder").decrypt());
		Keys[KeyName::Gamepad_RightShoulder].FName = SDK::FName(skCrypt(L"Gamepad_RightShoulder").decrypt());
		Keys[KeyName::Gamepad_LeftTrigger].FName = SDK::FName(skCrypt(L"Gamepad_LeftTrigger").decrypt());	
		Keys[KeyName::Gamepad_RightTrigger].FName = SDK::FName(skCrypt(L"Gamepad_RightTrigger").decrypt());
		Keys[KeyName::Gamepad_DPad_Up].FName = SDK::FName(skCrypt(L"Gamepad_DPad_Up").decrypt());
		Keys[KeyName::Gamepad_DPad_Down].FName = SDK::FName(skCrypt(L"Gamepad_DPad_Down").decrypt());	
		Keys[KeyName::Gamepad_DPad_Right].FName = SDK::FName(skCrypt(L"Gamepad_DPad_Right").decrypt());
		Keys[KeyName::Gamepad_DPad_Left].FName = SDK::FName(skCrypt(L"Gamepad_DPad_Left").decrypt());
		Keys[KeyName::Gamepad_LeftStick_Up].FName = SDK::FName(skCrypt(L"Gamepad_LeftStick_Up").decrypt());
		Keys[KeyName::Gamepad_LeftStick_Down].FName = SDK::FName(skCrypt(L"Gamepad_LeftStick_Down").decrypt());
		Keys[KeyName::Gamepad_LeftStick_Right].FName = SDK::FName(skCrypt(L"Gamepad_LeftStick_Right").decrypt());
		Keys[KeyName::Gamepad_LeftStick_Left].FName = SDK::FName(skCrypt(L"Gamepad_LeftStick_Left").decrypt());
		Keys[KeyName::Gamepad_RightStick_Up].FName = SDK::FName(skCrypt(L"Gamepad_RightStick_Up").decrypt());
		Keys[KeyName::Gamepad_RightStick_Down].FName = SDK::FName(skCrypt(L"Gamepad_RightStick_Down").decrypt());	
		Keys[KeyName::Gamepad_RightStick_Right].FName = SDK::FName(skCrypt(L"Gamepad_RightStick_Right").decrypt());	
		Keys[KeyName::Gamepad_RightStick_Left].FName = SDK::FName(skCrypt(L"Gamepad_RightStick_Left").decrypt());
	}

	DEBUG_LOG(LOG_OFFSET, skCrypt("Input system initialized!").decrypt());
}