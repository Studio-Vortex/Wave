#include <Wave/Wave.h>

#include <iostream>

using namespace Wave;

void MyLogCallback(void* pUserData, uint32_t logLevel, const char* pMessage) {
	switch (static_cast<LogLevel>(logLevel)) {
		case LogLevel::Info:    std::cout << "Info: " << pMessage << '\n';    return;
		case LogLevel::Warning: std::cout << "Warning: " << pMessage << '\n'; return;
		case LogLevel::Error:   std::cout << "Error: " << pMessage << '\n';   return;
		case LogLevel::Debug:   std::cout << "Debug: " << pMessage << '\n';   return;
	}
}

int main(int argc, char** argv) {
	std::unique_ptr<Context> ctx = CreateContext();

	ContextSettings settings;
	settings.EnumerateDevices = true;
	settings.EnableDebugLogging = true;
	settings.LogCallback = MyLogCallback;

	ContextResult result = ctx->Init(settings);

	if (!result.Success)
		std::cout << ctx->GetLastErrorMsg() << '\n';

	if (settings.EnumerateDevices)
		std::cout << "Enumerating Devices:\n";

	uint32_t i = 1;
	for (const auto& deviceInfo : result.PlaybackDeviceInfos) {
		std::cout << ' ' << i++ << "  Device Name: " << deviceInfo.Name << '\n';
		std::cout << "    Devive Type: Playback\n";
		std::cout << "    Is Default: " << std::boolalpha << deviceInfo.IsDefault << '\n' << '\n';
	}

	i = 1;
	for (const auto& deviceInfo : result.CaptureDeviceInfos) {
		std::cout << ' ' << i++ << "  Device Name: " << deviceInfo.Name << '\n';
		std::cout << "    Devive Type: Capture\n";
		std::cout << "    Is Default: " << std::boolalpha << deviceInfo.IsDefault << '\n' << '\n';
	}

	Engine engine = ctx->CreateEngine();
	if (engine.GetID() == ID::Invalid)
		std::cout << ctx->GetLastErrorMsg() << '\n';

	std::filesystem::path path = "Resources/Audio/darkdayroad.mp3";
	if (!std::filesystem::exists(path))
		std::cout << "Path doesn't exist: " << path << "\n";

	std::cout << "Filepath: " << path << '\n';

	Sound sound = ctx->CreateSoundFromFile(engine, path);
	if (sound.GetID() == ID::Invalid)
		std::cout << ctx->GetLastErrorMsg() << '\n';

	if (!engine.Start())
		std::cout << ctx->GetLastErrorMsg() << '\n';
	if (!sound.Play())
		std::cout << ctx->GetLastErrorMsg() << '\n';

	sound.SetAttenuationModel(AttenuationModel::None);
	sound.SetSpacialized(false);
	sound.SetLooping(true);
	sound.SetPitch(1.17f);
	sound.SetVolume(1.1f);

	getchar();

	if (!sound.Stop())
		std::cout << ctx->GetLastErrorMsg() << '\n';
	if (!engine.Stop())
		std::cout << ctx->GetLastErrorMsg() << '\n';

	if (!ctx->DestroySound(sound))
		std::cout << ctx->GetLastErrorMsg() << '\n';
	if (!ctx->DestroyEngine(engine))
		std::cout << ctx->GetLastErrorMsg() << '\n';
	if (!ctx->Shutdown())
		std::cout << ctx->GetLastErrorMsg() << '\n';

	printf("Done\n");
	getchar();

	DestroyContext(std::move(ctx));
	return 0;
}