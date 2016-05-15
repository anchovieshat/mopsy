#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mopsy.h"

#define BUFFER_SIZE 650

u16 swap_bytes_16(u16 val) {
	return __builtin_bswap16(val);
}

u32 swap_bytes_32(u32 val) {
	return __builtin_bswap32(val);
}

u64 swap_bytes_64(u64 val) {
	return __builtin_bswap64(val);
}

char *swap_string_bytes(char s[]) {
	char *ret = (char *)malloc(strlen(s));

	for (u32 i = 0; i < strlen(s); i += 2) {
    	ret[i] = s[i+1];
    	ret[i+1] = s[i];
	}
	return ret;
}

void parse_op(u32 instruction) {
	Instruction inst;
	inst.op = instruction >> 26;
	inst.rs = (instruction << 6) >> 27;
	inst.rt = (instruction << (6 + 5)) >> 27;
	inst.rd = (instruction << (6 + (5 * 2))) >> 27;
	inst.sa = (instruction << (6 + (5 * 3))) >> 27;
	inst.code = (instruction << (6 + (5 * 2))) >> 22;
	inst.funct = (instruction << 26) >> 26;
	inst.immediate = (instruction << 16) >> 16;
	inst.call_offset = (instruction << 6) >> 12;
	inst.target = instruction << 6;

	Opcode op_k = op_kind(inst.op);
	op_k = special_lookup(op_k, inst);
	op_k = control_lookup(op_k, inst);
	const char *op_k_string = kind_string(op_k);
	Type op_t = op_type(op_k);
	//const char *op_t_string = type_string(op_t);

	if (op_k == InvalidOp || op_t == InvalidType || op_k == Special || op_k == Control) {
		printf("[ Error ] 0x%x\n", instruction);
	} else {
		if (op_k == Nop) {
			printf("[ %s ]\n", op_k_string);
		}  else if (op_t == RType) {
			printf("[ %s ] R%u<<%u, R%u, R%u\n", op_k_string, inst.rs, inst.sa, inst.rt, inst.rd);
	 //   	printf("0x%x\n", instruction);
		} else if (op_t == IType) {
			printf("[ %s ] R%u, R%u, %u\n", op_k_string, inst.rs, inst.rd, inst.immediate);
		} else if (op_t == JType) {
			printf("[ %s ] 0x%x\n", op_k_string, inst.target);
		} else if (op_t == TType) {
			printf("[ %s ] R%u, R%u, %u\n", op_k_string, inst.rs, inst.rt, inst.code);
		} else if (op_t == SType) {
			printf("[ %s ] 0x%x\n", op_k_string, inst.call_offset);
		} else if (op_t == CType) {
			printf("[ %s ]\n", op_k_string);
		}
	}
}

int load_and_parse_pif(const char *filename) {
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

	for (u32 i = 0; i < BUFFER_SIZE; i++) {
		u32 instruction = swap_bytes_32(bios[i]);
		parse_op(instruction);
	}

	fclose(bios_file);
	return 0;
}

int load_and_parse_rom(const char *filename) {
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
	puts("|      Parsing ROM       |");
	puts("==========================");
	if (!big_endian) {
		for (u32 i = 0; i < BUFFER_SIZE; i++) {
			u32 instruction = program[i];
			parse_op(instruction);
		}
	} else {
		puts("swapping bytes");
		for (u32 i = 0; i < BUFFER_SIZE; i++) {
			u32 instruction = swap_bytes_32(program[i]);
			parse_op(instruction);
		}
	}

	fclose(rom_file);
	return 0;
}

int main() {
	load_and_parse_pif("pifdata.bin");
	load_and_parse_rom("smario.n64");
    return 0;
}
