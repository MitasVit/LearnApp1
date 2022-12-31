
rem compile lesbak
rem -lcairo-svg -lcairo
SET inc_dir="C:/Users/vitat/Desktop/programming"
SET inc_dir2="C:/Users/vitat/Desktop/LearnToEarnPrivate"
SET inc_dir3="C:/Users/vitat/Desktop/LearnToEarnPrivate/inc"
SET inc_dir4="C:/Users/vitat/Desktop/LearnToEarnPrivate/lib"
SET inc_dir5="C:/Users/vitat/Desktop/LearnToEarnPrivate/bakalari"
SET inc_dir6="C:/Users/vitat/Desktop/programming/curlpp/include"
SET inc_dir7="C:/msys64/mingw64/include"
SET inc_dir8="C:/msys64/mingw64/include/cairo"
SET inc_dir9="C:/Users/vitat/Desktop/LearnToEarnPrivate/lib/imgui"
SET inc_dir10="C:/msys64/mingw64/include/pango-1.0/"
SET link_dir="C:/Users/vitat/Desktop/programming/curlpp/build"
SET link_atr=-lstdc++ -lcurl -lcurlpp -lglfw3 -lpthread -lcairo
SET precompiled=win/stb.o win/glad.o win/pugixml.o win/imgui_widgets.o win/imgui.o win/imgui_impl_glfw.o win/imgui_draw.o win/imgui_impl_opengl3.o win/imgui_tables.o win/utils.o win/base64.o win/lesson.o win/lesson_win.o win/bakalari.o
g++ -c -I %inc_dir% -I %inc_dir2% -I %inc_dir3% -I %inc_dir4% -I %inc_dir5% -I %inc_dir6% -I %inc_dir7% -I %inc_dir8% -I %inc_dir9% lesson_win.cpp -o lesson_win.o
g++ -c -I %inc_dir% -I %inc_dir2% -I %inc_dir3% -I %inc_dir4% -I %inc_dir5% -I %inc_dir6% -I %inc_dir7% -I %inc_dir8% -I %inc_dir9% inc/lesson.cpp -o lesson.o
g++ -c -I %inc_dir% -I %inc_dir2% -I %inc_dir3% -I %inc_dir4% -I %inc_dir5% -I %inc_dir6% -I %inc_dir7% -I %inc_dir8% -I %inc_dir9% bakalari/bakalari.cpp -o bakalari.o
move lesson.o win
move lesson_win.o win
move bakalari.o win
g++  %precompiled% -o main.exe %link_atr%  -L %link_dir% -fexec-charset=UTF-8 
move main.exe win
pause
rem running
cd win
start main.exe
cd ..
exit
