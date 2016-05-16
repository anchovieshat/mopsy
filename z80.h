#ifndef Z80_H
#define Z80_H

#include "stdio.h"
#include "platform.h"

typedef enum Opcode {
	Nop,
	Ld,
	Add,
	Adc,
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
	Rl,
	Rla,
	Rlca,
	Rrca,
	Rra,
	Rlc,
	Rrc,
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
	Data_8_Addr,
	Data_8_Imm,
	Data_16,
	Data_16_Addr,
	Data_16_Imm,
	Zero,
	One,
	Two,
    Three,
	Four,
	Five,
	Six,
	Seven,
	Nz,
	Ez,
	Nc,
	Ec,
	RelC,
	LoHl,
	HiHl,
	RelBc,
	RelDe,
	RelHl,
	Af,
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
    	case Data_8_Addr: {
			return "Data_8_Addr";
		} break;
    	case Data_16_Addr: {
			return "Data_16_Addr";
		} break;
    	case Data_8_Imm: {
			return "Data_8_Imm";
		} break;
    	case Data_16_Imm: {
			return "Data_16_Imm";
		} break;
    	case Zero: {
			return "0";
		} break;
    	case One: {
			return "1";
		} break;
    	case Two: {
			return "2";
		} break;
    	case Three: {
			return "3";
		} break;
    	case Four: {
			return "4";
		} break;
    	case Five: {
			return "5";
		} break;
    	case Six: {
			return "6";
		} break;
    	case Seven: {
			return "7";
		} break;
		case Nz: {
			return "NZ";
		} break;
		case Ez: {
			return "Z";
		} break;
		case Nc: {
			return "NC";
		} break;
		case Ec: {
			return "C";
		} break;
		case RelC: {
			return "(FF00+C)";
		} break;
		case LoHl: {
			return "(Hl-)";
		} break;
		case HiHl: {
			return "(Hl+)";
		} break;
		case RelBc: {
			return "(Bc)";
		} break;
		case RelDe: {
			return "(De)";
		} break;
		case RelHl: {
			return "(Hl)";
		} break;
		case Af: {
			return "Af";
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
			return "Ld";
		} break;
		case Ldd: {
			return "Ld";
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
		case Rl: {
			return "Rl";
		} break;
		case Rla: {
			return "Rla";
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
	u32 increment = 0;

	Opcode op_k = InvalidOp;

	switch (op) {
		case 0x0: {
			op_k = Nop;
		} break;
		case 0x10: {
			op_k = Stop;
		} break;
		case 0x17: {
			op_k = Rla;
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
		case 0xC9: {
			op_k = Ret;
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
			case 0x1: {
				op_k = Ld;
				val1 = Bc;
				val2 = Data_16;
			} break;
			case 0x2: {
				op_k = Ld;
				val1 = RelBc;
				val2 = A;
			} break;
			case 0x4: {
				op_k = Inc;
				val1 = B;
			} break;
			case 0x5: {
				op_k = Dec;
				val1 = B;
			} break;
			case 0x6: {
				op_k = Ld;
				val1 = B;
				val2 = Data_8;
			} break;
			case 0x9: {
				op_k = Add;
				val1 = Hl;
				val2 = Bc;
			} break;
			case 0xA: {
				op_k = Ld;
				val1 = A;
				val2 = RelBc;
			} break;
			case 0xC: {
				op_k = Inc;
				val1 = C;
			} break;
			case 0xD: {
				op_k = Dec;
				val1 = C;
			} break;
			case 0xE: {
				op_k = Ld;
				val1 = C;
				val2 = Data_8;
			} break;
			case 0x11: {
				op_k = Ld;
				val1 = De;
				val2 = Data_16;
			} break;
			case 0x12: {
				op_k = Ld;
				val1 = RelDe;
				val2 = A;
			} break;
			case 0x13: {
				op_k = Inc;
				val1 = De;
			} break;
			case 0x14: {
				op_k = Inc;
				val1 = D;
			} break;
			case 0x15: {
				op_k = Dec;
				val1 = D;
			} break;
			case 0x16: {
				op_k = Ld;
				val1 = D;
				val2 = Data_8;
			} break;
			case 0x18: {
				op_k = Jr;
				val1 = Data_8;
			} break;
			case 0x19: {
				op_k = Add;
				val1 = Hl;
				val2 = De;
			} break;
			case 0x1C: {
				op_k = Inc;
				val1 = E;
			} break;
			case 0x1A: {
				op_k = Ld;
				val1 = A;
				val2 = RelDe;
			} break;
			case 0x1D: {
				op_k = Dec;
				val1 = E;
			} break;
			case 0x1E: {
				op_k = Ld;
				val1 = E;
				val2 = Data_8;
			} break;
			case 0x20: {
				op_k = Jr;
				val1 = Nz;
				val2 = Data_8;
			} break;
			case 0x21: {
				op_k = Ld;
				val1 = Hl;
				val2 = Data_16;
			} break;
			case 0x22: {
				op_k = Ld;
				val1 = HiHl;
				val2 = A;
			} break;
			case 0x23: {
				op_k = Inc;
				val1 = Hl;
			} break;
			case 0x24: {
				op_k = Inc;
				val1 = H;
			} break;
			case 0x25: {
				op_k = Dec;
				val1 = H;
			} break;
			case 0x26: {
				op_k = Ld;
				val1 = H;
				val2 = Data_8;
			} break;
			case 0x28: {
				op_k = Jr;
				val1 = Ez;
				val2 = Data_8;
			} break;
			case 0x29: {
				op_k = Add;
				val1 = Hl;
				val2 = RelHl;
			} break;
			case 0x2A: {
				op_k = Ld;
				val1 = A;
				val2 = HiHl;
			} break;
			case 0x2C: {
				op_k = Inc;
				val1 = L;
			} break;
			case 0x2D: {
				op_k = Dec;
				val1 = L;
			} break;
			case 0x2E: {
				op_k = Ld;
				val1 = L;
				val2 = Data_8;
			} break;
			case 0x30: {
				op_k = Jr;
				val1 = Nc;
				val2 = Data_8;
			} break;
			case 0x31: {
				op_k = Ld;
				val1 = Sp;
				val2 = Data_16;
			} break;
			case 0x32: {
				op_k = Ld;
				val1 = LoHl;
				val2 = A;
			} break;
			case 0x33: {
				op_k = Inc;
				val1 = Sp;
			} break;
			case 0x34: {
				op_k = Inc;
				val1 = RelHl;
			} break;
			case 0x35: {
				op_k = Dec;
				val1 = RelHl;
			} break;
			case 0x38: {
				op_k = Jr;
				val1 = Ec;
				val2 = Data_8;
			} break;
			case 0x39: {
				op_k = Add;
				val1 = Hl;
				val2 = Sp;
			} break;
			case 0x3C: {
				op_k = Inc;
				val1 = A;
			} break;
			case 0x3D: {
				op_k = Dec;
				val1 = A;
			} break;
			case 0x3E: {
				op_k = Ld;
				val1 = A;
				val2 = Data_8;
			} break;
			case 0x47: {
				op_k = Ld;
				val1 = B;
				val2 = A;
			} break;
			case 0x4F: {
				op_k = Ld;
				val1 = C;
				val2 = A;
			} break;
			case 0x57: {
				op_k = Ld;
				val1 = D;
				val2 = A;
			} break;
			case 0x5F: {
				op_k = Ld;
				val1 = E;
				val2 = A;
			} break;
			case 0x67: {
				op_k = Ld;
				val1 = H;
				val2 = A;
			} break;
			case 0x6F: {
				op_k = Ld;
				val1 = L;
				val2 = A;
			} break;
			case 0x77: {
				op_k = Ld;
				val1 = RelHl;
				val2 = A;
			} break;
			case 0x78: {
				op_k = Ld;
				val1 = A;
				val2 = B;
			} break;
			case 0x79: {
				op_k = Ld;
				val1 = A;
				val2 = C;
			} break;
			case 0x7A: {
				op_k = Ld;
				val1 = A;
				val2 = D;
			} break;
			case 0x7B: {
				op_k = Ld;
				val1 = A;
				val2 = E;
			} break;
			case 0x7C: {
				op_k = Ld;
				val1 = A;
				val2 = H;
			} break;
			case 0x7D: {
				op_k = Ld;
				val1 = A;
				val2 = L;
			} break;
			case 0x7E: {
				op_k = Ld;
				val1 = A;
				val2 = RelHl;
			} break;
			case 0x7F: {
				op_k = Ld;
				val1 = A;
				val2 = A;
			} break;
			case 0x80: {
				op_k = Add;
				val1 = A;
				val2 = B;
			} break;
			case 0x81: {
				op_k = Add;
				val1 = A;
				val2 = C;
			} break;
			case 0x82: {
				op_k = Add;
				val1 = A;
				val2 = D;
			} break;
			case 0x83: {
				op_k = Add;
				val1 = A;
				val2 = E;
			} break;
			case 0x84: {
				op_k = Add;
				val1 = A;
				val2 = H;
			} break;
			case 0x85: {
				op_k = Add;
				val1 = A;
				val2 = L;
			} break;
			case 0x86: {
				op_k = Add;
				val1 = A;
				val2 = RelHl;
			} break;
			case 0x87: {
				op_k = Add;
				val1 = A;
				val2 = A;
			} break;
			case 0x88: {
				op_k = Adc;
				val1 = A;
				val2 = B;
			} break;
			case 0x89: {
				op_k = Adc;
				val1 = A;
				val2 = C;
			} break;
			case 0x8A: {
				op_k = Adc;
				val1 = A;
				val2 = D;
			} break;
			case 0x8B: {
				op_k = Adc;
				val1 = A;
				val2 = E;
			} break;
			case 0x8C: {
				op_k = Adc;
				val1 = A;
				val2 = H;
			} break;
			case 0x8D: {
				op_k = Adc;
				val1 = A;
				val2 = L;
			} break;
			case 0x8E: {
				op_k = Adc;
				val1 = A;
				val2 = RelHl;
			} break;
			case 0x8F: {
				op_k = Adc;
				val1 = A;
				val2 = A;
			} break;
			case 0x90: {
				op_k = Sub;
				val1 = B;
			} break;
			case 0x91: {
				op_k = Sub;
				val1 = C;
			} break;
			case 0x92: {
				op_k = Sub;
				val1 = D;
			} break;
			case 0x93: {
				op_k = Sub;
				val1 = E;
			} break;
			case 0x94: {
				op_k = Sub;
				val1 = H;
			} break;
			case 0x95: {
				op_k = Sub;
				val1 = L;
			} break;
			case 0x96: {
				op_k = Sub;
				val1 = RelHl;
			} break;
			case 0x98: {
				op_k = Sbc;
				val1 = A;
				val2 = B;
			} break;
			case 0x99: {
				op_k = Sbc;
				val1 = A;
				val2 = C;
			} break;
			case 0x9A: {
				op_k = Sbc;
				val1 = A;
				val2 = D;
			} break;
			case 0x9B: {
				op_k = Sbc;
				val1 = A;
				val2 = E;
			} break;
			case 0x9C: {
				op_k = Sbc;
				val1 = A;
				val2 = H;
			} break;
			case 0x9D: {
				op_k = Sbc;
				val1 = A;
				val2 = L;
			} break;
			case 0x9E: {
				op_k = Sbc;
				val1 = A;
				val2 = RelHl;
			} break;
			case 0xAF: {
				op_k = Xor;
				val1 = A;
			} break;
			case 0xBF: {
				op_k = Cp;
				val1 = A;
			} break;
			case 0xB8: {
				op_k = Cp;
				val1 = B;
			} break;
			case 0xB9: {
				op_k = Cp;
				val1 = C;
			} break;
			case 0xBA: {
				op_k = Cp;
				val1 = D;
			} break;
			case 0xBB: {
				op_k = Cp;
				val1 = E;
			} break;
			case 0xBC: {
				op_k = Cp;
				val1 = H;
			} break;
			case 0xBD: {
				op_k = Cp;
				val1 = L;
			} break;
			case 0xBE: {
				op_k = Cp;
				val1 = RelHl;
			} break;
			case 0xC1: {
				op_k = Pop;
				val1 = Bc;
			} break;
			case 0xC5: {
				op_k = Push;
				val1 = Bc;
			} break;
			case 0xCB: {
				// Special case LONG opcodes
				switch (local_rom[idx+1]) {
					case 0x10: {
						op_k = Rl;
						val1 = B;
					} break;
					case 0x11: {
						op_k = Rl;
						val1 = C;
					} break;
					case 0x12: {
						op_k = Rl;
						val1 = D;
					} break;
					case 0x13: {
						op_k = Rl;
						val1 = E;
					} break;
					case 0x14: {
						op_k = Rl;
						val1 = H;
					} break;
					case 0x15: {
						op_k = Rl;
						val1 = L;
					} break;
					case 0x16: {
						op_k = Rl;
						val1 = RelHl;
					} break;
					case 0x7C: {
						op_k = Bit;
						val1 = Seven;
						val2 = H;
					} break;
				}
				increment += 1;
			} break;
			case 0xCD: {
				op_k = Call;
				val1 = Data_16_Imm;
			} break;
			case 0xD1: {
				op_k = Pop;
				val1 = De;
			} break;
			case 0xD5: {
				op_k = Push;
				val1 = De;
			} break;
			case 0xE0: {
				op_k = Ld;
				val1 = Data_8_Addr;
				val2 = A;
			} break;
			case 0xE1: {
				op_k = Pop;
				val1 = Hl;
			} break;
			case 0xE2: {
				op_k = Ld;
				val1 = RelC;
				val2 = A;
			} break;
			case 0xE5: {
				op_k = Push;
				val1 = Hl;
			} break;
			case 0xE8: {
				op_k = Add;
				val1 = Sp;
				val1 = Data_8;
			} break;
			case 0xEA: {
				op_k = Ld;
				val1 = Data_16_Imm;
				val2 = A;
			} break;
			case 0xF0: {
				op_k = Ld;
				val1 = A;
				val2 = Data_8_Addr;
			} break;
			case 0xF1: {
				op_k = Pop;
				val1 = Af;
			} break;
			case 0xF5: {
				op_k = Push;
				val1 = Af;
			} break;
			case 0xFE: {
				op_k = Cp;
				val1 = Data_8;
			} break;
		}
	}

	const char *op_k_string = kind_string(op_k);
 	char val1_string[40];
 	char val2_string[40];
	memset(val1_string, 0, sizeof(val1_string));
	memset(val2_string, 0, sizeof(val2_string));

	// Determine whether to pull data block from the buffer for val1
	if (val1 == None || (val1 != Data_8 && val1 != Data_16 && val1 != Data_8_Addr && val1 != Data_16_Addr &&
				         val1 != Data_8_Imm && val1 != Data_16_Imm)) {
		strcpy(val1_string, type_string(val1));
	} else {
		u16 val = 0;
		if (val1 == Data_8 || val1 == Data_8_Addr || val1 == Data_8_Imm) {
        	val = local_rom[idx+1];
			inst = (op << 16) | (val << 8);
			increment += 1;
		} else if (val1 == Data_16 || val1 == Data_16_Addr || val1 == Data_16_Imm) {
			val = (local_rom[idx+2] << 8) | local_rom[idx+1];
			increment += 2;
		}
		inst = (op << 16) | val;
		if (val1 == Data_8_Addr || val1 == Data_16_Addr) {
			sprintf(val1_string, "(FF00+0x%x)", val);
		} else if (val1 == Data_8_Imm || val1 == Data_16_Imm) {
			sprintf(val1_string, "(0x%x)", val);
        } else {
			sprintf(val1_string, "0x%x", val);
		}
	}

	// Determine whether to pull data block from the buffer for val2
	if (val2 == None || (val2 != Data_8 && val2 != Data_16 && val2 != Data_8_Addr && val2 != Data_16_Addr &&
				         val2 != Data_8_Imm && val2 != Data_16_Imm)) {
		strcpy(val2_string, type_string(val2));
	} else {
		u16 val = 0;
		if (val2 == Data_8 || val2 == Data_8_Addr || val2 == Data_8_Imm) {
        	val = local_rom[idx+1];
			inst = (op << 16) | (val << 8);
			increment += 1;
		} else if (val2 == Data_16 || val2 == Data_16_Addr || val2 == Data_16_Imm) {
			val = (local_rom[idx+2] << 8) | local_rom[idx+1];
			increment += 2;
		}
		inst = (op << 16) | val;
		if ((val2 == Data_8_Addr || val2 == Data_16_Addr)) {
			sprintf(val2_string, "(FF00+0x%x)", val);
		} else if ((val2 == Data_8_Imm || val2 == Data_16_Imm)) {
			sprintf(val2_string, "(0x%x)", val);
		} else {
			sprintf(val2_string, "0x%x", val);
		}
	}

	// Set instruction to the current op if nothing was set
	if (inst == 0) {
		inst = op;
	}

	increment += 1;
	// Pretty print only values that exist
	if (val1 != None && val2 != None) {
		printf("%x [ %s ] %s, %s | 0x%x\n", idx, op_k_string, val1_string, val2_string, inst);
	} else if (val1 != None && val2 == None) {
		printf("%x [ %s ] %s | 0x%x\n", idx, op_k_string, val1_string, inst);
	} else if (val1 == None && val2 == None) {
		printf("%x [ %s ] | 0x%x\n", idx, op_k_string, inst);
	} else {
		printf("%x [ERR] 0x%x", idx, inst);
	}
	return idx + increment;
}

#endif
