	section .text

	global strcmp:function

strcmp:
	mov rcx, 0
loop:
	mov bl, [rdi + rcx]
	mov dl, [rsi + rcx]

	cmp bl, 0
	je end

	cmp bl, dl
	jne end

	inc rcx
	jmp loop

end:
	sub bl, dl
	movsx rax, bl

	ret
