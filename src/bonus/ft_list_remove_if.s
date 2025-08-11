bits 64

extern	ft_list_remove

struc t_list
	pdata:	resq 1
	pnext:	resq 1
endstruc

section	.text

global	ft_list_remove_if

; void ft_list_remove_if(
;	t_list **begin_list,
;	void *data_ref,
;	int (*cmp)(),
;	void (*free_fct)(void *)
; );
ft_list_remove_if:
	PUSH	rbp
	MOV		rbp,rsp
	SUB		rsp,0x28	; Allocation 8*5 bytes.
	MOV		QWORD [rbp-0x8],rdi ; t_list **begin_list
	MOV		QWORD [rbp-0x10],rsi ; void *data_ref
	MOV		QWORD [rbp-0x18],rdx ; int (*cmp)()
	MOV		QWORD [rbp-0x20],rcx ; void (*free_fct)(void *))
	MOV		r8, QWORD [rbp-0x8]

.loop:
	CMP		QWORD [r8],0x0
	JE		.exit
	MOV		r8, QWORD [r8]
	MOV		rdi, QWORD [r8+pdata]
	MOV		rsi, QWORD [rbp-0x10]
	MOV		rdx, QWORD [rbp-0x18]
	PUSH	r8
	CALL	rdx
	POP		r8
	TEST	eax,eax
	JZ		.remove
	LEA		r8, QWORD [r8 + pnext]
	MOV		QWORD [rbp-0x8], r8
	JMP		.loop

.remove:
	MOV		rdi, QWORD [r8+pdata]
	MOV		rsi, QWORD [rbp-0x20]
	MOV		r9, QWORD [rbp-0x8]
	MOV		rdx, QWORD [r8+pnext]
	MOV		QWORD [r9], rdx
	MOV		rdi, r8
	PUSH	r9
	CALL	ft_list_remove
	POP		r8
	JMP		.loop

.exit:
	LEAVE
	RET
