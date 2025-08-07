bits 64

section .text
global ft_strchr

	ft_strchr:
		XOR		rax,rax
		MOV		dl,sil

	.loop:
		CMP		BYTE[rdi],dl
		JE		.found
		CMP		BYTE[rdi],0x0
		JE		.exit
		INC		rdi
		JMP		.loop

	.found:
		MOV		rax,rdi

	.exit:
		RET
