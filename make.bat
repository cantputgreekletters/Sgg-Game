@echo off
g++ main.cpp ./sgg/*.cpp ./include/*.cpp -DGLM_ENABLE_EXPERIMENTAL -I. -I"L:/Programming Languages/Languages/MySys2/ucrt64/include/freetype2"  -lopengl32 -lglew32 -lSDL2 -lSDL2_mixer -lfreetype -o main
echo "Runned compilation"