SET PATH=%PLAYDATE_ARM_PATH%;%PLAYDATE_CMAKE_PATH%;%PATH%
call %PLAYDATE_VSDEVCONSOLE%
mkdir VSProject
cd VSProject
cmake ..

