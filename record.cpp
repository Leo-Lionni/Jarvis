#include "record.h"

Record::Record()
{
}

void Record::run()
{
   QString audioDeviceName = QStringLiteral("audio=麦克风 (Realtek High Definition Audio)");
   AVFormatContext *pFormatCtx = new AVFormatContext;
   AVInputFormat *ifmt = av_find_input_format("dshow");
   if(avformat_open_input(&pFormatCtx,audioDeviceName.toUtf8().data(),ifmt,NULL)!=0){
        fprintf(stderr,"Couldn't open input stream.（无法打开输入流）");
        return;
   }
   int audioindex = -1;
   AVCodecContext *aCodecCtx = NULL;
   for(int i=0; i<pFormatCtx->nb_streams; i++){
       if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO){
            audioindex=i;
            break;
        }
   }
   if(audioindex==-1){
        printf("Didn't find a video stream.（没有找到视频流）");
        return;
   }
   aCodecCtx = pFormatCtx->streams[audioindex]->codec;
   AVCodec *aCodec = avcodec_find_decoder(aCodecCtx->codec_id);
   if(aCodec == NULL){
        printf("audio Codec not found.");
        return;
   }
   if(avcodec_open2(aCodecCtx, aCodec,NULL)<0){
        printf("Could not open video codec.");
        return;
   }
   AVFrame *aFrame = av_frame_alloc();
   int ret, got_frame;
   AVPacket *packet=(AVPacket *)av_malloc(sizeof(AVPacket));
   FILE *fp_pcm=fopen("output.pcm","wb");
   ///这里打印出音频的信息
   qDebug()<<"audio info:";
   qDebug()<<"audio info:"<<aCodecCtx->sample_fmt<<aCodecCtx->bit_rate
          <<aCodecCtx->sample_rate<<aCodecCtx->channels;
   float Time = 0;
   for(int i=0;;i++){
       if (Time > 30) break; //就采集30秒
       if(av_read_frame(pFormatCtx, packet) < 0){
                break;
       }
       if(packet->stream_index==audioindex){
           ret = avcodec_decode_audio4(aCodecCtx, aFrame, &got_frame, packet);
           if(ret < 0){
                    fprintf(stderr,"Audio Error.");
                    return;
           }
           if(got_frame){
               int pcmSize = av_samples_get_buffer_size(NULL,aCodecCtx->channels, aFrame->nb_samples,aCodecCtx->sample_fmt, 1);
               uint8_t * pcmBuffer = aFrame->data[0];
               float useTime = aFrame->nb_samples * 1.0 / aCodecCtx->sample_rate;
               Time += useTime;
               qDebug()<<i<<Time<<useTime;
               fwrite(pcmBuffer,1,pcmSize,fp_pcm); //写入文件
           }
       }
       av_free_packet(packet);
   }
   fclose(fp_pcm);
}
