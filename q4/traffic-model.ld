ENTRY(_Reset)
SECTIONS
{
 . = 0x0;
 .text : {
 startup.o (INTERRUPT_VECTOR)
 *(.text)
 }
 .data : { *(.data) }
 .bss : {
   __bss_start__ = .;
   *(.bss)
   *(COMMON)
   __bss_end__ = .;
 }
 . = ALIGN(8);
 . = . + 0x1000; /* 4kB of stack memory */
 stack_top = .;
 end = .;
}