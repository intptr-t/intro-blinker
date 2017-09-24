#define TARGET_HW_RPI_ZERO

/* Peripheral base address for Raspberry Pi1, model A, A+, B, B+, CM, Zero */
#define BASE_BCM2708_PERIPHERAL     0x20000000u
/* Peripheral base address for Raspberry Pi2 */
#define BASE_BCM2709_PERIPHERAL     0x3F000000u
/* Peripheral base address for Raspberry Pi3 */
#define BASE_BCM2710_PERIPHERAL     (BASE_BCM2709_PERIPHERAL)

#if defined(TARGET_HW_RPI3)
#   define SUBSYSTEM_BASE       BASE_BCM2710_PERIPHERAL
#elif defined(TARGET_HW_RPI2)
#   define SUBSYSTEM_BASE       BASE_BCM2709_PERIPHERAL
#elif defined(TARGET_HW_RPI1) || defined(TARGET_HW_RPI_ZERO)
#   define SUBSYSTEM_BASE       BASE_BCM2708_PERIPHERAL
#else
#   error "not defined TARGET_HW_xxxx @" __FILE__
#endif

#define BASE_CLOCK                  0x00101000u
#define BASE_GPIO                   0x00200000u

#define GPFSEL0                     (SUBSYSTEM_BASE + BASE_GPIO + 0x00u)
#define GPFSEL1                     (SUBSYSTEM_BASE + BASE_GPIO + 0x04u)
#define GPFSEL2                     (SUBSYSTEM_BASE + BASE_GPIO + 0x08u)
#define GPFSEL3                     (SUBSYSTEM_BASE + BASE_GPIO + 0x0Cu)
#define GPFSEL4                     (SUBSYSTEM_BASE + BASE_GPIO + 0x10u)
#define GPFSEL5                     (SUBSYSTEM_BASE + BASE_GPIO + 0x14u)

#define GPSET0                      (SUBSYSTEM_BASE + BASE_GPIO + 0x1Cu)
#define GPSET1                      (SUBSYSTEM_BASE + BASE_GPIO + 0x20u)

#define GPCLR0                      (SUBSYSTEM_BASE + BASE_GPIO + 0x28u)
#define GPCLR1                      (SUBSYSTEM_BASE + BASE_GPIO + 0x2Cu)

#define GPLEV0                      (SUBSYSTEM_BASE + BASE_GPIO + 0x34u)
#define GPLEV1                      (SUBSYSTEM_BASE + BASE_GPIO + 0x38u)

/*!
 * busy loop
 * \param [in] loop loop count
 */
void busy_loop(unsigned int loop)
{
    volatile unsigned int i;
    for(i = 0u; i < loop; i++);
}

/*!
 * entry point
 */
int main(void)
{
    /* GPIO16 Output:001b                                    */
    /*    BIT   : 00 000 000 000 001 000 000 000 000 000 000 */
    /*   GPIO   :  -  19  18  17  16  15  14  13  12  11  10 */
    *(volatile unsigned int *)GPFSEL1 = 0x01 << (3 * 6);

    while(1){
        /* GPIO16 LED ON */
        *(volatile unsigned int *)GPSET0 |= 0x01 << 16;
        busy_loop(0x100000u);

        /* LED OFF */
        *(volatile unsigned int *)GPCLR0 |= 0x01 << 16;
        busy_loop(0x100000u);
    }
    return 0;
}