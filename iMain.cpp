#include "iGraphics.h"
#include "iSound.h"

const int maxuser = 15, maxdua = 30;

int y, y_1, r, num = 0, length, length1, gap=0, gap1=0, hang, dialog_num;
int dua_slot[2][3] = { {81, 51, 21}, {95, 62, 35} };	// y of each dua dialog option above hang: [0] normal box, [1] inverted box
int two_option_slot[2][2] = { {48, 18}, {62, 32} };	// y of Rename / Delete above hang in the two-option box: [0] normal, [1] inverted
bool is_empty, is_dialog_open = false, is_deleting = false;
char s[100], nme[100];
char days[100];
int s_index, done[maxdua], size1, size2;
char participant[maxuser][100];
char dua[maxdua][100], dua1[maxdua][100], dua2[100];
const char regular_participant_list[100] = "data_files/regular_reads/participant_list.txt";
const char targetted_participant_list[100] = "data_files/targetted_reads/participant_list.txt";
const char file[100] = "data_files/regular_reads/participant%d.txt";
const char file1[100] = "data_files/targetted_reads/participant%d.txt";
char text[3][100] = { "Enter your name:", "Enter the Dua:", "Enter your target:" };
const char tasbeeh_pic[100] = "pictures/tasbeeh/pic%d.png";
int seq, tasbeeh_pic_index=0;
char random1[maxdua][5], random2[maxdua][5], random3[maxuser > maxdua ? maxuser : maxdua][5], random4[maxdua][5], name[maxuser][100], tym[100], cnt_dua[100];
const char bg[100] = "pictures/bg/plain_bg%d.bmp";
const char main_bg[100] = "pictures/bg/bg%d.bmp";
int bg_index = 0;
char theme[3][100] = { "1. Green", "2. Purple", "3. Blue" };
long long tm[maxdua], dur[maxdua], scnds;
long long tmr, plus1=86400, plus2=604800;
int tog;
bool musicOn = true, musicOn2 = true;
int bg_music, count_sound, goal_sound;
int count_dua[maxdua], count_dua1[maxdua], target[maxdua];
int count = 0, cnt=0, cnt1=0;
time_t seconds;
int b = 0, w = 0, l, g = 0, m = 0, f, call = 0;
char ti[30];
char *count_store = (char*)malloc(sizeof(char)* 10);
char comment[2][100] = { "Saved Successfully!!!", "Deleted Successfully!!!" };
char record[10][100];
int snd_index = 0;
char line[maxuser][100], line1[maxdua][100];
char path[100];

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void convert_int_to_str(int n, char rdm[]) {
	int total = 0, q = n;
	if (q == 0) {
		total++;
	} else {
		while (q) {
			q = q / 10;
			total++;
		}
	}

	rdm[total] = '\0';
	while (total) {
		rdm[total - 1] = '0' + (n % 10);
		n = n / 10;
		total--;
	}
}

void convert_char(int *n, char rdm[]) {
	long long power = 1;
	*n = 0;
	int length = strlen(rdm) - 1;
	for (int i = length; i >= 0; i--) {
		*n += (rdm[i] - 48)*power;
		power = power * 10;
	}
}

void load_bg() {
	if (num == 0) {
		sprintf(path, main_bg, bg_index + 1);
	} else {
		sprintf(path, bg, bg_index + 1);
	}
	iShowBMP2(0, 0, path, -1);
}

void delete_file() {
	y += 50;
	FILE *fp;
	if (num == 19) {
		fp = fopen(targetted_participant_list, "r");
	} else {
		fp = fopen("data_files/regular_reads/participant_list.txt", "r");
	} 
	
	for (int i = 0; i < cnt; i++) {
		fgets(participant[i], 100, fp);
		if (i>r) {
		    if(participant[i][1]>'0' && participant[i][1]<='9') {
                participant[i][1]--;
                continue;
            } else if(participant[i][1] == '0') {
                participant[i][1] = '9';
                participant[i][0]--;
                continue;
            } else;
		}
	}

	fclose(fp);

	if (num == 19) {
		fp = fopen(targetted_participant_list, "w");
	} else {
		fp = fopen(regular_participant_list, "w");
	}

	for (int i = 0; i < cnt; i++) {
		if (i == r) {
			continue;
		}
		fprintf(fp, "%s", participant[i]);
	}

	strcpy(participant[cnt - 1], "");
	fclose(fp);

	for (int i = r; i < maxuser; i++) {
		if (i == maxuser - 1) {
			FILE *f_out;

			if (num == 19) {
				sprintf(path, file1, i + 1);
				f_out = fopen(path, "w");
			} else {
				sprintf(path, file, i + 1);
				f_out = fopen(path, "w");
			}

			fclose(f_out);
		} else {
			FILE *f_in;
			FILE *f_out;

			if (num == 19) {
				sprintf(path, file1, i + 2);
				f_in = fopen(path, "r");
				sprintf(path, file1, i + 1);
				f_out = fopen(path, "w");
			} else {
				sprintf(path, file, i + 2);
				f_in = fopen(path, "r");
				sprintf(path, file, i + 1);
				f_out = fopen(path, "w");
			}

			char ch = fgetc(f_in);
			while (ch != EOF) {
				fputc(ch, f_out);
				ch = fgetc(f_in);
			}

			fclose(f_in);
			fclose(f_out);
		}
	}
	f = 1;
	num = 13;
}

void delete_data() {
	is_deleting = false;
	int v = 0;
	FILE *fp;

	if (num == 26 || call == 2) {
		sprintf(path, file1, r + 1);
		fp = fopen(path, "r");
	} else {
		sprintf(path, file, r + 1);
		fp = fopen(path, "r");
	}

	for (int i = 0; i < cnt1; i++) {
		fgets(dua[i], 100, fp);
		if (i>l) {
		    if(dua[i][1]>'0' && dua[i][1]<='9') {
                dua[i][1]--;
                continue;
            }

			if(dua[i][1]=='0') {
                dua[i][1]='9';
                dua[i][0]--;
                continue;
            }
		}
	}

	fclose(fp);
	if (num == 26 || call==2) {
		sprintf(path, file1, r + 1);
		fp = fopen(path, "w");
	} else {
		sprintf(path, file, r + 1);
		fp = fopen(path, "w");
	}

	for (int i = 0; i < cnt1; i++) {
		if (i == l) {
			continue;
		}

		fprintf(fp, "%s", dua[i]);
		v = 1;
	}

	if (cnt1 > 0) {
		strcpy(dua[cnt1 - 1], "");
	}
	fclose(fp);

	if (v == 1) {
		f = 1;
		v = 0;
	} else {
		if (num == 26 || call == 2) {
			fp = fopen(targetted_participant_list, "r");
		} else {
			fp = fopen(regular_participant_list, "r");
		}

		for (int i = 0; i < cnt; i++) {
			fgets(participant[i], 100, fp);
			if (i>r) {
			    if(participant[i][1]>'0' && participant[i][1]<='9') {
                    participant[i][1]--;
                }

				if(participant[i][1]=='0') {
                    participant[i][1]='9';
                    participant[i][0]--;
                }
			}
		}
		fclose(fp);

		if (num == 26 || call == 2) {
			fp = fopen(targetted_participant_list, "w");
		} else {
			fp = fopen(regular_participant_list, "w");
		}

		for (int i = 0; i < cnt; i++) {
			if (i == r) {
				continue;
			}
			fprintf(fp, "%s", participant[i]);
		}
		strcpy(participant[cnt - 1], "");
		fclose(fp);

		for (int i = r; i < maxuser; i++) {
			if (i == maxuser - 1) {
				FILE *f_out;
				if (num == 26 || call == 2) {
					sprintf(path, file1, i + 1);
					f_out = fopen(path, "w");
				} else {
					sprintf(path, file, i + 1);
					f_out = fopen(path, "w");
				}
				fclose(f_out);
			} else {
				FILE *f_in;
				FILE *f_out;

				if (num==26 || call == 2) {
					sprintf(path, file1, i + 2);
					f_in = fopen(path, "r");
					sprintf(path, file1, i + 1);
					f_out = fopen(path, "w");
				} else {
					sprintf(path, file, i + 2);
					f_in = fopen(path, "r");
					sprintf(path, file, i + 1);
					f_out = fopen(path, "w");
				}

				char ch = fgetc(f_in);
				while (ch != EOF) {
					fputc(ch, f_out);
					ch = fgetc(f_in);
				}
				fclose(f_in);
				fclose(f_out);
			}
		}

		if (call == 18) {
			num = 17;
		}

		if (call == 2) {
			num = 13;
		}

		if (num == 26) {
			num = 19;
		}
	}
}

void draw_scrollbar(int* length, int cnt, int width, int* y, int* gap) {
	int overflow = (cnt * width) - 375;	
	if (overflow > 0) {
		*length = 512 * 512 / (512 + overflow);
		if (*y < *length) {
			*y = *length;
		}
		iSetColor(200, 200, 200);
		iFilledRectangle(500, 0, 12, 512);
		iSetColor(96, 96, 96);
		iFilledRectangle(500, *y - *length, 12, *length);
		*gap = (512 - *y) * overflow / (512 - *length);
	} else {
		*length = 512;
		*gap = 0;
	}
}

int purple_plus_x(int len) {
	return (len < 512) ? 458 : 470;
}

int content_bar_width(int len) {
	int width = (len < 512) ? 405 : 417;
	if (num != 19 && num != 26) {
		width += 5;
	}
	return width;
}

void print_name_index() {
    call = num;
	is_empty = true;
	cnt = 0;
	iShowBMP2(5, 475, "pictures/red_back_arrow.bmp", 0);
	iSetColor(0, 0, 0);
	iText(100, 400 + gap, "Recent users", GLUT_BITMAP_TIMES_ROMAN_24);

	FILE *m_file;
	if (call == 19) {
		m_file = fopen(targetted_participant_list, "r");
	} else {
		m_file = fopen(regular_participant_list, "r");
	}

	int vert = 345 + gap;
	for (int i = 0; i < maxuser; i++) {
		strcpy(participant[i], "");
		fgets(participant[i], 100, m_file);
		if (participant[i][0] < '0' || participant[i][0]>'9') {
			continue;
		}

		iSetColor(196, 164, 132);
		iFilledRectangle(45, vert, content_bar_width(length), 25);
		iSetColor(0, 0, 0);
		iRectangle(45, vert, content_bar_width(length), 25);
		iText(50, vert + 5, participant[i], GLUT_BITMAP_TIMES_ROMAN_24);
		vert = vert - 50;
		cnt++;
		is_empty = false;
	}

	fclose(m_file);

	if (is_empty) {
		if (num != 19) {
			iSetColor(0, 0, 0);
			iText(100, 256, "No such existing file.", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(60, 226, "Click Enter to create new record.", GLUT_BITMAP_TIMES_ROMAN_24);
		} else {
			iSetColor(0, 0, 0);
			iText(100, 256, "No such existing file.", GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}

	if (is_dialog_open && (num == 17 || num == 19)) {
		iShowBMP2(205, hang, dialog_num == 0 ? "pictures/dialog_boxes/dialog_2_options1.bmp" : "pictures/dialog_boxes/dialog_2_options2.bmp", 0);

		if(dialog_num == 0) {
            iText(248, hang + 48, "Rename", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(248, hang + 18, "Delete", GLUT_BITMAP_TIMES_ROMAN_24);
        } else {
            iText(248, hang + 62, "Rename", GLUT_BITMAP_TIMES_ROMAN_24);
            iText(248, hang + 32, "Delete", GLUT_BITMAP_TIMES_ROMAN_24);
        }
	}

	if(is_deleting && (num == 17 || num == 19)) {
        iSetColor(255, 200, 100);
		iFilledRectangle(100, 148, 295, 220);
		iSetColor(98, 45, 67);
		iRectangle(100, 148, 295, 220);
		iSetColor(0, 0, 0);
		iText(130, 324, "Would you like to delete", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(185, 294, "this record?", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(50, 50, 50);
		iFilledRectangle(140, 204, 80, 35);
		iSetColor(50, 50, 50);
		iFilledRectangle(275, 204, 80, 35);
		iSetColor(250, 255, 200);
		iText(160, 214, "YES", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 255, 200);
		iText(298, 214, "NO", GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

void print_dua_index() {
	is_empty = true;
	cnt1 = 0;
	iShowBMP2(5, 475, "pictures/red_back_arrow.bmp", 0);
	iSetColor(0, 0, 0);
	FILE *fp;

	if (num == 26) {
		iText(145, 440 + gap1, "Your Targets", GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf(path, file1, r + 1);
		fp = fopen(path, "r");
	} else {
		iText(145, 420 + gap1, "Your History", GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf(path, file, r + 1);
		fp = fopen(path, "r");
	}

	int vert = 365 + gap1;
	for (int i = 0; i < maxdua; i++) {
		strcpy(dua[i], "");
		strcpy(random1[i], "");
		strcpy(dua1[i], "");
		strcpy(random2[i], "");
		fgets(dua[i], 100, fp);

		if (dua[i][0] < '0' || dua[i][0]>'9') {
			continue;
		}

		iSetColor(255, 255, 255);
		iFilledRectangle(45, vert, content_bar_width(length1), 25);
		iSetColor(0, 0, 0);
		iRectangle(45, vert, content_bar_width(length1), 25);
		struct tm* curr_time;
		int day=0;
		seconds = time(NULL);
		curr_time = localtime(&seconds);
		long long tmi;
		int buffer=0;

		if (num == 26) {
			sscanf(dua[i], "%s %s %s %d %s %d %lld %d %lld", random1[i], dua1[i], random2[i], &count_dua[i], random4[i], &count_dua1[i], &tm[i], &done[i], &dur[i]);
			if (tm[i] > seconds) {
				tmi = tm[i] - seconds;
			} else {
				tmi = 0;
			}

			strcpy(dua[i], "");
			if (count_dua1[i] >= count_dua[i]) {
			    buffer = 0;
				sprintf(dua[i], "%s %s %s %d", random1[i], dua1[i], random2[i], buffer);
			} else {
			    buffer = count_dua[i] - count_dua1[i];
				sprintf(dua[i], "%s %s %s %d", random1[i], dua1[i], random2[i], buffer);
			}

			if ((tmi / 86400) > 0) {
				day = tmi / 86400;
				tmi = tmi % 86400;
				convert_int_to_str(day, days);
				strftime(ti, 20, "%H:%M:%S", curr_time);
				if (day == 1) {
					strcat(days, " day ");
				} else {
					strcat(days, " days ");
				}
			}
		} else {
			sscanf(dua[i], "%s %s %s %d %s %lld", random1[i], dua1[i], random2[i], &count_dua[i], random4[i], &tm[i]);
			tmi = tm[i];
			strcpy(dua[i], "");
			sprintf(dua[i], "%s %s %s %d", random1[i], dua1[i], random2[i], count_dua[i]);
		}

		curr_time->tm_hour = tmi / 3600;
		curr_time->tm_min = (tmi % 3600) / 60;
		curr_time->tm_sec = (tmi % 3600) % 60;
		strftime(ti, 20, "%H:%M:%S", curr_time);

		if (call == 12) {
			iText(50, vert+5, dua1[i], GLUT_BITMAP_TIMES_ROMAN_24);
		} else {
			iText(50, vert + 5, dua[i], GLUT_BITMAP_TIMES_ROMAN_24);
			if(num == 26) {
                if(done[i] == 1) {
                    iText(50, vert + 5, dua[i], GLUT_BITMAP_TIMES_ROMAN_24);
                    iShowBMP2(432 + content_bar_width(length1) - 422, vert, "pictures/green_tick.bmp", 0);
                } else {
                    if(tm[i] <= seconds) {
                        iShowBMP2(432 + content_bar_width(length1) - 422, vert, "pictures/red_cross.bmp", 0);
                    } else {
                        if (day > 0) {
                            iText(330 + content_bar_width(length1) - 422, vert + 7, days, GLUT_BITMAP_HELVETICA_18);
                        }
                        iText(392 + content_bar_width(length1) - 422, vert + 7, ti, GLUT_BITMAP_HELVETICA_18);
                    }
                }
            } else {
				iText(392 + content_bar_width(length1) - 422, vert + 7, ti, GLUT_BITMAP_HELVETICA_18);
			}
		}
		vert = vert - 30;
		cnt1++;
		is_empty = false;
	}
	fclose(fp);

	if (is_dialog_open && num == 26 && done[l] == 1) {
		iShowBMP2(205, hang, dialog_num == 0 ? "pictures/dialog_boxes/dialog_2_options1.bmp" : "pictures/dialog_boxes/dialog_2_options2.bmp", 0);
		iText(248, hang + two_option_slot[dialog_num][0], "Rename", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(248, hang + two_option_slot[dialog_num][1], "Delete", GLUT_BITMAP_TIMES_ROMAN_24);
	} else if (is_dialog_open && (num == 18 || num==26)) {
		iShowBMP2(206, hang, dialog_num == 0 ? "pictures/dialog_boxes/dialog_3_options1.bmp" : "pictures/dialog_boxes/dialog_3_options2.bmp", 0);
		
		if (num == 26 && done[l] == 0 && tm[l] <= seconds) {
			iText(248, hang + dua_slot[dialog_num][0], "Restart", GLUT_BITMAP_TIMES_ROMAN_24);
		} else {
			iText(248, hang + dua_slot[dialog_num][0], "Continue", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iText(248, hang + dua_slot[dialog_num][1], "Rename", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(248, hang + dua_slot[dialog_num][2], "Delete", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (is_deleting && (num == 18 || num==26)) {
		iSetColor(255, 200, 100);
		iFilledRectangle(100, 148, 295, 220);
		iSetColor(98, 45, 67);
		iRectangle(100, 148, 295, 220);
		iSetColor(0, 0, 0);
		iText(130, 324, "Would you like to delete", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(185, 294, "this record?", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(50, 50, 50);
		iFilledRectangle(140, 204, 80, 35);
		iSetColor(50, 50, 50);
		iFilledRectangle(275, 204, 80, 35);
		iSetColor(250, 255, 200);
		iText(160, 214, "YES", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 255, 200);
		iText(298, 214, "NO", GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void append_file() {
	FILE *f_in;
	strcpy(name[0], " ");
	strcat(name[0], nme);
	strcpy(random3[0], "01.");

	if (num == 7) {
		f_in = fopen(regular_participant_list, "r");
	} else {
		f_in = fopen(targetted_participant_list, "r");
	}

	for (int i = 1; i < maxuser; i++) {
		fscanf(f_in, "%s", random3[i]);
		fgets(name[i], 100, f_in);
	}
	fclose(f_in);

	if (num == 7) {
		f_in = fopen(regular_participant_list, "w");
	} else {
		f_in = fopen(targetted_participant_list, "w");
	}

	for (int i = 0; i < maxuser; i++) {
		if (random3[i][0] < '0' || random3[i][0] > '9') {
			continue;
		}

		if(i<9) {
            fprintf(f_in, "0%d.%s", i + 1, name[i]);
        } else {
            fprintf(f_in, "%d.%s", i + 1, name[i]);
        }
	}

	fclose(f_in);
}

void create_file() {
	FILE *f_in;
	for (int i = maxuser - 1; i > 0; i--) {
		FILE *f_out;
		if (num == 7) {
			sprintf(path, file, i);
			f_in = fopen(path, "r");
			sprintf(path, file, i + 1);
			f_out = fopen(path, "w");
		} else {
			sprintf(path, file1, i);
			f_in = fopen(path, "r");
			sprintf(path, file1, i + 1);
			f_out = fopen(path, "w");
		}

		char ch = fgetc(f_in);
		while (ch != EOF) {
			fputc(ch, f_out);
			ch = fgetc(f_in);
		}
		fclose(f_in);
		fclose(f_out);
	}
	if (num == 7) {
		sprintf(path, file, 1);
		f_in = fopen(path, "w");
		fprintf(f_in, "01. %s - %d - %lld", s, count, tmr);
	} else {
		sprintf(path, file1, 1);
		f_in = fopen(path, "w");
		if (tog == 1) {
			fprintf(f_in, "01. %s - %s - %d %lld 0 %lld", dua2, s, count, seconds+plus1, plus1);
		}
		if (tog == 2) {
			fprintf(f_in, "01. %s - %s - %d %lld 0 %lld", dua2, s, count, seconds+plus2, plus2);
		}
		strcpy(dua2, "");
	}

	fclose(f_in);
	count = 0;
	num = 13;
}

void take_input() {
	for (int i = 0; i < maxdua; i++) {
		strcpy(random1[i], "");
	}
	FILE *fp;
	if (num == 30) {
		sprintf(path, file1, r + 1);
		fp = fopen(path, "r");
	} else {
		sprintf(path, file, r + 1);
		fp = fopen(path, "r");
	}
	for (int i = 0; i < maxdua; i++) {
		if (num == 30) {
			fscanf(fp, "%s %s %s %d %s %d %lld %d %lld", random1[i], dua1[i], random2[i], &count_dua[i], random4[i], &count_dua1[i], &tm[i], &done[i], &dur[i]);
		} else {
			fscanf(fp, "%s %s %s %d %s %lld", random1[i], dua1[i], random2[i], &count_dua[i], random4[i], &tm[i]);
		}
	}
	fclose(fp);
}

void shift_data() {
	for (int i = maxdua - 1; i > 0; i--) {
		count_dua[i] = count_dua[i - 1];
		count_dua1[i] = count_dua1[i - 1];
		done[i] = done[i - 1];
		strcpy(dua1[i], dua1[i - 1]);
		if (random1[i - 1][0] >= '0' && random1[i - 1][0] <= '9') {
			sprintf(random1[i], "%02d.", i + 1);
		}
		strcpy(random2[i], random2[i - 1]);
		strcpy(random4[i], random4[i - 1]);
		tm[i] = tm[i - 1];
		dur[i] = dur[i - 1];
	}
	count_dua[0] = count;
	count_dua1[0] = 0;
	done[0] = 0;
	if (num == 30) {
		strcpy(dua1[0], dua2);
	} else {
		strcpy(dua1[0], s);
	}
	strcpy(random1[0], "01.");
	strcpy(random2[0], "-");
	strcpy(random4[0], "-");
	if (num == 30) {
		if (tog == 1) {
			tm[0] = seconds+plus1;
			dur[0] = plus1;
		}
		if (tog == 2) {
			tm[0] = seconds+plus2;
			dur[0] = plus2;
		}
	} else {
		tm[0] = tmr;
	}
}

void replace_file() {
	char temp[100];
	strcpy(temp, dua1[l]);
	int temp1=count_dua[l],temp3=count_dua1[l],temp4=done[l];
	long long temp2 = tm[l], temp5 = dur[l];
	for (int i = l - 1; i >= 0; i--) {
		strcpy(dua1[i + 1], dua1[i]);
		count_dua[i + 1] = count_dua[i];
		count_dua1[i + 1] = count_dua1[i];
		done[i + 1] = done[i];
		tm[i + 1] = tm[i];
		dur[i + 1] = dur[i];
	}
	count_dua[0] = temp1;
	count_dua1[0] = temp3;
	done[0] = temp4;
	strcpy(dua1[0], temp);
	strcpy(temp, "");
	tm[0] = temp2;
	dur[0] = temp5;

	FILE *fp;
	fp = fopen("temp.txt", "w");
	for (int i = 0; i < maxdua; i++) {
		if (random1[i][0] < '0' || random1[i][0]>'9') {
			continue;
		}
		if (call == 26 || num == 30 || call==30 || call == 2) {
			fprintf(fp, "%s %s %s %d %s %d %lld %d %lld\n", random1[i], dua1[i], random2[i], count_dua[i], random4[i], count_dua1[i], tm[i], done[i], dur[i]);
		} else {
			fprintf(fp, "%s %s %s %d %s %lld\n", random1[i], dua1[i], random2[i], count_dua[i], random4[i], tm[i]);
		}
	}
	fclose(fp);

	for (int i = r - 1; i >= 0; i--) {
		FILE *f_in;
		FILE *f_out;
		if (num == 30 || call == 26 || call == 30 || call == 2) {
			sprintf(path, file1, i + 1);
			f_in = fopen(path, "r");
			sprintf(path, file1, i + 2);
			f_out = fopen(path, "w");
		} else {
			sprintf(path, file, i + 1);
			f_in = fopen(path, "r");
			sprintf(path, file, i + 2);
			f_out = fopen(path, "w");
		}
		char ch = fgetc(f_in);
		while (ch != EOF) {
			fputc(ch, f_out);
			ch = fgetc(f_in);
		}
		fclose(f_out);
		fclose(f_in);
	}
	FILE *f_in = fopen("temp.txt", "r");
	FILE *f_out;
	if (num == 30 || call == 26 || call == 30 || call == 2) {
		sprintf(path, file1, 1);
		f_out = fopen(path, "w");
	} else {
		sprintf(path, file, 1);
		f_out = fopen(path, "w");
	}
	int ch = fgetc(f_in);
	while (ch != EOF) {
		fputc(ch, f_out);
		ch = fgetc(f_in);
	}
	fclose(f_out);
	fclose(f_in);
	remove("temp.txt");

	FILE *fptr;
	if (num == 30 || call == 26 || call == 30 || call == 2) {
		fptr = fopen(targetted_participant_list, "r");
	} else {
		fptr = fopen(regular_participant_list, "r");
	}
	for (int i = 0; i < maxuser; i++) {
		fgets(participant[i], 100, fptr);
	}
	participant[r][0] = '0';
	participant[r][1] = '1';
	strcpy(temp, participant[r]);
	for (int i = r - 1; i >= 0; i--) {
	    if(participant[i][1]>='0' && participant[i][1]<'9') {
            participant[i][1]++;
        }
        if(participant[i][1]=='9') {
            participant[i][0]++;
            participant[i][1]='0';
        }
		strcpy(participant[i + 1], participant[i]);
	}
	strcpy(participant[0], temp);
	strcpy(temp, "");
	if (num == 30 || call == 26 || call == 30 || call == 2) {
		fp = fopen(targetted_participant_list, "w");
	} else {
		fp = fopen(regular_participant_list, "w");
	}
	for (int i = 0; i < maxuser; i++) {
		fprintf(fp, "%s", participant[i]);
	}
	fclose(fp);

	count = 0;
	f = 0;
	num = 13;
}

void rename() {
    FILE *fp;
    if(call == 17) {
        fp=fopen(regular_participant_list, "r");
    } else if(call == 19) {
        fp=fopen(targetted_participant_list, "r");
    } else if(call == 18) {
		sprintf(path, file, r + 1);
        fp=fopen(path, "r");
    } else {
		sprintf(path, file1, r + 1);
        fp=fopen(path, "r");
    }

    if(call == 17 || call == 19) {
        for(int i=0; i < maxuser; i++) {
            fgets(line[i],100, fp);
        }
        strcpy(line[r], "");
        if(r<9) {
            sprintf(line[r], "0%d. %s\n", r+1,s);
        } else {
            sprintf(line[r], "%d. %s\n", r+1, s);
        }
    } else {
        for(int i=0; i < maxdua; i++) {
            fgets(line1[i], 100, fp);
        }
        int rand, rand1, rand7;
        long long rand2, rand8;
        char rand3[50], rand4[3], rand5[3], rand6[3];
        if(call != 18) {
            sscanf(line1[l],"%s %s %s %d %s %d %lld %d %lld", rand4, rand3, rand5, &rand, rand6, &rand1, &rand2, &rand7, &rand8);
            strcpy(line1[l],"");
            if(l<9) {
                sprintf(line1[l],"0%d. %s - %d - %d %lld %d %lld\n",l+1,s,rand,rand1,rand2,rand7,rand8);
            } else {
                sprintf(line1[l],"%d. %s - %d - %d %lld %d %lld\n",l+1,s,rand,rand1,rand2,rand7,rand8);
            }
        } else {
            sscanf(line1[l],"%s %s %s %d %s %lld",rand4,rand3,rand5,&rand,rand6,&rand2);
            strcpy(line1[l],"");
            if(l<9) {
                sprintf(line1[l],"0%d. %s - %d - %lld\n",l+1,s,rand,rand2);
            } else {
                sprintf(line1[l],"%d. %s - %d - %lld\n",l+1,s,rand,rand2);
            }
        }
        strcpy(rand3,"");strcpy(rand4,"");strcpy(rand5,"");strcpy(rand6,"");
    }
    fclose(fp);

    if(call == 17) {
        fp=fopen(regular_participant_list,"w");
    } else if(call == 19) {
        fp=fopen(targetted_participant_list,"w");
    } else if(call == 18) {
		sprintf(path, file, r + 1);
        fp=fopen(path,"w");
    } else {
		sprintf(path, file1, r + 1);
        fp=fopen(path,"w");
    }

    if(call == 17 || call == 19) {
        for(int i=0;i < maxuser;i++) {
            if(line[i][0]>'0' || line[i][0]<='9') {
                fprintf(fp,"%s",line[i]);
            }
        }
    } else {
        for(int i=0;i < maxdua;i++) {
            if(line1[i][0]>'0' || line1[i][0]<='9') {
                fprintf(fp,"%s",line1[i]);
            }
        }
    }

    fclose(fp);
    num = call;
}

void notification() {
    cnt = 0;
    FILE *fp=fopen(targetted_participant_list,"r");
    for(int i=0;i < maxuser;i++) {
        fgets(participant[i],100,fp);
        if(participant[i][0]<'0' || participant[i][0]>'9') {
            continue;
        }
        cnt++;
        strcpy(participant[i],"");
    }
    fclose(fp);

    if(cnt == 0) {
        m=0;
        return;
    } else {
        for(int i=0;i<cnt;i++) {
            char dua3[maxdua][100];
			sprintf(path, file1, i + 1);
            fp=fopen(path,"r");
            size1=0;
            for(int j=0;j < maxdua;j++) {
                fgets(dua[j],100,fp);
                if(dua[j][0]<'0' || dua[j][0]>'9') {
                    continue;
                }
                int rnd,rnd2,rnd3;
                long long rnd1;
                sscanf(dua[j],"%s %s %s %d %s %d %lld %d",random1[j],dua1[j],random2[j],&rnd,random3[j],&rnd2,&rnd1,&rnd3);
                strcpy(random1[j],"");strcpy(random2[j],"");strcpy(random3[j],"");strcpy(dua1[j],"");

                if((rnd1+86400)>scnds) {
                    strcpy(dua3[size1],dua[j]);
                    size1++;
                }
                strcpy(dua[j],"");
            }
            fclose(fp);

            if(size1 != 0) {
                if(m==0) {
                    m=1;
                }
				sprintf(path, file1, i + 1);
                fp=fopen(path,"w");
                for(int k=0;k<size1;k++) {
                    fprintf(fp,"%s",dua3[k]);
                    strcpy(dua3[k],"");
                }
                fclose(fp);
            } else {
                char participant1[maxuser][100];
                fp=fopen(targetted_participant_list,"r");
                size2=0;
                for(int k=0;k < maxuser;k++) {
                    fgets(participant[k],100,fp);
                    if(participant[k][0]<'0' || participant[k][0]>'9') {
                        continue;
                    }
                    if(k!=i) {
                        strcpy(participant1[size2],participant[k]);
                        size2++;
                    }
                }
                fclose(fp);
                fp=fopen(targetted_participant_list,"r");
                for(int k=0;k<size2;k++) {
                    fprintf(fp,"%s",participant1[k]);
                }
                fclose(fp);

                for(int k=i;k<size2;k++) {
                    FILE *fp1;
					sprintf(path, file1, k + 1);
                    fp=fopen(path,"w");
					sprintf(path, file1, k + 2);
                    fp1=fopen(path,"r");

                    char c=fgetc(fp1);
                    while(c) {
                        fputc(c,fp);
                        c=fgetc(fp1);
                    }

                    fclose(fp);
                    fclose(fp1);
                }

				sprintf(path, file1, size2 + 1);
                fp=fopen(path,"w");
                fclose(fp);
            }
        }
        return;
    }
}

void before_save() {
	iSetColor(155, 255, 255);
	iFilledRectangle(128,128, 256, 50);
	iSetColor(0, 0, 0);
	iText(148, 143, text[seq], GLUT_BITMAP_TIMES_ROMAN_24);
	iShowBMP2(5, 475, "pictures/red_back_arrow.bmp", 0);
}

void new_save() {
	iSetColor(155, 255, 255);
	iFilledRectangle(128,128, 256, 50);
	iSetColor(0, 0, 0);
	iText(148, 143, s, GLUT_BITMAP_TIMES_ROMAN_24);
	iShowBMP2(5, 475, "pictures/red_back_arrow.bmp", 0);
}

void save_file() {
	load_bg();
	iSetColor(255, 255, 200);
	iFilledRectangle(100, 148, 295, 220);
	iSetColor(0, 0, 0);
	iRectangle(100, 148, 295, 220);
	iShowBMP2(5, 475, "pictures/red_back_arrow.bmp", 0);
	if (num == 16) {
		iText(130, 324, "Would you like to save", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(177, 294, "before exiting?", GLUT_BITMAP_TIMES_ROMAN_24);
	} else if (num == 14) {
		iText(130, 324, "The file already exists.", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(130, 294, "Would you like to update", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(177, 264, "the said file?", GLUT_BITMAP_TIMES_ROMAN_24);
	} else if (num == 15) {
		iText(130, 324, "The dua already exists.", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(130, 294, "Would you like to update", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(177, 264, "the said dua?", GLUT_BITMAP_TIMES_ROMAN_24);
	} else if (num == 31 || num==32) {
		iText(130, 324, "What would be the type", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(177, 294, "of your target?", GLUT_BITMAP_TIMES_ROMAN_24);
	} else {
		iText(125, 324, "Would you like to save in", GLUT_BITMAP_TIMES_ROMAN_24);
		if (num == 9) {
			iText(170, 294, "an existing Dua?", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (num == 3) {
			iText(170, 294, "an existing file?", GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}

	if (num == 31 || num==32) {
		iSetColor(50, 50, 50);
		iFilledRectangle(140, 204, 90, 35);
		iFilledRectangle(265, 204, 90, 35);
		iSetColor(250, 255, 200);
		iText(160, 214, "Daily", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(273, 214, "Weekly", GLUT_BITMAP_TIMES_ROMAN_24);
	} else {
		iSetColor(50, 50, 50);
		iFilledRectangle(140, 204, 80, 35);
		iFilledRectangle(275, 204, 80, 35);
		iSetColor(250, 255, 200);
		iText(160, 214, "YES", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(298, 214, "NO", GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void scan_file() {
	FILE *fp;
	if (num == 5) {
		fp = fopen(regular_participant_list, "r");
	} else if (num == 11) {
		sprintf(path, file, r + 1);
		fp = fopen(path, "r");
	} else if (num==21) {
		fp = fopen(targetted_participant_list, "r");
	} else {
		sprintf(path, file1, r + 1);
		fp = fopen(path, "r");
	}

	if (num == 5 || num==21) {
		for (int i = 0; i < maxuser; i++) {
			strcpy(name[i], "");
			fscanf(fp, "%s", random3[i]);
			fgets(name[i], 100, fp);
			if (strcmp(name[i], s)==0) {
				r = i;
				g = 1;
			}
		}
	} else {
		for (int i = 0; i < maxdua; i++) {
			if (num == 11) {
				strcpy(dua[i], "");
				fgets(dua[i], 100, fp);
				sscanf(dua[i], "%s %s %s %d %s %lld", random1[i], dua1[i], random2[i], &count_dua[i], random4[i], &tm[i]);
				if (strcmp(dua1[i], s) == 0) {
					l = i;
					g = 1;
				}
			} else {
				strcpy(dua[i], "");
				fgets(dua[i], 100, fp);
				sscanf(dua[i], "%s %s %s %d %s %d %lld %d %lld", random1[i], dua1[i], random2[i], &count_dua[i], random4[i], &count_dua1[i], &tm[i], &done[i], &dur[i]);
				if (strcmp(dua1[i], dua2) == 0) {
					l = i;
					g = 1;
				}
			}
		}
	}
	fclose(fp);
}

void iDraw() {
	iClear();

	if (musicOn && num != 2) {
		iResumeSound(bg_music);
	} else {
		iPauseSound(bg_music);
	}

	if (num == 0) {
		load_bg();
		iShowBMP2(128, 305, "pictures/title.bmp", 0);
		iSetColor(255, 235, 255);
		iFilledRectangle(100, 240, 100, 50);
		iFilledRectangle(100, 140, 100, 50);
		iFilledRectangle(312, 240, 100, 50);
		iFilledRectangle(312, 140, 100, 50);
		iSetColor(90, 12, 200);
		iRectangle(100, 240, 100, 50);
		iRectangle(100, 140, 100, 50);
		iRectangle(312, 240, 100, 50);
		iRectangle(312, 140, 100, 50);
		iSetColor(255, 255, 255);
		time_t q = time(NULL);
		scnds=q;
		struct tm* curr_time;
		curr_time = localtime(&q);
		strftime(ti, 30, "%X  %x", curr_time);
		iText(155, 400, ti, GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(0, 0, 0);
		iText(117, 257, "Count", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(113, 157, "History", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(320, 257, "Themes", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(328, 157, "Target", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP2(468, 471, musicOn ? "pictures/sound_on.bmp" : "pictures/sound_off.bmp", 0xffffff);

		//notification();

		if (m == 1) {
			iShowBMP2(385, 96, "pictures/down_arrow.bmp", 0);
			iSetColor(255, 255, 200);
			iFilledRectangle(215, 15, 180, 115);
			iSetColor(98, 45, 67);
			iRectangle(215, 15, 180, 115);
			iText(250, 100, "There is an", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(225, 70, "unfinished goal!", GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(255, 255, 255);
			iFilledRectangle(320, 25, 50, 20);
			iSetColor(90, 12, 200);
			iRectangle(320, 25, 50, 20);
			iText(331, 32, "VISIT", GLUT_BITMAP_TIMES_ROMAN_10);
		}
	}

	if (num == 2) {
		load_bg();
		iShowBMP2(5, 475, "pictures/red_back_arrow.bmp", 0);
		iShowBMP2(468, 471, musicOn2 ? "pictures/sound_on.bmp" : "pictures/sound_off.bmp", 0xffffff);

		tasbeeh_pic_index = count % 12;
		sprintf(path, tasbeeh_pic, tasbeeh_pic_index + 1);
		iShowBMP2(140, 190, path, 0);

		iSetColor(255, 255, 255);
		iFilledRectangle(60, 80, 100, 50);
		iFilledRectangle(231, 80, 50, 50);
		iFilledRectangle(352, 80, 100, 50);
		iSetColor(9, 121, 105);
		iRectangle(60, 80, 100, 50);
		iRectangle(231, 80, 50, 50);
		iRectangle(352, 80, 100, 50);
		iSetColor(0, 0, 0);
		iText(85, 98, "Save", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(243, 98, "-1", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(372, 98, "Reset", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(0, 0, 0);
		time_t q;
		q = time(NULL);
		struct tm* curr_time;
		curr_time = localtime(&q);
		if (call == 18) {
			tmr = tm[l] + q - seconds;
		} else {
			tmr = q - seconds;
		}
		curr_time->tm_hour = tmr / 3600;
		curr_time->tm_min = (tmr % 3600) / 60;
		curr_time->tm_sec = (tmr % 3600) % 60;
		strftime(ti, 20, "%H:%M:%S",curr_time);
		iText(200, 480, ti, GLUT_BITMAP_TIMES_ROMAN_24);
		convert_int_to_str(count, count_store);
		if (b == 1) {
			iText(180, 400, dua1[l], GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iText(230, 280, count_store, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (num == 3) {
		save_file();
	}

	if (num == 4) {
		seq = 0;
		before_save();
	}

	if (num == 5) {
		new_save();
	}

	if (num == 6) {
		seq = 1;
		before_save();
	}

	if (num == 7) {
		new_save();
	}

	if (num == 8) {
		load_bg();
		call = 8;
		print_name_index();
		draw_scrollbar(&length, cnt, 50, &y, &gap);
	}

	if (num == 9) {
		save_file();
	}

	if (num == 10) {
		seq = 1;
		before_save();
	}

	if (num == 11) {
		new_save();
	}

	if (num == 12) {
		load_bg();
		call = 12;
		print_dua_index();
		draw_scrollbar(&length1, cnt1, 30, &y_1, &gap1);
	}

	if (num == 13) {
		if (call == 2) {
			iSetColor(98, 45, 67);
			iFilledRectangle(100, 249, 312, 40);
			iSetColor(198, 245, 167);
			iRectangle(100, 249, 312, 40);
			iSetColor(0, 0, 0);
			iText(107, 256, "You have reached your goal!!!", GLUT_BITMAP_TIMES_ROMAN_24);
		} else {
			iSetColor(98, 45, 67);
			iFilledRectangle(128, 249, 256, 40);
			iSetColor(198, 245, 167);
			iRectangle(128, 249, 256, 40);
			iSetColor(0, 0, 0);
			iText(135, 256, comment[f], GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iSetColor(255, 255, 255);
		iText(134, 220, "Click Enter to go back.", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (num == 14) {
		save_file();
	}

	if (num == 15) {
		save_file();
	}

	if (num == 16) {
		save_file();
	}

	if (num == 17) {
		load_bg();
		call = 17;
		print_name_index();
		draw_scrollbar(&length, cnt, 50, &y, &gap);
	}

	if (num == 18) {
		load_bg();
		call = 18;
		print_dua_index();
		draw_scrollbar(&length1, cnt1, 30, &y_1, &gap1);
	}

	if (num == 19) {
		load_bg();
		iShowBMP2(purple_plus_x(length), 470, "pictures/purple_plus.bmp", 0);
		call = 19;
		print_name_index();
		draw_scrollbar(&length, cnt, 50, &y, &gap);
	}

	if (num == 20) {
		seq = 0;
		before_save();
	}

	if (num == 21) {
		new_save();
	}

	if (num == 22) {
		seq = 1;
		before_save();
	}

	if (num == 23) {
		new_save();
	}

	if (num == 24) {
		seq = 2;
		before_save();
	}

	if (num == 25) {
		new_save();
	}

	if (num == 26) {
		load_bg();
		iShowBMP2(purple_plus_x(length1), 470, "pictures/purple_plus.bmp", 0);
		print_dua_index();
		draw_scrollbar(&length1, cnt1, 30, &y_1, &gap1);
	}

	if (num == 27) {
		seq = 1;
		before_save();
	}

	if (num == 28) {
		new_save();
	}

	if (num == 29) {
		seq = 2;
		before_save();
	}

	if (num == 30) {
		new_save();
	}

	if (num == 31) {
		save_file();
	}

	if (num == 32) {
		save_file();
	}

	if (num == 33) {
		load_bg();
		iShowBMP2(5, 475, "pictures/red_back_arrow.bmp", 0);
		iSetColor(0, 0, 0);
		iText(45, 380, "Themes:", GLUT_BITMAP_TIMES_ROMAN_24);
		int vert = 280;
		for (int i = 0; i < 3; i++) {
			iSetColor(255, 255, 200);
			iFilledRectangle(45, vert, 422, 40);
			iSetColor(0, 0, 43);
			iRectangle(45, vert, 422, 40);
			iText(55, vert + 14, theme[i], GLUT_BITMAP_TIMES_ROMAN_24);
			vert = vert - 50;
		}
	}
}

/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/

void iMouseMove(int mx, int my) {
    if((num == 17 || num == 8 || num == 19) && length<512 && mx>=500) {
        if((512-my)<length) {
            y= 512;
        } else if(my<0) {
            y = length;
        } else {
            y = my + length;
        }
    }

    if((num == 12 || num == 18 || num == 26) && length1<512 && mx>=500) {
        if((512-my)<length1) {
            y_1 = 512;
        } else if(my<0) {
            y_1 = length1;
        } else {
            y_1 = my + length1;
        }
    }
}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my) {

}

void iMouse(int button, int state, int mx, int my) {

	if (num == 0) {
		if (mx >= 471 && mx <= 507 && my >= 471 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			musicOn = !musicOn;
		} else if (mx >= 100 && mx <= 200 && my >= 240 && my <= 290 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			seconds = time(NULL);
			num = 2;
		} else if (mx >= 100 && mx <= 200 && my >= 140 && my <= 190 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		    y=512;
			num = 17;
		} else if (mx >= 312 && mx <= 412 && my >= 240 && my <= 290 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 33;
		} else if (mx >= 312 && mx <= 412 && my >= 140 && my <= 190 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		    y=512;
			num = 19;
			if (m == 1) {
				m = 2;
			}
		} else if (m == 1 && mx >= 320 && mx <= 370 && my >= 25 && my <= 45 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 19;
			m = 2;
		} else;
	} else if (num == 2) {
		if (mx >= 471 && mx <= 507 && my >= 471 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			musicOn2 = !musicOn2;
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 16;
		} else if (mx >= 60 && mx <= 160 && my >= 80 && my <= 130 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (b == 1) {
				b = 0;
				if (call == 18) {
					count_dua[l] = count;
					tm[l] = tmr;
					call = 0;
					replace_file();
				} else {
				    time_t scnd;
				    scnd = time(NULL);
					count_dua1[l] = count;
					if (count_dua1[l] >= count_dua[l] && tm[l] > scnd) {
						call = 2;
						done[l] = 1;
						if (musicOn2) {
							iPlaySound(goal_sound);
						}
					} else {
                        done[l] = 0;
                    }
					replace_file();
					num = 13;
				}
			} else {
				call = 2;
				num = 3;
			}
		} else if (mx >= 231 && mx <= 281 && my >= 80 && my <= 130 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (count > 0) {
				count--;
			}
		} else if (mx >= 352 && mx <= 452 && my >= 80 && my <= 130 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			count = 0;
		} else;
	} else if (num == 3) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 2;
		} else if (mx >= 140 && mx <= 220 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 8;
		} else if (mx >= 275 && mx <= 355 && my >=204  && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 4;
		} else;
	} else if (num == 4) {
		if (mx >= 128 && mx <= 128 + 256 && my >= 128 && my <= 128 + 50 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s[0] = '\0';
			s_index = 0;
			num = 5;
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(call == 17 || call == 19 ) {
                num = call;
            } else {
                num = 3;
            }
		} else;
	} else if (num == 5) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 4;
		}
	} else if (num == 6) {
		if (mx >= 128 && mx <= 128 + 256 && my >= 128 && my <= 178 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s[0] = '\0';
			s_index = 0;
			num = 7;
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		    if(call==18 || call==26) {
                num=call;
            } else {
                num = 4;
            }
		} else;
	} else if (num == 7) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 6;
		}
	} else if (num == 8 && !is_empty) {
		for (int i = 0; i < maxuser; i++) {
			if (mx >= 45 && mx <= 45 + content_bar_width(length) && my >= 345 - (i * 50) && my <= 370 - (i * 50) && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && participant[i][0] >= '0' && participant[i][0] <= '9') {
				r = i;
				num = 9;
				break;
			}
		}
		
		if (mx >= 5 && mx <= 467 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 3;
		}
	} else if (num == 9) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 8;
		} else if (mx >= 140 && mx <= 220 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			y_1 = 512;
			num = 12;
		} else if (mx >= 275 && mx <= 355 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 10;
		} else;
	} else if (num == 10) {
		if (mx >= 128 && mx <= 128 + 256 && my >= 128 && my <= 178 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s[0] = '\0';
			s_index = 0;
			num = 11;
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 9;
		} else;
	} else if (num == 11) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 10;
		}
	} else if (num == 12) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 9;
		} 

		for (int i = 0; i < maxdua; i++) {
			if (mx >= 45 && mx <= 45 + content_bar_width(length1) && my >= 365 - (i * 30) + gap1 && my <= 390 - (i * 30) + gap1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && random1[i][0] >= '0' && random1[i][0] <= '9') {
				count_dua[i] += count;
				tm[i] = tmr;
				l = i;
				replace_file();
				break;
			}
		}
	} else if (num == 14) {
		if (mx >= 275 && mx <= 355 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 0;
			count = 0;
		} else if (mx >= 140 && mx <= 220 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (b == 1) {
				b = 0;
				count_dua[l] = count;
				tm[l] = tmr;
				replace_file();
			} else {
				call = 2;
				num = 3;
			}
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 2;
		}
	} else if (num == 15) {
		if (mx >= 275 && mx <= 355 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 0;
			count = 0;
		} else if (mx >= 140 && mx <= 220 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (call == 11) {
				count_dua[l]+=count;
				tm[l] += tmr;
				replace_file();
			}
			if (call == 30) {
				count_dua[l] = count;
				if (tog == 1) {
					tm[l] = seconds+plus1;
					dur[l] = plus1;
				}
				if (tog == 2) {
					tm[l] = seconds + plus2;
					dur[l] = plus2;
				}
				replace_file();
			}
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (call == 11) {
				num = 11;
			} else {
				num = 30;
			}
		}
	} else if (num == 16) {
		if (mx >= 275 && mx <= 355 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 0;
			count = 0;
		} else if (mx >= 140 && mx <= 220 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		    if (b == 1) {
				b = 0;
				if (call == 18) {
					count_dua[l] = count;
					tm[l] = tmr;
					call = 0;
					replace_file();
				} else {
				    time_t scnd;
				    scnd=time(NULL);
					count_dua1[l] = count;
					if (count_dua1[l] >= count_dua[l] && tm[l]>scnd) {
						call = 2;
						done[l]=1;
						if (musicOn2) {
							iPlaySound(goal_sound);
						}
					} else {
                        done[l] = 0;
                    }
					replace_file();
					num = 13;
				}
			} else {
				call = 2;
				num = 3;
			}
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 2;
		}
	} else if (num == 17) {
		if (!is_empty) {
			for (int i = 0; i < maxuser; i++) {
				if (!is_dialog_open && !is_deleting && mx >= 45 && mx <= 45 + content_bar_width(length) && my >= (345 - (i * 50) + gap) && my <= (370 - (i * 50) + gap) && participant[i][0] >= '0' && participant[i][0] <= '9') {
					r = i;
					if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
						y_1 = 512;
						num = 18;
					}
					if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
						if ((250 - (i * 50) + gap) >= 0) {
							hang = 250 - (i * 50) + gap;
							dialog_num = 0;
						} else {
							hang = 369 - (i * 50) + gap;
							dialog_num = 1;
						}
						is_dialog_open = true;
					}
					break;
				}
			}

			if (is_dialog_open && mx >= 248 && mx <= 312 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				if((my >= hang + 18 && my <= hang + 32 && dialog_num == 0) || (my >= hang + 32 && my <= hang + 46 && dialog_num == 1)) {
					is_deleting = true;
					is_dialog_open = false;
				}
				if((my >= hang + 48 && my <= hang + 62 && dialog_num == 0) || (my >= hang + 62 && my <= hang + 76 && dialog_num == 1)) {
					call = 17;
					num = 4;
					is_dialog_open = false;
				}
			} else if (is_deleting && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				if (mx >= 140 && mx <= 220) {
					is_deleting = false;
					call = 17;
					delete_file();
				} else if (mx >= 275 && mx <= 355) {
					is_deleting = false;
				} else;
			} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				if (is_dialog_open) {
					is_dialog_open = false;
				} else if (is_deleting) {
					is_deleting = false;
				} else {
					num = 0;
				}
			} else;
		} else {
			if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				num = 0;
			}
		}	
	} else if (num == 18) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (is_dialog_open) {
				is_dialog_open = false;
			} else if (is_deleting) {
				is_deleting = false;
			} else {
				num = 17;
			}
		}

		for (int i = 0; i < maxdua; i++) {
			if (!is_dialog_open && !is_deleting && mx >= 45 && mx <= 45 + content_bar_width(length1) && my >= 365 - (i * 30) + gap1 && my <= 390 - (i * 30) + gap1 && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && dua[i][0] >= '0' && dua[i][0] <= '9') {
				l = i;
				// the box hangs below the row, or sits above it when there is no room below
				if ((237 - (i * 30) + gap1) >= 0) {
					hang = 237 - (i * 30) + gap1;
					dialog_num = 0;
				} else {
					hang = 387 - (i * 30) + gap1;
					dialog_num = 1;
				}
				is_dialog_open = true;
				break;
			}
		}

		if (is_dialog_open && mx >= 248 && mx <= 390 && my >= hang + dua_slot[dialog_num][0] && my <= hang + dua_slot[dialog_num][0] + 14 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			count = count_dua[l];
			seconds = time(NULL);
			b = 1;
			w = 1;
			call = 18;
			num = 2;
			is_dialog_open = false;
		} else if (is_dialog_open && mx >= 248 && mx <= 328 && my >= hang + dua_slot[dialog_num][1] && my <= hang + dua_slot[dialog_num][1] + 14 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			is_dialog_open = false;
			call = num;
			num = 6;
		} else if (is_dialog_open && mx >= 248 && mx <= 312 && my >= hang + dua_slot[dialog_num][2] && my <= hang + dua_slot[dialog_num][2] + 14 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			is_deleting = true;
			is_dialog_open = false;
		} else if (is_deleting && mx >= 140 && mx <= 220 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			call = 18;
			delete_data();
		} else if (mx >= 275 && mx <= 355 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			is_deleting = false;
		} else;
	} else if (num == 19) {
		if (!is_dialog_open && !is_deleting && mx >= purple_plus_x(length) && mx <= purple_plus_x(length) + 32 && my >= 470 && my <= 502 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 20;
		} 
		
		if (!is_empty) {
			for (int i = 0; i < maxuser; i++) {
				if (!is_dialog_open && !is_deleting && mx >= 45 && mx <= 45 + content_bar_width(length) && my >= (345 - (i * 50) + gap) && my <= (370 - (i * 50) + gap) && participant[i][0] >= '0' && participant[i][0] <= '9') {
					r = i;
					if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
						y_1 = 512;
						num = 26;
					}
					if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
						if ((250 - (i * 50) + gap) >= 0) {
							hang = 250 - (i * 50) + gap;
							dialog_num = 0;
						} else {
							hang = 369 - (i * 50) + gap;
							dialog_num = 1;
						}
						is_dialog_open = true;
					}
					break;
				}
			}

			if (is_dialog_open && mx >= 248 && mx <= 312 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				if((my >= hang + 18 && my <= hang + 32 && dialog_num == 0) || (my >= hang + 32 && my <= hang + 46 && dialog_num == 1)) {
					is_deleting = true;
					is_dialog_open = false;
				}
				if((my >= hang + 48 && my <= hang + 62 && dialog_num == 0) || (my >= hang + 62 && my <= hang + 76 && dialog_num == 1)) {
					call = 19;
					num = 4;
					is_dialog_open = false;
				}
			} else if (is_deleting && mx >= 140 && mx <= 220 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				is_deleting = false;
				call = num;
				delete_file();
			} else if (is_deleting && mx >= 275 && mx <= 355 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				is_deleting = false;
			} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				if (is_dialog_open) {
					is_dialog_open = false;
				} else if (is_deleting) {
					is_deleting = false;
				} else {
					num = 0;
				}
			} else;
		} else {
			if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				num = 0;
			}
		}
	} else if (num == 20) {
		if (mx >= 128 && mx <= 128 + 256 && my >= 128 && my <= 178 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s[0] = '\0';
			s_index = 0;
			num = 21;
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 19;
		} else;
	} else if (num == 21) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 20;
		}
	} else if (num == 22) {
		if (mx >= 128 && mx <= 128 + 256 && my >= 128 && my <= 178 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s[0] = '\0';
			s_index = 0;
			num = 23;
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 31;
		} else;
	} else if (num == 23) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 22;
		}
	} else if (num == 24) {
		if (mx >= 128 && mx <= 128 + 256 && my >= 128 && my <= 178 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s[0] = '\0';
			s_index = 0;
			num = 25;
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 23;
		} else;
	} else if (num == 25) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 24;
		}
	} else if (num == 26) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (is_dialog_open) {
				is_dialog_open = false;
			} else if (is_deleting) {
				is_deleting = false;
			} else {
				num = 19;
			}
		}

		for (int i = 0; i < maxdua; i++) {
			if (!is_dialog_open && !is_deleting && mx >= 45 && mx <= 45 + content_bar_width(length1) && my >= 365 - (i * 30) + gap1 && my <= 390 - (i * 30) + gap1 && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && dua[i][0] >= '0' && dua[i][0] <= '9') {
				l = i;
				if (done[i] == 1) {
					if ((270 - (i * 30) + gap1) >= 0) {
						hang = 270 - (i * 30) + gap1;
						dialog_num = 0;
					} else {
						hang = 389 - (i * 30) + gap1;
						dialog_num = 1;
					}
				} else {
					if ((237 - (i * 30) + gap1) >= 0) {
						hang = 237 - (i * 30) + gap1;
						dialog_num = 0;
					} else {
						hang = 387 - (i * 30) + gap1;
						dialog_num = 1;
					}
				}
				is_dialog_open = true;
				break;
			}
		}
		
		if (is_dialog_open && done[l] == 1 && mx >= 248 && mx <= 328 && my >= hang + two_option_slot[dialog_num][0] && my <= hang + two_option_slot[dialog_num][0] + 14 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			is_dialog_open = false;
			call = num;
			num = 6;
		} else if (is_dialog_open && done[l] == 1 && mx >= 248 && mx <= 312 && my >= hang + two_option_slot[dialog_num][1] && my <= hang + two_option_slot[dialog_num][1] + 14 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			is_deleting = true;
			is_dialog_open = false;
		} else if (is_dialog_open && mx >= 248 && mx <= 390 && my >= hang + dua_slot[dialog_num][0] && my <= hang + dua_slot[dialog_num][0] + 14 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && done[l] == 0 && tm[l] <= time(NULL)) {
			count_dua1[l] = 0;
			seconds = time(NULL);
			tm[l] = seconds + dur[l];
			call = 26;
			is_dialog_open = false;
			replace_file();
		} else if (is_dialog_open && done[l] == 0 && mx >= 248 && mx <= 390 && my >= hang + dua_slot[dialog_num][0] && my <= hang + dua_slot[dialog_num][0] + 14 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			count = count_dua1[l];
			seconds = time(NULL);
			b = 1;
			w = 1;
			call = 26;
			num = 2;
			is_dialog_open = false;
		} else if (is_dialog_open && done[l] == 0 && mx >= 248 && mx <= 328 && my >= hang + dua_slot[dialog_num][1] && my <= hang + dua_slot[dialog_num][1] + 14 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			is_dialog_open = false;
			call = num;
			num = 6;
		} else if (is_dialog_open && done[l] == 0 && mx >= 248 && mx <= 312 && my >= hang + dua_slot[dialog_num][2] && my <= hang + dua_slot[dialog_num][2] + 14 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			is_deleting = true;
			is_dialog_open = false;
		} else if (is_deleting && mx >= 140 && mx <= 220 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			delete_data();
		} else if (is_deleting && mx >= 275 && mx <= 355 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			is_deleting = false;
		} else if (!is_dialog_open && !is_deleting && mx >= purple_plus_x(length1) && mx <= purple_plus_x(length1) + 32 && my >= 470 && my <= 502 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 32;
		}
	} else if (num == 27) {
		if (mx >= 128 && mx <= 128 + 256 && my >= 128 && my <= 178 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s[0] = '\0';
			s_index = 0;
			num = 28;
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 32;
		} else;
	} else if (num == 28) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 27;
		}
	} else if (num == 29) {
		if (mx >= 128 && mx <= 128 + 256 && my >= 128 && my <= 178 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s[0] = '\0';
			s_index = 0;
			num = 30;
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 28;
		} else;
	} else if (num == 30) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 29;
		}
	} else if (num == 31) {
		if (mx >= 140 && mx <= 230 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			tog = 1;
			num = 22;
		} else if (mx >= 265 && mx <= 355 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			tog = 2;
			num = 22;
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 21;
		}
	} else if (num == 32) {
		if (mx >= 140 && mx <= 230 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			tog = 1;
			num = 27;
		} else if (mx >= 265 && mx <= 355 && my >= 204 && my <= 239 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			tog = 2;
			num = 27;
		} else if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			y_1 = 512;
			num = 26;
		}
	} else if (num == 33) {
		if (mx >= 5 && mx <= 37 && my >= 475 && my <= 507 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			num = 0;
		} else if (mx >= 45 && mx <= 467 && my >= 280 && my <= 320 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			bg_index = 0;
		} else if (mx >= 45 && mx <= 467 && my >= 230 && my <= 270 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			bg_index = 1;
		} else if (mx >= 45 && mx <= 467 && my >= 180 && my <= 220 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			bg_index = 2;
		}
	} else;
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key) {
	if (key == '\b') {
		s_index--;
		s[s_index] = '\0';
	} else {
		if (key == ' ' && num==2) {
			count++;
			if (musicOn2) {
				iPlaySound(count_sound);
			}
		} else if (key == '\r') {
			if (num == 5) {
				if(call == 17 || call == 19) {
                    rename();
                } else {
                    s[s_index] = '\n';
                    s_index++;
                    s[s_index] = '\0';
                    scan_file();
                    if (g == 0) {
                        strcpy(nme, "");
                        strcpy(nme, s);
                        num = 6;
                    } else {
                        call = 5;
                        num = 14;
                        g = 0;
                    }
                }
			}
			if (num == 7) {
			    if(call == 18 || call == 26) {
                    rename();
                } else {
                    append_file();
                    create_file();
                    f = 0;
                }
			}
			if (num == 8 && is_empty) {
				num = 4;
			}
			if (num == 11) {
				scan_file();
				if (g == 0) {
					l = 0;
					take_input();
					shift_data();
					replace_file();
				} else {
					call = 11;
					num = 15;
					g = 0;
				}
			}
			if (num == 12 && is_empty) {
				num = 10;
			}
			if (num == 13) {
				if (f == 0) {
					num = 0;
				} else {
					if (call == 17) {
						num = 17;
					} else {
						num = 19;
					}
				}
			}
			if (num == 14 && is_empty) {
				num = 0;
			}
			if (num == 17 && is_empty) {
				num = 0;
			}
			if (num == 19 && is_empty) {
				num = 0;
			}
			if (num == 21) {
				s[s_index] = '\n';
				s_index++;
				s[s_index] = '\0';
				scan_file();
				if (g == 0) {
					strcpy(nme, "");
					strcpy(nme, s);
					num = 31;
				} else {
					call = 21;
					num = 14;
					g = 0;
				}
			}
			if (num == 23) {
				strcpy(dua2, s);
				num = 24;
			}
			if (num == 25) {
				seconds = time(NULL);
				append_file();
				create_file();
				f = 0;
			}
			if (num == 28) {
				strcpy(dua2, s);
				num = 29;
			}
			if (num == 30) {
				seconds = time(NULL);
				convert_char(&count, s);
				scan_file();
				if (g == 0) {
					l = 0;
					take_input();
					shift_data();
					replace_file();
					f = 0;
				} else {
					call = 30;
					num = 15;
					g = 0;
				}
			}
		} else if (key<1) {
			s_index = 0;
		} else {
			s[s_index] = key;
			s_index++;
			s[s_index] = '\0';
		}
	}
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key) {
	if (key == GLUT_KEY_RIGHT) {}

	if (key == GLUT_KEY_LEFT) {}

	if (key == GLUT_KEY_HOME) {}
}


int main() {
	bg_music = iLoadSound("music/Famous__bg_sound.wav", true);
	count_sound = iLoadSound("music/Water_Drop_Sound_Effect.wav");
	goal_sound = iLoadSound("music/correct answer.wav");
	iInitialize(512, 512, "Tasbeeh Count");
	return 0;
}
