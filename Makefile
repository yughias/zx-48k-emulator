gcc:
	gcc -Iinclude -Llib src/*.c -lmingw32 -lSDL2 -lopengl32 -O2 -D MAINLOOP_GL -DMAINLOOP_WINDOWS -lcomdlg32 -lole32 -lshlwapi -o spectrum.exe

emcc:
	emcc -Iinclude $(wildcard src/*.c) -sUSE_SDL=2 --preload-file data -O2 \
	--exclude-file data/BINs --exclude-file data/SCRs --exclude-file data/Z80s --exclude-file data/TAPs --exclude-file data/icon.bmp \
	-sFORCE_FILESYSTEM -sALLOW_MEMORY_GROWTH \
	-sEXPORTED_FUNCTIONS="[_stopTape,_emscripten_resetEmulation,_frontend_useKeyboard,_frontend_useKempston,_emscripten_loadTape,_emscripten_instantLoadTape,_emscripten_loadZ80,_main]" \
	-o website/emulator.js