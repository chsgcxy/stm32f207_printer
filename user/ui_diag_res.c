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
#include "main.h"
#include "beep.h"
#include "string.h"
#include "experiment.h"
#include "report.h"
#include "stdio.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0          (GUI_ID_USER + 0x00)
#define ID_TEXT_0            (GUI_ID_USER + 0x01)
#define ID_TEXT_1            (GUI_ID_USER + 0x03)
#define ID_TEXT_2            (GUI_ID_USER + 0x04)
#define ID_TEXT_3            (GUI_ID_USER + 0x05)
#define ID_TEXT_4            (GUI_ID_USER + 0x06)
#define ID_BUTTON_0          (GUI_ID_USER + 0x07)
#define ID_BUTTON_1          (GUI_ID_USER + 0x08)
#define ID_BUTTON_2          (GUI_ID_USER + 0x09)
#define ID_TEXT_PPM          (GUI_ID_USER + 0x0A)
#define ID_TEXT_PPM_VALUE    (GUI_ID_USER + 0x0B)
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
extern const GUI_FONT GUI_FontHZ_kaiti_20;
// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    {WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 151, 119, 500, 240, 0, 0x0, 0},
    {TEXT_CreateIndirect, "实验结果", ID_TEXT_0, 182, 12, 133, 25, 0, 0x64, 0},
    
    {TEXT_CreateIndirect, "Text", ID_TEXT_1, 10, 60, 250, 25, 0, 0x64, 0},
    {TEXT_CreateIndirect, "Text", ID_TEXT_2, 275, 60, 150, 25, 0, 0x64, 0},
    
    {TEXT_CreateIndirect, "Text", ID_TEXT_3, 10, 100, 250, 25, 0, 0x64, 0},
    {TEXT_CreateIndirect, "Text", ID_TEXT_4, 275, 100, 150, 25, 0, 0x64, 0},
    
    {TEXT_CreateIndirect, "PPM", ID_TEXT_PPM, 10, 140, 250, 25, 0, 0x64, 0},
    {TEXT_CreateIndirect, "0.02mol/L", ID_TEXT_PPM_VALUE, 275, 140, 150, 25, 0, 0x64, 0},

    {BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 10, 190, 120, 40, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 187, 190, 120, 40, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 368, 190, 120, 40, 0, 0x0, 0},
    // USER START (Optionally insert additional widgets)
    // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
static struct ui_exper_res exper_res;
// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE *pMsg)
{
    WM_HWIN hItem;
    int NCode;
    int Id;
    char buf[16];
    struct report *rep;
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
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
        TEXT_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
        TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00FFFFFF));
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
        TEXT_SetText(hItem, "AgNO3用量");
        TEXT_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00FFFFFF));
        //
        // Initialization of 'Text'
        //
        sprintf(buf, "%.2fmL", exper_res.agno3_used);
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
        TEXT_SetFont(hItem, GUI_FONT_24_1);
        TEXT_SetText(hItem, buf);
        TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00FFFFFF));
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
        TEXT_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00FFFFFF));
        switch (exper_res.func) {
        case EXPER_STAT_AGNO3_FINISHED:
            TEXT_SetText(hItem, "AgNO3浓度");
            break;
        case EXPER_STAT_BLOCK_FINISHED:
            WM_HideWindow(hItem);
            break;
        case EXPER_STAT_CL_FINISHED:
            TEXT_SetText(hItem, "水泥氯离子质量分数");
            break;
        case EXPER_STAT_STAND_FINISHED:
            TEXT_SetText(hItem, "氯离子浓度");
            break;
        default:
            break;
        }
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
        TEXT_SetFont(hItem, GUI_FONT_24_1);
        TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00FFFFFF));
        switch (exper_res.func) {
        case EXPER_STAT_AGNO3_FINISHED:
            sprintf(buf, "%.3fmol/L", exper_res.res);
            TEXT_SetText(hItem, buf);
            break;
        case EXPER_STAT_BLOCK_FINISHED:
            WM_HideWindow(hItem);
            break;
        case EXPER_STAT_CL_FINISHED:
            sprintf(buf, "%.3f%%", exper_res.res);
            TEXT_SetText(hItem, buf);
            break;
        case EXPER_STAT_STAND_FINISHED:
            sprintf(buf, "%.3fmol/L", exper_res.res);
            TEXT_SetText(hItem, buf);
            break;
        default:
            break;
        }

        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_PPM);
        switch (exper_res.func) {
        case EXPER_STAT_AGNO3_FINISHED:
        case EXPER_STAT_BLOCK_FINISHED:
        case EXPER_STAT_CL_FINISHED:
            WM_HideWindow(hItem);
            break;
        case EXPER_STAT_STAND_FINISHED:
            TEXT_SetFont(hItem, GUI_FONT_24_1);
            TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00FFFFFF));
            break;
        default:
            break;
        }

        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_PPM_VALUE);
        switch (exper_res.func) {
        case EXPER_STAT_AGNO3_FINISHED:
        case EXPER_STAT_BLOCK_FINISHED:
        case EXPER_STAT_CL_FINISHED:
            WM_HideWindow(hItem);
            break;
        case EXPER_STAT_STAND_FINISHED:
            TEXT_SetFont(hItem, GUI_FONT_24_1);
            TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00FFFFFF));
            sprintf(buf, "%.1f", exper_res.res2);
            TEXT_SetText(hItem, buf);
            break;
        default:
            break;
        }

        //
        // Initialization of 'Button'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
        BUTTON_SetTextColor(hItem, 0, GUI_BLUE);
        switch (exper_res.func) {
        case EXPER_STAT_AGNO3_FINISHED:
        case EXPER_STAT_BLOCK_FINISHED:
            WM_HideWindow(hItem);
            break;
        case EXPER_STAT_CL_FINISHED:
        case EXPER_STAT_STAND_FINISHED:
            BUTTON_SetFont(hItem, &GUI_FontHZ_kaiti_20);
            BUTTON_SetText(hItem, "打印");
            break;
        default:
            break;
        }
        //
        // Initialization of 'Button'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
        BUTTON_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        BUTTON_SetTextColor(hItem, 0, GUI_BLUE);
        switch (exper_res.func) {
        case EXPER_STAT_AGNO3_FINISHED:
        case EXPER_STAT_BLOCK_FINISHED:
            BUTTON_SetText(hItem, "确定");
            break;
        case EXPER_STAT_CL_FINISHED:
        case EXPER_STAT_STAND_FINISHED:
            BUTTON_SetText(hItem, "U盘导出");
            break;
        default:
            break;
        }
        //
        // Initialization of 'Button'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
        BUTTON_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        BUTTON_SetTextColor(hItem, 0, GUI_BLUE);
        switch (exper_res.func) {
        case EXPER_STAT_AGNO3_FINISHED:
        case EXPER_STAT_BLOCK_FINISHED:
            WM_HideWindow(hItem);
            break;
        case EXPER_STAT_CL_FINISHED:
        case EXPER_STAT_STAND_FINISHED:
            BUTTON_SetText(hItem, "保存返回");
            break;
        default:
            break;
        }
        // USER START (Optionally insert additional code for further widget initialization)
        // USER END
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
                rep = exper_get_report();
                report_show(rep);
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
        case ID_BUTTON_1: // Notifications sent by 'Button'
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                beep_clicked();
                // USER START (Optionally insert code for reacting on notification message)
                switch (exper_res.func) {
                case EXPER_STAT_AGNO3_FINISHED:
                case EXPER_STAT_BLOCK_FINISHED:
                    GUI_EndDialog(pMsg->hWin, 0);
                    break;
                case EXPER_STAT_CL_FINISHED:
                case EXPER_STAT_STAND_FINISHED:
                    // to be continued, save to usb
                    break;
                default:
                    break;
                }
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
        case ID_BUTTON_2: // Notifications sent by 'Button'
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                beep_clicked();
                GUI_EndDialog(pMsg->hWin, 0);
                // USER START (Optionally insert code for reacting on notification message)
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
int diag_res_creat(struct ui_exper_res *res)
{
    memcpy(&exper_res, res, sizeof(struct ui_exper_res));
    return GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
