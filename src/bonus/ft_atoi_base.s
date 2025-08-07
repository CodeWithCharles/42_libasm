bits 64

extern	ft_strlen
extern	ft_strchr

section .text

global ft_atoi_base

	_check_base_unauthorized:
		.main:
			LEA		rsi, [REL unauth_chars]	; ptr to forbidden chars list

		.unauth_loop:
			MOV		al, [rsi]				; load forbidden char
			TEST	al,al					; check for null terminator
			JE		.unauth_ok				; done, no forbidden chars found

			PUSH	rsi						; save regs for call
			PUSH	rdi
			MOVZX	rsi,al					; char to find in base string
			CALL	ft_strchr				; check if forbidden char present
			POP		rdi
			POP		rsi

			TEST	rax,rax					; found?
			JNE		.unauth_fail			; if yes, fail

			INC		rsi						; next forbidden char
			JMP		.unauth_loop

		.unauth_fail:
			MOV		rax,1					; return 1 = fail
			RET

		.unauth_ok:
			XOR		rax,rax					; return 0 = ok
			RET

	_check_base_dup:

		XOR	rcx,rcx

		.dup_loop:
			MOV		al,BYTE [rdi+rcx]			; get current base char
			TEST	al,al					; null terminator?
			JE		.dup_ok					; no dup if end

			MOV		r13,rdi					; save base ptr
			LEA		rdi,[rdi+rcx+1]				; ptr to next char
			MOVZX	rsi,al					; char to find duplicates of
			CALL	ft_strchr				; check for duplicates
			MOV		rdi,r13					; restore base ptr

			TEST	rax,rax					; found duplicate?
			JNE		.dup_fail				; yes -> fail

			INC		rcx						; next base char
			JMP		.dup_loop

		.dup_fail:
			MOV		rax,1					; fail
			RET

		.dup_ok:
			XOR		rax,rax					; no dup, ok
			RET

	_check_base:
		.main:
			MOV		r9,rdi					; save base ptr
			CALL	ft_strlen				; get base len
			MOV		rdi,r9					; restore base ptr

			CMP		rax,2					; base len <= 1?
			JL		.check_fail				; fail if so

			MOV		r9,rdi
			CALL	_check_base_dup			; check duplicates
			MOV		rdi,r9
			TEST	rax,rax
			JNE		.check_fail

			CALL	_check_base_unauthorized	; check invalid chars
			TEST	rax,rax
			JNE		.check_fail

		.check_ok:
			XOR		rax,rax					; success
			RET

		.check_fail:
			MOV		rax,1					; fail (1)
			RET

	ft_atoi_base:

		.main:
			PUSH	rbp
			MOV		rbp,rsp
			SUB		rsp,0x8				; align stack, local var

			TEST	rdi,rdi				; check str ptr
			JE		.fail
			TEST	rsi,rsi				; check base ptr
			JE		.fail

			MOV		r8,rdi				; save str ptr
			MOV		r14,rsi
			MOV		rdi,rsi				; base ptr in rdi
			CALL	_check_base			; validate base
			MOV		rsi,r14
			MOV		rdi,r8				; restore str ptr

			TEST	rax,rax				; base invalid?
			JNE		.fail

			MOV		rdi,rsi
			CALL	ft_strlen			; base length
			MOV		r10,rax				; store base len

			MOV		rdi,r8				; restore str ptr

			XOR		r8,r8				; r8 = result (accumulator)
			MOV		r9,1					; r9 = sign (+1 default)

		.skipspaces:
			MOVZX	rcx,BYTE [rdi]
			TEST	cl,cl				; end of string?
			JE		.done

			CMP		cl,' '				; space?
			JE		.inc_ptr

			CMP		cl,0x09				; below TAB?
			JB		.check_sign

			CMP		cl,0x0D				; <= CR?
			JBE		.inc_ptr

			JMP		.check_sign

		.inc_ptr:
			INC		rdi
			JMP		.skipspaces

		.check_sign:
			CMP		BYTE[rdi], '-'		; check for minus
			JNE		.positive

			NEG		r9					; sign = -1
			INC		rdi
			JMP		.check_sign

		.positive:
			CMP		BYTE[rdi], '+'		; check for plus
			JNE		.parse_loop

			INC		rdi					; skip '+'
			JMP		.check_sign

		.parse_loop:
			MOVZX	rcx, BYTE [rdi]		; current char
			TEST	cl,cl				; null?
			JE		.done

			PUSH	rdi					; save str ptr
			MOV		r12,rsi
			MOV		rdi,rsi				; base ptr for ft_strchr
			MOVZX	rsi,cl				; char to find
			CALL	ft_strchr
			MOV		rsi,r12
			POP		rdi

			TEST	rax,rax				; found in base?
			JE		.done				; not found => end parse

			SUB		rax,rsi				; calculate index in base
			CMP		rax,r10				; index >= base len?
			JAE		.done				; invalid char => end parse

			MOV		r11,rax				; index val (digit)
			MOV		rax,r8				; acc
			MUL		r10					; acc *= base len
			ADD		rax,r11				; acc += digit val
			MOV		r8,rax				; save acc

			INC		rdi					; next char
			JMP		.parse_loop

		.done:
			MOV		rax,r8				; return result
			IMUL	rax,r9				; apply sign

			JMP		.exit

		.fail:
			XOR		rax,rax				; return 0 on fail

		.exit:
			LEAVE					; restore stack frame
			RET

section	.data
	unauth_chars	db	0x0A, 0x0D, 0x0C, 0x0B, 0x09, 0x20, 0x2B, 0x2D, 0
