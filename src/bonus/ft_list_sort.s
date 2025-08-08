bits 64

struc	t_list
	pdata:	resq 1
	pnext:	resq 1
endstruc

section .text

global	ft_list_sort

ft_list_sort:
	PUSH	rbp
	MOV		rbp,rsp
	SUB		rsp,0x18
	MOV		rdi, QWORD [rdi] ; t_list ** to t_list *
	MOV		QWORD [rbp-0x8],rdi ; Save t_list *begin_list
	MOV		QWORD [rbp-0x10],rsi ; Save cmp fnc
	TEST	rdi,rdi
	JE		.exit
	MOV		r8,rdi

.loop:
	CMP		QWORD [r8+pnext],0x0 ; if next == NULL
	JE		.exit
	MOV		rdi,	QWORD [r8+pdata] ; Load data in rdi
	MOV		rdx,	QWORD [r8+pnext] ; Load next
	MOV		rsi,	QWORD [rdx+pdata] ; Load next->data
	MOV		rdx,	QWORD [rbp-0x10] ; Get cmp fnc
	MOV		QWORD [rbp-0x18],	r8 ; A security, so that r8 doesn't get modified
	CALL	rdx
	MOV		r8,		QWORD [rbp-0x18]
	CMP		eax,0x0
	JG		.swap
	MOV		r8,		QWORD [r8+pnext]
	JMP		.loop

.swap:
	MOV		r9,	QWORD [r8+pdata] ; l->data stored
	MOV		rdx,	QWORD [r8+pnext] ; l->next into rdx
	MOV		rcx,	QWORD [rdx+pdata] ; l->data = l->next->data
	MOV		QWORD [r8+pdata],	rcx ; l->data = l->next->data
	MOV		QWORD [rdx+pdata],	r9 ; l->next->data = old l->data
	MOV		r8,	QWORD [rbp-0x8] ; Reload begin list
	JMP		.loop

.exit:
	LEAVE
	RET
