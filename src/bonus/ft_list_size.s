bits 64

struc t_list
	pdata:	resq 1
	pnext:	resq 1
endstruc

section .text

global	ft_list_size

; int ft_list_size(t_list *begin_list);
ft_list_size:
	XOR	rax,rax
.loop
	TEST	rdi,rdi
	JE		.exit
	INC		rax
	MOV		rdi, [rdi+pnext]
	JMP		.loop
.exit
	RET
