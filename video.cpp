#include "video.h"

Video::Video(QString filename)
{
    if(!isValuable()){
        qDebug()<<"The Library is not avaliable";
        return;
    }
    this->filename=filename;
    qDebug()<<this->filename;
}

bool Video::isValuable()
{
    unsigned version = avcodec_version();
    if(version) return true;
    else return false;
}

void Video::run()
{
    const int count=filename.count();
    char url[count];
    QByteArray ba=filename.toLocal8Bit();
    strcpy(url,ba);
    qDebug()<<filename;
    AVFormatContext *pFormatCtx = avformat_alloc_context();
    if(avformat_open_input(&pFormatCtx,url,NULL,NULL)!=0){
        qDebug()<<"can not open the file";
        return;
    }
    if(avformat_find_stream_info(pFormatCtx,NULL)<0){
        qDebug()<<"can not find stream information";
        return;
    }
    int videoStream = -1;
    for(int i=0;i<pFormatCtx->nb_streams;i++){
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
            videoStream = i;
        }
    }
    if(videoStream==-1){
        qDebug()<<"did not find any audio stream";
        return;
    }
    AVCodecContext *pCodecCtx= pFormatCtx->streams[videoStream]->codec;
    AVCodec *pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodecCtx == NULL){
        qDebug()<<"can not find any codec decoder";
        return;
    }
    if(avcodec_open2(pCodecCtx,pCodec,NULL)<0){
        qDebug()<<"can not open codec decoder";
        return;
    }
    AVFrame *pFrame=av_frame_alloc();
    AVFrame *pFrameRGB = av_frame_alloc();
    static struct SwsContext *img_convert_ctx;
    AVPacket *packet;
    uint8_t *out_buffer;
    int numBytes;
    int ret,got_picture;
    img_convert_ctx =sws_getContext(pCodecCtx->width,pCodecCtx->height,
                                    pCodecCtx->pix_fmt,pCodecCtx->width, pCodecCtx->height,
                                    AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);
    numBytes = avpicture_get_size(AV_PIX_FMT_RGB32,pCodecCtx->width,pCodecCtx->height);
    out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *)pFrameRGB,out_buffer,AV_PIX_FMT_RGB32,
                pCodecCtx->width, pCodecCtx->height);
    int y_size = pCodecCtx->width * pCodecCtx->height;

    packet = (AVPacket *) malloc(sizeof(AVPacket)); //分配一个packet
    av_new_packet(packet, y_size); //分配packet的数据

    av_dump_format(pFormatCtx, 0,url, 0); //输出视频信息
    int index = 0;

    while (1){
       if (av_read_frame(pFormatCtx, packet) < 0){
                    break; //这里认为视频读取完了
       }
       if (packet->stream_index == videoStream){
       ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,packet);
       if (ret < 0){
                        printf("decode error.");
                        return;
                    }
                    if (got_picture) {
                        sws_scale(img_convert_ctx,
                                (uint8_t const * const *) pFrame->data,
                                pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                                pFrameRGB->linesize);
                /*
                sws_scale(img_convert_ctx,
                (uint8_t const * const *) pFrame->data,
                pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                pFrameRGB->linesize);*/
                        //SaveFrame(pFrameRGB, pCodecCtx->width,pCodecCtx->height,index++); //保存图片
                        if (index > 50) return; //这里我们就保存50张图片
                    }
                }
       av_free_packet(packet);
    }
    av_free(out_buffer);
    av_free(pFrameRGB);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
}
