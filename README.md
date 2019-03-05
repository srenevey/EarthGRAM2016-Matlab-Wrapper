Interface to call EarthGRAM 2016 directly from Matlab.

## Prerequisites

EarthGRAM 2016 is developed by NASA and can be obtained from the [NASA Software Catalog](https://software.nasa.gov/software/MFS-32780-2). By default, EarthGRAM 2016 prompts the user to enter the path to NameRef.txt which is not ideal for a seamless integration. The file *earthgram.patch* modifies some of the source files to suppress any prompt and return the output in a variable rather than write it in files. To apply the patch, copy *earthgram.patch* into EarthGram2016/Source and then on Unix, open Terminal, navigate to EarthGRAM2016/Source, and enter

    patch -p1 < earthgram.patch

Finally, copy the file CMakeLists.txt into EarthGRAM2016/Source.

## Installation

The following instructions were tested on:

- Windows 7
  - Visual Studio 2017
  - CMake 3.13.14
  - Matlab 2018b
- macos 10.12.6
  - Xcode 9.2
  - CMake 3.12.4
  - Matlab 2018a
- Ubuntu 18.04.1
  - gcc 7.3.0
  - CMake 3.12.1
  - Matlab 2018a



### Unix

1. Install a C++ compiler and [CMake](https://cmake.org/) (version 3.12 or higher is required).

   1. On macos: either install Xcode from the App Store or the command line tools by opening a Terminal and typing `xcode-select --install`.

2. In EarthGRAM2016, open NameRef.txt and modify as follows:

       atmpath = <PROJECT_ROOT>/EarthGRAM2016/IOfiles/
       NCEPpath = <PROJECT_ROOT>/EarthGRAM2016/NCEPdata/FixedBin/
       trapath = null
       prtpath = null
       nprpath =  null
       conpath =  null
       rrapath = <PROJECT_ROOT>/EarthGRAM2016/RRAdata/
       ...
       iurra = 0
       ...
       ibltest = 0

3. Open a terminal and navigate to EarthGRAM2016/Source:

   `cd <YOUR_PATH>/EarthGRAM2016/Source`

4. Type:

   `mkdir build`

   `cd build`

   `cmake ..`

   `make`

   This will generate the static library libEarthGRAM2016.a.

5. Open Matlab and type `mex -setup` in the command window and follow the instructions if no compiler is set.

6. Open build.m and modify the first line to point to the EarthGRAM2016 directory.

7. Run the script. This will produce the mex file get_atm_density.mexxxx.

8. Run test.m to check if everything works.

9. For help, type `help get_atm_density` in the command window.

### Windows

1. Install Visual Studio 2017 and [CMake](https://cmake.org/) (version 3.12 or higher is required).

2. In EarthGRAM2016, open NameRef.txt and modify as follows:

          atmpath = <PROJECT_ROOT>\EarthGRAM2016\IOfiles\
          NCEPpath = <PROJECT_ROOT>\EarthGRAM2016\NCEPdata\FixedBin\
          trapath = null
          prtpath = null
          nprpath =  null
          conpath =  null
          rrapath = <PROJECT_ROOT>\EarthGRAM2016\RRAdata\
          ...
          iurra = 0
          ...
          ibltest = 0

3. In EarthGRAM2016\Source, create a directory named *build*.

4. Open "Developer Command Prompt for VS 2017".

5. Navigate to the build directory:

   `cd <YOUR_PATH>\EarthGRAM2016\Source\build`

6. Then type:

   `cmake -G "Visual Studio 15 2017 Win64" ..`

   `msbuild EarthGRAM2016.sln /p:Configuration=Release`

7. This will create the library EarthGRAM2016.lib in build/Release.

8. Open Matlab and type `mex -setup` in the command window and follow the instructions if no compiler is set.

9. Open build.m and modify the first line to point to the EarthGRAM2016 directory.

10. Run the script. This will produce the mex file get_atm_density.mexw64.

11. Run test.m to check if everything works.

12. For help, type `help get_atm_density` in the command window.



## Usage

The function is called as follows:

​	`density = get_atm_density(altitude, latitude, longitude, epoch);`

where the altitude above see level is in km, the latitude and longitude are in degrees, and epoch is a char array with the current epoch formatted as 'YYYY-MM-DD hh:mm:ss'. The density is in kg/m^3. Help text for this function can be displayed by typing `help get_atm_density` in Matlab's Command Window.



## Troubleshooting

*Issue*: The compilation succeeds but Matlab crashes when running test.m.

*Fix*: Make sure that the paths in NameRef.txt and build.m contain a slash '/' (macos/Linux) or backslash '\\' (Windows) at the end of the path name. For instance, use `<YOUR_PATH>\EarthGRAM2016\` instead of `<YOUR_PATH>\EarthGRAM2016`. The EarthGRAM library and the mex file need to be recompiled if the paths are changed.