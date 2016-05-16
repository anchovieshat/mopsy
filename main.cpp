#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Currently cannot use more than one parser at a time
#include "z80.h"

#define BUFFER_SIZE 300


//   Jazzy-N64 Specific Code
int load_and_parse_n64_pif(const char *filename) {
	FILE *bios_file;
	bios_file = fopen(filename, "rb");

	if (!bios_file) {
		puts("Error opening PIF!");
		return 1;
	}

    u32 bios[BUFFER_SIZE];
	memset(bios, 0, sizeof(bios));
	fread(bios, sizeof(u32), BUFFER_SIZE, bios_file);

	puts("==========================");
	puts("|      Parsing PIF       |");
	puts("==========================");

	for (u32 i = 0; i < BUFFER_SIZE;) {
		i = parse_op(bios, i, true);
	}

	fclose(bios_file);
	return 0;
}

//   Jazzy-N64 Specific Code
int load_and_parse_n64_rom(const char *filename) {
	FILE *rom_file;
	rom_file = fopen(filename, "rb");

	if (!rom_file) {
		puts("Error opening ROM!");
		return 1;
	}

	u8 pi_reg[4];
	u32 info[5];
	u64 unknown[1];
	char name[21];
	u32 unknown2[1];
	u32 manufacturer[1];
	u16 more_info[2];
	u32 program[BUFFER_SIZE];

	memset(pi_reg, 0, sizeof(pi_reg));
	memset(info, 0, sizeof(info));
	memset(name, 0, sizeof(name));
	memset(manufacturer, 0, sizeof(manufacturer));
	memset(more_info, 0, sizeof(more_info));
	memset(program, 0, sizeof(program));

	fread(pi_reg, sizeof(u8), 4, rom_file);
	fread(info, sizeof(u32), 5, rom_file);
	fread(unknown, sizeof(u64), 1, rom_file);
	fread(name, sizeof(char), 20, rom_file);
	fread(unknown2, sizeof(u32), 1, rom_file);
	fread(manufacturer, sizeof(u32), 1, rom_file);
	fread(more_info, sizeof(u16), 2, rom_file);
	fread(program, sizeof(u32), BUFFER_SIZE, rom_file);

	//Check endianness; if pi_reg[0], pi_reg[1] is 0x80, 0x37, rom is in big endian, otherwise, swap.
	u32 big_endian = 0;
	if (pi_reg[0] < pi_reg[1]) {
		big_endian = 1;
	}

	puts("==========================");
	puts("|  Parsing ROM Header    |");
	puts("==========================");

	if (!big_endian) {
		printf("PI_BSB_DOM1_LAT_REG: 0x%x\n", pi_reg[0]);
		printf("PI_BSB_DOM1_PGS_REG: 0x%x\n", pi_reg[1]);
		printf("PI_BSB_DOM1_PWD_REG: 0x%x\n", pi_reg[2]);
		printf("PI_BSB_DOM1_PGS_REG: 0x%x\n", pi_reg[3]);

		printf("Clock Rate: %u\n", info[0]);
		printf("Program Counter: 0x%x\n", info[1]);
		printf("Release: %u\n", info[2]);
		printf("CRC1: %u\n", info[3]);
		printf("CRC2: %u\n", info[4]);

		name[20] = '\0';
		printf("Program Name: %s\n", name);

		printf("Manufacturer: 0x%x\n", manufacturer[0]);
		printf("Cartridge ID: 0x%x\n", more_info[0]);
		printf("Country Code: 0x%x\n", more_info[1]);
	} else {
		printf("PI_BSB_DOM1_LAT_REG: 0x%x\n", pi_reg[1]);
		printf("PI_BSB_DOM1_PGS_REG: 0x%x\n", pi_reg[0]);
		printf("PI_BSB_DOM1_PWD_REG: 0x%x\n", pi_reg[3]);
		printf("PI_BSB_DOM1_PGS_REG: 0x%x\n", pi_reg[2]);

		printf("Clock Rate: %u\n", swap_bytes_32(info[0]));
		printf("Program Counter: 0x%x\n", swap_bytes_32(info[1]));
		printf("Release: %u\n", swap_bytes_32(info[2]));
		printf("CRC1: %u\n", swap_bytes_32(info[3]));
		printf("CRC2: %u\n", swap_bytes_32(info[4]));

		char *swap_name = swap_string_bytes(name);
		swap_name[20] = '\0';
		printf("Program Name: %s\n", swap_name);

		printf("Manufacturer: 0x%x\n", swap_bytes_32(manufacturer[0]));
		printf("Cartridge ID: 0x%x\n", swap_bytes_16(more_info[0]));
		printf("Country Code: %c\n", swap_bytes_16(more_info[1]));
	}

	puts("==========================");
	puts("|   Parsing N64 ROM      |");
	puts("==========================");

	// if big_endian == true, swap bytes
	for (u32 i = 0; i < BUFFER_SIZE;) {
		i = parse_op(program, i, big_endian);
	}

	fclose(rom_file);
	return 0;
}

// Handmade Gameboy Emulator Specific Code
int load_and_parse_gb_boot(const char *filename) {
	FILE *rom_file;
	rom_file = fopen(filename, "rb");

	if (!rom_file) {
		puts("Error opening ROM!");
		return 1;
	}

    u8 rom[BUFFER_SIZE];
	memset(rom, 0, sizeof(rom));
	fread(rom, sizeof(u8), BUFFER_SIZE, rom_file);

	puts("==========================");
	puts("|   Parsing GB ROM       |");
	puts("==========================");

	for (u32 i = 0; i < BUFFER_SIZE;) {
		i = parse_op(rom, i, false);
	}

	fclose(rom_file);
	return 1;
}

int main() {
	load_and_parse_gb_boot("gb/gb_boot.bin");
	//load_and_parse_n64_pif("n64/pifdata.bin");
	//load_and_parse_n64_rom("n64/smario.n64");

	return 0;
}
