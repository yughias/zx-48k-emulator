gcc:
	gcc -Iinclude -Llib src/*.c -lSDL2 -lopengl32 -O2 -D MAINLOOP_GL -D MAINLOOP_WINDOWS -lcomdlg32 -lole32 -o spectrum.exe

emcc:
	emcc -Iinclude $(wildcard src/*.c) -sUSE_SDL=2 -O2 --preload-file data -o website/index.html