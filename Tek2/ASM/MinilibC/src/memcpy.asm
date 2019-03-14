	section .text

	global memcpy:function

memcpy:
	mov rcx, 0
loop:
	cmp rdx, rcx
	je end

	mov al, [rsi + rcx]
	mov [rdi + rcx], al

	inc rcx
	jmp loop
false:
	mov rax, 0
	ret

end:
	mov rax, rdi

	ret
