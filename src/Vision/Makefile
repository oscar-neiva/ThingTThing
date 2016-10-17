msg:
	@echo "To Download dependencies:"
	@echo "\tmake download\n"
	@echo "To lock the camera focus:"
	@echo "\tmake lock cam\n"
	@echo "To Compile the code:"
	@echo "\tmake compile\n"
	@echo "To Run the Vision:"
	@echo "\tmake run\n"
	
download:
	sudo apt-get install libopencv-dev python-opencv

lock cam:
	chmod 770 cameraConfig.sh
	./cameraConfig.sh 1

compile: 
	g++ *.cpp `pkg-config opencv --cflags --libs` -o Vision

run:
	./Vision
