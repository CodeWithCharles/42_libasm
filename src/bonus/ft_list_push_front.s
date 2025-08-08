bits 64

extern	ft_list_new

struct t_list
	pdata:	resq 1
	pnext:	resq 1
endstruct

section	.text

global	ft_list_push_front

ft_list_push_front:
	PUSH	rbp
	MOV		rbp,rsp
	SUB		rsp,0x10
	MOV		QWORD [rbp-0x8],rdi
	MOV		QWORD [rbp-0x10],rsi
	MOV		rdi,rsi
	CALL	ft_list_new
	TEST	rax,rax
	JE		.exit
	MOV		rdx, QWORD [rbp-0x8]
	CMP		QWORD [rdx], 0x0
	JNE		.push_front
	MOV		QWORD [rdx], rax
	JMP		.exit

.push_front:
	MOV		rcx, QWORD [rdx]
	MOV		QWORD [rdx], rax
	MOV		QWORD [rax+pnext], rcx

.exit:
	LEAVE
	RET
