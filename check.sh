if grub-file --is-x86-multiboot bin/mallard86.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi