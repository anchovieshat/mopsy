#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define u8 unsigned char
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t
#define bool u32

#define BUFFER_SIZE 500

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

typedef struct Instruction {
	u8 op;
	u8 rs;
	u8 rt;
	u8 rd;
	u8 sa;
	u8 funct;
	u16 code;
	u16 immediate;
	u32 call_offset;
	u32 target;
} Instruction;

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
	Mult,
	Div,
	Addu,
	Addi,
	Addiu,
	Daddu,
	Multu,
	Dmultu,
	Dsub,
	Subu,
	Slti,
	Sltiu,
	Slt,
	Sltu,
	Sdc1,
	Lwc1,
	Ldc1,
	Sc,
	Scd,
	And,
	Andi,
	Or,
	Ori,
	Nor,
	Xori,
	Xor,
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
	Lld,
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
	Srl,
	Srav,
	Dsll,
	Dsrl,
	Dsra32,
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
	Tge,
	Tgeu,
	Tltu,
	Teq,
	Tne,
	Nop,
	InvalidOp,
} Opcode;

typedef enum Type {
	RType,
	JType,
	IType,
	SType,
	TType,
	CType,
	NopType,
	InvalidType,
} Type;

Opcode op_kind(u8 op) {
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
		case 0x18: {
			return Daddi;
		} break;
		case 0x19: {
			return Daddiu;
		} break;
		case 0x1A: {
			return Ldl;
		} break;
		case 0x1B: {
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
		case 0x31: {
			return Lwc1;
		} break;
		case 0x34: {
			return Lld;
		} break;
		case 0x35: {
			return Ldc1;
		} break;
		case 0x38: {
			return Sc;
		} break;
		case 0x3C: {
			return Scd;
		} break;
		case 0x3D: {
			return Sdc1;
		} break;
		case 0x3F: {
			return Sd;
		} break;
		default: {
        	return InvalidOp;
		}
	}
	return InvalidOp;
}

const char *kind_string(Opcode op) {
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
		case Mult: {
			return "Mult";
		} break;
		case Div: {
			return "Div";
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
		case Multu: {
			return "Multu";
		} break;
		case Dmultu: {
			return "Dmultu";
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
		case Scd: {
			return "Scd";
		} break;
		case Sdc1: {
			return "Sdc1";
		} break;
		case Lwc1: {
			return "Lwc1";
		} break;
		case Ldc1: {
			return "Ldc1";
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
		case Lld: {
			return "Lld";
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
		case Lhu: {
			return "Lhu";
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
		case Srl: {
			return "Srl";
		} break;
		case Srav: {
			return "Srav";
		} break;
		case Dsll: {
			return "Dsll";
		} break;
		case Dsrl: {
			return "Dsrl";
		} break;
		case Dsra32: {
			return "Dsra32";
		} break;
		case Sb: {
			return "Sb";
		} break;
		case Sh: {
			return "Sh";
		} break;
		case Swl: {
			return "Swl";
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
		case Tge: {
			return "Tgeu";
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
			return "InvalidOp";
		}
	}
}


Type op_type(Opcode op) {
	if (op == InvalidOp) {
    	return InvalidType;
	}
    if (op == Nop) {
		return NopType;
	}

	if (op == Add || op == Addu || op == And || op == Div || op == Divu || op == Jr ||
		op == Mfhi || op == Mflo || op == Mfc0 || op == Mult || op == Multu || op == Nor ||
		op == Xor || op == Or || op == Slt || op == Sltu || op == Sll || op == Srl ||
		op == Sub || op == Subu || op == Jalr || op == Dsrlv || op == Dsll || op == Daddu ||
		op == Dsrl || op == Dsub || op == Mthi || op == Mtc0 || op == Dsra32) {
		return RType;
	} else if (op == Jump || op == Jal) {
		return JType;
	} else if (op == Beq || op == Bne || op == Lbu || op == Lhu || op == Lui ||
			   op == Lw || op == Ori || op == Sb || op == Sh || op == Slti ||
			   op == Sltiu || op == Sw || op == Sd || op == Sdl || op == Addi ||
			   op == Lb || op == Xori || op == Bgtz || op == Andi || op == Swr ||
			   op == Bnel || op == Bgez || op == Blez || op == Ll || op == Daddiu ||
			   op == Daddi || op == Ldl || op == Addiu || op == Cache || op == Sdr ||
			   op == Lwl || op == Ldr || op == Bgtzl || op == Dmultu || op == Sdc1 ||
			   op == Swl || op == Scd || op == Ldc1 || op == Lld || op == Sc ||
			   op == Lwc1) {
		return IType;
	} else if (op == Syscall) {
		return SType;
	} else if (op == Teq || op == Tltu || op == Tne || op == Tgeu || op == Tge) {
		return TType;
	} else if (op == Eret) {
		return CType;
	} else {
		return InvalidType;
	}
}

Opcode special_lookup(Opcode op, Instruction inst) {
	Opcode op_k = op;
	if (op_k == Special) {
		switch (inst.funct) {
			case 0: {
				if (!inst.rs && !inst.rt && !inst.rd && !inst.sa) {
					op_k = Nop;
				} else {
					op_k = Sll;
				}
			} break;
			case 2: {
				op_k = Srl;
			} break;
			case 8: {
				op_k = Jr;
			} break;
			case 9: {
				op_k = Jalr;
			} break;
			case 12: {
				op_k = Syscall;
			} break;
			case 16: {
				op_k = Mfhi;
			} break;
			case 17: {
				op_k = Mthi;
			} break;
			case 18: {
				op_k = Mflo;
			} break;
			case 22: {
				op_k = Dsrlv;
			} break;
			case 24: {
				op_k = Mult;
			} break;
			case 27: {
				op_k = Divu;
			} break;
			case 29: {
				op_k = Dmultu;
			} break;
			case 32: {
				op_k = Add;
			} break;
			case 34: {
				op_k = Sub;
			} break;
			case 35: {
				op_k = Subu;
			} break;
			case 36: {
				op_k = And;
			} break;
			case 37: {
				op_k = Or;
			} break;
			case 42: {
				op_k = Slt;
			} break;
			case 43: {
				op_k = Sltu;
			} break;
			case 45: {
				op_k = Daddu;
			} break;
			case 46: {
				op_k = Dsub;
			} break;
			case 48: {
				op_k = Tge;
			} break;
			case 49: {
				op_k = Tgeu;
			} break;
			case 51: {
				op_k = Tltu;
			} break;
			case 52: {
				op_k = Teq;
			} break;
			case 54: {
				op_k = Tne;
			} break;
			case 56: {
				op_k = Dsll;
			} break;
			case 58: {
				op_k = Dsrl;
			} break;
			case 63: {
				op_k = Dsra32;
			} break;
		}
	}
	return op_k;
}

Opcode control_lookup(Opcode op, Instruction inst) {
	Opcode op_k = op;

	if (op_k == Control) {
		if (inst.funct == 0) {
			switch (inst.rs) {
				case 0: {
					op_k = Mfc0;
				} break;
				case 4: {
					op_k = Mtc0;
				} break;
			}
		} else {
			switch (inst.funct) {
				case 1: {
					op_k = Tlbr;
				} break;
				case 2: {
					op_k = Tlbwi;
				} break;
				case 6: {
					op_k = Tlbwr;
				} break;
				case 8: {
					op_k = Tlbp;
				} break;
				case 24: {
					op_k = Eret;
				} break;
			}
		}
	}
	return op_k;
}

const char *type_string(Type t) {
	switch (t) {
		case RType: {
			return "RType";
		} break;
		case JType: {
			return "JType";
		} break;
		case IType: {
			return "IType";
		} break;
		case SType: {
			return "SType";
		} break;
		case TType: {
			return "TType";
		} break;
		case CType: {
			return "CType";
		} break;
		case NopType: {
			return "NopType";
		} break;
		default: {
			return "Invalid Type";
		}
	}
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

	fread(pi_reg, sizeof(u8), 4, asm_file);
	fread(info, sizeof(u32), 5, asm_file);
	fread(unknown, sizeof(u64), 1, asm_file);
	fread(name, sizeof(char), 20, asm_file);
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

	fclose(asm_file);
    return 0;
}
