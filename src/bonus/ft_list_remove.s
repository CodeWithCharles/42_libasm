bits 64

extern	free

struc t_list
	pdata:	resq 1
	pnext:	resq 1
endstruc

section	.text

global	ft_list_remove

; void	ft_list_remove(t_list *lst, void (*del)(void *))
ft_list_remove:
	TEST	rdi,rdi ; If lst == NULL, exit
	JZ		.done
	PUSH	rdi

	TEST	rsi,rsi ; If fnc == NULL skip deletion
	JZ		.skip_del
	MOV		rax, [rdi+pdata]
	TEST	rax,rax ; If lst->data == NULL skip deletion
	JZ		.skip_del

	MOV		rdi, rax
	CALL	rsi

.skip_del:
	POP		rdi
	JMP		free WRT ..plt
.done:
	RET
