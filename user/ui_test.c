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
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "main.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_TEXT_0 (GUI_ID_USER + 0x01)
#define ID_TEXT_1 (GUI_ID_USER + 0x02)
#define ID_TEXT_2 (GUI_ID_USER + 0x03)
#define ID_TEXT_3 (GUI_ID_USER + 0x04)
#define ID_TEXT_4 (GUI_ID_USER + 0x05)
#define ID_TEXT_5 (GUI_ID_USER + 0x06)
#define ID_TEXT_6 (GUI_ID_USER + 0x07)
#define ID_TEXT_7 (GUI_ID_USER + 0x08)

#define ID_BUTTON_GET (GUI_ID_USER + 0x09)
#define ID_BUTTON_PUT (GUI_ID_USER + 0x0A)
#define ID_BUTTON_RETURN (GUI_ID_USER + 0x0B)
#define ID_PROGBAR_0 (GUI_ID_USER + 0x0C)

// USER START (Optionally insert additional defines)
extern const GUI_FONT GUI_FontHZ_Consolas;
extern const GUI_FONT GUI_FontHZ_Arial;
// USER END

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
    {TEXT_CreateIndirect, "Text", ID_TEXT_0, 43, 32, 141, 33, 0, 0x64, 0},
    {TEXT_CreateIndirect, "Text", ID_TEXT_1, 32, 87, 155, 34, 0, 0x64, 0},
    {TEXT_CreateIndirect, "Text", ID_TEXT_2, 34, 147, 136, 31, 0, 0x64, 0},
    {TEXT_CreateIndirect, "Text", ID_TEXT_3, 37, 208, 137, 33, 0, 0x64, 0},
    {TEXT_CreateIndirect, "Text", ID_TEXT_4, 40, 267, 133, 33, 0, 0x64, 0},
    {TEXT_CreateIndirect, "Text", ID_TEXT_5, 210, 36, 97, 32, 0, 0x64, 0},
    {TEXT_CreateIndirect, "Text", ID_TEXT_6, 338, 33, 35, 36, 0, 0x64, 0},
    {TEXT_CreateIndirect, "Text", ID_TEXT_7, 530, 25, 130, 35, 0, 0x64, 0},
    // USER START (Optionally insert additional widgets)
    {BUTTON_CreateIndirect, "Button", ID_BUTTON_GET, 639, 103, 140, 40, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "Button", ID_BUTTON_PUT, 638, 189, 140, 40, 0, 0x0, 0},
    {BUTTON_CreateIndirect, "Button", ID_BUTTON_RETURN, 632, 370, 140, 40, 0, 0x0, 0},
    {PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 640, 17, 140, 40, 0, 0x0, 0},
    // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE *pMsg)
{
    WM_HWIN hItem;
    // USER START (Optionally insert additional variables)
    int Id, i, NCode;
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
        FRAMEWIN_SetFont(hItem, &GUI_FontHZ_Arial);
        FRAMEWIN_SetText(hItem, "�����Ӽ��");
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
        TEXT_SetFont(hItem, &GUI_FontHZ_Consolas);
        TEXT_SetTextColor(hItem, GUI_WHITE);
        TEXT_SetText(hItem, "ˮ������");
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
        TEXT_SetFont(hItem, &GUI_FontHZ_Consolas);
        TEXT_SetTextColor(hItem, GUI_WHITE);
        TEXT_SetText(hItem, "AgNO3Ũ��");
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
        TEXT_SetFont(hItem, &GUI_FontHZ_Consolas);
        TEXT_SetTextColor(hItem, GUI_WHITE);
        TEXT_SetText(hItem, "AgNO3����");
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
        TEXT_SetFont(hItem, &GUI_FontHZ_Consolas);
        TEXT_SetTextColor(hItem, GUI_WHITE);
        TEXT_SetText(hItem, "������Ũ��");
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
        TEXT_SetFont(hItem, &GUI_FontHZ_Consolas);
        TEXT_SetTextColor(hItem, GUI_WHITE);
        TEXT_SetText(hItem, "�缫��λ");
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
        TEXT_SetText(hItem, "5.000");
        TEXT_SetTextColor(hItem, GUI_WHITE);
        TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
        TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
        TEXT_SetTextColor(hItem, GUI_WHITE);
        TEXT_SetText(hItem, "g");
        // USER START (Optionally insert additional code for further widget initialization)
        //
        // Initialization of 'Button'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_GET);
        BUTTON_SetFont(hItem, &GUI_FontHZ_Consolas);
        BUTTON_SetTextColor(hItem, 0, GUI_BLUE);
        BUTTON_SetText(hItem, "��Һ");
        //
        // Initialization of 'Button'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_PUT);
        BUTTON_SetFont(hItem, &GUI_FontHZ_Consolas);
        BUTTON_SetTextColor(hItem, 0, GUI_BLUE);
        BUTTON_SetText(hItem, "��Һ");
        //
        // Initialization of 'Button'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_RETURN);
        BUTTON_SetFont(hItem, &GUI_FontHZ_Consolas);
        BUTTON_SetTextColor(hItem, 0, GUI_BLUE);
        BUTTON_SetText(hItem, "����");

        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
        TEXT_SetFont(hItem, &GUI_FontHZ_Consolas);
        TEXT_SetTextColor(hItem, GUI_WHITE);
        TEXT_SetText(hItem, "��Һ����");

        hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
        PROGBAR_SetFont(hItem, GUI_FONT_24B_ASCII);
        PROGBAR_SetMinMax(hItem, 0, 100);
        // USER END
        break;
    // USER START (Optionally insert additional message handling)
    case WM_NOTIFY_PARENT:
        Id = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch (Id) {
        case ID_BUTTON_GET: // Notifications sent by 'Button'
            switch (NCode) {
            case WM_NOTIFICATION_CLICKED:
                hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
                for (i = 0; i <= 100; i++) {
                    PROGBAR_SetValue(hItem, i);
                    WM_Exec();
                    vTaskDelay(50);
                }
                break;
            case WM_NOTIFICATION_RELEASED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
                // USER START (Optionally insert additional code for further notification handling)
                // USER END
            }
            break;
        case ID_BUTTON_PUT: // Notifications sent by 'Button'
            switch (NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
                for (i = 100; i >= 0; i--) {
                    PROGBAR_SetValue(hItem, i);
                    WM_Exec();
                    vTaskDelay(50);
                }
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
                printf("run main menu\r\n");
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
        }
        break;
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

WM_HWIN ui_test_creat(void)
{
    g_ui_msg.hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
    GUI_ExecCreatedDialog(g_ui_msg.hWin);
    return g_ui_msg.hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/