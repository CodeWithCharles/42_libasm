bits 64

extern	__errno_location

section	.text

global	ft_read
; Decided to switch to uppercase, easier to read.
; Read is the same principle as write
	ft_read:
		MOV		rax,0x0 ; Rax to 0, corresponds to syscall read
		SYSCALL
		CMP		rax,0xfffffffffffff000
		JA		.error
		RET

	.error:
		MOV		edx,eax
		SUB		rsp,0x8
		CALL	__errno_location WRT ..plt
		ADD		rsp,0x8
		NEG		edx
		MOV		DWORD [rax],edx
		MOV		rax, -1
		RET
