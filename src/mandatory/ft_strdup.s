bits 64

extern	malloc
extern	ft_strcpy
extern	ft_strlen

section	.text

global	ft_strdup

	ft_strdup:
		mov	rax,0x1
		syscall
		cmp	rax,0xfffffffffffff000
		ja	.error
		ret

	.error:
		mov		edx,eax
		sub		rsp,0x8 ; Stack is misaligned otherwise
		call	__errno_location WRT ..plt ; Gets the errno pointer into rax
		add		rsp,0x8 ; Re-align stack
		neg		edx ; Change errno to positive
		mov		DWORD [rax], edx ; Move err code to the adresse pointed by rax
		mov		rax, -1
		ret
