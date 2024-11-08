set_project("kernel")

set_toolchains("clang_nasm")

target("kernel")
    set_kind("binary")                    
    set_arch("elf64-x86-64") 
    add_files("src/*.c", "src/**/*.c")
    add_files("src/*.asm", "src/**/*.asm")
    set_filename("os.bin")
    set_targetdir(".")
    add_ldflags("-nostdlib", "-T linker.ld", {force = true})


toolchain("clang_nasm")
    set_kind("standalone")
    set_toolset("cc", "clang")       
    set_toolset("cxx", "clang++")    
    set_toolset("ld", "ld.lld.exe")
    set_toolset("as", "nasm")
    add_cflags("-target x86_64-pc-none-elf", "-ffreestanding", "-nostdlib", "-fno-exceptions", "-fno-rtti")
    add_cxxflags("-target x86_64-pc-none-elf", "-ffreestanding", "-nostdlib", "-fno-exceptions", "-fno-rtti")
    add_asflags("-f elf64") 
toolchain_end()