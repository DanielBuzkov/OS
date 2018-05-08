/*
#include <stddef.h>
#include <print.h>
#include <string.h>
#include <io.h>
#include <time.h>*/

#include "common.h"


uint32_t *SMI_CMD;
uint8_t ACPI_ENABLE;
uint8_t ACPI_DISABLE;
uint32_t *PM1a_CNT;
uint32_t *PM1b_CNT;
uint16_t SLP_TYPa;
uint16_t SLP_TYPb;
uint16_t SLP_EN;
uint16_t SCI_EN;
uint8_t PM1_CNT_LEN;


struct RSDPtr
{
   uint8_t Signature[8];
   uint8_t CheckSum;
   uint8_t OemID[6];
   uint8_t Revision;
   uint32_t *RsdtAddress;
};

struct FACP
{
   uint8_t Signature[4];
   uint32_t Length;
   uint8_t unneded1[40 - 8];
   uint32_t *DSDT;
   uint8_t unneded2[48 - 44];
   uint32_t *SMI_CMD;
   uint8_t ACPI_ENABLE;
   uint8_t ACPI_DISABLE;
   uint8_t unneded3[64 - 54];
   uint32_t *PM1a_CNT_BLK;
   uint32_t *PM1b_CNT_BLK;
   uint8_t unneded4[89 - 72];
   uint8_t PM1_CNT_LEN;
};

// check if the given address has a valid header
uint32_t *acpiCheckRSDPtr(uint32_t *ptr);

// finds the acpi header and returns the address of the rsdt
uint32_t *acpiGetRSDPtr(void);

// checks for a given header and validates checksum
uint32_t acpiCheckHeader(uint32_t *ptr, uint8_t *sig);

uint32_t acpiEnable(void);
uint32_t initAcpi(void);
void acpiPowerOff(void);