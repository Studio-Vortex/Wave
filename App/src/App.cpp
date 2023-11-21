#include "Wave/Wave.h"

#include <iostream>

void MyLogCallback(void* pUserData, uint32_t logLevel, const char* pMessage) {
	switch (static_cast<Wave::LogLevel>(logLevel)) {
		case Wave::LogLevel::Info:    std::cout << "Info: " << pMessage << '\n';    return;
		case Wave::LogLevel::Warning: std::cout << "Warning: " << pMessage << '\n'; return;
		case Wave::LogLevel::Error:   std::cout << "Error: " << pMessage << '\n';   return;
		case Wave::LogLevel::Debug:   std::cout << "Debug: " << pMessage << '\n';   return;
	}
}

int main(int argc, char** argv) {
	std::unique_ptr<Wave::Context> ctx = Wave::CreateContext();

	Wave::ContextSettings settings;
	settings.EnumerateDevices = true;
	settings.EnableDebugLogging = true;
	settings.LogCallback = MyLogCallback;

	Wave::ContextResult result = ctx->Init(settings);

	if (!result.Success) {
		std::cout << ctx->GetLastErrorMsg() << '\n';
	}

	std::cout << "Context successfully created!\n";

	for (const auto& deviceInfo : result.PlaybackDeviceInfos) {
		std::cout << "Device Name: " << deviceInfo.Name << '\n';
		std::cout << "Devive Type: Playback\n";
		std::cout << "Is Default: " << std::boolalpha << deviceInfo.IsDefault << '\n' << '\n';
	}

	for (const auto& deviceInfo : result.CaptureDeviceInfos) {
		std::cout << "Device Name: " << deviceInfo.Name << '\n';
		std::cout << "Devive Type: Capture\n";
		std::cout << "Is Default: " << std::boolalpha << deviceInfo.IsDefault << '\n' << '\n';
	}

	Wave::Engine engine = ctx->CreateEngine();
	if (engine.GetID() == Wave::ID::Invalid) {
		std::cout << ctx->GetLastErrorMsg() << '\n';
	}

	std::filesystem::path path = "Resources/Audio/music-file.mp3";
	if (!std::filesystem::exists(path)) {
		std::cout << "Path doesn't exist: " << path << "\n";
	}

	Wave::Sound sound = ctx->CreateSoundFromFile(engine.GetID(), path);
	if (sound.GetID() == Wave::ID::Invalid) {
		std::cout << ctx->GetLastErrorMsg() << '\n';
	}

	engine.Start();
	sound.Play();

	getchar();

	if (!ctx->Shutdown()) {
		std::cout << ctx->GetLastErrorMsg() << '\n';
	}

	Wave::DestroyContext(std::move(ctx));
	return 0;
}