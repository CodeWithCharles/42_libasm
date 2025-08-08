bits 64

extern malloc

struc t_list
	pdata:	resq 1
	pnext:	resq 1
endstruc

section	.text

global	ft_list_new

ft_list_new:
	PUSH	rbp
	MOV		rbp,rsp
	SUB		rsp,0x10
	MOV		QWORD [rbp-0x8],rdi
	MOV		rdi,t_list_size
	CALL	malloc	WRT	..plt
	CMP		rax,0x0
	JE		.exit
	MOV		rdi,QWORD [rbp-0x8]
	MOV		QWORD	[rax+pdata], rdi
	MOV		QWORD	[rax+pnext], 0x0

.exit:
	LEAVE
	RET
