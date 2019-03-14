	section .text

	global memset:function

memset:
	mov rcx, 0
loop:
	cmp BYTE [rdi + rcx], 0
	je false

	mov [rdi + rcx], sil

	inc rcx
	cmp rcx, rdx
	je end

	jmp loop
false:
	mov rax, 0
	ret
	
end:
	mov rax, rdi

	ret
