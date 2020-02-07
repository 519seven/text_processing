all: replacer.bin

replacer.bin: main.o replacer.o
	g++ -o replacer.bin main.o replacerImp.cpp -I/usr/include/mysql -L/usr/lib/libmysqlcppconn-static.a

main.o: main.cpp replacer.h
	g++ -Wall -c -g main.cpp -I/usr/include/mysql -L/usr/lib/libmysqlcppconn-static.a

replacer.o: replacerImp.cpp replacer.h
	g++ -Wall -c -g replacerImp.cpp

clean:
	# -f so this will succeed even if the files don't exist
	rm -f *.o replacer.bin
