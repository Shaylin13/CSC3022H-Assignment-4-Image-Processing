CC=g++

imageops: main.o Image.o
	$(CC) main.o Image.o -o imageops
	
main.o: main.cpp
	$(CC) -c main.cpp

Image.o: Image.cpp Image.h 
	$(CC) -c Image.cpp

add: imageops
	./imageops -a image1.pgm image2.pgm output.pgm
	
subtract: imageops
	./imageops -s image1.pgm image2.pgm output.pgm
	
mask: imageops
	./imageops -I image1.pgm image2.pgm output.pgm
	
threshold: imageops
	./imageops -t image1.pgm 50 output.pgm
	
invert: imageops
	./imageops -i image1.pgm output.pgm
	
clean:
	rm -f *.o imageops

	

