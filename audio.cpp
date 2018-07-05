#include "audio.h"

Audio::Audio(QString filename)
{
    if(!isValuable()){
        qDebug()<<"Library is not avaliable";
        return;
    }
    this->filename=filename;
    file.setFileName(this->filename);
}

bool Audio::isValuable()
{
    unsigned version = avcodec_version();
    if(version) return true;
    else return false;
}
/*   * 最简单的基于FFmpeg的音频解码器
     * Simplest FFmpeg Audio Decoder
     * 本程序可以将音频码流（mp3，AAC等）解码为PCM采样数据。
     * 是最简单的FFmpeg音频解码方面的教程。
     * 通过学习本例子可以了解FFmpeg的解码流程。
     *
     * This software decode audio streams (AAC,MP3 ...) to PCM data.
     * Suitable for beginner of FFmpeg.**/
void Audio::decoder()
{
   AVFormatContext	*pFormatCtx;
   int				i, audioStream;
   AVCodecContext	*pCodecCtx;
   AVCodec			*pCodec;
   AVPacket		    *packet;
   uint8_t			*out_buffer;
   AVFrame			*pFrame;
   int              ret;
   //uint32_t len = 0;
   int              got_picture;
   int              index = 0;
   int64_t          in_channel_layout;
   struct SwrContext *au_convert_ctx;
   FILE *pFile=fopen("output.pcm", "wb");
   char url[]="skycity1.mp3";
   avformat_network_init();
   pFormatCtx = avformat_alloc_context();
   //Open
   if(avformat_open_input(&pFormatCtx,url,NULL,NULL)!=0){
       printf("Couldn't open input stream.\n");
       return -1;
   }
   // Retrieve stream information
   if(avformat_find_stream_info(pFormatCtx,NULL)<0){
       printf("Couldn't find stream information.\n");
       return -1;
   }
   // Dump valid information onto standard error
   av_dump_format(pFormatCtx, 0, url, false);
   // Find the first audio stream
   audioStream=-1;
   for(i=0; i < pFormatCtx->nb_streams; i++)
       if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO){
           audioStream=i;
           break;
   }
   if(audioStream == -1){
       printf("Didn't find a audio stream.\n");
       return -1;
   }
   // Get a pointer to the codec context for the audio stream
   pCodecCtx=pFormatCtx->streams[audioStream]->codec;
   // Find the decoder for the audio stream
   pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
   if(pCodec==NULL){
       printf("Codec not found.\n");
       return -1;
   }
   // Open codec
   if(avcodec_open2(pCodecCtx, pCodec,NULL)<0){
       printf("Could not open codec.\n");
       return -1;
   }
   packet=(AVPacket *)av_malloc(sizeof(AVPacket));
   av_init_packet(packet);
   //Out Audio Param
   uint64_t out_channel_layout=AV_CH_LAYOUT_STEREO;
   //nb_samples: AAC-1024 MP3-1152
   int out_nb_samples=pCodecCtx->frame_size;
   AVSampleFormat out_sample_fmt=AV_SAMPLE_FMT_S16;
   int out_sample_rate=44100;
   int out_channels=av_get_channel_layout_nb_channels(out_channel_layout);
   //Out Buffer Size
   int out_buffer_size=av_samples_get_buffer_size(NULL,out_channels
                                                  ,out_nb_samples,out_sample_fmt, 1);
   out_buffer=(uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE*2);
   pFrame=av_frame_alloc();
   //FIX:Some Codec's Context Information is missing
   in_channel_layout=av_get_default_channel_layout(pCodecCtx->channels);
   //Swr
   au_convert_ctx = swr_alloc();
   au_convert_ctx=swr_alloc_set_opts(au_convert_ctx,out_channel_layout, out_sample_fmt, out_sample_rate,
            in_channel_layout,pCodecCtx->sample_fmt , pCodecCtx->sample_rate,0, NULL);
   swr_init(au_convert_ctx);
   while(av_read_frame(pFormatCtx, packet)>=0){
       if(packet->stream_index==audioStream){
           ret = avcodec_decode_audio4( pCodecCtx, pFrame,&got_picture, packet);
           if ( ret < 0 ){
               printf("Error in decoding audio frame.\n");
               return -1;
           }
           if ( got_picture > 0 ){
               swr_convert(au_convert_ctx,&out_buffer, MAX_AUDIO_FRAME_SIZE,
                           (const uint8_t **)pFrame->data , pFrame->nb_samples);
               printf("index:%5d\t pts:%lld\t packet size:%d\n",index,packet->pts,packet->size);
               //Write PCM
               fwrite(out_buffer, 1, out_buffer_size, pFile);
               index++;
           }
       }
       av_free_packet(packet);
   }
   swr_free(&au_convert_ctx);
   fclose(pFile);
   av_free(out_buffer);
   // Close the codec
   avcodec_close(pCodecCtx);
   // Close the video file
   avformat_close_input(&pFormatCtx);
   return 0;
}

/**
 * 最简单的SDL2播放音频的例子（SDL2播放PCM）
 * Simplest Audio Play SDL2 (SDL2 play PCM)
 *
 *
 * 本程序使用SDL2播放PCM音频采样数据。SDL实际上是对底层绘图
 * API（Direct3D，OpenGL）的封装，使用起来明显简单于直接调用底层
 * API。
 *
 * 函数调用步骤如下:
 *
 * [初始化]
 * SDL_Init(): 初始化SDL。
 * SDL_OpenAudio(): 根据参数（存储于SDL_AudioSpec）打开音频设备。
 * SDL_PauseAudio(): 播放音频数据。
 *
 * [循环播放数据]
 * SDL_Delay(): 延时等待播放完成。
 *
 * This software plays PCM raw audio data using SDL2.
 * SDL is a wrapper of low-level API (DirectSound).
 * Use SDL is much easier than directly call these low-level API.
 *
 * The process is shown as follows:
 *
 * [Init]
 * SDL_Init(): Init SDL.
 * SDL_OpenAudio(): Opens the audio device with the desired
 *					parameters (In SDL_AudioSpec).
 * SDL_PauseAudio(): Play Audio.
 *
 * [Loop to play data]
 * SDL_Delay(): Wait for completetion of playback.
 */
bool Audio::encoder(QString input, QString output)
{//Init
   if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER)){
       printf( "Could not initialize SDL - %s\n", SDL_GetError());
       return false;
   }
   //SDL_AudioSpec
   SDL_AudioSpec wanted_spec;
   wanted_spec.freq = 44100;
   wanted_spec.format = AUDIO_S16SYS;
   wanted_spec.channels = 2;
   wanted_spec.silence = 0;
   wanted_spec.samples = 1024;
   wanted_spec.callback = fill_audio;
   if(SDL_OpenAudio(&wanted_spec, NULL)<0){
       printf("can't open audio.\n");
       return -1;
   }
   FILE *fp=fopen("NocturneNo2inEflat_44.1k_s16le.pcm","rb+");
   if(fp==NULL){
       printf("cannot open this file\n");
       return -1;
   }
   int pcm_buffer_size=4096;
   char *pcm_buffer=(char *)malloc(pcm_buffer_size);
   int data_count=0;
   //Play
   SDL_PauseAudio(0);
   while(1){
   if(fread(pcm_buffer, 1, pcm_buffer_size, fp) != pcm_buffer_size){
       // Loop
       fseek(fp, 0, SEEK_SET);
       fread(pcm_buffer, 1, pcm_buffer_size, fp);
       data_count=0;
   }
   printf("Now Playing %10d Bytes data.\n",data_count);
   data_count+=pcm_buffer_size;
   //Set audio buffer (PCM data)
   audio_chunk = (Uint8 *) pcm_buffer;
   //Audio buffer length
   audio_len =pcm_buffer_size;
   audio_pos = audio_chunk;
   while(audio_len>0)//Wait until finish
       SDL_Delay(1);
   }
   free(pcm_buffer);
   SDL_Quit();
   return 0;
}

void Audio::run()
{
}

QStringList Audio::getOutputDevice()
{
    //获取输出音频设备名称
    //QVector<QString> aDeviceListO;
    QStringList aDeviceListO;
    QList<QAudioDeviceInfo> audioDeviceListO =
            QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    foreach (QAudioDeviceInfo devInfo, audioDeviceListO){
       QString strName = devInfo.deviceName();
       if (devInfo.isNull()) continue;
       if (strName[0] == 65533) continue;
       bool bFound = false;
       foreach (QString dev, aDeviceListO){
           if (strName == dev){
               bFound = true;
           }
       }
       if (bFound == true) continue;
       aDeviceListO.push_back(strName);
       qDebug()<<strName;
    }
    return aDeviceListO;
}
