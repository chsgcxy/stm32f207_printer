/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "beep.h"
#include "experiment.h"
#include "main.h"
#include "string.h"
#include "stepmotor.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_TEXT_0 (GUI_ID_USER + 0x01)
#define ID_IMAGE_0 (GUI_ID_USER + 0x02)
#define ID_TEXT_1 (GUI_ID_USER + 0x03)
#define ID_BUTTON_0 (GUI_ID_USER + 0x04)
#define ID_TEXT_2 (GUI_ID_USER + 0x05)
// USER START (Optionally insert additional defines)
// USER END
extern const GUI_FONT GUI_FontHZ_kaiti_20;
extern const GUI_BITMAP bmerror_32px;
extern const GUI_BITMAP bminfor_32px;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    {WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 150, 120, 500, 240, 0, 0x0, 0},
    {TEXT_CreateIndirect, "Text", ID_TEXT_0, 10, 105, 480, 25, 0, 0x64, 0},
    {IMAGE_CreateIndirect, "Image", ID_IMAGE_0, 11, 10, 32, 32, 0, 0, 0},
    {TEXT_CreateIndirect, "Text", ID_TEXT_1, 51, 15, 66, 25, 0, 0x64, 0},
    {TEXT_CreateIndirect, "Text", ID_TEXT_2, 10, 70, 480, 25, 0, 0x64, 0},
    {BUTTON_CreateIndirect, "确认", ID_BUTTON_0, 180, 190, 135, 40, 0, 0x0, 0},
    // USER START (Optionally insert additional widgets)
    // USER END
};

static struct ui_exper_info ginfo;
static struct data_usb_cmd usb_cmd;

extern void uidata_usb_cmd_load(struct data_usb_cmd *cmd);

static void _cbDialog(WM_MESSAGE *pMsg)
{
    WM_HWIN hItem;
    int NCode;
    int Id;
    int status;
    uint32_t res;
    char buf[32];
    float volt;
    // USER START (Optionally insert additional variables)
    // USER END

    switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
        //
        // Initialization of 'Window'
        //
        hItem = pMsg->hWin;
        WINDOW_SetBkColor(hItem, GUI_DARKBLUE);
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
        TEXT_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        TEXT_SetTextColor(hItem, GUI_WHITE);
        switch (ginfo.func) {
        case ERROR_MOTO:
            TEXT_SetText(hItem, "吸液超时，电机或限位开关异常");
            break;
        case ERROR_DATA_LOOKUP:
        case INFO_DATE_SAVE:
        case INFO_DATA_EXPORT:
        case INFO_DATA_EXPROTING:
            TEXT_SetText(hItem, ginfo.str);
            break;
        case INFO_ZSB_CALI:
        case INFO_DJDW_CALC:
            TEXT_SetText(hItem, "校准中,请稍后......");
            break;
        default:
            break;
        }

        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
        TEXT_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        TEXT_SetTextColor(hItem, GUI_WHITE);
        switch (ginfo.func) {
        case ERROR_MOTO:
            TEXT_SetText(hItem, "请检查设备硬件");
            break;
        case ERROR_DATA_LOOKUP:
        case INFO_DATE_SAVE:
        case INFO_DATA_EXPORT:
        case INFO_DATA_EXPROTING:
        case INFO_ZSB_CALI:
        case INFO_DJDW_CALC:
            WM_HideWindow(hItem);
            break;
        default:
            break;
        }
        //
        // Initialization of 'Image'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_0);
        switch (ginfo.func) {
        case ERROR_MOTO:
            IMAGE_SetBitmap(hItem, &bmerror_32px);
            break;
        case ERROR_DATA_LOOKUP:
        case INFO_DATE_SAVE:
        case INFO_DATA_EXPORT:
        case INFO_DATA_EXPROTING:
        case INFO_ZSB_CALI:
        case INFO_DJDW_CALC:
            IMAGE_SetBitmap(hItem, &bminfor_32px);
            break;
        default:
            break;
        }
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
        TEXT_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        TEXT_SetTextColor(hItem, GUI_WHITE);
        switch (ginfo.func) {
        case ERROR_MOTO:
            TEXT_SetText(hItem, "错误");
            break;
        case ERROR_DATA_LOOKUP:
        case INFO_DATE_SAVE:
        case INFO_DATA_EXPORT:
        case INFO_DATA_EXPROTING:
        case INFO_ZSB_CALI:
        case INFO_DJDW_CALC:
            TEXT_SetText(hItem, "信息");
            break;
        default:
            break;
        }        
        //
        // Initialization of 'Button'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
        BUTTON_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        BUTTON_SetTextColor(hItem, 0, GUI_BLUE);
        // USER START (Optionally insert additional code for further widget initialization)
        // USER END
        
        /* funcs */
        switch (ginfo.func) {
        case ERROR_MOTO:
        case ERROR_DATA_LOOKUP:
        case INFO_DATE_SAVE:
        case INFO_DATA_EXPORT:
            break;
        case INFO_ZSB_CALI:
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
            WM_HideWindow(hItem);
            WM_Exec();
            res = stepmotor_calibrate();
            if (res) {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
                TEXT_SetText(hItem, "校准成功!");
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
                WM_ShowWindow(hItem);
                sprintf(buf, "注射泵行程: %.1fmL", ((float)res / 10));
                TEXT_SetText(hItem, buf);
            } else {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
                TEXT_SetText(hItem, "校准失败!");
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
                WM_ShowWindow(hItem);
                TEXT_SetText(hItem, "电机或限位开关异常");
            }
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
            WM_ShowWindow(hItem);
            break;
        case INFO_DJDW_CALC:
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
            WM_HideWindow(hItem);
            WM_Exec();
            volt = djdw_calc();
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
            TEXT_SetText(hItem, "校准成功!");
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
            WM_ShowWindow(hItem);
            sprintf(buf, "电极电位校准值: %.3f", volt);
            TEXT_SetText(hItem, buf);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
            WM_ShowWindow(hItem);
            break;
        case INFO_DATA_EXPROTING:
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
            WM_HideWindow(hItem);
            WM_Exec();
            data_usb_detect();
            status = usb_wait_ready(4000);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
            if (status) {
                TEXT_SetText(hItem, "U盘检测成功，正在导出......");
                WM_Exec();
            } else {
                TEXT_SetText(hItem, "U盘检测失败，请确认U盘插入......");
                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
                WM_ShowWindow(hItem);
                WM_Exec();
                break;
            }

            usb_cmd.cmd = USB_MKDIR;
            usb_cmd_set(&usb_cmd);
            status = usb_wait_ready(2000);
            if (!status) {
                TEXT_SetText(hItem, "创建目录失败，请确认U盘状态......");
                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
                WM_ShowWindow(hItem);
                WM_Exec();
                break;
            }

            uidata_usb_cmd_load(&usb_cmd);
            usb_cmd_set(&usb_cmd);
            status = usb_wait_ready(4000);
            if (status)
                TEXT_SetText(hItem, "导出成功!");
            else
                TEXT_SetText(hItem, "导出失败，请确认U盘状态......");
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
            WM_ShowWindow(hItem);
            usb_cmd.cmd = USB_QUIT;
            usb_cmd_set(&usb_cmd);
            break;
        default:
            break;
        }
        break;
    case WM_NOTIFY_PARENT:
        Id = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch (Id)
        {
        case ID_BUTTON_0: // Notifications sent by 'Button'
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                beep_clicked();
                GUI_EndDialog(pMsg->hWin, 0);
                // USER END
                break;
            case WM_NOTIFICATION_RELEASED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
                // USER START (Optionally insert additional code for further notification handling)
                // USER END
            }
            break;
            // USER START (Optionally insert additional code for further Ids)
            // USER END
        }
        break;
    // USER START (Optionally insert additional message handling)
    // USER END
    default:
        WM_DefaultProc(pMsg);
        break;
    }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/
int diag_err_creat(struct ui_exper_info *info)
{
    memcpy(&ginfo, info, sizeof(struct ui_exper_info));
    return GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
