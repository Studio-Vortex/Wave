#include <Wave/Wave.h>

#include <iostream>

void LowLevelDemo(std::shared_ptr<Wave::Context> ctx, const std::filesystem::path& path)
{
	if (!std::filesystem::exists(path)) // Make sure our path exists, otherwise context will give us an error
		std::cout << "Path doesn't exist: " << path << "\n";

	std::cout << "Filepath: " << path << '\n';

	// Create an engine to play our sound
	Wave::Engine engine = ctx->CreateEngine();
	if (engine.GetID() == Wave::ID::Invalid) // Make sure it is valid
		std::cout << ctx->GetLastErrorMsg() << '\n';

	// Use the context to create a sound from an engine and a filepath
	Wave::Sound sound = ctx->CreateSoundFromFile(engine, path);
	if (sound.GetID() == Wave::ID::Invalid) // Make sure it is valid
		std::cout << ctx->GetLastErrorMsg() << '\n';

	if (!engine.Start()) // Start the engine
		std::cout << ctx->GetLastErrorMsg() << '\n';
	if (!sound.Play()) // Play the sound
		std::cout << ctx->GetLastErrorMsg() << '\n';

	// Some various functions that change the output of the sound
	sound.SetAttenuationModel(Wave::AttenuationModel::None);
	sound.SetPosition(Wave::Vec3(0.0f));
	sound.SetSpacialized(false);
	sound.SetLooping(true);
	sound.SetPitch(1.17f);
	sound.SetVolume(1.1f);

	getchar(); // Let the sound play until we click a key

	// (NOTE): if you just stop an engine, this will cause the underlying implementation to 
	//         throw an error. So make sure that the sound is stopped first then the engine.
	if (!sound.Stop()) // Stop the sound
		std::cout << ctx->GetLastErrorMsg() << '\n';
	if (!engine.Stop()) // Stop the engine
		std::cout << ctx->GetLastErrorMsg() << '\n';

	// (NOTE): the same thing applies here, we must destroy the sound before the engine because
	//         the sound relies on the engine to live until at least the lifetime of itself
	if (!ctx->DestroySound(sound))
		std::cout << ctx->GetLastErrorMsg() << '\n';
	if (!ctx->DestroyEngine(engine))
		std::cout << ctx->GetLastErrorMsg() << '\n';

	// Now we can shutdown the context because we are done playing sounds
	if (!ctx->Shutdown())
		std::cout << ctx->GetLastErrorMsg() << '\n';

	printf("Done\n");
	getchar();
}

void HighLevelDemo(std::shared_ptr<Wave::Context> ctx, const std::filesystem::path& path)
{
	if (!std::filesystem::exists(path)) // Make sure our path exists, otherwise context will give us an error
		std::cout << "Path doesn't exist: " << path << "\n";

	std::cout << "Filepath: " << path << '\n';

	// Create an instance of a PlaybackDevice
	Wave::PlaybackDevice device;
	device.Init(ctx, path); // Initialize the device

	device.Play(); // Play the sound

	// We can get the sound from the device
	Wave::Sound sound = device.GetSound();

	// Some various functions that change the output of the sound
	sound.SetAttenuationModel(Wave::AttenuationModel::None);
	sound.SetPosition(Wave::Vec3(0.0f));
	sound.SetSpacialized(false);
	sound.SetLooping(true);
	sound.SetPitch(1.17f);
	sound.SetVolume(1.1f);

	getchar();

	// Stop the sound (device.Shutdown() will stop the sound anyway so this is not necessary)
	device.Stop();

	device.Shutdown(ctx); // Shutdown the device

	printf("Done\n");
	getchar();
}

void MyLogCallback(void* pUserData, uint32_t logLevel, const char* pMessage) {
	switch (static_cast<Wave::LogLevel>(logLevel)) {
		case Wave::LogLevel::Info:    std::cout << "Info: " << pMessage << '\n';    return;
		case Wave::LogLevel::Warning: std::cout << "Warning: " << pMessage << '\n'; return;
		case Wave::LogLevel::Error:   std::cout << "Error: " << pMessage << '\n';   return;
		case Wave::LogLevel::Debug:   std::cout << "Debug: " << pMessage << '\n';   return;
	}
}

int main(int argc, char** argv) {
	std::shared_ptr<Wave::Context> ctx = Wave::CreateContext();

	Wave::ContextSettings settings;
	settings.EnumerateDevices = true;
	settings.EnableDebugLogging = true;
	settings.LogCallback = MyLogCallback;

	Wave::ContextResult result = ctx->Init(settings);

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

	std::filesystem::path path = "Resources/Audio/darkdayroad.mp3";

	//LowLevelDemo(ctx, path);
	HighLevelDemo(ctx, path);

	Wave::DestroyContext(ctx);
	return 0;
}