# ISA Definition & Documentation #

## 1. Overview & Motivation ##

### Purpose & Application Context ###
The purpose of this ISA is to accelarate low-cost mobile phones AI applications of voice
recognition, biometric security, and intelligent connectivity. These applications
require real time processing of sensor data, secure handling of sensitive infomation, and
efficient network management. By designing an ISA customized for these workloads, the 
processor can efficiently execute feature extraction, neural network interference, and
cryptographic operations, enabling responsive devices.

### Design Goals ###
a.	Energy efficiency: essential for extending battery life in mobile phones. <br>
b.	Low cost: achieved through simplified hardware and minimal complexity. <br>
c.	High performance for AI: optimized acceleration for key computational tasks such as
    voice recognition, biometric security, and intelligent connectivity. <br>
d.	Security support: integrate instructions to protect biometric templates and secure 
    communications. <br>
e.	Real time responsiveness: reduce latency for voice commands, biometric authentication,
    and adaptive network decisions.
    
### Suitability for Target Workload ###
The ISA is built upon the open and simple RISC-V architecture, which inherently satisfies 
the low-cost and simplicity goals. Voice recognition benefits from vector instructions and 
fast MAC operations for audio signal processing. Biometric security relies on cryptographic 
and image processing extensions to securely and efficiently analyse fingerprints and faces.
Intelligent connectivity leverages AI acceleration and packet processing instructions for
adaptive, low-latency network management.

## 2. Architectural Design Choices ##

### Instruction Philosophy ###
RISC-style has been chosen.  RISC provides simplicity, fixed instruction length, and ease 
of hardware pipelining. It allows easy integration of custom AI and instructions without 
the complexity of CISC. This lead to lower power consumption, and better clock speeds, 
aligning perfectly with low-cost, energy-efficient mobile goal.

### Registers ###
32 general purpose registers (R0 – R31), each 32 bits wide (32 x 32). R0 is hardwired to 
zero. Registers R28-R31 are reserved for special use like program counter and stack pointer.

### Data Types ###
8-bit byte, 16-bit half-word, and 32-bit word. These sizes cover audio samples, biometric 
templates, video/image data, and AI computations efficiently.

### Addressing ###
Immediate: embed constants directly in instructions (useful for thresholds in feature 
extraction).
Register: access memory via register pointers.
Base + offset: common for arrays (audio buffers, image frames).
These simple and predictable addressing modes are sufficient for real time processing and
reduce instruction complexity.

### Memory Model ###
Little endian. Enforced alignment. 
Little endian is common in modern processors and compatible with many AI and IoT libraries. 
Enforced alignment improve access speed and reduce misaligned memory penalties.

### Instruction Formats ###
Fixed length instruction format: 32 – bit base instructions for predictability and 
pipelining efficiency. Optional 16 – bit compressed instructions; for code size reduction 
in memory constrained edge devices. <br>
R-type: register to register operations. <br>
I-type: immediate operations and load instructions.<br>
S-type: store instructions.<br>
B-type: branch instructions.<br>
J-type: jump instuctions.<br>
U-type: load upper immediate.<br>
Fixed length instructions simplify decode logic and pipelining, while optional compressed 
instructions reduce memory footprint for edge AI devices.

## 3. Instruction Set Summary ##
| Category | Mnemonic(s) | Operands Descriptions | Function |
| ------------- | ------------ | ------------ | ----------- |
| Base Arithmetic | ADD, SUB, SHIFT_L, SHIFT_R | Rdest, Rsrc1, Rsrc2 | Standard register to register arithmetic and shift operands |
| Immediate Arithmetic | ADDI, ANDI, XORI | Rdest, Rsrc1, Immediate | Arithmetic/Logic operations using a register and a sign extended immediate constant |
| Load / Store | LD_W, ST_W, LD_B, ST_B | Rdest, offset(Rbase) | Load or store a Word or Byte from memory using register relative addressing |
| Control Flow | JUMP, JMP_REG, BR_EQ, BR_NEQ | Label/Rdest, Rsrc/Rsrc1, Rsrc2, Label | Unconditional jumps, jumps to register address, and conditional branches |

## 4. Instruction Encoding Summary ##
The encoding follows a regular RISC structure to simplify the datapath and control unit.
●	Instruction Sizes: 32-bit (Base/Custom) and 16-bit (Compressed).<br>
●	Register Fields: 5 bits are used to address any of the 32 GPRs.<br>
●	Regularity: The Opcode is consistent across all 32-bit formats. Destination registers (Rdest) are consistently found in the same bit positions, reducing complexity in the instruction decoder.

32-bit R-Type Format (e.g., ADD, MAC_D32)
The R-type format is used for register-to-register operations, including our custom extensions.
| Bit Range | [31:25] | [24:20] | [19:15] | [14:12] | [11:7] | [6:0] |
| -------- | ------- | -------- | -------- | --------- | -------- | ------ |
| Field | Funct7(7 bits) | Rsrc2(5 bits) | Rsrc1(5 bits) | Funct3(3 bits) | Rdest(5 bits) | Opcode(7 bits) |

32-bit I-Type Format (e.g., ADDI, LD_W)
| Bit Range | [31:20] | [19:15] | [14:12] | [11:7] | [6:0] |
| -------- | ------- | -------- | --------- | -------- | ------ |
| Field | Immediate[11:0] (12 bits) | Rsrc1 (5 bits) | Funct3 (3 bits) | Rdest (5 bits) | Opcode (7 bits) |

Custom Extension Encoding (MAC_D32)
The MAC_D32 instruction requires four register operands. It is encoded as a variation of the R-Type format, using the Funct7 and Funct3 fields to designate the operation and incorporating the fourth source register (Rsrc3) into the immediate space of an extended format (or using a dedicated custom format with three source fields and one destination field, relying on an unused 7-bit slot for the fourth register if an R4-type extension is implemented). For simplicity in this base specification, we assume a custom R4-type instruction that reserves more space for registers.
| Bit Range | [31:27] | [26:22] | [21:17] | [16:12] | [11:7] | [6:0] |
| -------- | ------- | -------- | -------- | --------- | -------- | ------ |
| Field | Rsrc3 (5 bits) | Rsrc2 (5 bits) | Rsrc1 (5 bits) | Rdest (5 bits) | Funct5 (5 bits) | Opcode (7 bits) |
| Note | Uses dedicated custom Opcode space. |

## 5. Design Rationale & Trade-offs ##

### Simplicity vs Capability ###
Trade-off: The design prioritizes Simplicity by choosing the minimal RV32I base, which ensures low hardware complexity and power consumption. The potential loss of general-purpose Capability (e.g., large address space of RV64I) is mitigated by focusing the ISA's complexity budget on domain-specific capability. The custom MAC_D32 and SAD_8x4 instructions provide massive performance boosts for the target workloads, achieving a favorable balance of efficiency and required power.

### Code Density vs Performance ###
Trade-off: Performance is supported by the 32-bit fixed instruction format, which simplifies instruction fetching and pipeline scheduling. Code Density is addressed by including the 16-bit compressed instruction subset (C extension). This hybrid strategy allows critical performance-sensitive code paths to use 32-bit instructions, while general-purpose and frequently used operations leverage 16-bit instructions to reduce code size by up to 30%, directly saving memory and battery power.

### Hardware Impact ###
The use of standard RISC formats and consistent register placement ensures that the core datapath and control unit remain relatively simple. The main hardware impact is the requirement for a specialized MAC/SAD Execution Unit. While this adds hardware complexity, it is a single, isolated block that delivers a significant payoff: it performs operations in a single cycle that would otherwise require dozens of cycles on a general-purpose ALU, making the overall system much more power-efficient for AI tasks.

### Extensibility ###
The ISA is highly extensible. As a customized RISC-V design, it retains the modularity of the base architecture. Significant portions of the opcode space are deliberately unused, designated as "Custom" or "Reserved." This allows the ISA to easily accommodate future extensions (e.g., enhanced cryptography for secure transactions or specialized vector instructions for more complex AI models) without requiring a complete redesign of the core instruction formats or decoding logic.
