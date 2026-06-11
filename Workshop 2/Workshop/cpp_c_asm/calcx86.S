.global addWithAsmX86
.type addWithAsmX86, @function

# int addWithAsmX86(int a, int b)
# cdecl:
# 4(%esp) = a
# 8(%esp) = b

addWithAsmX86:
    movl 4(%esp), %eax
    addl 8(%esp), %eax
    ret