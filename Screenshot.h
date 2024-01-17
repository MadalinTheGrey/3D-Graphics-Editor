#pragma once

struct BmpHeader {
    char bitmapSignatureBytes[2] = { 'B', 'M' }; //format bitmap
    uint32_t sizeOfBitmapFile = 54 + 1040*685*3; //54 pixel header, img size = 1040*685 *3(pixel = 3bites)
    uint32_t reservedBytes = 0;
    uint32_t pixelDataOffset = 54;
} bmpHeader;
struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = 40;
    int32_t width = 1040; // in pixels
    int32_t height = 685; // in pixels
    uint16_t numberOfColorPlanes = 1; // must be 1
    uint16_t colorDepth = 24;
    uint32_t compressionMethod = 0;
    uint32_t rawBitmapDataSize = 0; // generally ignored
    int32_t horizontalResolution = 3780; // in pixel per meter
    int32_t verticalResolution = 3780; // in pixel per meter
    uint32_t colorTableEntries = 0;
    uint32_t importantColors = 0;
} bmpInfoHeader;
struct Pixel {
    uint8_t blue = 255;
    uint8_t green = 255;
    uint8_t red = 0;
};
bool save;
void SaveScreenShot(bool w = 0) {
	setviewport(0, 0, 1280, 720, 1);
	int x1, y1, x2, y2;
	y1 = 0; y2 = 30;
	if (w == 0) {
		x1 = 500; x2 = 700;
	}
	else {
		x1 = 900; x2 = 1100;
	}
	save = false;
	string path = current_file;
	path = path.substr(0, path.size() - 4);
	path += "|";
	drawFilledRectangle(x1 + 5, y1 + 5, x2 - 5, y2 - 5, COLOR(35,35,35));
	writeText(x1 + 10, y1 + 25, (char*)path.c_str(), COLOR(182, 182, 182), 1, COLOR(35, 35, 35));

	while (!save) {
		if (!_closeSaveWindow) {
			bool ok = false;
			if (GetAsyncKeyState(0x41)) { // A
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'A';
				else
					path += 'a';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x42)) { // B
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'B';
				else
					path += 'b';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x43)) { // C
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'C';
				else
					path += 'c';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x44)) { // D
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'D';
				else
					path += 'd';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x45)) { // E
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'E';
				else
					path += 'e';				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x46)) { // F
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'F';
				else
					path += 'f';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x47)) { // G
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'G';
				else
					path += 'g';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x48)) { // H
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'H';
				else
					path += 'h';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x49)) { // I
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'I';
				else
					path += 'i';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x4A)) { // J
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'J';
				else
					path += 'j';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x4B)) { // K
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'K';
				else
					path += 'k';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x4C)) { // L
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'L';
				else
					path += 'l';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x4D)) { // M
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'M';
				else
					path += 'm';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x4E)) { // N
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'N';
				else
					path += 'n';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x4F)) { // O
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'O';
				else
					path += 'o';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x50)) { // P
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'P';
				else
					path += 'p';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x51)) { // Q
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'Q';
				else
					path += 'q';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x52)) { // R
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'R';
				else
					path += 'r';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x53)) { // S
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'S';
				else
					path += 's';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x54)) { // T
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'T';
				else
					path += 't';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x55)) { // U
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'U';
				else
					path += 'u';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x56)) { // V
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'V';
				else
					path += 'v';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x57)) { // W
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'W';
				else
					path += 'w';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x58)) { // X
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'X';
				else
					path += 'x';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x59)) { // Y
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'Y';
				else
					path += 'y';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x5A)) { // Z
				path = path.substr(0, path.length() - 1);
				if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) ^ GetKeyState(VK_CAPITAL))
					path += 'Z';
				else
					path += 'z';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x30)) { // 0
				path = path.substr(0, path.length() - 1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += ')';
				else
					path += '0';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x31)) { // 1
				path = path.substr(0, path.length() - 1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '!';
				else
					path += '1';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x32)) { // 2
				path = path.substr(0, path.length() - 1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '@';
				else
					path += '2';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x33)) { // 3
				path = path.substr(0, path.length() - 1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '#';
				else
					path += '3';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x34)) { // 4
				path = path.substr(0, path.length() - 1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '$';
				else
					path += '4';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x35)) { // 5
				path = path.substr(0, path.length() - 1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '%';
				else
					path += '5';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x36)) { // 6
				path = path.substr(0, path.length() - 1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '^';
				else
					path += '6';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x37)) { // 7
				path = path.substr(0, path.length() - 1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '&';
				else
					path += '7';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x38)) { // 8
				path = path.substr(0, path.length() - 1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '*';
				else
					path += '8';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(0x39)) { // 9
				path = path.substr(0, path.length() - 1);
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
					path += '(';
				else
					path += '9';
				ok = true;
				path += "|";
			}
			else if (GetAsyncKeyState(VK_SPACE)) {
				path = path.substr(0, path.length() - 1);
				ok = true;
				path += " ";
				path += "|";
			}
			else if (GetAsyncKeyState(VK_BACK) && path.length() > 1) {
				path = path.substr(0, path.length() - 2);
				ok = true;
				path += "|";
			}
			if (ok == true) {
				drawFilledRectangle(x1 + 5, y1 + 5, x2 - 5, y2 - 5, COLOR(35,35,35));
				writeText(x1 + 10, y1 + 25, (char*)path.c_str(), COLOR(182,182,182), 1, COLOR(35,35,35));
			}
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			save = true;
		}
		delay(100);
	}
	path = path.substr(0, path.size() - 1);
	path += ".bmp";
	TCHAR NPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, NPath);
	string _path = string(NPath);

	path = _path + "\\SavedImages\\" + path;

    ofstream fout(path.c_str(), ios::binary);

	drawFilledRectangle(x1 + 5, y1 + 5, x2 - 5, y2 - 5, COLOR(35, 35, 35));
	writeText(x1 + 10, y1 + 25, "Wait...", COLOR(182, 182, 182), 1, COLOR(35, 35, 35));

    fout.write((char*)&bmpHeader.bitmapSignatureBytes, 2);
    fout.write((char*)&bmpHeader.sizeOfBitmapFile, sizeof(uint32_t));
    fout.write((char*)&bmpHeader.reservedBytes, sizeof(uint32_t));
    fout.write((char*)&bmpHeader.pixelDataOffset, sizeof(uint32_t));

    fout.write((char*)&bmpInfoHeader.sizeOfThisHeader, sizeof(uint32_t));
    fout.write((char*)&bmpInfoHeader.width, sizeof(int32_t));
    fout.write((char*)&bmpInfoHeader.height, sizeof(int32_t));
    fout.write((char*)&bmpInfoHeader.numberOfColorPlanes, sizeof(uint16_t));
    fout.write((char*)&bmpInfoHeader.colorDepth, sizeof(uint16_t));
    fout.write((char*)&bmpInfoHeader.compressionMethod, sizeof(uint32_t));
    fout.write((char*)&bmpInfoHeader.rawBitmapDataSize, sizeof(uint32_t));
    fout.write((char*)&bmpInfoHeader.horizontalResolution, sizeof(uint32_t));
    fout.write((char*)&bmpInfoHeader.verticalResolution, sizeof(uint32_t));
    fout.write((char*)&bmpInfoHeader.colorTableEntries, sizeof(uint32_t));
    fout.write((char*)&bmpInfoHeader.importantColors, sizeof(uint32_t));
    
    vector<Pixel> v;
    setviewport(0, 0, 1280, 720, 1);
    for (int i = 30; i <= 685+30; ++i) {
        for (int j = 40; j < 1040+40; ++j) {
            auto p = getpixel(j, i);
            int x = converttorgb(p);
            Pixel pp = { BLUE_VALUE(p), GREEN_VALUE(p), RED_VALUE(p) };
            v.push_back(pp);
        }
        
        std::reverse(v.end()-1040, v.end());
    }
    std::reverse(v.begin(), v.end());
    size_t numberOfPixels = bmpInfoHeader.width * bmpInfoHeader.height;
    for (int i = 0; i < numberOfPixels; i++) {
        fout.write((char*)&v[i].blue, sizeof(uint8_t));
        fout.write((char*)&v[i].green, sizeof(uint8_t));
        fout.write((char*)&v[i].red, sizeof(uint8_t));
    }
    fout.close();
	drawFilledRectangle(x1 + 5, y1 + 5, x2 - 5, y2 - 5, COLOR(35, 35, 35));
	writeText(x1 + 10, y1 + 25, "Done...", COLOR(182, 182, 182), 1, COLOR(35, 35, 35));
	Sleep(1000);
	drawFilledRectangle(x1 + 5, y1 + 5, x2 - 5, y2 - 5, COLOR(35, 35, 35));
	setviewport(vp_tl_x, vp_tl_y, vp_dr_x, vp_dr_y, 1);
	setbkcolor(BLACK);
}