
#ifndef _EASYTEL_H_
#define _EASYTEL_H_
/* Includes */
#include "SimpleDPP/SimpleDPP.h"
#include "BytesUtil/BytesUtil.h"

#define DEBUG

#ifdef DEBUG
// TODO: debug method
#endif

/* Macro definition */
#define CALLBACK_LIST_LENGTH 0xFF

/*Type definition */
typedef void (*EasyTelCmdCallback_C)(const bu_byte *data, bu_uint32 len);

/* Class Structure */
/**
 * EasyTelPoint name rule:
 * etp : pointer of EasyTelPoint
 * etp_o: object of EasyTelPoint
 */
typedef struct
{
    Endian endian;
    bool need_to_change_endian;
    bool found_point;
    EasyTelCmdCallback_C callback_list[CALLBACK_LIST_LENGTH];
    // thread control
    bool close_rev_thread;
    int thread_delay_ms;
    SimpleDPP sdp_o;
} EasyTelPoint, *pEasyTelPoint;

void EasyTel_ThreadDelay(int ms);
void EasyTel_Thread(EasyTelPoint *etp);

void EasyTelPoint_Constructor(EasyTelPoint *etp,sdp_byte *send_buffer,int send_buffer_capacity,sdp_byte *recv_buffer,int recv_buffer_capacity,SimpleDPP_putchar_t SimpleDPP_putchar);
void EsayTelPoint_Destructor(EasyTelPoint *etp);
bool registerCmdCallback(EasyTelPoint *etp, bu_uint8 cmd, EasyTelCmdCallback_C callback);
bool EasyTel_send(EasyTelPoint *etp, bu_byte cmd, const char *data, bu_uint32 len);
void EasyTel_start(EasyTelPoint *etp);
void EasyTel_stop(EasyTelPoint *etp);
bool EasyTel_isRunning(EasyTelPoint *etp);
bool EasyTel_foundPoint(EasyTelPoint *etp);
void EasyTel_AsMaster_FindPeer_Thread(EasyTelPoint *etp);
void EasyTel_AsMaster_FindPeer_ScanMeta(EasyTelPoint *etp);

#endif // _EASYTEL_H_