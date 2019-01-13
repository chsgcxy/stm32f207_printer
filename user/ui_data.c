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
#include "stdio.h"
#include "main.h"
#include "beep.h"
#include "data.h"
#include "experiment.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0       (GUI_ID_USER + 0x00)
#define ID_LISTBOX_0        (GUI_ID_USER + 0x01)
#define ID_BUTTON_LOOK      (GUI_ID_USER + 0x02)
#define ID_BUTTON_DEL       (GUI_ID_USER + 0x03)
#define ID_BUTTON_EXP       (GUI_ID_USER + 0x04)
#define ID_BUTTON_RETURN    (GUI_ID_USER + 0x05)
#define ID_BUTTON_EXPALL    (GUI_ID_USER + 0x06)
#define ID_BUTTON_DELALL    (GUI_ID_USER + 0x07)

// USER START (Optionally insert additional defines)
extern const GUI_FONT GUI_FontHZ_kaiti_28;
extern const GUI_FONT GUI_FontHZ_kaiti_20;
// USER END
extern int diag_info_creat(struct ui_exper_info *info);
extern int diag_err_creat(struct ui_exper_info *info);
/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    {FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0},
    
    {LISTBOX_CreateIndirect, "Listbox", ID_LISTBOX_0, 5, 5, 380, 415, 0, 0x0, 0},

    {BUTTON_CreateIndirect, "查看", ID_BUTTON_LOOK, 430, 30, 140, 60, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "返回", ID_BUTTON_RETURN, 640, 30, 140, 60, 0, 0x0, 0},

    {BUTTON_CreateIndirect, "删除", ID_BUTTON_DEL, 430, 180, 140, 60, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "全部删除", ID_BUTTON_DELALL, 640, 180, 140, 60, 0, 0x0, 0},
    
    {BUTTON_CreateIndirect, "导出", ID_BUTTON_EXP, 430, 330, 140, 60, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "全部导出", ID_BUTTON_EXPALL, 640, 330, 140, 60, 0, 0x0, 0},
    // USER START (Optionally insert additional widgets)
    // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
static struct lb_idx idx_table[DATA_MAX_NUM];
static struct ui_exper_info ginfo;
static int count = 0;
// USER START (Optionally insert additional static code)
// USER END

static void ctrl_all_items(WM_HWIN hWin, int enable)
{
    WM_HWIN hItem;
    int id;

    for (id = ID_LISTBOX_0; id <= ID_BUTTON_DELALL; id++) {
        hItem = WM_GetDialogItem(hWin, id);
        if (enable)
            WM_EnableWindow(hItem);
        else
            WM_DisableWindow(hItem);
    }    
}
/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE *pMsg)
{
    WM_HWIN hItem;
    int NCode;
    int Id;
    int i;
    struct data_ui *du;
    // USER START (Optionally insert additional variables)
    // USER END

    switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
        //
        // Initialization of 'Framewin'
        //
        hItem = pMsg->hWin;
        FRAMEWIN_SetTitleHeight(hItem, 50);
        FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
        FRAMEWIN_SetTextColor(hItem, GUI_BLUE);
        FRAMEWIN_SetClientColor(hItem, GUI_GRAY);
        FRAMEWIN_SetText(hItem, "数据处理");
        FRAMEWIN_SetFont(hItem, &GUI_FontHZ_kaiti_28);
        //
        // Initialization of 'Listbox'
        //
        //
        // Initialization of 'Button'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_LOOK);
        BUTTON_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        BUTTON_SetTextColor(hItem, 0, GUI_BLUE);
        //
        // Initialization of 'Button'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_DEL);
        BUTTON_SetTextColor(hItem, 0, GUI_BLUE);
        BUTTON_SetFont(hItem, &GUI_FontHZ_kaiti_20);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_DELALL);
        BUTTON_SetTextColor(hItem, 0, GUI_BLUE);
        BUTTON_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        //
        // Initialization of 'Button'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_EXP);
        BUTTON_SetTextColor(hItem, 0, GUI_BLUE);
        BUTTON_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        //
        // Initialization of 'Button'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_RETURN);
        BUTTON_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        BUTTON_SetTextColor(hItem, 0, GUI_RED);
        //
        // Initialization of 'Button'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_EXPALL);
        BUTTON_SetFont(hItem, &GUI_FontHZ_kaiti_20);
        BUTTON_SetTextColor(hItem, 0, GUI_BLUE);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
        LISTBOX_SetFont(hItem, GUI_FONT_32_ASCII);
        LISTBOX_SetAutoScrollV(hItem, 1);
        LISTBOX_SetScrollbarWidth(hItem, 30);

        count = data_indextable_update(idx_table);
        for (i = 0; i < count; i++) {
            du = data_ui_get(idx_table[i].data_idx);
            if (du) {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
                LISTBOX_AddString(hItem, du->string);
            }
        }
        // USER START (Optionally insert additional code for further widget initialization)
        // USER END
        break;
    case WM_NOTIFY_PARENT:
        Id = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch (Id)
        {
        case ID_LISTBOX_0: // Notifications sent by 'Listbox'
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
            case WM_NOTIFICATION_RELEASED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
            case WM_NOTIFICATION_SEL_CHANGED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
                // USER START (Optionally insert additional code for further notification handling)
                // USER END
            }
            break;
        case ID_BUTTON_LOOK: // Notifications sent by 'Button'
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                beep_clicked();
                hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
                i = LISTBOX_GetSel(hItem);
                if (i < count) {
                    g_ui_msg.param0 = idx_table[i].data_idx;
                    g_ui_msg.msg = MSG_LOAD_UI_DETAIL;
                    GUI_EndDialog(pMsg->hWin, 0);
                } else if (count == 0) {
                    ctrl_all_items(pMsg->hWin, 0);
                    WM_DisableWindow(pMsg->hWin);
                    WM_Exec();
                    ginfo.func = ERROR_DATA_LOOKUP;
                    ginfo.flag = 0;
                    ginfo.str = "没有可查看数据";
                    diag_err_creat(&ginfo);
                    WM_EnableWindow(pMsg->hWin);
                    ctrl_all_items(pMsg->hWin, 1);
                } else {
                    ctrl_all_items(pMsg->hWin, 0);
                    WM_DisableWindow(pMsg->hWin);
                    WM_Exec();
                    ginfo.func = ERROR_DATA_LOOKUP;
                    ginfo.flag = 0;
                    ginfo.str = "系统异常,找不到对应数据";
                    diag_err_creat(&ginfo);
                    WM_EnableWindow(pMsg->hWin);
                    ctrl_all_items(pMsg->hWin, 1);
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
        case ID_BUTTON_DEL: // Notifications sent by 'Button'
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                beep_clicked();
                hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
                
                i = LISTBOX_GetSel(hItem);
                if (count == 0) {
                    ctrl_all_items(pMsg->hWin, 0);
                    WM_DisableWindow(pMsg->hWin);
                    WM_Exec();
                    ginfo.func = ERROR_DATA_LOOKUP;
                    ginfo.flag = 0;
                    ginfo.str = "没有可删除数据";
                    diag_err_creat(&ginfo);
                    WM_EnableWindow(pMsg->hWin);
                    ctrl_all_items(pMsg->hWin, 1);
                    break;
                } else if (i >= count) {
                    ctrl_all_items(pMsg->hWin, 0);
                    WM_DisableWindow(pMsg->hWin);
                    WM_Exec();
                    ginfo.func = ERROR_DATA_LOOKUP;
                    ginfo.flag = 0;
                    ginfo.str = "系统异常,找不到对应数据";
                    diag_err_creat(&ginfo);
                    WM_EnableWindow(pMsg->hWin);
                    ctrl_all_items(pMsg->hWin, 1);
                    break;
                }

                du = data_ui_get(idx_table[i].data_idx);
                if (du) {
                    ginfo.func = DATA_MSG_DEL;
                    ginfo.flag = 0;
                    ginfo.str = du->string;
                } else
                    break;

                ctrl_all_items(pMsg->hWin, 0);
                WM_DisableWindow(pMsg->hWin);
                WM_Exec();
                if (diag_info_creat(&ginfo)) {
                    ctrl_all_items(pMsg->hWin, 1);
                    break;
                }
                WM_EnableWindow(pMsg->hWin);
                ctrl_all_items(pMsg->hWin, 1);
                /* I don't know why LISTBOX_DeleteItem can not work
                 * so, reload this windows to runaway this bug
                 */
                if (data_del(idx_table[i].data_idx)) {
                    g_ui_msg.msg = MSG_LOAD_UI_DATA;
                    GUI_EndDialog(pMsg->hWin, 0);
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
        case ID_BUTTON_DELALL: // Notifications sent by 'Button'
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                beep_clicked();

                if (count == 0) {
                    ctrl_all_items(pMsg->hWin, 0);
                    WM_DisableWindow(pMsg->hWin);
                    WM_Exec();
                    ginfo.func = ERROR_DATA_LOOKUP;
                    ginfo.flag = 0;
                    ginfo.str = "没有可删除数据";
                    diag_err_creat(&ginfo);
                    WM_EnableWindow(pMsg->hWin);
                    ctrl_all_items(pMsg->hWin, 1);
                    break;
                }

                ginfo.func = DATA_MSG_DEL_ALL;
                ginfo.flag = 0;
                ctrl_all_items(pMsg->hWin, 0);
                WM_DisableWindow(pMsg->hWin);
                WM_Exec();
                if (diag_info_creat(&ginfo)) {
                    ctrl_all_items(pMsg->hWin, 1);
                    break;
                }
                WM_EnableWindow(pMsg->hWin);
                ctrl_all_items(pMsg->hWin, 1);
                
                data_delall();
                
                /* I don't know why LISTBOX_DeleteItem can not work
                 * so, reload this windows to runaway this bug
                 */
                g_ui_msg.msg = MSG_LOAD_UI_DATA;
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
        case ID_BUTTON_EXP: // Notifications sent by 'Button'
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                beep_clicked();
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
        case ID_BUTTON_RETURN: // Notifications sent by 'Button'
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                beep_clicked();
                g_ui_msg.msg = MSG_LOAD_UI_MENU;
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
        case ID_BUTTON_EXPALL: // Notifications sent by 'Button'
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                beep_clicked();
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
*       CreateFramewin
*/

int ui_data_creat(void)
{
    return GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
