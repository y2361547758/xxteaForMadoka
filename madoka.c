#include <stdio.h>
#include <string.h>
#include "xxtea-c/xxtea.c"
#include "madoka.h"
//const int argc = 2;
//const char *argv[] = {"1.c.exe","D:\\working\\res\\bilibili.png","D:\\working\\dres\\bilibili.png"};
size_t getFileSize(FILE *fn){
	size_t ret=-1;
	if(fn!=NULL){
		fseek(fn,0,SEEK_END);
		ret = ftell(fn);
	}
	return ret;
}
int fileerr(FILE* fn){
	extern int errno;
	if(!fn){
		switch(errno){
			case 13: printf("Permission Deny!");break;
			case 2: printf("File Not Found!");break;
		}
		return errno;
	}
	return 0;
}
int write(const char* fn, const char* decrypt_data, int len){
	extern int errno;
	FILE* fout;
	fout = fopen(fn,"wb");
	if(fileerr(fout))return errno;
	fwrite(decrypt_data,sizeof(char),len,fout);
	fclose(fout);
	return 0;
}
int main(int argc, const char* argv[]) {
//int main() {
	FILE *fsrc, *fout;
	extern int errno;
	char *encrypt_data,comm[4],ID[7];
	size_t len;
	char *decrypt_data;

	if(argc<2){
		printf("No Input File");
		return 1;
	}
	fsrc = fopen(argv[1],"rb");
	if(fileerr(fsrc))return errno;

	len = getFileSize(fsrc) - 6;
	rewind(fsrc);
	fscanf(fsrc,"%6s",ID);
	if(strcmp(ID,ident){
		printf("NOT Require File!");
		return 2;
	}
	encrypt_data = (uint8_t *)malloc(len + 1);
	len = fread(encrypt_data,sizeof(char),len,fsrc);
	encrypt_data[len] = 0;
	fclose(fsrc);

	decrypt_data = xxtea_decrypt(encrypt_data, len, key, &len);
	if(!len || !decrypt_data){
		printf("ERROR!");
		return 3;
	}

	if(argc == 2 || stricmp(argv[1],argv[2]) == 0){
/*		printf("Rewrite the sorce file. Yes or No ?\n");
		gets(comm);
		if(comm[0]=='Y' || comm[0]=='y'){
*/			write(argv[1],decrypt_data,len);
/*		}else{
			printf("%s",decrypt_data);
		}
*/	}else write(argv[2],decrypt_data,len);

	free(encrypt_data);
	free(decrypt_data);
	return 0;
}