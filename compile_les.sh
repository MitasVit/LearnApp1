inc_dir="../../../../../../../../../../home/mitas/Desktop/programming/game/00build/lib/"
inc_dir2="../../../../../../../../../../home/mitas/Desktop/programming/game/00build/"
inc_dir3="../../../../../../../../../../home/mitas/Desktop/programming/game/00build/inc/"
link_atr="-lGL -lGLU -lglut -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lassimp"
precompiled="out/precompiled/glad.o out/precompiled/pugixml.o out/precompiled/imgui_widgets.o out/precompiled/imgui.o out/precompiled/imgui_impl_glfw.o out/precompiled/imgui_impl_opengl3.o out/precompiled/imgui_draw.o out/precompiled/imgui_tables.o"
g++ -c -I $inc_dir -I $inc_dir2 -I $inc_dir3 lesson_win.cpp
g++ -c -I $inc_dir -I $inc_dir2 -I $inc_dir3 inc/lesson.cpp
g++ -c -I $inc_dir -I $inc_dir2 -I $inc_dir3 inc/utils.cpp
g++ lesson_win.o lesson.o utils.o  $precompiled -o main_lesson_win.exec $link_atr -fexec-charset=UTF-8 
mv main_lesson_win.exec out
rm lesson_win.o
rm lesson.o
rm utils.o
