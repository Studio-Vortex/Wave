#!/bin/bash

pushd ..
vendor/bin/premake/macOS/premake5 --cc=clang --file=build.lua make
popd