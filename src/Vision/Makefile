msg:
	@echo "To Download dependencies:"
	@echo "\tmake download\n"
	@echo "To Compile the code:"
	@echo "\tmake compile\n"
	@echo "To Run the Vision:"
	@echo "\tmake run\n"
	

download:
	sudo apt-get install libopencv-dev python-opencv

compile: 
	g++ *.cpp `pkg-config opencv --cflags --libs` -o Vision

run:
	./Vision
