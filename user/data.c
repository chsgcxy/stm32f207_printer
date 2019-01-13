#include "data.h"
#include "w25xxx.h"
#include "stdio.h"

#define DATA_CFG_SECTOR      W25X20_BLOCK_TO_SECTOR(1)
#define DATA_START_SECTOR    W25X20_BLOCK_TO_SECTOR(2)
#define DATA_CFG_MAGIC       0xB5
#define DATA_MAGIC           0x5A

struct data_cfg {
    uint8_t magic;
    uint8_t crc;

    uint16_t start_sector;
    uint16_t next_sector;
    uint16_t total_num;
};

/* read data from flash is too too too slow
 * so build a data table to save data to mem
 * and data table must init when system init
 */
static struct data_ui data_table[DATA_MAX_NUM];

static struct result_data res_data;

static const uint8_t crc_table[] = {
    0x00,0x31,0x62,0x53,0xc4,0xf5,0xa6,0x97,0xb9,0x88,0xdb,0xea,0x7d,0x4c,0x1f,0x2e,
    0x43,0x72,0x21,0x10,0x87,0xb6,0xe5,0xd4,0xfa,0xcb,0x98,0xa9,0x3e,0x0f,0x5c,0x6d,
    0x86,0xb7,0xe4,0xd5,0x42,0x73,0x20,0x11,0x3f,0x0e,0x5d,0x6c,0xfb,0xca,0x99,0xa8,
    0xc5,0xf4,0xa7,0x96,0x01,0x30,0x63,0x52,0x7c,0x4d,0x1e,0x2f,0xb8,0x89,0xda,0xeb,
    0x3d,0x0c,0x5f,0x6e,0xf9,0xc8,0x9b,0xaa,0x84,0xb5,0xe6,0xd7,0x40,0x71,0x22,0x13,
    0x7e,0x4f,0x1c,0x2d,0xba,0x8b,0xd8,0xe9,0xc7,0xf6,0xa5,0x94,0x03,0x32,0x61,0x50,
    0xbb,0x8a,0xd9,0xe8,0x7f,0x4e,0x1d,0x2c,0x02,0x33,0x60,0x51,0xc6,0xf7,0xa4,0x95,
    0xf8,0xc9,0x9a,0xab,0x3c,0x0d,0x5e,0x6f,0x41,0x70,0x23,0x12,0x85,0xb4,0xe7,0xd6,
    0x7a,0x4b,0x18,0x29,0xbe,0x8f,0xdc,0xed,0xc3,0xf2,0xa1,0x90,0x07,0x36,0x65,0x54,
    0x39,0x08,0x5b,0x6a,0xfd,0xcc,0x9f,0xae,0x80,0xb1,0xe2,0xd3,0x44,0x75,0x26,0x17,
    0xfc,0xcd,0x9e,0xaf,0x38,0x09,0x5a,0x6b,0x45,0x74,0x27,0x16,0x81,0xb0,0xe3,0xd2,
    0xbf,0x8e,0xdd,0xec,0x7b,0x4a,0x19,0x28,0x06,0x37,0x64,0x55,0xc2,0xf3,0xa0,0x91,
    0x47,0x76,0x25,0x14,0x83,0xb2,0xe1,0xd0,0xfe,0xcf,0x9c,0xad,0x3a,0x0b,0x58,0x69,
    0x04,0x35,0x66,0x57,0xc0,0xf1,0xa2,0x93,0xbd,0x8c,0xdf,0xee,0x79,0x48,0x1b,0x2a,
    0xc1,0xf0,0xa3,0x92,0x05,0x34,0x67,0x56,0x78,0x49,0x1a,0x2b,0xbc,0x8d,0xde,0xef,
    0x82,0xb3,0xe0,0xd1,0x46,0x77,0x24,0x15,0x3b,0x0a,0x59,0x68,0xff,0xce,0x9d,0xac
};

static uint8_t crc8(uint8_t *buf, int len) 
{
    uint8_t crc = 0x00;

    while (len--)
        crc = crc_table[crc ^ *buf++];
    return crc;
}

static void data_read_flash(uint8_t *buf, u32 sector, int len)
{
    w25xxx_read_sector(buf, sector, len);
}

static void data_write_flash(uint8_t *buf, u32 sector, int len)
{
    w25xxx_write_sector(buf, sector, len);
}

static struct data_cfg *data_cfg_get(void)
{
    static struct data_cfg cfg;
    return &cfg;
}

struct data_ui *data_ui_get(int index)
{
    if (index < DATA_MAX_NUM)
        return &data_table[index];
    else
        return NULL;
}

static void data_cfg_save(void)
{
    struct data_cfg *cfg = data_cfg_get();

    cfg->crc = crc8((uint8_t *)(&cfg->start_sector), sizeof(struct data_cfg) - 2);
    data_write_flash((uint8_t *)cfg, DATA_CFG_SECTOR, sizeof(struct data_cfg));
}

int data_cfg_init(void)
{
    //uint8_t crc;
    struct data_cfg *cfg = data_cfg_get();

    data_read_flash((uint8_t *)cfg, DATA_CFG_SECTOR, sizeof(struct data_cfg));
    if (cfg->magic != DATA_CFG_MAGIC) {
        printf("%s: data config bad magic\r\n", __FUNCTION__);
        cfg->magic = DATA_CFG_MAGIC;
        cfg->start_sector = DATA_START_SECTOR;
        cfg->next_sector = DATA_START_SECTOR;
        cfg->total_num = 0;
        return 1;
    }

#if 0
    crc = crc8(&cfg->crc_start, sizeof(struct data_cfg) - 2);
    if (cfg->crc != crc) {
        printf("%s: data config bad crc\r\n", __FUNCTION__);
        return -1;
    }    
#endif
    return 0;
}

static void dataui_setup(int idx, const struct result_data *rd)
{
    struct data_ui *du = data_ui_get(idx);

    if (!du)
        return;
    
    if (rd->magic == DATA_MAGIC)
        du->valid = rd->valid;
    else
        du->valid = 0;

    if (du->valid)
        sprintf(du->string, "data-%03d-20%02d%02d%02d_%02d%02d",
            rd->index, rd->year, rd->month,
            rd->day, rd->hour, rd->minute);            
}

int data_save(struct result_data *stream)
{
    struct data_cfg *cfg = data_cfg_get();

    stream->magic = DATA_MAGIC;
    stream->index = cfg->next_sector - cfg->start_sector;
    stream->valid = 1;
    stream->crc = crc8((uint8_t *)(&stream->index), sizeof(struct result_data) - 2);
    data_write_flash((uint8_t *)stream, cfg->next_sector, sizeof(struct result_data));
 
    if (cfg->total_num < DATA_MAX_NUM)
        cfg->total_num++;

    dataui_setup(stream->index, stream);

    if (cfg->next_sector - cfg->start_sector > DATA_MAX_NUM)
        cfg->next_sector = cfg->start_sector;
    else
        cfg->next_sector++;
        
    data_cfg_save();

    return stream->index;
}

int data_del(int idx)
{
    struct data_cfg *cfg = data_cfg_get();

    if (idx < cfg->total_num) {
        data_read_flash((uint8_t *)&res_data, cfg->start_sector + idx, sizeof(struct result_data));
        res_data.valid = 0;
        data_write_flash((uint8_t *)&res_data, cfg->start_sector + idx, sizeof(struct result_data));
        dataui_setup(idx, &res_data);
        return 1;
    } else
        return 0; 
}

int data_delall(void)
{
    int i;
    struct data_cfg *cfg = data_cfg_get();

    cfg->magic = DATA_CFG_MAGIC;
    cfg->start_sector = DATA_START_SECTOR;
    cfg->next_sector = DATA_START_SECTOR;
    cfg->total_num = 0;

    for (i = 0; i < DATA_MAX_NUM; i++)
        data_table[i].valid = 0;
    
    data_cfg_save();
    return 0;
}

int data_get(struct result_data *stream, int idx)
{
    struct data_cfg *cfg = data_cfg_get();

    if (idx < cfg->total_num) {
        data_read_flash((uint8_t *)stream, cfg->start_sector + idx, sizeof(struct result_data));
        if (stream->magic != DATA_MAGIC)
            stream->valid = 0;
        return 1;
    }
    return 0;
}

int data_count(void)
{
    struct data_cfg *cfg = data_cfg_get();
    
    return cfg->total_num;
}

int data_indextable_update(struct lb_idx *lbi)
{
    int i;
    int count = 0;
    struct data_ui *du;
    struct data_cfg *cfg = data_cfg_get();

    for (i = cfg->total_num - 1; i >= cfg->next_sector - cfg->start_sector; i--) {
        du = data_ui_get(i);
        if (du && du->valid) {
            lbi->data_idx = i;
            lbi++;
            count++;
        }
    }
    
    for (i = cfg->next_sector - cfg->start_sector - 1; i >= 0; i--) {
        du = data_ui_get(i);
        if (du && du->valid) {
            lbi->data_idx = i;
            lbi++;
            count++;
        }
    }
    return count;
}

int data_init(void)
{
    int data_idx;
    struct data_cfg *cfg = NULL;

    data_cfg_init();
    cfg = data_cfg_get();
    
    for (data_idx = 0; data_idx < cfg->total_num; data_idx++) {
        data_read_flash((uint8_t *)(&res_data), cfg->start_sector + data_idx, sizeof(struct result_data));
        dataui_setup(data_idx, &res_data);
    }
    return 0;
}
