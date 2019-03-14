	section .text

	global strcasecmp:

strcasecmp:
	xor rcx, rcx

start:
	mov r10b, [rdi + rcx]
	mov r11b, [rsi + rcx]

loop:
	cmp r10b, 0
	je end
	cmp r11b, 0
	je end
	cmp r10b, 90
	jle check_up_r10b
	
sec_loop:
	cmp r11b, 90
	jle check_up_r11b
	
th_loop:
	cmp r10b, r11b
	jne end
	inc rcx
	jmp start

check_up_r10b:
	cmp r10b, 65
	jge r10b_to_lowcase
	jmp sec_loop

check_up_r11b:
	cmp r11b, 65
	jge r11b_to_lowcase
	jmp th_loop

r10b_to_lowcase:
	add r10b, 32
	jmp loop

r11b_to_lowcase:
	add r11b, 32
	jmp loop

end:
	movzx rax, r10b
	movzx rbx, r11b
	sub rax, rbx
	ret