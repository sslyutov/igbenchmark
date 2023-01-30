cmake -B "binary" -G "Visual Studio 16 2019"

cd "binary"

devenv "igbenchmark.vcxproj" /Rebuild "Release|x64"

devenv "igbenchmark.vcxproj" /Rebuild "Debug|x64"

cd ..
