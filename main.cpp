#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
#define u64 unsigned long
#define bool u32

#define BUFFER_SIZE 240

// TODO: Use BSWAP ASM instruction for this!
u32 swap_bytes(u32 val) {
	return (val >> 24) | ((val << 8) & 0xFF0000) | ((val >> 8) & 0xFF00) | (val << 24);
}

char *swap_string_bytes(char s[]) {
	char *ret = (char *)malloc(strlen(s));

	for (u32 i = 0; i < strlen(s); i += 2) {
    	ret[i] = s[i+1];
    	ret[i+1] = s[i];
	}
	return ret;
}

typedef enum Opcode {
	Special,
	Bgez,
	Jump,
	Jr,
	Jal,
	Jalr,
    Beq,
	Bne,
	Blez,
	Bgtz,
	Add,
	Sub,
	Addi,
	Addiu,
	Daddu,
	Dsub,
	Subu,
	Slti,
	Sltiu,
	Slt,
	Sltu,
	And,
	Andi,
	Or,
	Ori,
	Xori,
	Lui,
	Control,
	Beql,
	Bnel,
	Blezl,
	Bgtzl,
	Daddi,
	Daddiu,
	Divu,
	Ldl,
	Ldr,
	Lb,
	Lh,
	Lwl,
	Lw,
	Sd,
	Lbu,
	Lhu,
	Lwr,
	Lwu,
	Sll,
	Dsll,
	Dsrl,
	Sb,
	Sh,
	Swl,
	Sw,
	Sdl,
	Sdr,
	Swr,
	Dsrlv,
	Ll,
	Mfc0,
	Mtc0,
	Mthi,
	Mflo,
	Mfhi,
	Tlbr,
	Tlbwi,
	Tlbwr,
	Tlbp,
	Eret,
	Cache,
	Syscall,
	Tgeu,
	Tltu,
	Teq,
	Tne,
	Nop,
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
			return Control;
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
		case 0x2F: {
			return Cache;
		} break;
		case 0x30: {
			return Ll;
		} break;
		case 0x3F: {
			return Sd;
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
		case Jr: {
			return "Jr";
		} break;
		case Jal: {
			return "Jal";
		} break;
		case Jalr: {
			return "Jalr";
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
		case Add: {
			return "Add";
		} break;
		case Sub: {
			return "Sub";
		} break;
		case Addi: {
			return "Addi";
		} break;
		case Addiu: {
			return "Addiu";
		} break;
		case Daddu: {
			return "Daddu";
		} break;
		case Dsub: {
			return "Dsub";
		} break;
		case Subu: {
			return "Subu";
		} break;
		case Slti: {
			return "Slti";
		} break;
		case Slt: {
			return "Slt";
		} break;
		case Sltu: {
			return "Sltu";
		} break;
		case Sltiu: {
			return "Sltiu";
		} break;
		case And: {
			return "And";
		} break;
		case Andi: {
			return "Andi";
		} break;
		case Or: {
			return "Or";
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
		case Control: {
			return "Control";
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
		case Divu: {
			return "Divu";
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
		case Lw: {
			return "Lw";
		} break;
		case Sd: {
			return "Sd";
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
		case Sll: {
			return "Sll";
		} break;
		case Dsll: {
			return "Dsll";
		} break;
		case Dsrl: {
			return "Dsrl";
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
		case Sw: {
			return "Sw";
		} break;
		case Swr: {
			return "Swr";
		} break;
		case Dsrlv: {
			return "Dsrlv";
		} break;
		case Ll: {
			return "Ll";
		} break;
		case Mfc0: {
			return "Mfc0";
		} break;
		case Mtc0: {
			return "Mtc0";
		} break;
		case Tlbr: {
			return "Tlbr";
		} break;
		case Tlbwi: {
			return "Tlbwi";
		} break;
		case Tlbwr: {
			return "Tlbwr";
		} break;
		case Tlbp: {
			return "Tlbp";
		} break;
		case Eret: {
			return "Eret";
		} break;
		case Cache: {
			return "Cache";
		} break;
		case Syscall: {
			return "Syscall";
		} break;
		case Tgeu: {
			return "Tgeu";
		} break;
		case Tltu: {
			return "Tltu";
		} break;
		case Teq: {
			return "Teq";
		} break;
		case Tne: {
			return "Tne";
		} break;
		case Mthi: {
			return "Mthi";
		} break;
		case Mfhi: {
			return "Mfhi";
		} break;
		case Mflo: {
			return "Mflo";
		} break;
		case Nop: {
			return "Nop";
		} break;
		default: {
			return "Unknown";
		}
	}
	return "Unknown";
}

void parse_op(u32 instruction) {
	u8 op = instruction >> 26;
	u8 rs = (instruction << 6) >> 27;
	u8 rt = (instruction << (6 + 5)) >> 27;
	u8 rd = (instruction << (6 + (5 * 2))) >> 27;
	u8 sa = (instruction << (6 + (5 * 3))) >> 27;
	u8 funct = (instruction << 26) >> 26;
	u16 immediate = (instruction << 16) >> 16;
	u32 target = instruction << 6;

	Opcode op_t = op_type(op);
	if (op_t == Special) {
		switch (funct) {
			case 0: {
				if (!rs && !rt && !rd && !sa) {
					op_t = Nop;
				} else {
					op_t = Sll;
				}
			} break;
			case 8: {
				op_t = Jr;
			} break;
			case 9: {
				op_t = Jalr;
			} break;
			case 12: {
				op_t = Syscall;
			} break;
			case 16: {
				op_t = Mfhi;
			} break;
			case 17: {
				op_t = Mthi;
			} break;
			case 18: {
				op_t = Mflo;
			} break;
			case 22: {
				op_t = Dsrlv;
			} break;
			case 27: {
				op_t = Divu;
			} break;
			case 32: {
				op_t = Add;
			} break;
			case 34: {
				op_t = Sub;
			} break;
			case 35: {
				op_t = Subu;
			} break;
			case 36: {
				op_t = And;
			} break;
			case 37: {
				op_t = Or;
			} break;
			case 42: {
				op_t = Slt;
			} break;
			case 43: {
				op_t = Sltu;
			} break;
			case 45: {
				op_t = Daddu;
			} break;
			case 46: {
				op_t = Dsub;
			} break;
			case 49: {
				op_t = Tgeu;
			} break;
			case 51: {
				op_t = Tltu;
			} break;
			case 52: {
				op_t = Teq;
			} break;
			case 54: {
				op_t = Tne;
			} break;
			case 56: {
				op_t = Dsll;
			} break;
			case 58: {
				op_t = Dsrl;
			} break;
		}
	} else if (op_t == Control) {
		if (funct == 0) {
			switch (rs) {
				case 0: {
					op_t = Mfc0;
				} break;
				case 4: {
					op_t = Mtc0;
				} break;
			}
		} else {
			switch (funct) {
				case 1: {
					op_t = Tlbr;
				} break;
				case 2: {
					op_t = Tlbwi;
				} break;
				case 6: {
					op_t = Tlbwr;
				} break;
				case 8: {
					op_t = Tlbp;
				} break;
				case 24: {
					op_t = Eret;
				} break;
			}
		}
	}

	const char *op_string = type_string(op_t);
	if (op_t == Nop) {
#ifdef DEBUG
		printf("read: 0x%x, op_type: %s\n", instruction, op_string);
#else
		printf("%s\n", op_string);
#endif
	} else if (op_t == Special) {
		printf("read: 0x%x, op_type: %s, source reg: %d, target reg: %d, immediate: 0x%x, target: 0x%x, dest reg: %d, shift amount: %d, function field: %d\n", instruction, op_string, rs, rt, immediate, target, rd, sa, funct);
	} else if (op_t != Unknown && strncmp(op_string, "Unknown", 7) != 0) {
#ifdef DEBUG
		printf("read: 0x%x, op_type: %s, source reg: %d, target reg: %d, immediate: 0x%x, target: 0x%x, dest reg: %d, shift amount: %d\n", instruction, op_string, rs, rt, immediate, target, rd, sa);
#else
		printf("%s\n", op_string);
#endif
	} else {
		printf("read: %x, op: %x\n", instruction, op);
	}
}

int main() {
    FILE *asm_file;
    asm_file = fopen("smario.n64", "rb");

	if (!asm_file) {
		puts("Error opening file!");
		return 1;
	}

	u8 pi_reg[4];
	u32 info[5];
	u64 unknown[1];
	char name[41];
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

	fread(pi_reg, sizeof(u8), 4, asm_file);
	fread(info, sizeof(u32), 5, asm_file);
	fread(unknown, sizeof(u64), 1, asm_file);
	fread(name, sizeof(char), 40, asm_file);
	fread(unknown2, sizeof(u32), 1, asm_file);
	fread(manufacturer, sizeof(u32), 1, asm_file);
	fread(more_info, sizeof(u16), 2, asm_file);

	fread(program, sizeof(u32), BUFFER_SIZE, asm_file);

	//Check endianness; if pi_reg[0], pi_reg[1] is 0x80, 0x37, rom is in big endian, otherwise, swap.
	u32 big_endian = 0;
	if (pi_reg[0] < pi_reg[1]) {
		big_endian = 1;
	}

	if (!big_endian) {
		printf("PI_BSB_DOM1_LAT_REG: 0x%x\n", pi_reg[0]);
		printf("PI_BSB_DOM1_PGS_REG: 0x%x\n", pi_reg[1]);
		printf("PI_BSB_DOM1_PWD_REG: 0x%x\n", pi_reg[2]);
		printf("PI_BSB_DOM1_PGS_REG: 0x%x\n", pi_reg[3]);

		printf("Clock Rate: %d\n", info[0]);
		printf("Program Counter: %d\n", info[1]);
		printf("Release: %d\n", info[2]);
		printf("CRC1: %d\n", info[3]);
		printf("CRC2: %d\n", info[4]);

		name[40] = '\0';
		printf("Program Name: %s\n", name);

		printf("Manufacturer: 0x%x\n", manufacturer[0]);
		printf("Cartridge ID: 0x%x\n", more_info[0]);
		printf("Country Code: 0x%x\n", more_info[1]);
	} else {
		printf("PI_BSB_DOM1_LAT_REG: 0x%x\n", pi_reg[1]);
		printf("PI_BSB_DOM1_PGS_REG: 0x%x\n", pi_reg[0]);
		printf("PI_BSB_DOM1_PWD_REG: 0x%x\n", pi_reg[3]);
		printf("PI_BSB_DOM1_PGS_REG: 0x%x\n", pi_reg[2]);

		printf("Clock Rate: %d\n", swap_bytes(info[0]));
		printf("Program Counter: %d\n", swap_bytes(info[1]));
		printf("Release: %d\n", swap_bytes(info[2]));
		printf("CRC1: %d\n", swap_bytes(info[3]));
		printf("CRC2: %d\n", swap_bytes(info[4]));

		char *swap_name = swap_string_bytes(name);
		swap_name[40] = '\0';
		printf("Program Name: %s\n", swap_name);

		printf("Manufacturer: 0x%x\n", swap_bytes(manufacturer[0]));
		printf("Cartridge ID: 0x%x\n", swap_bytes(more_info[0]));
		printf("Country Code: 0x%x\n", swap_bytes(more_info[1]));
	}

	if (!big_endian) {
		puts("swapping bytes");
		for (u32 i = 0; i < BUFFER_SIZE; i++) {
			u32 instruction = swap_bytes(program[i]);
			parse_op(instruction);
		}
	} else {
		for (u32 i = 0; i < BUFFER_SIZE; i++) {
			u32 instruction = program[i];
			parse_op(instruction);
		}
	}

	fclose(asm_file);
    return 0;
}
