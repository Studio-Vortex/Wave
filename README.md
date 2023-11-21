# Wave

Wave is a lightning fast cross-platform 2d & 3d audio library suitable for use in game engines or other applications that require fast audio solutions.

You can choose to use the high or low-level api to accommodate your needs.

## Building Wave

Wave will build as a static library using Premake. To get started, clone the project

```bash
git clone --recursive "https://github.com/Jshuk-7/Wave"
```

Then head to [Wave/scripts](https://github.com/JShuk-7/Wave/blob/master/scripts) and run the appropriate setup script for your platform.
This will generate a Visual Studio solution file that you can use to build the library.

Note: switching from a static to dynamic library is trivial with Premake, just head to [build-wave.lua](https://github.com/JShuk-7/Wave/blob/master/Wave/build-wave.lua) in 'Wave/Wave'. Change 'staticruntime' to 'on', and under 'defines' add 'WAVE_BUILD_DLL'.

## Creating a Context

```cpp
#include <Wave/Wave.h>

void foo() {
    // Create the Context
	std::shared_ptr<Wave::Context> ctx = Wave::CreateContext();

    // Settings for the Context
	Wave::ContextSettings settings;

    // Initialize the Context
	Wave::ContextResult result = ctx->Init(settings);

    // Make sure the Context is valid
	if (!result.Success)
		std::cout << ctx->GetLastErrorMsg() << '\n';
}
```

## Destroying a Context

```cpp
#include <Wave/Wave.h>

void foo() {
    // Create the Context
    std::shared_ptr<Wave::Context> ctx = Wave::CreateContext();

    // Destroy the Context
	Wave::DestroyContext(ctx);
}
```

## Setting Context Settings

```cpp
#include <Wave/Wave.h>

void foo() {
    // Create the Context
    std::shared_ptr<Wave::Context> ctx = Wave::CreateContext();

    // Settings for the Context
	Wave::ContextSettings settings;
	settings.EnumerateDevices = true; // Must be enabled to enumerate devices
	settings.EnableDebugLogging = true; // Must be enabled to use callback
	settings.LogCallback = MyLogCallback; // Callback to logger

    // Initialize the Context
	Wave::ContextResult result = ctx->Init(settings);

     // Make sure the Context is valid
	if (!result.Success)
		std::cout << ctx->GetLastErrorMsg() << '\n';

    // Destroy the Context
	Wave::DestroyContext(ctx);
}
```

## Enumerating Devices

```cpp
#include <Wave/Wave.h>

void foo() {
    // Create the Context
    std::shared_ptr<Wave::Context> ctx = Wave::CreateContext();

    // Settings for the Context
	Wave::ContextSettings settings;
	settings.EnumerateDevices = true; // Must be enabled to enumerate devices

    // Initialize the Context
	Wave::ContextResult result = ctx->Init(settings);

    // Make sure the Context is valid
	if (!result.Success)
		std::cout << ctx->GetLastErrorMsg() << '\n';

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

    // Destroy the Context
	Wave::DestroyContext(ctx);
}
```

## High-Level API

```cpp
#include <Wave/Wave.h>

void HighLevelDemo(std::shared_ptr<Wave::Context> ctx, const std::filesystem::path& path)
{
    // Make sure our path exists, otherwise context will give us an error
	if (!std::filesystem::exists(path))
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
```

## Low-Level API

```cpp
#include <Wave/Wave.h>

void LowLevelDemo(std::shared_ptr<Wave::Context> ctx, const std::filesystem::path& path)
{
    // Make sure our path exists, otherwise context will give us an error
	if (!std::filesystem::exists(path))
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
```
