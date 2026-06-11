.global addWithAsmX64
.type addWithAsmX64, @function

# int addWithAsmX64(int a, int b)
# System V ABI:
# edi = a
# esi = b

addWithAsmX64:
    movl %edi, %eax
    addl %esi, %eax
    ret