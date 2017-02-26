Mobjects = MMain.o MSocket.o MParser.o MOled.o MGpio.o MAction.o MBasic.o MFile.o MPeripheral.o

edit:$(Mobjects)
	gcc -o main $(Mobjects) -lbluetooth -lpthread
MMain.o: MMain.c MConstant.h MSocket.h MOled.h MParser.h MGpio.h MFile.h MAction.h MPeripheral.h
	gcc -c MMain.c -lpthread
MSocket.o: MSocket.c MSocket.h
	gcc -c MSocket.c -lbluetooth
MParser.o: MParser.c MParser.h MConstant.h MOled.h MAction.h
	gcc -c MParser.c
MOled.o: MOled.c MOled.h MBasic.h
	gcc -c MOled.c
MGpio.o: MGpio.c MGpio.h
	gcc -c MGpio.c
MAction.o: MAction.c MAction.h MOled.h MGpio.h MFile.h MPeripheral.h
	gcc -c MAction.c
MBasic.o: MBasic.c MBasic.h
	gcc -c MBasic.c
MFile.o: MFile.c MFile.h
	gcc -c MFile.c
MPeripheral.o: MPeripheral.c MPeripheral.h
	gcc -c MPeripheral.c
clean:
	rm main $(Mobjects)
