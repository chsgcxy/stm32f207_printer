/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "usb_conf.h"
#include "usbh_msc_core.h"
/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */

#define ATA		0
#define MMC		1
#define USB		2
#define SPI     3

static volatile DSTATUS ata_stat = STA_NOINIT;	/* Disk status */
static volatile DSTATUS mmc_stat = STA_NOINIT;	/* Disk status */
static volatile DSTATUS usb_stat = STA_NOINIT;	/* Disk status */
static volatile DSTATUS spi_stat = STA_NOINIT;	/* Disk status */

extern USB_OTG_CORE_HANDLE          USB_OTG_Core;
extern USBH_HOST                     USB_Host;

/*-----------------------------------------------------------------------*/
/* Inicializes a Drive                                                    */

DSTATUS disk_initialize (BYTE drv)    /* Physical drive nmuber (0..) */
{
	switch (drv) {
	case ATA:
		return ata_stat;
	case MMC:
		return mmc_stat;
	case USB:
		if (HCD_IsDeviceConnected(&USB_OTG_Core))  
			usb_stat &= ~STA_NOINIT;
		return usb_stat;
	case SPI:
		return spi_stat;
		break;
	default:
		break;
	}
}

/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
	switch (drv) {
	case ATA:
		return ata_stat;
	case MMC:
		return mmc_stat;
	case USB:
		return usb_stat;
	case SPI:
		return spi_stat;
	default:
		break;
	}
	
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
	DRESULT res;
	int result;

	switch (drv) {
	case ATA :
		result = ATA_disk_read(buff, sector, count);
		// translate the reslut code here

		return res;

	case MMC :
		result = MMC_disk_read(buff, sector, count);
		// translate the reslut code here

		return res;

	case USB :
		result = USB_disk_read(buff, sector, count);
		// translate the reslut code here

		return res;
	}
	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
	DRESULT res;
	int result;

	switch (drv) {
	case ATA :
		result = ATA_disk_write(buff, sector, count);
		// translate the reslut code here

		return res;

	case MMC :
		result = MMC_disk_write(buff, sector, count);
		// translate the reslut code here

		return res;

	case USB :
		result = USB_disk_write(buff, sector, count);
		// translate the reslut code here

		return res;
	}
	return RES_PARERR;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (drv) {
	case ATA :
		// pre-process here

		result = ATA_disk_ioctl(ctrl, buff);
		// post-process here

		return res;

	case MMC :
		// pre-process here

		result = MMC_disk_ioctl(ctrl, buff);
		// post-process here

		return res;

	case USB :
		// pre-process here

		result = USB_disk_ioctl(ctrl, buff);
		// post-process here

		return res;
	}
	return RES_PARERR;
}

