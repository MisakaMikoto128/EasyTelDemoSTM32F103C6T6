#include "SimpleDPP.h"

static void SimpleDPP_send_buffer(SimpleDPP* sdp);
static void SimpleDPPRecvInnerCallback(SimpleDPP* sdp);
static void SimpleDPPRevErrorInnerCallback(SimpleDPP* sdp,SimpleDPPERROR error_code);

// #define SimpleDPP_ESCAPE_CHAR_LEN 2
// static char SimpleDPP_control_byte_buf[SimpleDPP_ESCAPE_CHAR_LEN] = {0};

/**
 * @brief 
 * 
 * @param sdp : pointer of SimpleDPP object
 * @param send_buffer 
 * @param send_buffer_capacity 
 * @param recv_buffer 
 * @param recv_buffer_capacity 
 * @param SimpleDPPRecvCallback 
 * @param SimpleDPPRevErrorCallback 
 * @param SimpleDPP_putchar : putchar function
 * @param callback_arg : it used to pass a argument to callback function,if it is NULL,it equals to sdp argument.
 */
void SimpleDPP_Constructor(SimpleDPP* sdp,sdp_byte *send_buffer,int send_buffer_capacity,sdp_byte *recv_buffer,int recv_buffer_capacity,SimpleDPPRecvCallback_t SimpleDPPRecvCallback,SimpleDPPRevErrorCallback_t SimpleDPPRevErrorCallback,SimpleDPP_putchar_t SimpleDPP_putchar,void * callback_arg)
{
    byte_buffer_setmemory(&sdp->send_buffer, send_buffer, send_buffer_capacity);
    byte_buffer_setmemory(&sdp->recv_buffer, recv_buffer, recv_buffer_capacity);
    sdp->SimpleDPPErrorCnt = 0;
    sdp->SimpleDPPRevState = SIMPLEDPP_REV_WAIT_START;
    sdp->SimpleDPPRecvCallback = SimpleDPPRecvCallback;
    sdp->SimpleDPPRevErrorCallback = SimpleDPPRevErrorCallback;
    sdp->SimpleDPP_putchar = SimpleDPP_putchar;
    if(callback_arg != NULL)
    {
        sdp->callback_arg = callback_arg;
    }
    else
    {
        sdp->callback_arg = sdp;
    }
}

static void SimpleDPP_send_buffer(SimpleDPP* sdp)
{
    int i;
    if(sdp->SimpleDPP_putchar != NULL)
    {
       for (i = 0; i < sdp->send_buffer.size; i++)
        {
            sdp->SimpleDPP_putchar(sdp->send_buffer.data[i]);
        } 
    }
}

static void SimpleDPPRecvInnerCallback(SimpleDPP* sdp)
{
    if(sdp->SimpleDPPRecvCallback != NULL)
    {
        sdp->SimpleDPPRecvCallback(sdp->callback_arg,sdp->recv_buffer.data,sdp->recv_buffer.size);
    }
    byte_buffer_clear(&sdp->recv_buffer);
}


static void SimpleDPPRevErrorInnerCallback(SimpleDPP* sdp,SimpleDPPERROR error_code)
{
    if(sdp->SimpleDPPRevErrorCallback != NULL)
    {
        sdp->SimpleDPPRevErrorCallback(sdp->callback_arg,error_code);
    }
    byte_buffer_clear(&sdp->recv_buffer);
    sdp->SimpleDPPErrorCnt++;
}

int getSimpleDPPErrorCnt(SimpleDPP* sdp)
{
    return sdp->SimpleDPPErrorCnt;
}

/**
 * @brief must be used before SimpleDPP_send_datas_add() and SimpleDPP_send_datas_end()
 * @return success : the number of bytes in the current buffer
 * fail : SIMPLEDPP_SENDFAILED
 */
int SimpleDPP_send_datas_start(SimpleDPP* sdp)
{
    //1. empty buffer
    byte_buffer_clear(&sdp->send_buffer);
    //2. push SHO
    if (byte_buffer_push(&sdp->send_buffer, SOH) == OVER_CAPACITY_ERROR)
    {
        return SIMPLEDPP_SENDFAILED;
    }
    return byte_buffer_size(&sdp->send_buffer);
}

/**
     * @brief must be used between SimpleDPP_send_datas_start() and SimpleDPP_send_datas_add()
 * @return success : the number of bytes in the current buffer
 * fail : SIMPLEDPP_SENDFAILED
     */
int SimpleDPP_send_datas_add(SimpleDPP* sdp,const sdp_byte *data, int len)
{
    for (int i = 0; i < len; i++)
    {
        //3. push message body,when encounter SOH,EOT or ESC,using ESC escape it.
        if (containSimpleDPPCtrolByte(data[i]))
        {
            // escaped control byte only 2 bytes
            if (byte_buffer_push(&sdp->send_buffer, ESC) == OVER_CAPACITY_ERROR)
            {
                return SIMPLEDPP_SENDFAILED;
            }
            if (byte_buffer_push(&sdp->send_buffer, data[i]) == OVER_CAPACITY_ERROR)
            {
                return SIMPLEDPP_SENDFAILED;
            }
        }
        else
        {
            if (byte_buffer_push(&sdp->send_buffer, data[i]) == OVER_CAPACITY_ERROR)
            {
                return SIMPLEDPP_SENDFAILED;
            }
        }
    }
    return byte_buffer_size(&sdp->send_buffer);
}

/**
 * @brief must be used after SimpleDPP_send_datas_start() and SimpleDPP_send_datas_add()
 * @return success : the number of bytes in the current buffer
 * fail : SIMPLEDPP_SENDFAILED
 */
int SimpleDPP_send_datas_end(SimpleDPP* sdp)
{
    //4. push EOT
    if (byte_buffer_push(&sdp->send_buffer, EOT) == OVER_CAPACITY_ERROR)
    {
        return SIMPLEDPP_SENDFAILED;
    }
    //5. send message
    SimpleDPP_send_buffer(sdp);
    return byte_buffer_size(&sdp->send_buffer);
}


/*
Return:
    success: The number of bytes actually sent
    fail: SIMPLEDPP_SENDFAILED
*/
int SimpleDPP_send(SimpleDPP* sdp,const sdp_byte *data, int len)
{
    int i;
    //1. empty buffer
    byte_buffer_clear(&sdp->send_buffer);
    //2. push SHO
    byte_buffer_push(&sdp->send_buffer, SOH);
    for (i = 0; i < len; i++)
    {
        //3. push message body,when encounter SOH,EOT or ESC,using ESC escape it.
        if (containSimpleDPPCtrolByte(data[i]))
        {
            // escaped control byte only 2 bytes
            if (byte_buffer_push(&sdp->send_buffer, ESC) == OVER_CAPACITY_ERROR)
            {
                return SIMPLEDPP_SENDFAILED;
            }
            if (byte_buffer_push(&sdp->send_buffer, data[i]) == OVER_CAPACITY_ERROR)
            {
                return SIMPLEDPP_SENDFAILED;
            }
        }
        else
        {
            if (byte_buffer_push(&sdp->send_buffer, data[i]) == OVER_CAPACITY_ERROR)
            {
                return SIMPLEDPP_SENDFAILED;
            }
        }
    }
    //4. push EOT
    if (byte_buffer_push(&sdp->send_buffer, EOT) == OVER_CAPACITY_ERROR)
    {
        return SIMPLEDPP_SENDFAILED;
    }
    //5. send message
    SimpleDPP_send_buffer(sdp);
    return len;
}

/**
 * @brief simple dpp send datas,the input datas will be treated as one data.The last parameter should be VAR_ARG_END.
 * @return success: The number of bytes actually sent
 * fail: SIMPLEDPP_SENDFAILED
 * @example __SimpleDPP_send_datas("data1",len1,"data2",len2,"data3",len3,...,VAR_ARG_END);
 */
int __SimpleDPP_send_datas(SimpleDPP* sdp,const sdp_byte *data, int data_len, ...)
{
    va_list args;
    int i;
    SimpleDPP_send_datas_start(sdp);
    //3. push message body,when encounter SOH,EOT or ESC,using ESC escape it.
    va_start(args, data_len);
    while (true)
    {
        for (i = 0; i < data_len; i++)
        {
            //3. push message body,when encounter SOH,EOT or ESC,using ESC escape it.
            if (containSimpleDPPCtrolByte(data[i]))
            {
                // escaped control byte only 2 bytes
                if (byte_buffer_push(&sdp->send_buffer, ESC) == OVER_CAPACITY_ERROR)
                {
                    return SIMPLEDPP_SENDFAILED;
                }
                if (byte_buffer_push(&sdp->send_buffer, data[i]) == OVER_CAPACITY_ERROR)
                {
                    return SIMPLEDPP_SENDFAILED;
                }
            }
            else
            {
                if (byte_buffer_push(&sdp->send_buffer, data[i]) == OVER_CAPACITY_ERROR)
                {
                    return SIMPLEDPP_SENDFAILED;
                }
            }
        }
        data = va_arg(args, const sdp_byte *);
        if (data == VAR_ARG_END)
        {
            break;
        }
        data_len = va_arg(args, int);
    }
    va_end(args);
    return SimpleDPP_send_datas_end(sdp);
}

// SimpleDPP receive state machine's states
void SimpleDPP_parse(SimpleDPP* sdp,sdp_byte c)
{
    switch (sdp->SimpleDPPRevState)
    {
    case SIMPLEDPP_REV_WAIT_START:
        if (c == SOH)
        {
            sdp->SimpleDPPRevState = SIMPLEDPP_REV_WAIT_END;
        }
        break;
    case SIMPLEDPP_REV_WAIT_END:
        switch (c)
        {
        case SOH:
            sdp->SimpleDPPRevState = SIMPLEDPP_REV_WAIT_START;
            SimpleDPPRevErrorInnerCallback(sdp,SIMPLEDPP_ERROR_REV_SOH_WHEN_WAIT_END);
            break;
        case EOT:
            sdp->SimpleDPPRevState = SIMPLEDPP_REV_WAIT_START;
            SimpleDPPRecvInnerCallback(sdp);
            break;
        case ESC:
            sdp->SimpleDPPRevState = SIMPLEDPP_REV_WAIT_CTRL_BYTE;
            break;
        default:
            if (byte_buffer_push(&sdp->recv_buffer, c) == OVER_CAPACITY_ERROR)
            {
                SimpleDPPRevErrorInnerCallback(sdp,SIMPLEDPP_ERROR_REV_OVER_CAPACITY);
            }
            break;
        }
        break;
    case SIMPLEDPP_REV_WAIT_CTRL_BYTE:
        if (containSimpleDPPCtrolByte(c))
        {
            if (byte_buffer_push(&sdp->recv_buffer, c) == OVER_CAPACITY_ERROR)
            {
                SimpleDPPRevErrorInnerCallback(sdp,SIMPLEDPP_ERROR_REV_OVER_CAPACITY);
            }
            sdp->SimpleDPPRevState = SIMPLEDPP_REV_WAIT_END;
        }
        else
        {
            SimpleDPPRevErrorInnerCallback(sdp,SIMPLEDPP_ERROR_REV_NONCTRL_BYTE_WHEN_WAIT_CTRL_BYTE);
        }
        break;
    default:
        break;
    }
}