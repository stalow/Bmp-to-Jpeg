#include <stdio.h>
#include <stdlib.h>


#include "cjpeg.h"
#include "cio.h"

int main()
{
        /* open bmp file */
        FILE *bmp_fp = fopen("image24.bmp", "rb");
        if (!bmp_fp)
            err_exit(FILE_OPEN_ERR);
        if (!is_bmp(bmp_fp))
            err_exit(FILE_TYPE_ERR);

        /* open jpeg file */
        FILE *jpeg_fp = fopen("sorie.jpeg", "wb");
        if (!jpeg_fp)
            err_exit(FILE_OPEN_ERR);

        /* get bmp info */
        bmp_info binfo;
        read_bmp(bmp_fp, &binfo);

        /* init memory for input and output */
        compress_io cio;
        int in_size = (binfo.width * 3 + 3) / 4 * 4 * DCTSIZE;
        int out_size = MEM_OUT_SIZE;
        init_mem(&cio, bmp_fp, in_size, jpeg_fp, out_size);

        /* main encode process */
        jpeg_encode(&cio, &binfo);

        /* flush and free memory, close files */
        if (! (cio.out->flush_buffer) (&cio))
            err_exit(BUFFER_WRITE_ERR);
        free_mem(&cio);
        fclose(bmp_fp);
        fclose(jpeg_fp);
}
