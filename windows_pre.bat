rem precompile
SET inc_dir="C:/Users/vitat/Desktop/programming"
SET inc_dir2="C:/Users/vitat/Desktop/LearnToEarnPrivate"
SET inc_dir3="C:/Users/vitat/Desktop/LearnToEarnPrivate/inc"
SET inc_dir4="C:/Users/vitat/Desktop/LearnToEarnPrivate/lib"
SET inc_dir5="C:/Users/vitat/Desktop/LearnToEarnPrivate/bakalari"
SET inc_dir6="C:/Users/vitat/Desktop/programming/curlpp/include"
SET link_dir="C:/Users/vitat/Desktop/programming/curlpp/build"
g++ -c lib/glad.c
g++ -c lib/pugixml/pugixml.cpp -o pugixml.o
g++ -c lib/imgui/imgui_widgets.cpp -o imgui_widgets.o
g++ -c lib/imgui/imgui.cpp -o imgui.o
g++ -c lib/imgui/imgui_impl_glfw.cpp -o imgui_impl_glfw.o
g++ -c lib/imgui/imgui_draw.cpp -o imgui_draw.o
g++ -c lib/imgui/imgui_impl_opengl3.cpp -o imgui_impl_opengl3.o
g++ -c lib/imgui/imgui_tables.cpp -o imgui_tables.o
g++ -c -I %inc_dir% -I %inc_dir2% -I %inc_dir3% -I %inc_dir4% -I %inc_dir5% -I %inc_dir6% inc/utils.cpp -o utils.o
g++ -c -I %inc_dir% -I %inc_dir2% -I %inc_dir3% -I %inc_dir4% -I %inc_dir5% -I %inc_dir6% lib/base64.cpp -o base64.o
mv glad.o win
mv pugixml.o win
mv imgui_widgets.o win
mv imgui.o win
mv imgui_impl_glfw.o win
mv imgui_draw.o win
mv imgui_impl_opengl3.o win
mv imgui_tables.o win
mv utils.o win
mv base64.o win
exit