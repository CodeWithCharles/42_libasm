bits 64

section .text
global ft_strcmp

	ft_strcmp:
		xor	rax,rax ; Initialize rax to 0
		xor	rdx,rdx ; Initialize rdx to 0
		; rax is the return register, where the result will be stored

	.loop:
		mov		al,BYTE[rsi+rdx] ; Move rsi+rdx byte to al
		mov		cl,BYTE[rdi+rdx] ; Using CL because rbx is a specific register
		cmp		al, cl ; Comparing two bytes
		jnz		.diff ; If different, return diff
		test	al, al ; If we go here, check if end of string
		jz		.exit
		inc		rdx
		jmp		.loop ; Loop

	.diff:
		movzx	eax,BYTE[rdi+rdx]
		movzx	ecx,BYTE[rsi+rdx]
		sub		eax, ecx ; sub goes to eax, 32-bits lower part of rax
		; sub has a special behavior, and will zero-extend the whole 64-bits rax
		ret

	.exit:
		xor rax,rax
		ret
