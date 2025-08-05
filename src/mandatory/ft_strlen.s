bits 64

section .text
global ft_strlen

	ft_strlen:
		xor	rax,rax ; Initialize rax to 0
		; rax is the return register, where the result will be stored

	ft_strlen_loop:
		cmp	BYTE[rdi+rax], 0x0 ; rdi is the first argument, we offset it by rax
		jz	ft_strlen_ret ; if the comp result is 0, return
		inc	rax ; increment rax
		jmp	ft_strlen_loop ; go back to the start of the loop

	ft_strlen_ret:
		ret
