# LearnToEarnPrivate
Learn to earn is an app which helps you with learning, improve your learning methos, planning and time saving.

# Build

## Linux

### Preparing dependecies

```bash
sudo apt-get install libpthread-dev
sudo apt-get install libmesa-dev
sudo apt-get install libfreeglut-dev
sudo apt-get install libxorg-dev
sudo apt-get install libcurl-dev
sudo apt-get install libcurlpp-dev
```

### Download + build + run

```sh
git clone https://github.com/MitasVit/LearnToEarnPrivate.git
cd LearnToEarnPrivate
sh compile_run_lesbak.sh
```

## Windows

### Preparing dependecies

```cmd
curl https://github.com/msys2/msys2-installer/releases/download/2022-06-03/msys2-x86_64-20220603.exe >> msys2.exe
start msys2.exe

```

Run this in msys2 console
```cmd
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
pacman -S --needed base-devel mingw-w64-x86_64-mesa
pacman -S --needed base-devel mingw-w64-x86_64-freeglut
pacman -S --needed base-devel mingw-w64-x86_64-glfw
pacman -S --needed base-devel mingw-w64-x86_64-curl

```

Add the path to your Mingw-w64 bin folder to the Windows PATH environment variable by using the following steps:

- In the Windows search bar, type 'settings' to open your Windows Settings.
- Search for Edit environment variables for your account.
- Choose the Path variable in your User variables and then select Edit.
- Select New and add the Mingw-w64 destination folder path to the system path. The exact path depends on which version of Mingw-w64 you have installed and where you installed it. 
- If you used the settings above to install Mingw-w64, then add this to the path:  `C:\msys64\mingw64\bin `.
- Select OK to save the updated PATH. You will need to reopen any console windows for the new PATH location to be available.
- Check your MinGW installation with command:  `g++ --version `

```cmd
git clone https://github.com/MitasVit/LearnToEarnPrivate.git
git clone https://github.com/jpbarrette/curlpp.git
cd curlpp 
mkdir build
cd build
cmake -G "MinGW Makefiles"
mingw32-make -f Makefile
copy libcurlpp.dll ../../LearnToEarnPrivate/
cd ..
cd ..
cd LearnToEarnPrivate
```

### Build

Precompiled objects - it's nesseseary to run it once:
```cmd
start windows_pre.bat
```

Final compile + linking precompiled objects:
```cmd
start windows.bat
```

### Running

Go to `LearnToEarnPrivate/win` directory and open main.exe.