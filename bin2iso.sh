mkdir -p bin/boot/grub
cp bin/mallard86.bin bin/boot/mallard86.bin
grub-mkrescue -o mallard86.iso bin