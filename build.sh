make
mkdir -p isodir/boot/grub
cp myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
cp filesystem/initrd.img isodir/boot/initrd.img
grub-mkrescue -o myos.iso isodir
