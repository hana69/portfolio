#include"Coin.h"
#include"DxLib.h"

CCoin::CCoin(int _width)
	:width(_width),graph(LoadGraph("noseResource/coin.png"))
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < 15;j++) {
			validMem[i][j]=valid[i][j] = false;
		}
	}
}

void CCoin::Reset() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < 15; j++) {
			if (validMem[i][j]) {
				valid[i][j] = true;
			}
		}
	}
}

void CCoin::Draw(int _scroll) {
	for (int i = 0; i < width;i++) {
		for (int j = 0; j < 15;j++) {
			if (valid[i][j]) {
				DrawExtendGraph( i * 50 - _scroll, j * 50, i*50 - _scroll + 50, j * 50 + 50 , graph, true);
			}
		}
	}
}

bool CCoin::Add(int x,int y) {
	if ( 0 <= x && x <= width && 0<= y && y<= 10) {
		validMem[x][y]=valid[x][y] = true;
		return true;
	}
	return false;
}

void CCoin::Delete(int x, int y) {
	valid[x][y] = false;
}


