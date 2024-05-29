bits 64
;uint8_t inb(uint16_t port);
global inb
inb:
	mov dx, [esp + 4]
  xor eax, eax
  in al, dx
	ret

;void outb(uint16_t port, uint8_t value);
global outb
outb:
	mov dx, [esp + 4]
  mov al, [esp + 8]
	out dx, al
  ret

;void iowait();
global iowait
iowait:
	out 0x80, al ; dummy call to keep the function happy :)
	ret
	