Mobjects = MMain.o MSocket.o MParser.o MOled.o

edit:$(Mobjects)
	gcc -o main $(Mobjects) -lbluetooth -lpthread
MMain.o: MMain.c MConstant.h MSocket.h MOled.h MParser.h
	gcc -c MMain.c -lpthread
MSocket.o: MSocket.c MSocket.h
	gcc -c MSocket.c -lbluetooth
MParser.o: MParser.c MParser.h MConstant.h MOled.h
	gcc -c MParser.c
MOled.o: MOled.c MOled.h
	gcc -c MOled.c
clean:
	rm main $(Mobjects)
