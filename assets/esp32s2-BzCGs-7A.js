import{R as r}from"./rom-Caghk6Eh.js";class U extends r{constructor(){super(...arguments),this.CHIP_NAME="ESP32-S2",this.IMAGE_CHIP_ID=2,this.IROM_MAP_START=1074266112,this.IROM_MAP_END=1085800448,this.DROM_MAP_START=1056964608,this.DROM_MAP_END=1061093376,this.CHIP_DETECT_MAGIC_VALUE=[1990],this.SPI_REG_BASE=1061167104,this.SPI_USR_OFFS=24,this.SPI_USR1_OFFS=28,this.SPI_USR2_OFFS=32,this.SPI_MOSI_DLEN_OFFS=36,this.SPI_MISO_DLEN_OFFS=40,this.SPI_W0_OFFS=88,this.SPI_ADDR_REG_MSB=!1,this.MAC_EFUSE_REG=1061265476,this.UART_CLKDIV_REG=1061158932,this.SUPPORTS_ENCRYPTED_FLASH=!0,this.FLASH_ENCRYPTED_WRITE_ALIGN=16,this.EFUSE_BASE=1061265408,this.EFUSE_RD_REG_BASE=this.EFUSE_BASE+48,this.EFUSE_BLOCK1_ADDR=this.EFUSE_BASE+68,this.EFUSE_BLOCK2_ADDR=this.EFUSE_BASE+92,this.EFUSE_PURPOSE_KEY0_REG=this.EFUSE_BASE+52,this.EFUSE_PURPOSE_KEY0_SHIFT=24,this.EFUSE_PURPOSE_KEY1_REG=this.EFUSE_BASE+52,this.EFUSE_PURPOSE_KEY1_SHIFT=28,this.EFUSE_PURPOSE_KEY2_REG=this.EFUSE_BASE+56,this.EFUSE_PURPOSE_KEY2_SHIFT=0,this.EFUSE_PURPOSE_KEY3_REG=this.EFUSE_BASE+56,this.EFUSE_PURPOSE_KEY3_SHIFT=4,this.EFUSE_PURPOSE_KEY4_REG=this.EFUSE_BASE+56,this.EFUSE_PURPOSE_KEY4_SHIFT=8,this.EFUSE_PURPOSE_KEY5_REG=this.EFUSE_BASE+56,this.EFUSE_PURPOSE_KEY5_SHIFT=12,this.EFUSE_DIS_DOWNLOAD_MANUAL_ENCRYPT_REG=this.EFUSE_RD_REG_BASE,this.EFUSE_DIS_DOWNLOAD_MANUAL_ENCRYPT=1<<19,this.EFUSE_SPI_BOOT_CRYPT_CNT_REG=this.EFUSE_BASE+52,this.EFUSE_SPI_BOOT_CRYPT_CNT_MASK=7<<18,this.EFUSE_SECURE_BOOT_EN_REG=this.EFUSE_BASE+56,this.EFUSE_SECURE_BOOT_EN_MASK=1<<20,this.EFUSE_RD_REPEAT_DATA3_REG=this.EFUSE_BASE+60,this.EFUSE_RD_REPEAT_DATA3_REG_FLASH_TYPE_MASK=512,this.PURPOSE_VAL_XTS_AES256_KEY_1=2,this.PURPOSE_VAL_XTS_AES256_KEY_2=3,this.PURPOSE_VAL_XTS_AES128_KEY=4,this.UARTDEV_BUF_NO=1073741076,this.UARTDEV_BUF_NO_USB_OTG=2,this.USB_RAM_BLOCK=2048,this.GPIO_STRAP_REG=1061175352,this.GPIO_STRAP_SPI_BOOT_MASK=8,this.GPIO_STRAP_VDDSPI_MASK=16,this.RTC_CNTL_OPTION1_REG=1061191976,this.RTC_CNTL_FORCE_DOWNLOAD_BOOT_MASK=1,this.RTCCNTL_BASE_REG=1061191680,this.RTC_CNTL_WDTCONFIG0_REG=this.RTCCNTL_BASE_REG+148,this.RTC_CNTL_WDTCONFIG1_REG=this.RTCCNTL_BASE_REG+152,this.RTC_CNTL_WDTWPROTECT_REG=this.RTCCNTL_BASE_REG+172,this.RTC_CNTL_WDT_WKEY=1356348065,this.MEMORY_MAP=[[0,65536,"PADDING"],[1056964608,1073217536,"DROM"],[1062207488,1073217536,"EXTRAM_DATA"],[1073340416,1073348608,"RTC_DRAM"],[1073340416,1073741824,"BYTE_ACCESSIBLE"],[1073340416,1074208768,"MEM_INTERNAL"],[1073414144,1073741824,"DRAM"],[1073741824,1073848576,"IROM_MASK"],[1073872896,1074200576,"IRAM"],[1074200576,1074208768,"RTC_IRAM"],[1074266112,1082130432,"IROM"],[1342177280,1342185472,"RTC_DATA"]],this.EFUSE_VDD_SPI_REG=this.EFUSE_BASE+52,this.VDD_SPI_XPD=16,this.VDD_SPI_TIEH=32,this.VDD_SPI_FORCE=64,this.UF2_FAMILY_ID=3218951918,this.EFUSE_MAX_KEY=5,this.KEY_PURPOSES={0:"USER/EMPTY",1:"RESERVED",2:"XTS_AES_256_KEY_1",3:"XTS_AES_256_KEY_2",4:"XTS_AES_128_KEY",5:"HMAC_DOWN_ALL",6:"HMAC_DOWN_JTAG",7:"HMAC_DOWN_DIGITAL_SIGNATURE",8:"HMAC_UP",9:"SECURE_BOOT_DIGEST0",10:"SECURE_BOOT_DIGEST1",11:"SECURE_BOOT_DIGEST2"},this.UART_CLKDIV_MASK=1048575,this.UART_DATE_REG_ADDR=1610612856,this.FLASH_WRITE_SIZE=1024,this.BOOTLOADER_FLASH_OFFSET=4096,this.FLASH_SIZES={"1MB":0,"2MB":16,"4MB":32,"8MB":48,"16MB":64}}async getPkgVersion(_){const s=this.EFUSE_BLOCK1_ADDR+16;return await _.readReg(s)>>0&15}async getMinorChipVersion(_){const s=await _.readReg(this.EFUSE_BLOCK1_ADDR+12)>>20&1,i=await _.readReg(this.EFUSE_BLOCK1_ADDR+4*4)>>4&7;return(s<<3)+i}async getMajorChipVersion(_){return await _.readReg(this.EFUSE_BLOCK1_ADDR+4*3)>>18&3}async getFlashVersion(_){return await _.readReg(this.EFUSE_BLOCK1_ADDR+4*3)>>21&15}async getChipDescription(_){const E={0:"ESP32-S2",1:"ESP32-S2FH2",2:"ESP32-S2FH4",102:"ESP32-S2FNR2",100:"ESP32-S2R2"},s=await this.getFlashCap(_)+await this.getPsramCap(_)*100,t=await this.getMajorChipVersion(_),i=await this.getMinorChipVersion(_);return`${E[s]||"unknown ESP32-S2"} (revision v${t}.${i})`}async getFlashCap(_){return await this.getFlashVersion(_)}async getPsramVersion(_){const s=this.EFUSE_BLOCK1_ADDR+12;return await _.readReg(s)>>28&15}async getPsramCap(_){return await this.getPsramVersion(_)}async getBlock2Version(_){const s=this.EFUSE_BLOCK2_ADDR+16;return await _.readReg(s)>>4&7}async getChipFeatures(_){const E=["Wi-Fi"],s={0:"No Embedded Flash",1:"Embedded Flash 2MB",2:"Embedded Flash 4MB"},t=await this.getFlashCap(_),i=s[t]||"Unknown Embedded Flash";E.push(i);const S={0:"No Embedded Flash",1:"Embedded PSRAM 2MB",2:"Embedded PSRAM 4MB"},h=await this.getPsramCap(_),R=S[h]||"Unknown Embedded PSRAM";E.push(R);const e={0:"No calibration in BLK2 of efuse",1:"ADC and temperature sensor calibration in BLK2 of efuse V1",2:"ADC and temperature sensor calibration in BLK2 of efuse V2"},n=await this.getBlock2Version(_),a=e[n]||"Unknown Calibration in BLK2";return E.push(a),E}async getCrystalFreq(_){return 40}_d2h(_){const E=(+_).toString(16);return E.length===1?"0"+E:E}async readMac(_){let E=await _.readReg(this.MAC_EFUSE_REG);E=E>>>0;let s=await _.readReg(this.MAC_EFUSE_REG+4);s=s>>>0&65535;const t=new Uint8Array(6);return t[0]=s>>8&255,t[1]=s&255,t[2]=E>>24&255,t[3]=E>>16&255,t[4]=E>>8&255,t[5]=E&255,this._d2h(t[0])+":"+this._d2h(t[1])+":"+this._d2h(t[2])+":"+this._d2h(t[3])+":"+this._d2h(t[4])+":"+this._d2h(t[5])}getEraseSize(_,E){return E}async usingUsbOtg(_){return(await _.readReg(this.UARTDEV_BUF_NO)&255)===this.UARTDEV_BUF_NO_USB_OTG}async postConnect(_){const E=await this.usingUsbOtg(_);_.debug("In _post_connect using USB OTG ?"+E),E&&(_.ESP_RAM_BLOCK=this.USB_RAM_BLOCK)}}export{U as ESP32S2ROM};