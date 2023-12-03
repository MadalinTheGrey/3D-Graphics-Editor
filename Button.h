#pragma once
class Button{
public:
    int Xs, Ys, Xd, Yd;
    Button(int xup, int yup, int xdown, int ydown) {
        Xs = xup; Ys = yup;
        Xd = xdown; Yd = ydown;
    }
};

