/*
 * probe.h - constants and on-disk structures for extracting device data
 *
 * Copyright (C) 1999 by Andries Brouwer
 * Copyright (C) 1999, 2000 by Theodore Ts'o
 * Copyright (C) 2001 by Andreas Dilger
 *
 * %Begin-Header%
 * This file may be redistributed under the terms of the
 * GNU Lesser General Public License.
 * %End-Header%
 */

#ifndef _BLKID_PROBE_H
#define _BLKID_PROBE_H

#include <blkid/blkid_types.h>

struct blkid_magic;

typedef int (*blkid_probe_t)(int fd, blkid_dev *dev_p, const char *devname,
			     struct blkid_magic *id, unsigned char *buf,
			     blkid_loff_t size);

struct blkid_magic {
	const char	*bim_type;	/* type name for this magic */
	long		bim_kboff;	/* kilobyte offset of superblock */
	unsigned	bim_sboff;	/* byte offset within superblock */
	unsigned	bim_len;	/* length of magic */
	const char	*bim_magic;	/* magic string */
	unsigned	bim_align;	/* byte alignment of superblock */
	unsigned	bim_kbsize;	/* size of superblock in kilobytes */
	blkid_probe_t	bim_probe;	/* probe function */
};

/*
 * Structures for each of the content types we want to extract information
 * from.  We do not necessarily need the magic field here, because we have
 * already identified the content type before we get this far.  It may still
 * be useful if there are probe functions which handle multiple content types.
 */
struct ext2_super_block {
	__u32		s_inodes_count;
	__u32		s_blocks_count;
	__u32		s_r_blocks_count;
	__u32		s_free_blocks_count;
	__u32		s_free_inodes_count;
	__u32		s_first_data_block;
	__u32		s_log_block_size;
	__u32		s_dummy3[7];
	unsigned char	s_magic[2];
	__u16		s_state;
	__u32		s_dummy5[8];
	__u32		s_feature_compat;
	__u32		s_feature_incompat;
	__u32		s_feature_ro_compat;
	unsigned char   s_uuid[16];
	char	   s_volume_name[16];
};
#define EXT3_FEATURE_COMPAT_HAS_JOURNAL		0x00000004
#define EXT3_FEATURE_INCOMPAT_RECOVER		0x00000004
#define EXT3_FEATURE_INCOMPAT_JOURNAL_DEV	0x00000008

struct xfs_super_block {
	unsigned char	xs_magic[4];
	__u32		xs_blocksize;
	__u64		xs_dblocks;
	__u64		xs_rblocks;
	__u32		xs_dummy1[8];
	unsigned char	xs_uuid[16];
	__u32		xs_dummy2[15];
	char		xs_fname[12];
	__u32		xs_dummy3[2];
	__u64		xs_icount;
	__u64		xs_ifree;
	__u64		xs_fdblocks;
};

struct reiserfs_super_block {
	__u32		rs_blocks_count;
	__u32		rs_free_blocks;
	__u32		rs_root_block;
	__u32		rs_journal_block;
	__u32		rs_journal_dev;
	__u32		rs_orig_journal_size;
	__u32		rs_dummy2[5];
	__u16		rs_blocksize;
	__u16		rs_dummy3[3];
	unsigned char	rs_magic[12];
	__u32		rs_dummy4[5];
	unsigned char	rs_uuid[16];
	char		rs_label[16];
};

/* Yucky misaligned values */
struct vfat_super_block {
/* 00*/	unsigned char	vs_ignored[3];
/* 03*/	unsigned char	vs_sysid[8];
/* 0b*/	unsigned char	vs_sector_size[2];
/* 0d*/	__u8		vs_cluster_size;
/* 0e*/	__u16		vs_reserved;
/* 10*/	__u8		vs_fats;
/* 11*/	unsigned char	vs_dir_entries[2];
/* 13*/	unsigned char	vs_sectors[2];
/* 15*/	unsigned char	vs_media;
/* 16*/	__u16		vs_fat_length;
/* 18*/	__u16		vs_secs_track;
/* 1a*/	__u16		vs_heads;
/* 1c*/	__u32		vs_hidden;
/* 20*/	__u32		vs_total_sect;
/* 24*/	__u32		vs_fat32_length;
/* 28*/	__u16		vs_flags;
/* 2a*/	__u8		vs_version[2];
/* 2c*/	__u32		vs_root_cluster;
/* 30*/	__u16		vs_insfo_sector;
/* 32*/	__u16		vs_backup_boot;
/* 34*/	__u16		vs_reserved2[6];
/* 40*/	unsigned char	vs_unknown[3];
/* 43*/	unsigned char	vs_serno[4];
/* 47*/	char		vs_label[11];
/* 52*/	unsigned char   vs_magic[8];
/* 5a*/	unsigned char	vs_dummy2[164];
/*1fe*/	unsigned char	vs_pmagic[2];
};

/* Yucky misaligned values */
struct msdos_super_block {
/* 00*/	unsigned char	ms_ignored[3];
/* 03*/	unsigned char	ms_sysid[8];
/* 0b*/	unsigned char	ms_sector_size[2];
/* 0d*/	__u8		ms_cluster_size;
/* 0e*/	__u16		ms_reserved;
/* 10*/	__u8		ms_fats;
/* 11*/	unsigned char	ms_dir_entries[2];
/* 13*/	unsigned char	ms_sectors[2];
/* 15*/	unsigned char	ms_media;
/* 16*/	__u16		ms_fat_length;
/* 18*/	__u16		ms_secs_track;
/* 1a*/	__u16		ms_heads;
/* 1c*/	__u32		ms_hidden;
/* 20*/	__u32		ms_total_sect;
/* 24*/	unsigned char	ms_unknown[3];
/* 27*/	unsigned char	ms_serno[4];
/* 2b*/	char		ms_label[11];
/* 36*/	unsigned char   ms_magic[8];
/* 3d*/	unsigned char	ms_dummy2[192];
/*1fe*/	unsigned char	ms_pmagic[2];
};

struct minix_super_block {
	__u16		ms_ninodes;
	__u16		ms_nzones;
	__u16		ms_imap_blocks;
	__u16		ms_zmap_blocks;
	__u16		ms_firstdatazone;
	__u16		ms_log_zone_size;
	__u32		ms_max_size;
	unsigned char	ms_magic[2];
	__u16		ms_state;
	__u32		ms_zones;
};

struct swap_header {
	char		sh_bootbits[1024];
	unsigned int	sh_version;
	unsigned int	sh_last_page;
	unsigned int	sh_nr_badpages;
	char		sh_label[16];
};

struct mdp_superblock_s {
	__u32 md_magic;
	__u32 major_version;
	__u32 minor_version;
	__u32 patch_version;
	__u32 gvalid_words;
	__u32 set_uuid0;
	__u32 ctime;
	__u32 level;
	__u32 size;
	__u32 nr_disks;
	__u32 raid_disks;
	__u32 md_minor;
	__u32 not_persistent;
	__u32 set_uuid1;
	__u32 set_uuid2;
	__u32 set_uuid3;
};

struct hfs_super_block {
	char	h_magic[2];
	char	h_dummy[18];
	__u32	h_blksize;
};

/*
 * Byte swap functions
 */
#ifdef __GNUC__
#define _INLINE_ extern __inline__
#else				/* For Watcom C */
#define _INLINE_ extern inline
#endif

#if ((defined __GNUC__) && \
     (defined(__i386__) || defined(__i486__) || defined(__i586__)))

#define _BLKID_HAVE_ASM_BITOPS_

_INLINE_ __u32 blkid_swab32(__u32 val)
{
#ifdef EXT2FS_REQUIRE_486
	__asm__("bswap %0" : "=r" (val) : "0" (val));
#else
	__asm__("xchgb %b0,%h0\n\t"	/* swap lower bytes	*/
		"rorl $16,%0\n\t"	/* swap words		*/
		"xchgb %b0,%h0"		/* swap higher bytes	*/
		:"=q" (val)
		: "0" (val));
#endif
	return val;
}

_INLINE_ __u16 blkid_swab16(__u16 val)
{
	__asm__("xchgb %b0,%h0"		/* swap bytes		*/ \
		: "=q" (val) \
		:  "0" (val)); \
		return val;
}

_INLINE_ __u64 blkid_swab64(__u64 val)
{
	return (blkid_swab32(val >> 32) |
		(((__u64) blkid_swab32(val & 0xFFFFFFFFUL)) << 32));
}
#endif

#if !defined(_BLKID_HAVE_ASM_BITOPS_)

_INLINE_  __u16 blkid_swab16(__u16 val)
{
	return (val >> 8) | (val << 8);
}

_INLINE_ __u32 blkid_swab32(__u32 val)
{
	return ((val>>24) | ((val>>8)&0xFF00) |
		((val<<8)&0xFF0000) | (val<<24));
}

_INLINE_ u64 blkid_swab64(__u64 val)
{
	return (blkid_swab32(val >> 32) |
		(((__u64) blkid_swab32(val & 0xFFFFFFFFUL)) << 32));
}
#endif 



#if  __BYTE_ORDER == __BIG_ENDIAN
#define blkid_le16(x) blkid_swab16(x)
#define blkid_le32(x) blkid_swab32(x)
#define blkid_le64(x) blkid_swab64(x)
#define blkid_be16(x) (x)
#define blkid_be32(x) (x)
#define blkid_be64(x) (x)
#else
#define blkid_le16(x) (x)
#define blkid_le32(x) (x)
#define blkid_le64(x) (x)
#define blkid_be16(x) blkid_swab16(x)
#define blkid_be32(x) blkid_swab32(x)
#define blkid_be64(x) blkid_swab64(x)
#endif

#endif /* _BLKID_PROBE_H */