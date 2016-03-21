Mobjects = MMain.o MSocket.o

edit:$(Mobjects)
	gcc -o main $(Mobjects) -lbluetooth -lpthread
MMain.o: MMain.c MConstant.h MSocket.h
	gcc -c MMain.c -lpthread
MSocket.o: MSocket.c MSocket.h
	gcc -c MSocket.c -lbluetooth
clean:
	rm main $(Mobjects)
