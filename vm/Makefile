# 编译器
GCC			= gcc
# 优化选项
O_opt		= -O2
# 压缩
strip		= strip
UPX			= upx
# 可执行文件后缀名，默认exe
executable_file_suffix	= .exe

welcome_vm:
	$(info [RLC3] Welcome to RLC3-VM)

install_vm:
	$(info [RLC3] Compileing VM...)
	$(GCC) vm.c $(O_opt) -o rlc3_vm

compress_vm:
	$(info [RLC3] Compressing VM...)
	$(strip) -s rlc3_vm$(executable_file_suffix)
	$(UPX) -9 rlc3_vm$(executable_file_suffix)

vm: welcome_vm install_vm compress_vm
	$(info [RLC3] Done!)