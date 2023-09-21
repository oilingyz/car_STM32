#ifndef  _UART_PARSE_H
#define  _UART_PARSE_H

void printarray(float* array,int n);
void printfloat(float data);
void printstr(char* str);

char* sbz_format(float *data,int size);
void sbz_parse_new(char *data, float *output);

void VL53L0_parse(char *data, float *output);
void arraycopy(float a[],float b[],int len);
int sbz_parse(char *data, float *output,int STA,int len);
extern char datatrans[50];

void SYN6288_SPEAK(char *a);
extern int syn6288_flag;
void SYN6288_Report(void);

extern int Print_Flag;
#endif
