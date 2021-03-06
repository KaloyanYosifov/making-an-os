FILES = ./build/kernel.asm.o ./build/kernel.o ./build/display.o ./build/idt/idt.asm.o ./build/idt/idt.o ./build/memory/memory.o ./build/string/string.o ./build/io/io.asm.o ./build/io/io.o
INCLUDE = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-functions -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc
COMPILER = i686-elf-gcc

all: ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin

./bin/kernel.bin: $(FILES)
	i686-elf-ld -g -relocatable $(FILES) -o ./build/kernelfull.o -Map=./build/kernelfull.map
	$(COMPILER) $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o

./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin $^ -o $@

./build/kernel.asm.o: ./src/kernel.asm
	nasm -f elf -g $^ -o $@

./build/kernel.o: ./src/kernel.c
	$(COMPILER) $(INCLUDES) $(FLAGS) -std=gnu99 -c $^ -o $@

./build/display.o: ./src/display.c
	$(COMPILER) $(INCLUDES) $(FLAGS) -std=gnu99 -c $^ -o $@

./build/idt/idt.asm.o: ./src/idt/idt.asm
	mkdir -p ./build/idt
	nasm -f elf -g $^ -o $@

./build/idt/idt.o: ./src/idt/idt.c
	mkdir -p ./build/idt
	$(COMPILER) $(INCLUDES) -I./src/idt $(FLAGS) -std=gnu99 -c $^ -o $@

./build/memory/memory.o: ./src/memory/memory.c
	mkdir -p ./build/memory
	$(COMPILER) $(INCLUDES) -I./src/memory $(FLAGS) -std=gnu99 -c $^ -o $@

./build/string/string.o: ./src/string/string.c
	mkdir -p ./build/string
	$(COMPILER) $(INCLUDES) -I./src/string $(FLAGS) -std=gnu99 -c $^ -o $@

./build/io/io.asm.o: ./src/io/io.asm
	mkdir -p ./build/io
	nasm -f elf -g $^ -o $@

./build/io/io.o: ./src/io/io.c
	mkdir -p ./build/io
	$(COMPILER) $(INCLUDES) -I./src/io $(FLAGS) -std=gnu99 -c $^ -o $@

clean:
	rm -f ./bin/*.bin
	rm -f ./build/*.{o,s,map}
	rm -f ./bin/**/*.bin
	rm -f ./build/**/*.{o,s,map}
