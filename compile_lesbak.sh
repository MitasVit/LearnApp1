inc_dir="../../../../../../../../../../home/mitas/Bureau/programming/game/00build/lib/"
inc_dir2="../../../../../../../../../../home/mitas/Bureau/programming/game/00build/"
inc_dir3="../../../../../../../../../../home/mitas/Bureau/programming/game/00build/inc/"
inc_dir4="../../../../../../../../../../home/mitas/Bureau/programming/game/00build/bakalari/"
link_atr="-lstdc++ -lcurl -lcurlpp -lGL -lGLU -lglut -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lassimp"
precompiled="out/precompiled/glad.o out/precompiled/pugixml.o out/precompiled/imgui_widgets.o out/precompiled/imgui.o out/precompiled/imgui_impl_glfw.o out/precompiled/imgui_impl_opengl3.o out/precompiled/imgui_draw.o out/precompiled/imgui_tables.o"
g++ -c -I $inc_dir -I $inc_dir2 -I $inc_dir3 -I $inc_dir4 lesson_win.cpp
g++ -c -I $inc_dir -I $inc_dir2 -I $inc_dir3 -I $inc_dir4 inc/lesson.cpp
g++ -c -I $inc_dir -I $inc_dir2 -I $inc_dir3 -I $inc_dir4 inc/utils.cpp
g++ -c -I $inc_dir -I $inc_dir2 -I $inc_dir3 -I $inc_dir4 lib/base64.cpp
g++ -c -I $inc_dir -I $inc_dir2 -I $inc_dir3 -I $inc_dir4 bakalari/bakalari.cpp
g++ bakalari.o lesson_win.o base64.o lesson.o utils.o  $precompiled -o main_lesson_win2.exec $link_atr -fexec-charset=UTF-8 
mv main_lesson_win2.exec out
rm lesson_win.o
rm lesson.o
rm utils.o
rm bakalari.o
