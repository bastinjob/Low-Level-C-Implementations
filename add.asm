section .data
    num1 dq 10           ; Use 64-bit (quadword) for consistency
    num2 dq 20
    result dq 0
    msg db "The Sum is: ", 0xA  ; Add newline for formatting
    len equ $ - msg  ; Length of msg

section .bss
    buffer resb 20       ; Buffer to store string output

section .text
    global _start

_start:
    ; Load num1 and num2, perform addition
    mov rax, [num1]
    add rax, [num2]
    mov [result], rax  ; Store sum

    ; Check if result is zero
    cmp rax, 0
    jne convert_number
    mov byte [buffer], '0'  ; Store '0' if result is zero
    mov byte [buffer + 1], 0  ; Null-terminate the string
    jmp print_output  ; Skip conversion

convert_number:
    mov rdi, buffer + 19  ; Start from the end of buffer (reverse order)
    mov byte [rdi], 0  ; Null-terminate the string
    dec rdi

    ; Convert integer to string (store in reverse order)
    call int_to_string

print_output:
    ; Print message
    mov rax, 1  ; syscall number for sys_write
    mov rdi, 1  ; file descriptor (stdout)
    mov rsi, msg
    mov rdx, len
    syscall

    ; Print result string
    mov rax, 1
    mov rdi, 1
    mov rsi, rdi  ; Start printing from converted number
    mov rdx, buffer + 19 - rdi  ; Calculate length of the number
    syscall

    ; Exit program
    mov rax, 60  ; syscall number for exit
    xor rdi, rdi
    syscall

; Integer to string conversion function (stores digits in reverse)
int_to_string:
    mov rcx, 10       ; Divisor = 10
    xor rdx, rdx
.next_digit:
    div rcx           ; RAX = RAX / 10, remainder in RDX
    add dl, '0'       ; Convert remainder to ASCII
    mov [rdi], dl     ; Store character in buffer
    dec rdi           ; Move left
    test rax, rax     ; Check if quotient is 0
    jnz .next_digit   ; Repeat if more digits
    inc rdi           ; Move back to the first digit
    ret
