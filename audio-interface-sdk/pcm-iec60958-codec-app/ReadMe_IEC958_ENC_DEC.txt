# Build Steps

Makefile are made that can build application and library individually as well as combined.

1. In app: make can independentally build iec60958-enc-dec-main.c with below command:
	make all/ make app-iec60958-enc-dec/ make

That will build object file: iec60958-enc-dec-main.o and executable file : app-iec60958-enc-dec

	- make clean: remove all executables and object files

[NOTE : For this library should be built earlier otherwise it will not get build]

2. In library: similar pattern - to build library source file iec958_custom.c (header :iec958_custom.h)
	make all/ make libiec958.so/ make : create shared library: libiec958.so and objecive: iec958_custom.o 
	make clean: remove libiec958.so , iec958_custom.o 
	
3. In 8mp-spdif-iec60958 (project) directory: there is combined make file
	make all: first build library (as required) and then app
	make clean: clean both app and library executables and objectives

Manually also can be created from outer makefile
	make app: build app-iec60958-enc-dec out of iec60958-enc-dec-main.c
	make lib-iec: build libiec958.so 
	make clean-app: clean app directory's executables and objectives
	make clean-lib-iec: clean library executables

# Features of Application
	User can have major two facilities of either encode(framing in iec60958) or decode(extract pcm) of any audio file
	
	Format can be given below:
	Format: ./app-iec60958-enc-dec [encode/decode] [src_file] [dst_file] [raw/wav]

	Mentioning raw or wav is optional (wav is DEFAULT)

	NOTE: for "encoding" raw input is not allowed as wavHeader is must for iec958 framing, so raw/wav becomes irrelevent
	      Though in the case of "decoding", raw: suggests that in output file only pcm data will be extracted, there will not be wavheader in top of pcm audio
	      					while wav: make wavHeader in top of extracted pcm and proper .wav file can be extracted
 
# Verification Steps

sine tone was created from audacity software , consisting below parameters:
	channel = 2
	sample rate = 48000
	pcm bits = 16
	freq = 1000
	time = 10s

file name : pcm_sine_1000Hz_2ch_48000_16bit.wav   size: 1920044

This was played in imx8mp ab2 board using ALSA command given below :
 	aplay -Dsysdefault:CARD=imxaudioxcvr pcm_sine_1000Hz_2ch_48000_16bit.wav
 
After play SDMA buffer data (iec60958 frames) was dumped into a file named: sdma-dump-iec60958-frames.txt

sdma-dump-iec60958-frames.txt (size: 3840000) then used to test decode functionality of our application.So below commands were given to create decoded file and build application

/project/8mp-spdif-iec60957
1. make clean
2. make all
3. cd app/
4. ./app-iec60958-enc-dec decode <sdma-dump-iec60958-frames.txt> <extracted-pcm-from-dumped-frames.txt>

This extracted pcm (raw audio - without wavheader), (size : 1920000) then tested in audacity software, where it gives proper sine wav shaped visuals verifies functionality of application
Size of different files are also observed and verified as expected

original sine tone : pcm_sine_1000Hz_2ch_48000_16bit.wav  1920044
sdma dumped frames : sdma-dump-iec60958-frames.txt	  3840000
decoded audio file : extracted-pcm-from-dumped-frames.txt 1920000

