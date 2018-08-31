PDYSHA009

to compile go to the directory PDYSHA009_A4 (in zip folder) in the terminal and type make

to run the different commands type:
./imageops -<command character> <image1 name> <image2 name>(optional depending on process) <threshold value>(depending on process> <output name>

the following commands are in the make file for convinience:

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
	
these can be used to test each of the different processes on the test images in the folder.
to run these type:
make add etc to run the add process
