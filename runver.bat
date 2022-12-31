rem compile
g++ ver.cpp -lcairo -lfreetype -l "pango-1.0" -l "pangocairo-1.0" -L "C:\msys64\mingw64\lib" -l "glib-2.0" -lintl -l "gobject-2.0" -I "C:\msys64\mingw64\include\cairo" -I "C:\msys64\mingw64\include\pango-1.0" -I "C:\msys64\mingw64\include\pango-1.0\pango" -I "C:\msys64\mingw64\include\glib-2.0" -I "C:\msys64\mingw64\include\glib-2.0\glib" -I "C:\msys64\mingw64\include\glib-2.0\gobject" -I "C:\msys64\mingw64\include\glib-2.0\gio" -I "C:\msys64\mingw64\lib\glib-2.0\include" -I "C:\msys64\mingw64\include\freetype2\freetype" -I "C:\msys64\mingw64\include\freetype2" -I "C:\msys64\mingw64\include\harfbuzz" -o ver.exe
rem run
start ver.exe
rem open generated pdf
pause
start hi.pdf