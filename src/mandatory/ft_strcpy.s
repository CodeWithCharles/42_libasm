bits 64

section .text
global ft_strcpy

	ft_strcpy:
		xor	rax,rax ; Initialize rax to 0
		; rax is the return register, where the result will be stored

	ft_strcpy_loop:
		mov	cl, BYTE[rsi+rax] ; Storing the byte from src offset by rax to cl
		mov	BYTE[rdi+rax],cl ; Storing CL back into dest offset by rax
		cmp	cl, 0 ; Compare CL register to 0
		jz	ft_strcpy_ret ; If CL is 0, exit
		inc	rax ; Increment rax
		jmp	ft_strcpy_loop ; Loop


	ft_strcpy_ret:
		mov	cl, 0 ; Reset CL register
		mov rax, rdi ; Move rdi to rax to return copy
		ret
