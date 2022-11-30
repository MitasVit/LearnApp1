inc_dir="../../../../../../../../../../../home/mitas/Desktop/programming/game"
link_atr="-lGL -lGLU -lglut -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lassimp"
precompiled="out/precompiled/glad.o out/precompiled/pugixml.o out/precompiled/imgui.o out/precompiled/imgui_impl_glfw.o out/precompiled/imgui_impl_opengl3.o out/precompiled/imgui_draw.o out/precompiled/imgui_widgets.o out/precompiled/imgui_tables.o"
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/model.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/game.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/mesh.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game main.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/camera.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/EBO.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/VAO.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/shader.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/texture.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/transform3d.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/VBO.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/interactive.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/path.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/light.cpp
g++ -c -I/../../../../home/mitas/Desktop/programming/game inc/lesson.cpp
g++ main.o game.o transform3d.o camera.o light.o interactive.o lesson.o model.o path.o VBO.o VAO.o EBO.o mesh.o texture.o shader.o $precompiled -o main.exec $link_atr
mv main.exec out
rm main.o
rm EBO.o
rm VAO.o
rm VBO.o
rm shader.o
rm texture.o
rm camera.o
rm mesh.o
rm model.o
rm lesson.o
rm game.o
rm path.o
rm transform3d.o
rm interactive.o
rm light.o
