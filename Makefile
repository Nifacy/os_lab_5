all: main1 main2

# Object files

compiled/main1.o: src/main1.c
	gcc -c src/main1.c -o compiled/main1.o

compiled/main2.o: src/main2.c
	gcc -c src/main2.c -o compiled/main2.o

compiled/gcf1.o: src/gcf/gcf1.c
	gcc -c -fpic src/gcf/gcf1.c -o compiled/gcf1.o

compiled/gcf2.o: src/gcf/gcf2.c
	gcc -c -fpic src/gcf/gcf2.c -o compiled/gcf2.o

compiled/translation1.o: src/translation/translation1.c
	gcc -c -fpic src/translation/translation1.c -o compiled/translation1.o

compiled/translation2.o: src/translation/translation2.c
	gcc -c -fpic src/translation/translation2.c -o compiled/translation2.o

compiled/convert.o: src/translation/convert/convert.c
	gcc -c -fpic src/translation/convert/convert.c -o compiled/convert.o

# Dynamic libraries

libs/libgcf1.so: compiled/gcf1.o
	gcc -shared compiled/gcf1.o -o libs/libgcf1.so

libs/libgcf2.so: compiled/gcf2.o
	gcc -shared compiled/gcf2.o -o libs/libgcf2.so

libs/libtranslation1.so: compiled/translation1.o compiled/convert.o
	gcc -shared compiled/translation1.o compiled/convert.o -o libs/libtranslation1.so

libs/libtranslation2.so: compiled/translation2.o compiled/convert.o
	gcc -shared compiled/translation2.o compiled/convert.o -o libs/libtranslation2.so

# Link with dynamic libs

main1: libs/libgcf1.so libs/libtranslation1.so compiled/main1.o
	gcc compiled/main1.o -L./libs -Wl,-rpath,./libs -lgcf1 -ltranslation1 -o main1

main2: libs/libgcf1.so libs/libgcf2.so libs/libtranslation1.so libs/libtranslation2.so compiled/main2.o
	gcc compiled/main2.o -L. -ldl -o main2

# Utils

clean:
	rm compiled/*
	rm libs/*
	rm *.out

dirs:
	mkdir -p compiled
	mkdir -p compiled/ofiles
	mkdir -p libs
