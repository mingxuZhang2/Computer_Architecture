#include <stdio.h>
#include "shell.h"
void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */
    uint32_t instruction = mem_read_32(CURRENT_STATE.PC);
    int update = FALSE;
    printf("Now the address is :%d\n",CURRENT_STATE.PC);
    uint32_t opcode = (instruction & 0xFC000000) >> 26;
    printf("instruction is : %u\n",instruction);
    printf("opcode is : %u\n",opcode);
    if (opcode == 0) {
        // R-type instruction
        uint32_t funct = instruction & 0x3F;
        uint32_t rs = (instruction & 0x03E00000) >> 21;
        uint32_t rt = (instruction & 0x001F0000) >> 16;
        uint32_t rd = (instruction & 0x0000F800) >> 11;
        uint32_t shamt = (instruction & 0x000007C0) >> 6;

    switch (funct) {
        uint32_t HI, LO;    
        HI = CURRENT_STATE.HI;
        LO = CURRENT_STATE.LO;
        case 0x00: // SLL
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << shamt;
            break;
        case 0x02: // SRL
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shamt;
            break;
        case 0x03: // SRA
            NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rt] >> shamt;
            break;
        case 0x04: // SLLV
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << (CURRENT_STATE.REGS[rs] & 0x1F);
            break;
        case 0x06: // SRLV
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> (CURRENT_STATE.REGS[rs] & 0x1F);
            break;
        case 0x07: // SRAV
            NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rt] >> (CURRENT_STATE.REGS[rs] & 0x1F);
            break;
        case 0x08: // JR
            NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
            break;
        case 0x09: // JALR
            NEXT_STATE.REGS[rd] = CURRENT_STATE.PC + 4;
            NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
            break;
        case 0x20: // ADD
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
            printf("There is ADD instructions!");
            printf("The operands is:%d %d\n",CURRENT_STATE.REGS[rs],CURRENT_STATE.REGS[rt]);
            printf("The answer is :%d\n",NEXT_STATE.REGS[rd]);
            break;
        case 0x21: // ADDU
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
            printf("There is ADDU instruction!");
            printf("The operands is:%u %u\n",CURRENT_STATE.REGS[rs],CURRENT_STATE.REGS[rt]);
            printf("The answer is :%u\n",NEXT_STATE.REGS[rd]);
            break;      
        case 0x22: // SUB
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
            break;
        case 0x23: // SUBU
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
            break;
        case 0x24: // AND
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];
            break;
        case 0x25: // OR
            printf("This is OR instruction!");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];
            printf("The operands is:%d %d\n",CURRENT_STATE.REGS[rs],CURRENT_STATE.REGS[rt]);
            printf("The answer is :%d\n",NEXT_STATE.REGS[rd]);
            break;
        case 0x26: // XOR
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] ^ CURRENT_STATE.REGS[rt];
            break;
        case 0x27: // NOR
            NEXT_STATE.REGS[rd] = ~(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]);
            break;
        case 0x2A: // SLT
            NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rs] < (int32_t)CURRENT_STATE.REGS[rt];
            break;
        case 0x2B: // SLTU
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt];
            break;
        case 0x18: // MULT
            // Note: This is a simplified version, real implementation should consider 64-bit result
            NEXT_STATE.HI = ((int64_t)CURRENT_STATE.REGS[rs] * (int64_t)CURRENT_STATE.REGS[rt]) >> 32;
            NEXT_STATE.LO = ((int64_t)CURRENT_STATE.REGS[rs] * (int64_t)CURRENT_STATE.REGS[rt]) & 0xFFFFFFFF;
            break;
        case 0x19: // MULTU
            NEXT_STATE.HI = ((uint64_t)CURRENT_STATE.REGS[rs] * (uint64_t)CURRENT_STATE.REGS[rt]) >> 32;
            NEXT_STATE.LO = ((uint64_t)CURRENT_STATE.REGS[rs] * (uint64_t)CURRENT_STATE.REGS[rt]) & 0xFFFFFFFF;
            break;
        case 0x1A: // DIV
            if (CURRENT_STATE.REGS[rt] != 0) {
                NEXT_STATE.LO = (int32_t)CURRENT_STATE.REGS[rs] / (int32_t)CURRENT_STATE.REGS[rt];
                NEXT_STATE.HI = (int32_t)CURRENT_STATE.REGS[rs] % (int32_t)CURRENT_STATE.REGS[rt];
            } else {
                // Handle division by zero error here
            }
            break;
        case 0x1B: // DIVU
            if (CURRENT_STATE.REGS[rt] != 0) {
                NEXT_STATE.LO = CURRENT_STATE.REGS[rs] / CURRENT_STATE.REGS[rt];
                NEXT_STATE.HI = CURRENT_STATE.REGS[rs] % CURRENT_STATE.REGS[rt];
            } else {
                // Handle division by zero error here
            }
            break;
        case 0x10: // MFHI
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[HI];
            break;
        case 0x12: // MFLO
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[LO];
            break;
        case 0x11: // MTHI
            NEXT_STATE.REGS[HI] = CURRENT_STATE.REGS[rs];
            break;
        case 0x13: // MTLO
            NEXT_STATE.REGS[LO] = CURRENT_STATE.REGS[rs];
            break;
        default:
            // Handle unknown instruction
            break;
    }
    } 
    else if (opcode == 2 || opcode == 3) {
        uint32_t address = instruction & 0x03FFFFFF;
        uint32_t targetAddress = (CURRENT_STATE.PC & 0xF0000000) | (address << 2);
        int bitCount = 0;
        int pow = 1;
        while (targetAddress) {
            bitCount++;
            targetAddress /= 10;
            pow  = pow * 10;
        }
        targetAddress = (CURRENT_STATE.PC & 0xF0000000) | (address << 2);
        switch (opcode) {
            case 2: // J
                NEXT_STATE.PC = CURRENT_STATE.PC/pow *pow + targetAddress;
                update = TRUE;
                printf("This is J instruction\n");
                printf("Now the address is: %u\n",address);
                printf("The target address is %u\n",targetAddress);
                printf("The pc is: %u\n",CURRENT_STATE.PC);
                break;
            case 3: // JAL
                printf("This is JAL instruction\n");
                printf("Now the address is: %u\n",address);
                printf("The target address is %u\n",targetAddress);
                NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4; // 将返回地址保存到寄存器$ra中
                NEXT_STATE.PC = CURRENT_STATE.PC/pow *pow + targetAddress;
                update = TRUE;
                break;
            default:
                // Handle unknown instruction
                break;
        }
    }
    else {
        // I-type instruction
        uint32_t rs = (instruction & 0x03E00000) >> 21;
        uint32_t rt = (instruction & 0x001F0000) >> 16;
        int16_t imm = instruction & 0xFFFF; // sign-extended immediate
        uint32_t address = CURRENT_STATE.REGS[rs] + (int32_t)imm;
        switch (opcode) {
            case 0x1: // BGEZ or BLTZAL
                if(rt == 0x1) { // BGEZ
                    printf("BGEZ!\n");
                    if((int32_t)CURRENT_STATE.REGS[rs] >= 0) {
                        NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (imm << 2);
                        printf("Now the pc is: %u\n", NEXT_STATE.PC);
                    }
                } else if(rt == 0x10) { // BLTZAL
                    printf("BLTZAL!\n");
                    NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4; // Link Register
                    if((int32_t)CURRENT_STATE.REGS[rs] < 0) {
                        NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (imm << 2);
                        printf("Now the pc is: %u\n", NEXT_STATE.PC);
                    }
                }
                break;
            case 0x6: // BLEZ
                printf("BLEZ!\n");
                if((int32_t)CURRENT_STATE.REGS[rs] <= 0) {
                    NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (imm << 2);
                    printf("Now the pc is: %u\n", NEXT_STATE.PC);
                }
                break;
            case 0x7: // BGTZ
                printf("BGTZ!\n");
                if((int32_t)CURRENT_STATE.REGS[rs] > 0) {
                    NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (imm << 2);
                    printf("Now the pc is: %u\n", NEXT_STATE.PC);
                }
                break;
            case 0x8: // ADDI
                printf("the imm is : %u\n",imm);
                printf("now is: %u\n",CURRENT_STATE.REGS[rs]);
                NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + imm;
                printf("the answer is : %u\n",NEXT_STATE.REGS[rt]);
                break;
            case 0x9: // ADDIU
                printf("the imm is : %u\n",imm);
                printf("now is: %u\n",CURRENT_STATE.REGS[rs]);
                NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + (uint32_t)imm;
                printf("the answer is : %u\n",NEXT_STATE.REGS[rt]);
                break;
            case 0xC: // ANDI
                NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] & (uint32_t)imm;
                break;
            case 0xD: // ORI
                printf("This is ORI instruction!\n");
                NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] | (uint32_t)imm;
                printf("The operands are: %d %u\n",CURRENT_STATE.REGS[rs],imm);
                printf("The answer is :%d\n",NEXT_STATE.REGS[rt]);
                break;
            case 0xE: // XORI
                NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] ^ (uint32_t)imm;
                break;
            case 0xA: // SLTI
                NEXT_STATE.REGS[rt] = (int32_t)CURRENT_STATE.REGS[rs] < (int32_t)imm ? 1 : 0;
                break;
            case 0xB: // SLTIU
                NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] < (uint32_t)imm ? 1 : 0;
                break;
            case 0xF: // LUI
                NEXT_STATE.REGS[rt] = (uint32_t)imm << 16;
                break;
            case 0x4: // BEQ
                printf("BEQ!\n");
                printf("The address is: %u\n",imm);
                printf("the pc is: %u\n",NEXT_STATE.PC);
                if (CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt]){
                    NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (imm << 2);
                    
                    printf("Now the pc is: %u\n",NEXT_STATE.PC);
                    update=TRUE;
                }
                break;
            case 0x5: // BNE
                printf("BNE!\n");
                printf("The address is: %u\n",imm);
                printf("the pc is: %u\n",NEXT_STATE.PC);
                if (CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]){
                    NEXT_STATE.PC = CURRENT_STATE.PC + 4 + (imm << 2);
                    update = TRUE;
                    printf("BNE success!\n");
                    printf("Now the pc is: %u\n",NEXT_STATE.PC);
                }
                break;
            case 0x23: // LW
                NEXT_STATE.REGS[rt] = mem_read_32(address);
                printf("Load word,from %d\n ",address);
                printf("The words is : %d\n ",NEXT_STATE.REGS[rt]);
                break;
            case 0x2B: // SW
                mem_write_32(address,NEXT_STATE.REGS[rt]);
                printf("save word in %d\n",address);
                printf("The words is : %d\n ",NEXT_STATE.REGS[rt]);
                break;
            case 0x28: // SB
                mem_write_32(address, (uint32_t)(NEXT_STATE.REGS[rt] & 0xFF));
                printf("Store byte in %d\n", address);
                printf("The byte is: %d\n", NEXT_STATE.REGS[rt] & 0xFF);
                break;
            case 0x29: //SH
                mem_write_32(address, (uint32_t)(NEXT_STATE.REGS[rt] & 0xFFFF));
                printf("Store halfword in %d\n", address);
                printf("The halfword is: %d\n", NEXT_STATE.REGS[rt] & 0xFFFF);
                break;
            case 0x21: //LH
                NEXT_STATE.REGS[rt] = (int32_t)(int16_t)mem_read_32(address);
                printf("Load halfword from %d\n", address);
                printf("The halfword is: %d\n", NEXT_STATE.REGS[rt]);
                break;  
            case 0x25: // LHU (Load Halfword Unsigned)
                NEXT_STATE.REGS[rt] = mem_read_32(address) & 0xFFFF;
                printf("Load halfword unsigned from %d\n", address);
                printf("The halfword is: %d\n", NEXT_STATE.REGS[rt]);
                break;

            case 0x20: // LB (Load Byte)
                NEXT_STATE.REGS[rt] = (int32_t)(int8_t)mem_read_32(address);
                printf("Load byte from %d\n", address);
                printf("The byte is: %d\n", NEXT_STATE.REGS[rt]);
                break;
            // ... Implement other I-type instructions
            default:
                // Handle unknown instruction
                break;
        }
        
    }
    // Update the program counter
    if(!update) NEXT_STATE.PC = CURRENT_STATE.PC + 4 ;
    // Handle special cases, exceptions, etc. if necessary
}
