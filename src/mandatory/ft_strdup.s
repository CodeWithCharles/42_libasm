bits 64

extern	malloc
extern	ft_strcpy
extern	ft_strlen

section	.text

global	ft_strdup   ; declare ft_strdup as global symbol (exported)

	ft_strdup:
		; save base pointer of caller stack frame
		PUSH	rbp
		; set new base pointer for this function's stack frame
		MOV		rbp,rsp
		; allocate 16 bytes on stack (for alignment and local storage)
		SUB		rsp,0x10
		; Store the source pointer (rdi) into stack at [rbp-0x8]
		MOV		QWORD [rbp-0x8],rdi
		CALL	ft_strlen
		; increment length by 1 to include null terminator
		INC		rax
		; arg for malloc
		MOV		rdi,rax
		; call malloc(size), returns pointer in rax
		CALL	malloc	WRT	..plt
		; exit if malloc res is NULL
		CMP		rax,0x0
		JZ		.exit
		; put dest and src into the right reg
		MOV		rdi,rax
		MOV		rsi,QWORD[rbp-0x8]
		CALL	ft_strcpy
		JMP		.exit
	.exit:
		LEAVE ; restore stack frame (mov rsp, rbp; pop rbp)
		RET
