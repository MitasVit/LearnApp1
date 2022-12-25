inc_dir="../../../../../../../../../../home/mitas/Desktop/programming/game/00build/lib/"
inc_dir2="../../../../../../../../../../home/mitas/Desktop/programming/game/00build/"
inc_dir4="../../../../../../../../../../home/mitas/Desktop/programming/game/00build/bakalari/"
inc_dir3="../../../../../../../../../../home/mitas/Desktop/programming/game/00build/inc/"
link_atr=" -lstdc++ -lcurl -lcurlpp "
g++ -c -I $inc_dir  -I $inc_dir2 -I $inc_dir3 -I $inc_dir4 baka_test.cpp bakalari.cpp
g++ baka_test.o bakalari.o -o baka_test.out $link_atr
./baka_test.out