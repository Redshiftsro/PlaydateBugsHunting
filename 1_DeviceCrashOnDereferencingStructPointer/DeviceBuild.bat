SET PATH=%PLAYDATE_ARM_PATH%;%PLAYDATE_CMAKE_PATH%;%PATH%
call %PLAYDATE_VSDEVCONSOLE%

IF EXIST DeviceBuild (
    rmdir /s /q DeviceBuild
)

mkdir DeviceBuild
cd DeviceBuild
nmake clean
cmake .. -G "NMake Makefiles" --toolchain=%PLAYDATE_SDK_PATH%\C_API\buildsupport\arm.cmake
nmake

