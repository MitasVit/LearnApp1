inc_dir="../../../../../../../../../../home/mitas/Desktop/programming/game/00build/lib/"
inc_dir2="../../../../../../../../../../home/mitas/Desktop/programming/game/00build/"
inc_dir3="../../../../../../../../../../home/mitas/Desktop/programming/game/00build/inc/"
link_atr=" -lstdc++ -lcurl -lcurlpp "
g++ -c -I $inc_dir  -I $inc_dir2 -I $inc_dir3 hamtak.cpp
g++ hamtak.o -o test2.out $link_atr