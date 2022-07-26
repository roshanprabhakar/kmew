# kmew

## Resources

- [os dev](https://wiki.osdev.org/Main_Page)
- [GrUB](https://www.gnu.org/software/grub/)
- http://www.jamesmolloy.co.uk/tutorial_html/
- [.elf special sections explanations](https://refspecs.linuxbase.org/LSB_3.0.0/LSB-PDA/LSB-PDA/specialsections.html)

## Docker

We need this package in the container: gcc-aarch64-linux-gnu

Create the container:
`docker build env -t kmew-env`

Run the container:
`docker run --rm -it -v "$(pwd)":/root/env kmew-env`

Compile command:
`aarch64-linux-gnu-[gcc/ld]`

## Run
```sh
qemu-system-aarch64 -machine raspi3b -kernel build/kmew_os.img
```

## Debug

On Host:
```sh
$ sh run.sh
(qemu) gdbserver
```

In Docker
```sh
$ gdb-multiarch build/kmew_os.elf
(gdb) target remote host.docker.internal:1234
(gdb) *0x80000
(gdb) c
```
