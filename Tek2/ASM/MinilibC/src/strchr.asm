	section .text

	global strchr:function

strchr:
	push rdi

loop:
	cmp BYTE [rdi], sil
	jz found
	cmp BYTE [rdi], 0
	jz not_found
	inc rdi
	jmp loop

not_found:
	mov rax, 0
	jmp end

found:	mov rax, rdi

end:
	pop rdi

	ret