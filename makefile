PROJECT_NAME=SDL_Project 

run:
	./build/bin/$(PROJECT_NAME)

build_project:
	cd build/ && make -j

rebuild_and_run: build_project run

run_test:
	./build/bin/GLTests -v