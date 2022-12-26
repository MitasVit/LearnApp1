
rem compile lesbak
SET inc_dir="C:/Users/vitat/Desktop/programming"
SET inc_dir2="C:/Users/vitat/Desktop/LearnToEarnPrivate"
SET inc_dir3="C:/Users/vitat/Desktop/LearnToEarnPrivate/inc"
SET inc_dir4="C:/Users/vitat/Desktop/LearnToEarnPrivate/lib"
SET inc_dir5="C:/Users/vitat/Desktop/LearnToEarnPrivate/bakalari"
SET inc_dir6="C:/Users/vitat/Desktop/programming/curlpp/include"
SET link_dir="C:/Users/vitat/Desktop/programming/curlpp/build"
SET link_atr=-lstdc++ -lcurl -lcurlpp -lglfw3 -lpthread
SET precompiled=win/glad.o win/pugixml.o win/imgui_widgets.o win/imgui.o win/imgui_impl_glfw.o win/imgui_draw.o win/imgui_impl_opengl3.o win/imgui_tables.o win/utils.o win/base64.o win/lesson.o win/lesson_win.o win/bakalari.o
g++ -c -I %inc_dir% -I %inc_dir2% -I %inc_dir3% -I %inc_dir4% -I %inc_dir5% -I %inc_dir6% lesson_win.cpp -o lesson_win.o
g++ -c -I %inc_dir% -I %inc_dir2% -I %inc_dir3% -I %inc_dir4% -I %inc_dir5% -I %inc_dir6% inc/lesson.cpp -o lesson.o
g++ -c -I %inc_dir% -I %inc_dir2% -I %inc_dir3% -I %inc_dir4% -I %inc_dir5% -I %inc_dir6% bakalari/bakalari.cpp -o bakalari.o
mv lesson.o win
mv lesson_win.o win
mv bakalari.o win
g++ bakalari.o lesson_win.o base64.o lesson.o utils.o %precompiled% -o main.exe %link_atr%  -L %link_dir% -fexec-charset=UTF-8 
mv main.exe win
pause
exit
