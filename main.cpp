#include <stdio.h>
#include <string.h>

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
#define bool u32

#define BUFFER_SIZE 50

// TODO: Use BSWAP ASM instruction for this!
u32 swap_bytes(u32 val) {
	return (val >> 24) | ((val << 8) & 0xFF0000) | ((val >> 8) & 0xFF00) | (val << 24);
}

typedef enum Opcode {
	Special,
	Bgez,
	Jump,
	Jal,
    Beq,
	Bne,
	Blez,
	Bgtz,
	Addi,
	Addiu,
	Slti,
	Sltiu,
	Andi,
	Ori,
	Xori,
	Lui,
	Eret,
	Beql,
	Bnel,
	Blezl,
	Bgtzl,
	Daddi,
	Daddiu,
	Ldl,
	Ldr,
	Lb,
	Lh,
	Lwl,
	Lw,
	Lbu,
	Lhu,
	Lwr,
	Lwu,
	Sb,
	Sh,
	Swl,
	Sw,
	Sdl,
	Sdr,
	Swr,
	Ll,
	Unknown,
} Opcode;

Opcode op_type(u8 op) {
	switch (op) {
		case 0x0: {
			return Special;
		} break;
		case 0x1: {
			return Bgez;
		} break;
		case 0x2: {
			return Jump;
		} break;
		case 0x3: {
			return Jal;
		} break;
		case 0x4: {
			return Beq;
		} break;
		case 0x5: {
			return Bne;
		} break;
		case 0x6: {
			return Blez;
		} break;
		case 0x7: {
			return Bgtz;
		} break;
		case 0x8: {
			return Addi;
		} break;
		case 0x9: {
			return Addiu;
		} break;
		case 0xA: {
			return Slti;
		} break;
		case 0xB: {
			return Sltiu;
		} break;
		case 0xC: {
			return Andi;
		} break;
		case 0xD: {
			return Ori;
		} break;
		case 0xE: {
			return Xori;
		} break;
		case 0xF: {
			return Lui;
		} break;
		case 0x10: {
			return Eret;
		} break;
		case 0x11: {
			return Beql;
		} break;
		case 0x12: {
			return Bnel;
		} break;
		case 0x13: {
			return Blezl;
		} break;
		case 0x14: {
			return Bgtzl;
		} break;
		case 0x15: {
			return Daddi;
		} break;
		case 0x16: {
			return Daddiu;
		} break;
		case 0x17: {
			return Ldl;
		} break;
		case 0x18: {
			return Ldr;
		} break;
		case 0x20: {
			return Lb;
		} break;
		case 0x21: {
			return Lh;
		} break;
		case 0x22: {
			return Lwl;
		} break;
		case 0x23: {
			return Lw;
		} break;
		case 0x24: {
			return Lbu;
		} break;
		case 0x25: {
			return Lhu;
		} break;
		case 0x26: {
			return Lwr;
		} break;
		case 0x27: {
			return Lwu;
		} break;
		case 0x28: {
			return Sb;
		} break;
		case 0x29: {
			return Sh;
		} break;
		case 0x2A: {
			return Swl;
		} break;
		case 0x2B: {
			return Sw;
		} break;
		case 0x2C: {
			return Sdl;
		} break;
		case 0x2D: {
			return Sdr;
		} break;
		case 0x2E: {
			return Swr;
		} break;
		case 0x30: {
			return Ll;
		} break;
		default: {
        	return Unknown;
		}
	}
	return Unknown;
}

const char *type_string(Opcode op) {
	switch (op) {
		case Special: {
			return "special";
		} break;
		case Bgez: {
			return "Bgez";
		} break;
		case Jump: {
			return "Jump";
		} break;
		case Jal: {
			return "Jal";
		} break;
		case Beq: {
			return "Beq";
		} break;
		case Bne: {
			return "Bne";
		} break;
		case Blez: {
			return "Blez";
		} break;
		case Bgtz: {
			return "Bgtz";
		} break;
		case Addi: {
			return "Addi";
		} break;
		case Addiu: {
			return "Addiu";
		} break;
		case Slti: {
			return "Slti";
		} break;
		case Sltiu: {
			return "Sltiu";
		} break;
		case Andi: {
			return "Andi";
		} break;
		case Ori: {
			return "Ori";
		} break;
		case Xori: {
			return "Xori";
		} break;
		case Lui: {
			return "Lui";
		} break;
		case Eret: {
			return "Eret";
		} break;
		case Beql: {
			return "Beql";
		} break;
		case Bnel: {
			return "Bnel";
		} break;
		case Blezl: {
			return "Blezl";
		} break;
		case Bgtzl: {
			return "Bgtzl";
		} break;
		case Daddi: {
			return "Daddi";
		} break;
		case Daddiu: {
			return "Daddiu";
		} break;
		case Ldl: {
			return "Ldl";
		} break;
		case Ldr: {
			return "Ldr";
		} break;
		case Lb: {
			return "Lb";
		} break;
		case Lh: {
			return "Lh";
		} break;
		case Lwl: {
			return "Lwl";
		} break;
		case Lbu: {
			return "Lbu";
		} break;
		case Lwr: {
			return "Lwr";
		} break;
		case Lwu: {
			return "Lwu";
		} break;
		case Sb: {
			return "Sb";
		} break;
		case Sh: {
			return "Sh";
		} break;
		case Sdl: {
			return "Sdl";
		} break;
		case Sdr: {
			return "Sdr";
		} break;
		case Swr: {
			return "Swr";
		} break;
		case Ll: {
			return "Ll";
		} break;
		default: {
			return "unknown";
		}
	}
	return "unknown";
}

int main() {
    FILE *asm_file;
    asm_file = fopen("test.bin", "rb");

	if (!asm_file) {
		puts("Error opening file!");
		return 1;
	}

	u32 buffer[BUFFER_SIZE];
	memset(buffer, 0, sizeof(buffer));

	fread(buffer, sizeof(u32), BUFFER_SIZE, asm_file);

#if 0
	puts("byteswapped");
	for (u32 i = 0; i < BUFFER_SIZE; i++) {
		u32 instruction = swap_bytes(buffer[i]);
#else
	puts("not byteswapped");
	for (u32 i = 0; i < BUFFER_SIZE; i++) {
		u32 instruction = buffer[i];
#endif
		u8 op = instruction >> 26;
		u8 rs = (instruction << 6) >> 27;
		u8 rt = (instruction << (6 + 5)) >> 27;
		u8 rd = (instruction << (6 + (5 * 2))) >> 27;
		u8 sa = (instruction << (6 + (5 * 3))) >> 27;
		u8 funct = (instruction << 26) >> 26;
		u16 immediate = (instruction << 16) >> 16;
		u32 target = instruction << 6;
		Opcode op_t = op_type(op);
		if (op_t != Unknown) {
			printf("read: 0x%x, op_type: %s, source reg: %d, target reg: %d, immediate: 0x%x, target: 0x%x, dest reg: %d, shift amount: %d, function field: %d\n", instruction, type_string(op_t), rs, rt, immediate, target, rd, sa, funct);
		} else {
			printf("read: %x, op: %x\n", instruction, op);
		}
	}

	fclose(asm_file);
    return 0;
}
