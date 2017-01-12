#include <stdio.h>
#include <string.h>
#include "xxtea-c/xxtea.c"

const char *key = "";//自己找去
//const int argc = 3;
//const char *argv[] = {"1.c.exe","D:\\working\\res\\aniplex.png","D:\\working\\dres\\aniplex.png"};
size_t getFileSize(FILE *fn){
	size_t ret=-1;
	if(fn!=NULL){
		fseek(fn,0,SEEK_END);
		ret = ftell(fn);
	}
	return ret;
}
int main(int argc, const char* argv[]) {
//int main() {
	FILE *fsrc, *fout;
	//const char encrypt_data[] = {0x59,0xFF,0x1F,0x3A,0xCD,0xB9,0xBC,0x3F,0xC6,0x39,0x54,0x74,0xC4,0x18,0xD3,0xDD,0x6B,0x9A,0x03,0xA6,0};
	char *encrypt_data,comm[4];
	size_t len;
	char *decrypt_data;

	if(argc<2){
		printf("No Input File");
		return 1;
	}
	fsrc = fopen(argv[1],"rb");
	if(!fsrc){
		printf("File Can't Read!");
		return 2;
	}
	len = getFileSize(fsrc) - 6;
	fseek(fsrc,6,SEEK_SET);
	encrypt_data = (uint8_t *)malloc(len + 1);
	len = fread(encrypt_data,sizeof(unsigned char),len,fsrc);
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
*/			fout = fopen(argv[1],"w");
			fwrite(decrypt_data,sizeof(unsigned char),len,fout);
			fclose(fout);
/*		}else{
			printf("%s",decrypt_data);
		}
*/	}else{
		fout = fopen(argv[2],"wb");
		fwrite(decrypt_data,sizeof(unsigned char),len,fout);
		fclose(fout);
	}

	free(encrypt_data);
	free(decrypt_data);
	return 0;
}