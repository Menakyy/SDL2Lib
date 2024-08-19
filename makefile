PROJECT_NAME=SDL_Project 

run:
	./build/bin/$(PROJECT_NAME)

build_project:
	cd build/ && ninja

rebuild_and_run: build_project run