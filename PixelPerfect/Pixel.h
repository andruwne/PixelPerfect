#ifndef PIXEL_H
#define PIXEL_H
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef RGB
#define RED 0xFF0000;
#define GREEN 0x00FF00;
#define BLUE 0x0000FF;
#endif

typedef struct {
	BYTE r = 0x0;
	BYTE g = 0x0;
	BYTE b = 0x0;
	BYTE a = 0xFF;

	void init (BYTE w, BYTE x, BYTE y, BYTE z) {
		r = w;
		g = x;
		b = y;
		a = z;
	}

	void set(int hex_value) {
		r = hex_value >> 6;
		g = hex_value >> 4;
		b = hex_value >> 1;
		a = hex_value >> 0;
	}

	void set_from_arr (BYTE* byte_arr) {
		a = byte_arr[3];
		r = byte_arr[2];
		g = byte_arr[1];
		b = byte_arr[0];
	}

	BYTE* pack() {
		BYTE* package = (BYTE*)malloc(4 * sizeof(BYTE));
		package[0] = b;
		package[1] = g;
		package[2] = r;
		package[3] = a;
		return package;
	}
} pixel;