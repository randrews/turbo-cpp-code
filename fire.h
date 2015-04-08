//== The functions ==//
void set_mx();
void set_pal();
void flame();
void dump2con();
void b4exit();

//== How much to add to 'x' or 'y', used in calculating averages. ==//
//== Use either -1, 0, or 1; this tells it where to get a pixel value
//
//== to use in averaging ==//
char x_amt_1 = 0, x_amt_2 = 1, x_amt_3 = -1, x_amt_4 = 1, x_amt_5 = -1;
char y_amt_1 = -1, y_amt_2 = 0, y_amt_3 = 0, y_amt_4 = 1, y_amt_5 = 1;

//== Decay values ==//
int opt_decay_at = 2, opt_decay_by = 2;

//== How dark the pallette is to be, from 0 - 7 ==//
//== Try changing to 0 or 1!!!! ==//
int pal_darkness = 2;

//== The two arrays the frames are stored in ==//
int current[56][80], working[56][80];

//== Our palette ==//
unsigned char pal[768]={   0,  0,  0,  0,  0, 0,  0,  0, 24,  0,  0, 28,
                           0,  0, 32,  0,  0, 32,  0,  0, 36,  0,  0, 40,
                           8,  0, 40, 16,  0, 36, 24,  0, 36, 32,  0, 32,
                          40,  0, 28, 48,  0, 28, 56,  0, 24, 64,  0, 20,
                          72,  0, 20, 80,  0, 16, 88,  0, 16, 96,  0, 12,
                         104,  0,  8,112,  0,  8,120,  0,  4,128,  0,  0,
                         128,  0,  0,132,  0,  0,136,  0,  0,140,  0,  0,
                         144,  0,  0,144,  0,  0,148,  0,  0,152,  0,  0,
                         156,  0,  0,160,  0,  0,160,  0,  0,164,  0,  0,
                         168,  0,  0,172,  0,  0,176,  0,  0,180,  0,  0,
                         184,  4,  0,188,  4,  0,192,  8,  0,196,  8,  0,
                         200, 12,  0,204, 12,  0,208, 16,  0,212, 16,  0,
                         216, 20,  0,220, 20,  0,224, 24,  0,228, 24,  0,
                         232, 28,  0,236, 28,  0,240, 32,  0,244, 32,  0,
                         252, 36,  0,252, 36,  0,252, 40,  0,252, 40,  0,
                         252, 44,  0,252, 44,  0,252, 48,  0,252, 48,  0,
                         252, 52,  0,252, 52,  0,252, 56,  0,252, 56,  0,
                         252, 60,  0,252, 60,  0,252, 64,  0,252, 64,  0,
                         252, 68,  0,252, 68,  0,252, 72,  0,252, 72,  0,
                         252, 76,  0,252, 76,  0,252, 80,  0,252, 80,  0,
                         252, 84,  0,252, 84,  0,252, 88,  0,252, 88,  0,
                         252, 92,  0,252, 96,  0,252, 96,  0,252,100,  0,
                         252,100,  0,252,104,  0,252,104,  0,252,108,  0,
                         252,108,  0,252,112,  0,252,112,  0,252,116,  0,
                         252,116,  0,252,120,  0,252,120,  0,252,124,  0,
                         252,124,  0,252,128,  0,252,128,  0,252,132,  0,
                         252,132,  0,252,136,  0,252, 136,   0,252, 140,   0,
                         252, 140,   0,252, 144,   0,252, 144,   0,252, 148,   0,
                         252, 152,   0,252, 152,   0,252, 156,   0,252, 156,   0,
                         252, 160,   0,252, 160,   0,252, 164,   0,252, 164,   0,
                         252, 168,   0,252, 168,   0,252, 172,   0,252, 172,   0,
                         252, 176,   0,252, 176,   0,252, 180,   0,252, 180,   0,
                         252, 184,   0,252, 184,   0,252, 188,   0,252, 188,   0,
                         252, 192,   0,252, 192,   0,252, 196,   0,252, 196,   0,
                         252, 200,   0,252, 200,   0,252, 204,   0,252, 208,   0,
                         252, 208,   0,252, 208,   0,252, 208,   0,252, 208,   0,
                         252, 212,   0,252, 212,   0,252, 212,   0,252, 212,   0,
                         252, 216,   0,252, 216,   0,252, 216,   0,252, 216,   0,
                         252, 216,   0,252, 220,   0,252, 220,   0,252, 220,   0,
                         252, 220,   0,252, 224,   0,252, 224,   0,252, 224,   0,
                         252, 224,   0,252, 228,   0,252, 228,   0,252, 228,   0,
                         252, 228,   0,252, 228,   0,252, 232,   0,252, 232,   0,
                         252, 232,   0,252, 232,   0,252, 236,   0,252, 236,   0,
                         252, 236,   0,252, 236,   0,252, 240,   0,252, 240,   0,
                         252, 240,   0,252, 240,   0,252, 240,   0,252, 244,   0,
                         252, 244,   0,252, 244,   0,252, 244,   0,252, 248,   0,
                         252, 248,   0,252, 248,   0,252, 248,   0,252, 252,   0,
                         252, 252,   4,252, 252,   8,252, 252,  12,252, 252,  16,
                         252, 252,  20,252, 252,  24,252, 252,  28,252, 252,  32,
                         252, 252,  36,252, 252,  40,252, 252,  40,252, 252,  44,
                         252, 252,  48,252, 252,  52,252, 252,  56,252, 252,  60,
                         252, 252,  64,252, 252,  68,252, 252,  72,252, 252,  76,
                         252, 252,  80,252, 252,  84,252, 252,  84,252, 252,  88,
                         252, 252,  92,252, 252,  96,252, 252, 100,252, 252, 104,
                         252, 252, 108,252, 252, 112,252, 252, 116,252, 252, 120,
                         252, 252, 124,252, 252, 124,252, 252, 128,252, 252, 132,
                         252, 252, 136,252, 252, 140,252, 252, 144,252, 252, 148,
                         252, 252, 152,252, 252, 156,252, 252, 160,252, 252, 164,
                         252, 252, 168,252, 252, 168,252, 252, 172,252, 252, 176,
                         252, 252, 180,252, 252, 184,252, 252, 188,252, 252, 192,
                         252, 252, 196,252, 252, 200,252, 252, 204,252, 252, 208,
                         252, 252, 208,252, 252, 212,252, 252, 216,252, 252, 220,
                         252, 252, 224,252, 252, 228,252, 252, 232,252, 252, 236,
                         252, 252, 240,252, 252, 244,252, 252, 248,252, 252, 252};