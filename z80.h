#ifndef Z80_H
#define Z80_H

#include "stdio.h"
#include "platform.h"

typedef enum Opcode {
	Nop,
	Ld,
	Add,
	Sub,
	Sbc,
	And,
	Xor,
	Or,
	Cp,
	Inc,
	Dec,
	Stop,
	Jr,
	Ldi,
	Ldd,
	Daa,
	Cpl,
	Scf,
	Ccf,
	Halt,
	Alu,
	Pop,
	Push,
	Rst,
	Ret,
	Reti,
	Jp,
	Call,
	Di,
	Ei,
	Rd,
	Sd,
	Swap,
	Srl,
	Bit,
	Res,
	Set,
	InvalidOp,
} Opcode;

typedef enum Type {
	A,
	B,
	C,
	D,
	E,
	H,
    L,
	Bc,
	De,
	Hl,
	Sp,
	Data_8,
	Data_16,
	None,
} Type;

char *type_string(Type t) {
	switch (t) {
    	case A: {
			return "A";
		} break;
    	case B: {
			return "B";
		} break;
    	case C: {
			return "C";
		} break;
    	case D: {
			return "D";
		} break;
    	case E: {
			return "E";
		} break;
    	case H: {
			return "H";
		} break;
    	case L: {
			return "L";
		} break;
    	case Bc: {
			return "Bc";
		} break;
    	case De: {
			return "De";
		} break;
    	case Hl: {
			return "Hl";
		} break;
    	case Sp: {
			return "Sp";
		} break;
    	case Data_8: {
			return "Data_8";
		} break;
    	case Data_16: {
			return "Data_16";
		} break;
		default: {
			return "None";
		}
	}
}

const char *kind_string(Opcode op) {
	switch (op) {
		case Nop: {
			return "Nop";
		} break;
		case Ld: {
			return "Ld";
		} break;
		case Add: {
			return "Add";
		} break;
		case Sub: {
			return "Sub";
		} break;
		case Sbc: {
			return "Sbc";
		} break;
		case And: {
			return "And";
		} break;
		case Xor: {
			return "Xor";
		} break;
		case Or: {
			return "Or";
		} break;
		case Cp: {
			return "Cp";
		} break;
		case Inc: {
			return "Inc";
		} break;
		case Dec: {
			return "Dec";
		} break;
		case Stop: {
			return "Stop";
		} break;
		case Jr: {
			return "Jr";
		} break;
		case Ldi: {
			return "Ldi";
		} break;
		case Ldd: {
			return "Ldi";
		} break;
		case Daa: {
			return "Daa";
		} break;
		case Cpl: {
			return "Cpl";
		} break;
		case Scf: {
			return "Scf";
		} break;
		case Ccf: {
			return "Ccf";
		} break;
		case Halt: {
			return "Halt";
		} break;
		case Alu: {
			return "Alu";
		} break;
		case Pop: {
			return "Pop";
		} break;
		case Push: {
			return "Push";
		} break;
		case Rst: {
			return "Rst";
		} break;
		case Ret: {
			return "Ret";
		} break;
		case Reti: {
			return "Reti";
		} break;
		case Jp: {
			return "Jp";
		} break;
		case Call: {
			return "Call";
		} break;
		case Di: {
			return "Di";
		} break;
		case Ei: {
			return "Ei";
		} break;
		case Rd: {
			return "Rd";
		} break;
		case Sd: {
			return "Sd";
		} break;
		case Swap: {
			return "Swap";
		} break;
		case Srl: {
			return "Srl";
		} break;
		case Bit: {
			return "Bit";
		} break;
		case Res: {
			return "Res";
		} break;
		case Set: {
			return "Set";
		} break;
		default: {
			return "InvalidOp";
		}
	}
}

// swapped is unused in the z80, exists for function compatibility with mips
u32 parse_op(void *rom, u32 idx, bool swapped) {
	u8 *local_rom = (u8 *)rom;
	u8 op = local_rom[idx];
	Type val1 = None;
	Type val2 = None;
	u32 inst = 0;

	Opcode op_k = InvalidOp;

	switch (op) {
		case 0x0: {
			op_k = Nop;
		} break;
		case 0x10: {
			op_k = Stop;
		} break;
		case 0x27: {
			op_k = Daa;
		} break;
		case 0x2F: {
			op_k = Cpl;
		} break;
		case 0x37: {
			op_k = Scf;
		} break;
		case 0x3F: {
			op_k = Ccf;
		} break;
		case 0xD9: {
			op_k = Reti;
		} break;
		case 0xF3: {
			op_k = Di;
		} break;
		case 0xFB: {
			op_k = Ei;
		} break;
		case 0xB6: {
			op_k = Halt;
		} break;
	}

	if (op_k == InvalidOp) {
		switch (op) {
			case 0x31: {
				op_k = Ld;
				val1 = Sp;
				val2 = Data_16;
			} break;
			case 0xAF: {
				op_k = Xor;
				val1 = A;
			} break;
		}
	}

	const char *op_k_string = kind_string(op_k);
 	char val1_string[10];
 	char val2_string[10];
	memset(val1_string, 0, sizeof(val1_string));
	memset(val2_string, 0, sizeof(val2_string));

	// Determine whether to pull data block from the buffer for val1
	if (val1 == None || (val1 != Data_8 && val1 != Data_16)) {
		strcpy(val1_string, type_string(val1));
	} else {
		u16 val = 0;
		if (val1 == Data_8) {
        	val = local_rom[++idx];
			inst = (op << 16) | (val << 8);
		} else if (val2 == Data_16) {
			val = (local_rom[idx+2] << 8) | local_rom[idx+1];
			idx += 2;
		}
		inst = (op << 16) | val;
		sprintf(val1_string, "0x%x", val);
	}

	// Determine whether to pull data block from the buffer for val2
	if (val2 == None || (val2 != Data_8 && val2 != Data_16)) {
		strcpy(val2_string, type_string(val2));
	} else {
		u16 val = 0;
		if (val2 == Data_8) {
        	val = local_rom[++idx];
			inst = (op << 16) | (val << 8);
		} else if (val2 == Data_16) {
			val = (local_rom[idx+2] << 8) | local_rom[idx+1];
			idx += 2;
		}
		inst = (op << 16) | val;
		sprintf(val2_string, "0x%x", val);
	}

	// Set instruction to the current op if nothing was set
	if (inst == 0) {
		inst = op;
	}

	// Pretty print only values that exist
	if (val1 != None && val2 != None) {
		printf("[ %s ] %s, %s | 0x%x\n", op_k_string, val1_string, val2_string, inst);
	} else if (val1 != None && val2 == None) {
		printf("[ %s ] %s | 0x%x\n", op_k_string, val1_string, inst);
	} else if (val1 == None && val2 == None) {
		printf("[ %s ] | 0x%x\n", op_k_string, inst);
	} else {
		printf("[ERR] 0x%x", inst);
	}
	return ++idx;
}

#endif
