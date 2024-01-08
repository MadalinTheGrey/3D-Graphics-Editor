#pragma once
#include "Button.h"
#include "ButtonManager.h"
#include "EditObject.h"
using namespace std;
void checkMouseClick(int x, int y) {
    bool is_button = false;
    //pasul la care este user-ul in desenarea unei forme simple (0 = neapelat/terminat, 1 = pozitionat primul punct)
    static int form_draw_step = 0;
    for (auto& button : buttons)
        if (x >= button.x1 && x <= button.x2 && y >= button.y1 && y <= button.y2)
        {
            is_button = true;
            button.onClick();
        }
    if (!is_button)
    {
        if (2 <= last_clicked_button && last_clicked_button <= 6)
        {
            int c; //ultima cifra a pozitiei mouse-ului pe ecran
            x -= vp_tl_x; y -= vp_tl_y;
            if (draw_precision == 5)
            {
                c = x % 10;
                if (c > 5) c -= 5;
                if (c >= 3) x += (5 - c);
                else x -= c;
                c = y % 10;
                if (c > 5) c -= 5;
                if (c >= 3) y += (5 - c);
                else y -= c;
            }
            else if (draw_precision == 10)
            {
                c = x % 10;
                if (c > 5) x += (10 - c);
                else x -= c;
                c = y % 10;
                if (c > 5) y += (10 - c);
                else y -= c;
            }
            if (buttons[last_clicked_button].name == "Draw Line" && S.corpuri_selectate.size() == 1)
            {
                int i = S.corpuri_selectate[0];
                S.UserDrawLine(x, y, form_draw_step, selectedStrat, i);
                form_draw_step = 1 - form_draw_step;
            }
            else if (buttons[last_clicked_button].name == "Draw rectangle" && S.corpuri_selectate.size() == 1)
            {
                int i = S.corpuri_selectate[0];
                S.UserDrawRectangle(x, y, form_draw_step, selectedStrat, i);
                form_draw_step = 1 - form_draw_step;
            }
            else if (buttons[last_clicked_button].name == "Draw circle" && S.corpuri_selectate.size() == 1)
            {
                int i = S.corpuri_selectate[0];
                S.UserDrawCircle(x, y, form_draw_step, selectedStrat, i);
                form_draw_step = 1 - form_draw_step;
            }
            else if (buttons[last_clicked_button].name == "Add point" && S.corpuri_selectate.size() == 1)
            {
                int i = S.corpuri_selectate[0];
                S.UserAddPoint(x, y, selectedStrat, i);
            }
            else if (buttons[last_clicked_button].name == "Link points" && S.corpuri_selectate.size() == 1)
            {
                int i = S.corpuri_selectate[0];
                S.UserLinkPoints(x, y, form_draw_step, i);
                form_draw_step = 1 - form_draw_step;
            }
        }
        else
        {
            S.ChangeSelected(x, y);
        }
        if (form_draw_step == 0 && last_clicked_button != 0)
        {
            setviewport(0, 0, getmaxx(), getmaxy(), 0);
            drawLine(buttons[last_clicked_button].x1, buttons[last_clicked_button].y1, buttons[last_clicked_button].x2, buttons[last_clicked_button].y1, COLOR(118, 118, 118), 1);
            drawLine(buttons[last_clicked_button].x1, buttons[last_clicked_button].y2, buttons[last_clicked_button].x2, buttons[last_clicked_button].y2, COLOR(118, 118, 118), 1);
            setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
            last_clicked_button = 0;
        }
    }
    if (S.corpuri_selectate.size() == 1 && !editButtonSelectable && !editMode) {
        setviewport(0, 0, 1280, 720, 1);
        buttons[18].drawButton();
        setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
        setbkcolor(BLACK);
    }
    else if(S.corpuri_selectate.size() != 1 && editButtonSelectable && !editMode) {
        setviewport(0, 0, 1280, 720, 1);
        buttons[18].drawButtonDif();
        setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
        setbkcolor(BLACK);
    }
    if (editMode && S.corpuri_selectate.size() == 1) {
        for (auto& btn : strats) {
            if (x > btn.x1 && x < btn.x2 && y > btn.y1 && y < btn.y2) {
                btn.onClick();
            }
        }
        for (auto& btn : menuStratsButtons) {
            if (x > btn.x1 && x < btn.x2 && y > btn.y1 && y < btn.y2) {
                btn.onClick();
            }
        }
    }
    else if (editMode && S.corpuri_selectate.size() != 1) {
        CleanUp();
    }
}
